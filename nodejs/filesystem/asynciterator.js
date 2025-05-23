function createNumberGenerator(start, end, delay) {
  return {
    [Symbol.asyncIterator]() {
      let current = start;

      return {
        async next() {
          if (current <= end) {
            await new Promise((resolve) => setTimeout(resolve, delay));
            return { value: current++, done: false };
          } else {
            return { done: true };
          }
        },
      };
    },
  };
}

(async () => {
  const watcher = createNumberGenerator(1, 5, 1000);

  for await (let num of watcher) {
    console.log(num);
  }
})();
