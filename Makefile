##################################################################
##
## NAME: Glenn Galvizo
##
## HOMEWORK: Project 1
##
## CLASS: ICS 212
##
## INSTRUCTOR: Ravi Narayan
##
## DATE: March 14, 2016
##
## FILE: Makefile
##
## DESCRIPTION: This file contains the rules for make to update 
## the executable and object files for project 1, and to and 
## remove all the files above.
##
##################################################################

dba_access: database_access.o user_interface.o
	cc -o dba_access database_access.o user_interface.o 

user_interface.o: user_interface.c database_access.c user_interface.h database_access.h record.h
	cc -c user_interface.c 

database_access.o: database_access.c database_access.h record.h
	cc -c database_access.c

clean: 
	rm *.o dba_access 
