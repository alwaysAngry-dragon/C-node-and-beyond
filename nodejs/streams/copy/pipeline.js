const { pipeline } = require("stream");
const fs = require("fs/promises");

// Execution Time: 170ms
// Memory usage:
(async () => {
  console.time("Copy");
  const destFile = await fs.open("text-copy.txt", "w");
  const sourceFile = await fs.open("bigFile.txt", "r");

  const readStream = sourceFile.createReadStream();
  const writeStream = destFile.createWriteStream();

  pipeline(readStream, writeStream, async (err) => {
    if (err) {
      console.log("Error: ", err);
    } else {
      console.log("Pipeline finished");
      console.timeEnd("Copy");
      await destFile.close();
      await sourceFile.close();
    }
  });
})();
