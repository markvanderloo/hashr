#' Hash R objects to 32bit integers
#'
#' @param x Object to hash
#' @param ... Arguments to be passed to other functions
#'
#' @export
hash <- function(x,...){
  UseMethod('hash')
}

