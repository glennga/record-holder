/*****************************************************************
//
// NAME: Glenn Galvizo
//
// HOMEWORK: Project 1
//
// CLASS: ICS 212
//
// INSTRUCTOR: Ravi Narayan
//
// DATE: March 15, 2016
//
// FILE: database_access.h
//
// DESCRIPTION: This file contains the function prototypes for the
// database access functions in database_access.c.
//
//****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

int addRecord (struct record **, int, char [],char [], int);

int printRecord (struct record *, int);

int modifyRecord (struct record *, int, char []);

void printAllRecords (struct record *);

int deleteRecord (struct record **, int);

int readfile(struct record **, char []);

void writefile(struct record *, char []);

void cleanup (struct record *);
