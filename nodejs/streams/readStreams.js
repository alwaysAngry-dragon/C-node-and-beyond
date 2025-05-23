// const fs = require("fs/promises");

const fs = require("fs");

// what is readable event - called when the internal buffer is filled with data to the highwwater mark
// what is read method - returns the data in the internal buffer and removed it from the buffer, the default size of the return is the size of the internal buffer
// we can also set the size of the chunk we want to read by passing the size as an argument to the read method
// read method will return null at the end of the stream and trigger the end event
// what is end event - this is called when the stream has no more data to read

function readStream() {
  const rr = fs.createReadStream("foo.txt", { highWaterMark: 4 }); // 4-byte, the size of the internal buffer

  // Ensure no encoding is set
  console.log(rr._readableState.encoding); // Should log `null`

  rr.on("readable", () => {
    let chunk;
    while ((chunk = rr.read()) !== null) {
      // .read will read from the internal buffer, and if buffer is empty will request for more data, until EOF i.e null
      console.log(chunk); // Logs Buffer objects
      console.log(chunk.toString()); // Logs string representation of the Buffer default utf-8
    }
  });

  rr.on("end", () => {
    console.log("end");
  });
}

function readStreamFlowing() {
  const fs = require("fs");

  const rr = fs.createReadStream("foo.txt", { highWaterMark: 8 });

  // attach the data event lintener to the stream to make it a flowing stream
  rr.on("data", (chunk) => {
    console.log(`Received chunk: ${chunk}`);
  });

  rr.on("end", () => {
    console.log("Stream ended");
  });
}

readStream();
