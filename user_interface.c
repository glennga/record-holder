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
// FILE: user_interface.c
//
// DESCRIPTION: This file contains the user interface that
// allows a user to interact with a database. Has optional 
// debug output. 
//
//****************************************************************/

#include "database_access.h"
#include "user_interface.h"

int debugmode;

int main (int argc, char * argv []) 
{
	int menuoption = -1;
	struct record *start = NULL;
	char storagefile[] = "address_book.txt";

	if (argc == 1)
	{
		debugmode = 0;
	}
	else if (argc == 2)
	{
		if (strcmp ("debug", argv[1]) == 0) 
		{
			printf ("\nWarning: Debug mode is on. There will be additional output.\n");
			debugmode = 1;
		}
		else
		{
			printf ("Error. [debug] argument must be just \"debug\".\n");
			menuoption = 0;
		}
	}
	else
	{
		printf ("Usage: dba_interface [debug]\n");
		menuoption = 0;
	}

	if (menuoption != 0)
	{
		readfile (&start, storagefile);

		printf ("Hello! This program allows a user to interface with a database holding:");
		printf ("\n\tAccount Numbers\n\tNames\n\tAddresses\n\tBirth Years\n");
	}
	
	while (menuoption != 0)
	{
		printmenu();

		if (scanf ("%d", &menuoption) != 1)
		{
			menuoption = -1;
		}
		switch (menuoption)
		{
			case 0:
				printf ("You have chosen to exit the program. Goodbye.\n");
				break;
		
			case 1:
				printf ("You have chosen to add a new record.\n");

				addoption (&start);
				break;
		
			case 2:
				printf ("You have chosen to modify record(s).\n");

				modifyoption (start);
				break;

			case 3:
				printf ("You have chosen to delete record(s).\n");

				deleteoption (&start);
				break;

			case 4:
				printf ("You have chosen to print specific record(s).\n");

				printspecificoption (start);
				break;

			case 5:
				printf ("You have chosen to print all records.\n\n");

				if (start != NULL)
				{
					printf ("All of the current records in the database are below.\n");
					printAllRecords (start);
				}
				else
				{
					printf ("No records currently exist in the database.\n");
				}
				break;

			default:
				printf ("Invalid option entered. Please enter a number between 0 and 5.\n");

				while (fgetc(stdin) != '\n');
				break;
		}
	}
	
	writefile (start, storagefile);

	cleanup (start);
}

/*****************************************************************
//
// FUNCTION NAME: printmenu
//
// DESCRIPTION:   Prints all possible options the user can perform.
// 
// PARAMETERS:    None. 
//
// RETURN VALUES: None. 
//
//****************************************************************/

void printmenu () 
{
	printf ("\n------------------------------------------------\n");
	printf ("Available Options to Interact with Database:\n"); 
	printf ("Enter 0 to quit and exit the program.\n");
	printf ("Enter 1 to add a record.\n");
	printf ("Enter 2 to modify record(s).\n");
	printf ("Enter 3 to delete existing record(s).\n");
	printf ("Enter 4 to print specific record(s).\n");
	printf ("Enter 5 to print all existing records.\n");
	printf ("------------------------------------------------\n");
	printf ("Your option: ");

}

/*****************************************************************
//
// FUNCTION NAME: getfield
//
// DESCRIPTION:   Obtains address information, ending characters
//                are two newlines. Input must be less than 79
/                 characters.
// 
// PARAMETERS:    addressfield (char *) : Pointer to address
//                field that will be changed by altered.
//                size (int) : Size of character array.

// RETURN VALUES: None. 
//
//****************************************************************/

void getfield (char addressfield [], int size)
{
	int isaddressdone = 0;
	
	int i = 0;
	char nextc, previousc;

	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("getfield has been called.\n");
		printf ("%p has been passed to \"addressfield\".\n", addressfield);
		printf ("%d has been passed to \"size\".\n", size);
		printf ("******DEBUG OUTPUT END******\n\n");
	}

	printf ("\nAddresses longer than 79 characters will be cut off.\n");
	printf ("Enter your address, hit enter twice to stop: ");
  
	/* check for two new lines in a row */
	while (isaddressdone == 0) 
	{
		nextc = fgetc (stdin);
    
		if (nextc != '\n' || nextc != previousc)
		{
			if (i < (size - 1))
			{
				addressfield[i] = nextc;
				i++;
			}
			previousc = nextc;
		}
		else 
		{
			isaddressdone = 1;
		}
	}
	addressfield[i - 1] = '\0';
}

/*****************************************************************
// 
// FUNCTION NAME: addoption  
//                
// DESCRIPTION:   Adds a record to the database using addRecord.
//                
// PARAMETERS:    startplace (struct record **) : Pointer to a
//                pointer to the start of the list.
//                
// RETURN VALUES: None.
// 
//****************************************************************/

