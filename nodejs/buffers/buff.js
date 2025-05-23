const { Buffer } = require("buffer");

const fs = require("fs");

const memoryContainer = Buffer.alloc(4); // allocate 4 bytes

const tempBuff = Buffer.alloc(16384, 10);
//The buffer created by is filled with the hex value of 10 decimal, i.e <Buffer 0a 0a 0a 0a...>, which corresponds to if read in  ASCII as Line Feed (\n) character.

memoryContainer[0] = 56; // it is stored as its hex value ie 38, or as binary 00111000 in the memory, the buffer does not know about endcoding etc it just stores
memoryContainer[1] = 0xff; // save as hex

memoryContainer.forEach((byte, index) => {
  console.log(`Byte at index ${index}: ${byte}`);
});

console.log(memoryContainer.toString("hex")); // Output in hex

console.log(memoryContainer[0]); // output will be in decimal representation of the byte, that is 56, as no decoding is done here while reading
console.log(memoryContainer[1]); // output will be 255

memoryContainer.writeInt8(-11, 2); // add signed value
console.log(memoryContainer.readInt8(2));

const bigBuffer = Buffer.alloc(8e8, "a"); // the 'a' will be converted to hex , i.e 97  in decimal ascii -> 61 in hex, in the buffer, in the file it will be saved as binary of value of 61

function readFile() {
  fs.readFile("binarytext.txt", (err, data) => {
    console.log("reading file");
    console.log(err ? err : data);
    console.log(data.length);
    console.log(data.toString("utf-8"));
  });
}

function writeToFile() {
  // Create a Buffer containing the binary-encoded data
  // we can use binary or hex
  let buffer = Buffer.from([0b01001000, 0b01101001, 0b00100001]);

  // Or we can use hex as a string argument

  buffer = Buffer.from("486921", "hex");

  // Write the buffer to a file
  fs.writeFile("binarytext.txt", buffer, (err) => {
    if (err) console.error(err);
    else console.log("Binary data written to file");
  });
}

readFile();

// Buffer out of string
const bt = Buffer.from("Hello, World!", "utf-8"); // each character is encoded as per utf-8 encoding
console.log(bt); // Output: 48656c6c6f2c20576f726c6421
console.log(bt.toString("utf-8")); // Output: Hello, World!

const buff = Buffer.from([0x48, 0x69, 0x00, 0x21]);
console.log(buff[0]); // prints: 72, the decimal representation of 0x48
