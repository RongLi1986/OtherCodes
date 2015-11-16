// File from page 91 in "Thinking in C++" by Bruce Eckel
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

/*: LIB.H -- Header file: example C library */
/* Array-like entity created at run-time */

typedef struct STASHtag {
  int size;  /* Size of each space */
  int quantity; /* Number of storage spaces */
  int next; /* Next empty space */
  /* Dynamically allocated array of bytes: */
  unsigned char* storage;
} Stash;

void initialize(Stash* S, int Size);
void cleanup(Stash* S);
int add(Stash* S, void* element);
void* fetch(Stash* S, int index);
int count(Stash* S);
void inflate(Stash* S, int increase);
