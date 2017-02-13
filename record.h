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
// FILE: record.h
//
// DESCRIPTION: This file contains the struct record that holds
// the information pertaining to one account in the database.
//
//****************************************************************/

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    int                yearofbirth;
    struct record*     next;
};
