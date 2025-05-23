const { Buffer } = require("buffer");

const fs = require("fs/promises");

/*
// CREATE A BIG FILE

// High water Mark:  16384
// Total writes:  5426
// Execution Time: 35.593s

(async () => {
  const fileHandle = await fs.open("bigFile.txt", "w");

  const stat = await fileHandle.stat();
  const writeStream = fileHandle.createWriteStream();
  let drains = 0;

  writeStream.on("drain", () => {
    // console.log("Drained");
    // console.log(writeStream.writableLength);
    drains++;
    wirteToFile();
  });

  writeStream.on("finish", async () => {
    console.log("Total writes: ", drains);
    console.timeEnd("big");
    await fileHandle.close(); // Ensure file is closed after logging
  });

  console.log("High water Mark: ", writeStream.writableHighWaterMark);

  let i = 0;
  const wirteToFile = () => {
    while (i < 1e5) {
      const canWrite = writeStream.write(Buffer.from(` ${i} `));
      i++;
      if (!canWrite) {
        return;
      }
      if (i == 1e5) {
        writeStream.end();
      }
    }
  };

  wirteToFile();
})();

*/

// use the read stream to read the big file and write it to another file

// Execution Time : 410ms

console.time("Execution-Time");

let caryOver = false;

function sanitizeChunk(chunk) {
  let newChunk = [];

  let data = chunk.toString("utf-8").split("  ");

  data.forEach((item, index) => {
    item = item.trim();
    if (item.length > 0) {
      newChunk.push(item);
    }
  });

  if (caryOver) {
    newChunk[0] = `${newChunk[1] * 1 - 1}`;
  }

  if (
    newChunk[newChunk.length - 1] * 1 !==
    newChunk[newChunk.length - 2] * 1 + 1
  ) {
    caryOver = true;
    newChunk.pop();
  } else {
    caryOver = false;
  }

  return newChunk;
}

async function readWriteStream() {
  const readFileHandle = await fs.open("bigFile.txt", "r");

  //   const stat = await readFileHandle.stat();

  const rr = readFileHandle.createReadStream({ highWaterMark: 16384 });
  console.log("Read High Water Mark: ", rr.readableHighWaterMark);

  const writeBigFileHanlde = await fs.open("bigFileCopy.txt", "w");

  const writeStream = writeBigFileHanlde.createWriteStream({
    highWaterMark: 16384,
  });

  console.log("Write High Water Mark: ", writeStream.writableHighWaterMark);

  writeStream.on("drain", () => {
    rr.resume();
  });

  writeStream.on("finish", async () => {
    console.timeEnd("Execution-Time");
    await writeBigFileHanlde.close(); // Ensure file is closed after logging
  });

  let stop = 0;
  rr.on("readable", () => {
    let chunk;
    while ((chunk = rr.read()) !== null) {
      //   console.log(chunk); // Logs Buffer objects
      //   console.log(chunk.toString()); // Logs string representation of the Buffer default utf-8

      let newChunk = sanitizeChunk(chunk);
      newChunk = newChunk.join("  ");
      newChunk = newChunk + "  ";

      stop++;

      const canWrite = writeStream.write(newChunk);
      if (!canWrite) {
        rr.pause();
      }
    }
  });

  rr.on("end", () => {
    console.log("File handle closed");
    writeStream.end();
    readFileHandle.close();
  });

  // Handle errors on the write stream
  writeStream.on("error", (err) => {
    console.error("Write stream error:", err);
    throw err; // Propagate the error to the catch block
  });

  // Handle errors on the read stream
  rr.on("error", (err) => {
    console.error("Read stream error:", err);
    throw err; // Propagate the error to the catch block
  });
}

readWriteStream().catch((err) => {
  console.log("Error reading stream: ", err);
});
