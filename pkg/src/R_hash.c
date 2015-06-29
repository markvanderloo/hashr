/*  Copyright (C) Mark van der Loo 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *
 *  You can contact the author at: mark _dot_ vanderloo _at_ gmail _dot_ com
 */

#include <R.h>
#include <Rdefines.h>
#include <stdint.h>
#include "sfh.h"


SEXP R_hash_raw(SEXP X){
  PROTECT(X);
  
  SEXP h; 
  PROTECT(h = allocVector(INTSXP,1L));
  
  INTEGER(h)[0] = (int) SuperFastHash((char *) RAW(X),length(X));


  UNPROTECT(2);
  return h;
}

SEXP R_hash_charvec(SEXP X){
  PROTECT(X);
  int n = length(X);

  SEXP H;
  PROTECT(H = allocVector(INTSXP,length(X)));
  int *h = INTEGER(H);

  for (int i = 0; i < n; i++, h++) {  
   (*h) = (int) SuperFastHash( CHAR(STRING_ELT(X,i)), length(STRING_ELT(X,i)));
  }

  UNPROTECT(2);
  return H;

}





