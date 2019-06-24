#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP R_all_char(SEXP);
extern SEXP R_hash_charlist(SEXP, SEXP);
extern SEXP R_hash_charvec(SEXP, SEXP, SEXP);
extern SEXP R_hash_raw(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"R_all_char",      (DL_FUNC) &R_all_char,      1},
    {"R_hash_charlist", (DL_FUNC) &R_hash_charlist, 2},
    {"R_hash_charvec",  (DL_FUNC) &R_hash_charvec,  3},
    {"R_hash_raw",      (DL_FUNC) &R_hash_raw,      1},
    {NULL, NULL, 0}
};

void R_init_hashr(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
