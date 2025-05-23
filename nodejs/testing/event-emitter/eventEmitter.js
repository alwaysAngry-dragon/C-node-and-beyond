const EventEmitter = require("events");

class MyEmitter extends EventEmitter {}

const myEmitter = new MyEmitter();

myEmitter.once("foo", (data) => {
  console.log(`Event 2 triggered: ${data}`);
});

myEmitter.on("foo", (data) => {
  console.log(`Event triggered: ${data}`);
});

console.log(myEmitter);

myEmitter.emit("foo", "Hello, World!");

console.log(myEmitter);