void addoption (struct record ** startplace) 
{
	int isinputvalid = 0;

	int i = 0;
	struct record temp;
	char nextc = 'a';

	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("printspecifcoption has been called.\n");
		printf ("%p has been passed to \"startplace\".\n", startplace);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
  
	while (isinputvalid == 0)
	{
		printf ("\nEnter the account number: ");
		if (scanf("%d", &(temp.accountno)) == 1)
		{
			isinputvalid = 1;
		}
		else 
		{
			printf ("Invalid input. No characters or strings allowed. \n");
		}

		while(fgetc (stdin) != '\n');
	}
  
	printf ("\nNames longer than 24 characters will be cut off.\n");
	printf ("Enter a name: ");
 
	nextc = fgetc (stdin);
	while (i < 24 && nextc != '\n')
	{
		temp.name[i] = nextc;
		i++;

		nextc = fgetc (stdin);
	}

	/* append null character to end of array to keep as string */
	temp.name[i] = '\0';

	/* clear if input is oversized */
	if (i == 24)
	{
		while (fgetc (stdin) != '\n');
	}
	
	getfield (temp.address, 80);

	isinputvalid = 0;
	while (isinputvalid == 0)
	{
		printf ("\nEnter the year of birth number: ");
		if (scanf ("%d", &(temp.yearofbirth)) == 1)
		{
			isinputvalid = 1;
		}
		else 
		{
			printf ("Invalid input. No characters or strings allowed. \n");
		}

		while(fgetc (stdin) != '\n');
	}
  
	printf ("\n------------------------------------------------\n");
	printf ("You have entered %d as an account number.\n", temp.accountno);

	i = 0;
	printf ("You have entered ");
	while (temp.name[i] != '\0')
	{
		printf ("%c", temp.name[i]);
		i++;
	}
	printf (" as a name.\n");

	i = 0;
	printf ("You have entered ");
	while (temp.address[i] != '\0')
	{
		printf ("%c", temp.address[i]);
		i++;
	}
	printf (" as an address.\n");
	
	printf ("You have entered %d as a year of birth.\n", temp.yearofbirth);
	printf ("------------------------------------------------\n");
	
	addRecord (startplace, temp.accountno, temp.name, temp.address, temp.yearofbirth);
}

/*****************************************************************
// 
// FUNCTION NAME: modifyoption  
//                
// DESCRIPTION:   Modifies a record in the database using 
//                modifyRecord.
//                
// PARAMETERS:    start (struct record *) : Pointer to the 
//                start of the list.
//                
// RETURN VALUES: None.
// 
//****************************************************************/

void modifyoption (struct record * start) 
{
	int isinputvalid = 0;

	int currentaccountno;
	char currentaddress[80];
	int i = 0;

	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("modifyoption has been called.\n");
		printf ("%p has been passed to \"start\".\n", start);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
  
	while (isinputvalid == 0)
	{
		printf ("\nEnter the account number: ");
		if (scanf ("%d", &currentaccountno) == 1)
		{
			isinputvalid = 1;
		}
		else 
		{
			printf ("Invalid input. No characters or strings allowed. \n");
		}

		while(fgetc (stdin) != '\n');
	}
  
	getfield (currentaddress, 80);
 	
	printf ("------------------------------------------------\n");
	printf ("You have entered %d as an account number.\n", currentaccountno);

	i = 0;
	printf ("You have entered ");
	while (currentaddress[i] != '\0')
	{
		printf ("%c", currentaddress[i]);
		i++;
	}
	printf (" as an address.\n");
	printf ("------------------------------------------------\n");
	
	if (modifyRecord (start, currentaccountno, currentaddress) == -1)
	{
		printf ("\nNo records were found with the account number %d.\n", currentaccountno);
	}
	else
	{
		printf ("\nYou have modified all records with the account number %d.\n", currentaccountno);
	}
}

/*****************************************************************
// 
// FUNCTION NAME: deleteoption  
//                
// DESCRIPTION:   Deletes a record in the database using 
//                deleteRecord.
//                
// PARAMETERS:    startplace (struct record **) : Pointer to a
//                pointer to the start of the list.
//                
// RETURN VALUES: None.
// 
//****************************************************************/

void deleteoption (struct record ** startplace)
{
	int isinputvalid = 0;

	int currentaccountno;
  
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("deleteoption has been called.\n");
		printf ("%p has been passed to \"startplace\".\n", startplace);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
  
	while (isinputvalid == 0)
	{
		printf ("\nEnter the account number: ");
		if (scanf ("%d", &currentaccountno) == 1)
		{
			if (deleteRecord (startplace, currentaccountno) == -1)
			{
				printf ("\nNo records were found with the account number %d.\n", currentaccountno);
			}
			else
			{
				printf ("\nYou have deleted all records with the account number %d.\n", currentaccountno);
			}
      
			isinputvalid = 1;
		}
		else 
		{
			printf ("Invalid input. No characters or strings allowed. \n");
		}

		while(fgetc (stdin) != '\n');
	}
}

/*****************************************************************
// 
// FUNCTION NAME: printspecificoption  
//                
// DESCRIPTION:   Prints a specific record in the database using
//                printRecord.
//                
// PARAMETERS:    start (struct record *) : Pointer to the
//                start of the list.
//                
// RETURN VALUES: None.
// 
//****************************************************************/

void printspecificoption (struct record * start)
{
	int isinputvalid = 0;

	int currentaccountno;
  
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("printspecifcoption has been called.\n");
		printf ("%p has been passed to \"start\".\n", start);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
  
	while (isinputvalid == 0)
	{
		printf ("\nEnter the account number: ");
		if (scanf ("%d", &currentaccountno) == 1)
		{
			printf ("\nThe records with the account number %d are listed below.\n", currentaccountno);
			if (printRecord (start, currentaccountno) == -1)
			{
				printf ("There are no records with the account number %d in the database.\n", currentaccountno);
			}
      
			isinputvalid = 1;
		}
		else 
		{
			printf ("Invalid input. No characters or strings allowed. \n");
		}

		while(fgetc (stdin) != '\n');
	}
}
