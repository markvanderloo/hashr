#' Hashing R objects, big and small
#'  
#' More stuff here
#'
#' @name hashr-package
#' @docType package
#' @useDynLib hashr
#' 
{}



#' Hash R objects to 32bit integers
#'
#'
#' @param x Object to hash
#' @param ... Arguments to be passed to other methods. In particular, for the default method, 
#'  these arguments are passed to \code{\link[base]{serialize}}.
#'
#'
#' @section Details:
#' The default method \code{\link[base]{serialize}}s the input to a single
#' \code{\link[base]{raw}} vector which is then hashed to a single signed
#' integer. This is also true for \code{character} vectors when
#' \code{recursive=FALSE}. When \code{recursive=TRUE} each element of a
#' \code{character} vector is hashed separately, based on the underlying
#' \code{char} representation in \code{C}.
#'
#' @example ../examples/hash.R
#' @export
hash <- function(x,...){
  UseMethod('hash')
}

#' @export
#' @rdname hash
hash.default <- function(x,...){
  X <- serialize(x, connection=NULL, ...)
  .Call("R_hash_raw", X)
}

#'
#' @method hash character
#'
#' @param recursive hash each element separately?
#' @rdname hash
#' @export 
hash.character <- function(x, recursive=TRUE, ...){
  if (recursive){
    .Call("R_hash_charvec",x)
  } else {
    hash.default(x,...)
  }
}

#'
#' @method hash list
#'
#' @rdname hash
#' @export 
hash.list <- function(x, recursive=TRUE, ...){
  if (recursive){
    lapply(x,hash,...)
  } else {
    hash.default(x,...)
  }
}




