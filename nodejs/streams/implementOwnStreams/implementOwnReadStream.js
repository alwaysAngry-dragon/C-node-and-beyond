const { Readable } = require("node:stream");
const { Buffer } = require("buffer");
const fs = require("node:fs");

class MyReadableStream extends Readable {
  constructor(options) {
    super(options);
    this.current = 1;
    this.max = 5;
  }

  /*

    Each time this.push(data) is called:
    The "data" event fires.
    When this.push(null) is called:
    The "end" event fires.

  */

  _read(size) {
    if (this.current > this.max) {
      this.push(null); // signal end of stream, or EOF
      return;
    }

    // Simulate async reading
    setTimeout(() => {
      console.log(`Pushing chunk #${this.current}`);
      this.push(String(this.current)); // push as string (buffers preferred), the data is pushed to the internal buffer
      this.current++;
    }, 1000);
  }

  _destroy(err, callback) {
    if (err) {
      callback(err);
    } else {
      console.log("Stream finished");
      callback();
      // do the cleanup
    }
  }
}

const myStream = new MyReadableStream();

// .on("data") registered → stream starts flowing (that means the stream is started)

// myStream.on("data", (chunk) => {
//   console.log("Received:", chunk.toString());
// });

// implementing paused mode, when the readable event is attached the _read is fired
myStream.on("readable", () => {
  let chunk;
  while ((chunk = myStream.read()) !== null) {
    // .read will reads from the internal buffer
    console.log("Read chunk:", chunk.toString());
  }

  console.log("Reading a chunk done");
});

myStream.on("end", () => {
  console.log("Stream ended.");
});
