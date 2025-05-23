const fs = require("fs/promises");

const FILE_PATH = "text.txt";

async function updateFile(fileName, content) {
  try {
    await fs.access(fileName);
    await fs.appendFile(fileName, content);
    console.log(`Content appended to "${fileName}".`);
  } catch (err) {
    throw err;
  }
}

async function renameFile(oldFileName, newFileName) {
  try {
    await fs.access(oldFileName);
    await fs.rename(oldFileName, newFileName);
    console.log(`File "${oldFileName}" renamed to "${newFileName}".`);
  } catch (err) {
    throw err;
  }
}

async function deleteFile(fileName) {
  // delete the file with the given fileName if it exists
  try {
    await fs.access(fileName);
    await fs.unlink(fileName);
    console.log(`File "${fileName}" deleted.`);
  } catch (err) {
    throw err;
  }
}

async function create(fileName) {
  // create a new file with the given fileName and no content
  try {
    await fs.open(fileName, "r");
    throw new Error("File exists");
  } catch (error) {
    if (error.message == "File exists") {
      throw error;
      return;
    }
    // file does not exists so create a new file
    await fs.writeFile(fileName, "");
    console.log(`File "${fileName}" created.`);
  }
}

async function getFileName(string) {
  const tokens = string.split(" ");
  if (tokens.length < 2) {
    throw new Error("Invalid command - File name is required");
  }
  const fileName = tokens[1];
  return fileName;
}

async function getNewFileName(string) {
  const tokens = string.split(" ");
  if (tokens.length < 3) {
    throw new Error("Invalid command - destination file name is required");
  }
  const newFileName = tokens[2];
  return newFileName;
}

async function getNewContent(string) {
  const tokens = string.split(" ");
  if (tokens.length < 3) {
    throw new Error("Invalid command - new content is required");
  }
  // add a new line at the start of the content
  const content = `\n${tokens.slice(2).join(" ")}`;
  return content;
}

async function checkCommand(string) {
  string = string.trim();

  try {
    const fileName = await getFileName(string);
    if (string.startsWith("create")) {
      await create(fileName);
    } else if (string.startsWith("delete")) {
      await deleteFile(fileName);
    } else if (string.startsWith("rename")) {
      const newFileName = await getNewFileName(string);
      await renameFile(fileName, newFileName);
    } else if (string.startsWith("update")) {
      const content = await getNewContent(string);
      await updateFile(fileName, content);
    } else {
      throw new Error("Invalid command");
    }
  } catch (error) {
    console.log(error.message);
  }
}

async function readFile() {
  try {
    const data = await fs.readFile(FILE_PATH, "utf-8");
    console.log(data);
    await checkCommand(data.toLocaleLowerCase());
  } catch (error) {
    console.error(error);
    process.exit(1);
  }
}

// watch for file change
async function watchFile(filePath) {
  try {
    const watcher = fs.watch(FILE_PATH);

    console.log("File watcher started");

    for await (const event of watcher) {
      if (event.eventType == "change") {
        await readFile();
      }
    }
  } catch (error) {
    console.error(error);
  }
}

watchFile();
