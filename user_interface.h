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
// FILE: user_interface.h
//
// DESCRIPTION: This file contains the function prototypes for the
// user interface functions in user_interface.c
//
//****************************************************************/

void printmenu ();

void getfield (char [], int);

void addoption (struct record **);

void modifyoption (struct record *);

void deleteoption (struct record **);

void printspecificoption (struct record *);
