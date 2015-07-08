#' Hashing R objects, big and small
#'  
#' This package exports Paul Hsies's \code{SuperFastHash} C-code to R.
#' It can be used to hash either whole R objects or, for vectors or lists,
#' R objects can be hashed recursively, so one gets a set of hash values
#' that is stored in a structure equivalent to the input.
#'
#'
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
#' @section Hash function:
#' The hash function used is Paul Hsieh's' \code{SuperFastHash} function which is
#' described on his \href{http://www.azillionmonkeys.com/qed/hash.html}{website}.
#'
#' @example ../examples/hash.R
#' @export
hash <- function(x, ...){
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
#' @param nthread maximum number of threads used (currently only for \code{character} method)
#' @rdname hash
#' @export 
hash.character <- function(x, recursive=TRUE, nthread=getOption("hashr_num_thread"),...){
  stopifnot(is.numeric(nthread))
  if (recursive){
    .Call("R_hash_charvec",x,as.integer(nthread))
  } else {
    hash.default(x,...)
  }
}

#'
#' @method hash list
#'
#' @rdname hash
#' @export 
hash.list <- function(x, recursive=TRUE, nthread = getOption("hashr_num_thread"), ...){
  if (recursive){
    if ( all_char_list(x) ){
      .Call("R_hash_charlist", x, as.integer(nthread))
    } else {
      lapply(x, hash, ...)
    }
  } else {
    hash.default(x, ...)
  }
}

# determine whether a list contains only character vectors.
all_char_list <- function(x){
  .Call("R_all_char",x)
}




