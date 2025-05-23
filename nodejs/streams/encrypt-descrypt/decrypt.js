const { Transform } = require("node:stream");
const fs = require("node:fs/promises");

class Decrypt extends Transform {
  _transform(chunk, encoding, callback) {
    // rember that the chunk is a buffer of hex values
    console.log(chunk);

    for (let i = 0; i < chunk.length; i++) {
      // decrypt the data by substracting 1 from each
      if (chunk[i] != 255) {
        chunk[i] = chunk[i] - 1;
      }
    }

    // Push the data onto the readable queue.
    callback(null, chunk);
  }
}

let myTransformer = new Decrypt();

(async () => {
  const readFileHanldle = await fs.open("write.md", "r");
  const writeFileHanlde = await fs.open("decrypt.md", "w");

  console.log(await readFileHanldle.stat());
  const readStream = readFileHanldle.createReadStream();
  const writeStream = writeFileHanlde.createWriteStream();

  // pipes handle backpressrue and other events
  readStream.pipe(myTransformer).pipe(writeStream);

  console.log("This is executed First.");
})();
