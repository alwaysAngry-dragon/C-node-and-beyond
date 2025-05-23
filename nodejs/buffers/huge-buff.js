const { Buffer } = require("buffer");

const buffer = Buffer.alloc(1000, 0xff);

const unsafeBuffer = Buffer.allocUnsafe(100);

console.log(unsafeBuffer[0] == 0x00);

for (let i = 0; i < unsafeBuffer.length; i++) {
  if (unsafeBuffer[i] !== 0x00) {
    console.log(`unsafeBuffer[${i}] = ${String.fromCharCode(unsafeBuffer[i])}`); // print the utf-8 character for the byte
  }
}

const buff = Buffer.from([0x48, 0x69, 0x00, 0x21]);
console.log(buff[0]); // prints: 72, the decimal representation of 0x48
