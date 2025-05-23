const { Transform } = require("node:stream");
const fs = require("node:fs/promises");

class Encrypt extends Transform {
  _transform(chunk, encoding, callback) {
    // rember that the chunk is a buffer of hex values
    console.log(chunk);

    for (let i = 0; i < chunk.length; i++) {
      // encrypting the data by adding 1 to each
      if (chunk[i] != 255) {
        chunk[i] = chunk[i] + 1;
      }
    }

    // Push the data onto the readable queue.
    callback(null, chunk);
  }
}

let myTransformer = new Encrypt();

(async () => {
  const readFileHanldle = await fs.open("read.md", "r");
  const writeFileHanlde = await fs.open("write.md", "w");

  const readStream = readFileHanldle.createReadStream();
  const writeStream = writeFileHanlde.createWriteStream();

  // pipes handle backpressrue and other events
  readStream.pipe(myTransformer).pipe(writeStream);

  console.log("Done transforming");
})();
