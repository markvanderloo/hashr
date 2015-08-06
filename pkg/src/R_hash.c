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
#ifdef _OPENMP
#include <omp.h>
#endif

SEXP R_hash_raw(SEXP X){
  PROTECT(X);
  
  SEXP h; 
  PROTECT(h = allocVector(INTSXP,1L));
  
  INTEGER(h)[0] = (int) SuperFastHash((char *) RAW(X),length(X));


  UNPROTECT(2);
  return h;
}

SEXP R_hash_charvec(SEXP X, SEXP NTHRD, SEXP MODE){
  PROTECT(X);
  PROTECT(NTHRD);
  PROTECT(MODE); 
  int n = length(X)
    , nthrd = INTEGER(NTHRD)[0];

  SEXP H;
  PROTECT(H = allocVector(INTSXP,length(X)));

  #ifdef _OPENMP
  #pragma omp parallel num_threads(nthrd)
  #endif
  {
    int *h = INTEGER(H)
      , ID = 0
      , nthreads = 1L;
    #ifdef _OPENMP
    ID = omp_get_thread_num();
    nthreads = omp_get_num_threads();
    #endif
    if (INTEGER(MODE)[0] == 0){ // has string
      for (int i = ID; i < n; i += nthreads ) {
       h[i] = (int) SuperFastHash( CHAR(STRING_ELT(X,i)), length(STRING_ELT(X,i)));
      }
    } else if (INTEGER(MODE)[0] == 1){ // hash pointer to unique string
      char c[sizeof(long int)];
      long int ii;
      for (int i = ID; i < n; i += nthreads ) {
       ii = (long int) CHAR(STRING_ELT(X,i));
       memcpy(c, &ii, sizeof(long int));
       h[i] = (int) SuperFastHash( c, sizeof(long int));
      }
    } else {
      error("Unrecognized hash mode");
    }
  }// end of parallel region

  UNPROTECT(4);
  return H;

}


// hash a list consisting of only character vectors
SEXP R_hash_charlist(SEXP X, SEXP NTHRD){
  PROTECT(X);
  PROTECT(NTHRD);
  int n = length(X)
    , nthrd = INTEGER(NTHRD)[0];

  SEXP out;
  out = PROTECT(allocVector(VECSXP,n));

  int ni = 0;
  // we can't parallelize this because R's allocation isn't thread-safe :-(
  for ( int i = 0 ; i < n; i++ ){
    ni = length(VECTOR_ELT(X,i));
    SET_VECTOR_ELT(out, i, allocVector(INTSXP, ni));
  }


  #ifdef _OPENMP
  #pragma omp parallel num_threads(nthrd)
  #endif
  {
    SEXP S;
    int *v;
    int n_str;
    #ifdef _OPENMP
    #pragma omp for
    #endif
    for ( int i = 0; i < n; i++ ){
      S = VECTOR_ELT(X,i);
      v = INTEGER(VECTOR_ELT(out, i));
      n_str = length(S);
      for ( int j = 0; j < n_str; j++){
        v[j] = SuperFastHash( CHAR(STRING_ELT(S,j)),length(STRING_ELT(S,j)) );
      }
    }
  }// end of parallel region

  UNPROTECT(3);
  return out;

}

// Determine whether all elements of a list are of type charater.
SEXP R_all_char(SEXP X){
  PROTECT(X);
  SEXP all_char;
  all_char = PROTECT(allocVector(LGLSXP,1L));

  int n = length(X);
  LOGICAL(all_char)[0] =  1L;
  for (int i=0; i<n; i++){
    if (TYPEOF(VECTOR_ELT(X,i)) != STRSXP){
      LOGICAL(all_char)[0] = 0L;
      break;
    }
  }

  UNPROTECT(2);
  return all_char;

}








