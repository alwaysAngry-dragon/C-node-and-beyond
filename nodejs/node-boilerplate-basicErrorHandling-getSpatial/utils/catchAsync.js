function catchCaAsync(fn) {
  return function (req, res, next) {
    fn(req, res, next).catch((err) => {
      console.log('Async error caught in catchAsync');
      next(err);
    });
  };
}

module.exports = catchCaAsync;
