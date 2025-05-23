const fs = require("fs/promises");

const fscallback = require("fs");

const { Buffer } = require("buffer");

console.time("big");
/*
// Time: 994.884ms
(async () => {
  const bigBuffer = Buffer.alloc(8e8, "a"); // the 'a' will be converted to hex (the ascii representation of a) in the buffer, in the file it will be saved as binary

  const fileHandle = await fs.open("bigFile.txt", "w");
  await fileHandle.write(bigBuffer);

  console.timeEnd("big");
  fileHandle.close();
})();

*/
/*
(async () => {
  fscallback.open("bigFile.txt", "w", (err, fd) => {
    if (err) {
      console.log(err);
    }
    fscallback.write(fd, Buffer.alloc(10), (err, wn) => {
      if (err) {
        console.log(err);
      }
    });
  });
})();
*/

/*
// Time:  2.783s
// CPU: 25%
// Memory: 45MB
(async () => {
  fscallback.open("bigFile.txt", "w", (err, fd) => {
    if (err) {
      console.log(err);
    }
    for (let i = 0; i < 1e6; i++) {
      const buff = Buffer.from(` ${i} `, "utf-8");
      fscallback.writeFileSync(fd, buff);
    }
    console.timeEnd("big");
    fscallback.close(fd, (err) => {
      if (err) {
        console.log(err);
      } else {
        console.log("File closed");
      }
    });
  });
})();
*/

/*
// Time: 2.7 s
// CPU: 25%
// Memory: 230MB

(async () => {
  const fileHandle = await fs.open("bigFile.txt", "w");

  const stat = await fileHandle.stat();
  const writeStream = fileHandle.createWriteStream();

  for (let i = 0; i < 1e6; i++) {
    writeStream.write(Buffer.from(`${i}`));
  }

  writeStream.end();
  await fileHandle.close();
  console.timeEnd("big");
})();

*/
// Time: 2.8s
// CPU: 11%
// Memory: 49MB

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

  console.log(writeStream.writableHighWaterMark);

  let i = 0;
  const wirteToFile = () => {
    while (i < 1e6) {
      // .write will retrun false if the internal buffer is full, it however does not pause writing to the internal buffer
      // we need to pause ourselves, this prevents backpressure and ensures low memory usage
      // the drain event will be triggered when the internal buffer is flushed,
      // we can then write the next chunks
      const canWrite = writeStream.write(Buffer.from(`${i}`));

      if (!canWrite) {
        return;
      }
      i++;
      if (i == 1e6) {
        writeStream.end();
      }
    }
  };

  wirteToFile();
})();
