const fs = require("fs/promises");

(async () => {
  const fileHandle = await fs.open("./text.txt", "r");

  const watcher = fs.watch("./text.txt");

  for await (const event of watcher) {
    console.log(event.eventType);
    const stat = await fileHandle.stat();
    const buffer = Buffer.alloc(stat.size);
    await fileHandle.read(buffer, 0, stat.size, 0);
    console.log(buffer);
    console.log(buffer.toString("utf-8"));
  }
})();
