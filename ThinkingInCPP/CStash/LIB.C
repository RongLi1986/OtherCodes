// File from page 92 in "Thinking in C++" by Bruce Eckel
//////////////////////////////////////////////////
// From the compressed package ECKELT04.ZIP 5/22/95
// (Original ECKELT01.ZIP dated 2/21/95)
// Copyright (c) Bruce Eckel, 1995 
// Source code file from the book "Thinking in C++", 
// Prentice Hall, 1995, ISBN: 0-13-917709-4
// All rights reserved EXCEPT as allowed by the following 
// statements: You may freely use this file for your own 
// work, including modifications and distribution in 
// executable form only. You may copy and distribute this 
// file, as long as it is only distributed in the complete 
// (compressed) package with the other files from this 
// book and you do not remove this copyright and notice. 
// You may not distribute modified versions of the source 
// code in this package. This package may be freely placed 
// on bulletin boards, internet nodes, shareware disks and 
// product vendor disks. You may not use this file in 
// printed media without the express permission of the 
// author. Bruce Eckel makes no 
// representation about the suitability of this software 
// for any purpose. It is provided "as is" without express 
// or implied warranty of any kind. The entire risk as to 
// the quality and performance of the software is with 
// you. Should the software prove defective, you assume 
// the cost of all necessary servicing, repair, or 
// correction. 
// If you think you've found an error, please 
// email all modified files with loudly commented changes 
// to: eckel@aol.com (please use the same 
// address for non-code errors found in the book).
//////////////////////////////////////////////////

/*: LIB.C -- Implementation of
    example C library */
/* Declare structure and functions: */
#include "lib.h"
/* Error testing macros: */
#include <assert.h>
/* Dynamic memory allocation functions: */
#include <stdlib.h>
#include <string.h> /* memcpy() */
#include <stdio.h>

void initialize(Stash* S, int Size) {
  S->size = Size;
  S->quantity = 0;
  S->storage = 0;
  S->next = 0;
}

void cleanup(Stash* S) {
  if(S->storage) {
	 puts("freeing storage");
	 free(S->storage);
  }
}

int add(Stash* S, void* element) {
  /* enough space left? */
  if(S->next >= S->quantity)
    inflate(S, 100);
  /* Copy element into storage,
  starting at next empty space: */
  memcpy(&(S->storage[S->next * S->size]),
	  element, S->size);
  S->next++;
  return(S->next - 1); /* Index number */
}

void* fetch(Stash* S, int index) {
  if(index >= S->next || index < 0)
    return 0;  /* Not out of bounds? */
  /* Produce pointer to desired element: */
  return &(S->storage[index * S->size]);
}

int count(Stash* S) {
  /* Number of elements in stash */
  return S->next;
}

void inflate(Stash* S, int increase) {
  void* v =
    realloc(S->storage,
	    (S->quantity + increase)
	    * S->size);
  /* Was it successful? */
  assert(v);
  S->storage = (unsigned char*) v;
  S->quantity += increase;
}
