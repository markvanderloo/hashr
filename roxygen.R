library(roxygen2)
library(devtools)
options(error=traceback)
unlink( 'pkg/man', TRUE)

document('./pkg')


if (length(list.files('inst/doc')) == 0){
   unlink( 'inst/doc', TRUE)   
}
