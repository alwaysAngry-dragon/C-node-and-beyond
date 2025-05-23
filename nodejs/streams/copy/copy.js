const fs = require("fs/promises");
/*
// CREATE A BIG FILE
(async () => {
  console.time("big");
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
    while (i < 1e7) {
      const canWrite = writeStream.write(Buffer.from(`${i}`));

      if (!canWrite) {
        return;
      }
      i++;
      if (i == 1e7) {
        writeStream.end();
      }
    }
  };

  wirteToFile();
})();

*/

// implementing own read and write without using streams to mimic the stream functionality
// Execution Time: 370ms
// Memory usage: 20MB
// High water Mark: 16384 default
(async () => {
  console.time("Copy");
  const destFile = await fs.open("text-copy.txt", "w");
  const sourceFile = await fs.open("bigFile.txt", "r");

  let bytesRead = -1;

  while (bytesRead !== 0) {
    // the buffer size if 16KB by default, even if the data in the file is less,
    // the read will reaturn a buffer of 16KB, the bytes read will keep track of the actual amount of bytes read

    const readData = await sourceFile.read();
    bytesRead = readData.bytesRead;

    if (bytesRead === 0) {
      // eof
      break;
    }
    const buffer = readData.buffer.subarray(0, bytesRead);
    await destFile.write(buffer);

    // console.log(readData);
  }

  // clos the files handlers
  await destFile.close();
  await sourceFile.close();
  console.timeEnd("Copy");
})();
