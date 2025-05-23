const { Writable } = require("node:stream");
const { Buffer } = require("buffer");
const fs = require("node:fs");

class FileWriteStream extends Writable {
  constructor({ highWaterMark, fileName }) {
    super({ highWaterMark });
    this.fileName = fileName;
    this.fd = null; // file descriptor
    this.chunks = []; // this is not the internal buffer.
    this.chunkSize = 0;
    this.totalWrites = 0;
    // Save highWaterMark explicitly
    this.highWaterMark = highWaterMark;
  }

  _construct(callback) {
    fs.open(this.fileName, "w", (err, fd) => {
      if (err) return callback(err);
      this.fd = fd;
      console.time("big");
      callback();
    });
  }

  _write(chunk, encoding, callback) {
    // _write runs asynchronusly afeter stream.write and not immediately

    if (!this.fd) return callback(new Error("File descriptor not ready yet."));

    this.chunks.push(chunk);
    this.chunkSize += chunk.length;

    console.log("2");
    console.log(this.chunkSize);

    // Only flush if we exceed highWaterMark
    if (this.chunkSize > this.highWaterMark) {
      fs.write(this.fd, Buffer.concat(this.chunks), (err) => {
        if (err) return callback(err);

        console.log("Writing to file done.");
        this.chunks = [];
        this.chunkSize = 0;
        ++this.totalWrites;
        callback(); // signal this write is complete and may emit 'drain'
      });
    } else {
      console.log("3");
      callback();
    }
  }

  _final(callback) {
    // Write any remaining chunks
    if (this.chunks.length === 0) {
      return callback();
    }

    fs.write(this.fd, Buffer.concat(this.chunks), (err) => {
      if (err) return callback(err);

      console.log("This is final write");

      ++this.totalWrites;
      this.chunks = [];
      this.chunkSize = 0;
      callback(); // finish event is called
    });
  }

  _destroy(error, callback) {
    fs.close(this.fd, (closeErr) => {
      console.log("Number of writes:", this.totalWrites);
      callback(closeErr || error);
      console.timeEnd("big");
    });
  }
}

// ===============
// Usage
// ===============

const stream = new FileWriteStream({
  highWaterMark: 16,

  fileName: "bigFile.md",
});

let i = 0;

function writeMany() {
  if (i >= 100) {
    stream.end();
    console.log("All writes scheduled.");
    return;
  }

  const chunk = Buffer.from("x".repeat(15)); // 15 bytes per chunk
  i++;

  console.log("1");
  // the chunk is added to the internal buffer, if it is full false is returned signalling backpressure
  const ok = stream.write(chunk);
  // console.log(`Write #${i} → returned: ${ok ? "true" : "false"}`);

  console.log("4");

  if (ok) {
    console.log("5");
    writeMany(); // continue writing
  } else {
    console.log("6");
    stream.once("drain", () => {
      console.log("Drain event received, resuming...");
      writeMany();
    });
  }
}

writeMany();

// when stream.end, _final called then 'finish' event is triggered and then the _destroy method is triggered
stream.on("finish", () => {
  console.log("✅ All data has been flushed to the file.");
});

// there is a bug here as drain is issued only once, its likely due to fast synchronous execution of the while loop or _write running asynchronously after .write

/* When _write calls its callback

The processed chunk is removed from the internal buffer. That is the chunk is considered to be processed and the internal buffer empty

If the internal buffer was full (backpressure), a 'drain' event is may be emitted, allowing more writes.

*/
