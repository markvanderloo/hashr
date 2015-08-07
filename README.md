[![Build Status](https://travis-ci.org/markvanderloo/hashr.svg)](https://travis-ci.org/markvanderloo/hashr) [![Coverage Status](https://coveralls.io/repos/markvanderloo/hashr/badge.svg?branch=master)](https://coveralls.io/r/markvanderloo/hashr?branch=master)
[![CRAN version](http://www.r-pkg.org/badges/version/hashr)](http://www.r-pkg.org/pkg/hashr)
[![RStudio CRAN Downloads](http://cranlogs.r-pkg.org/badges/hashr)](http://www.r-pkg.org/pkg/hashr)

# hashr
Quicly compute hash values for R objects

# Installation
From R:
```
install.packages("hashr")
```
The latest beta-versions are available through my [drat](http://www.r-pkg.org/pkg/drat) repository. 
```
# if you don't have drat:
install.packages('drat')

# to install from my drat repo:
drat::addRepo("markvanderloo")
install.packages("hashr")
```
If you are in for some excitement you can build the development version by cloning this github page.
In a `bash` command shell do:
```
git clone http://github.com/markvanderloo/hashr.git
cd hashr
./build.bash
R CMD INSTALL output/hashr*.tar.gz
```


