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
// FILE: database_access.c
//
// DESCRIPTION: This file contains all of the functions needed
// to access the database. Debug output is controlled by 'debugmode'.
//
//****************************************************************/

#include "database_access.h"

extern int debugmode;

/*****************************************************************
//
// FUNCTION NAME: addRecord
//
// DESCRIPTION:   Adds another element to the linked list, 
//                ordered by ascending account numbers. If
//                there is a duplicate, then the record is 
//                added before the duplicate.
//
// PARAMETERS:    startplace (struct record **) : Holds the
//                pointer to the struct record pointer that holds
//                the starting point of the linked list.
//                accountnumber (int) : Holds the account number
//                associated with the record.
//                name (char []) : Holds the name associated
//                with the record.
//                address (char []) : Holds the address associated
//                with the record.
//                yearofbirth (int) : Holds birth year associated
//                with the record. 
// RETURN VALUES: 0 : If successful.
//
//****************************************************************/

int addRecord (struct record ** startplace, int accountnumber,
               char name [], char address [], int yearofbirth)
{
	struct record *newrecord;
	struct record *previousrecord = *startplace;
	struct record *nextrecord = *startplace;

	int isstartlist = 0;
	
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("addRecord has been called.\n");
		printf ("%p has been passed to \"startplace\".\n", startplace);
		printf ("%d has been passed to \"accountnumber\".\n", accountnumber);

        for (int i = 0; name[j] != '\0'; j++)
		{
			printf ("%c", name[j]);
		}
		printf (" has been passed to \"name\".\n");

        for (int i = 0; address[j] != '\0'; j++)
		{
			printf ("%c", address[j]);
		}
		printf (" has been passed to \"address\".\n");
		printf ("%d has been passed to \"yearofbirth\".\n", yearofbirth);
		printf ("******DEBUG OUTPUT END******\n\n");
	} 

	while (nextrecord != NULL && accountnumber > nextrecord->accountno)
	{
		previousrecord = nextrecord;
		nextrecord = nextrecord->next;

		isstartlist = 1;
	}
	
	newrecord = (struct record *) malloc (sizeof (struct record));
	
	/* change start of list if list is empty or new record is first */
	if (isstartlist == 0)
	{
		*startplace = newrecord;
	} 
	/* link previous record to the new record if not at start */ 
	else 
	{
		previousrecord->next = newrecord;
	}
	
	newrecord->accountno = accountnumber;

    for (int i = 0; name[i] != '\0'; i++)    
	{
		newrecord->name[i] = name[i];
	}
	newrecord->name[i] = '\0';
	
	for (int i = 0; name[i] != '\0'; i++)
	{
		newrecord->address[i] = address[i];
	}
	newrecord->address[i] = '\0';

	newrecord->yearofbirth = yearofbirth;

	newrecord->next = nextrecord;
	
	return 0;
}

/*****************************************************************
//
// FUNCTION NAME: printRecord
//
// DESCRIPTION:   Prints all records with the matching account
//                number.
//
// PARAMETERS:    start (struct record *) : Holds the
//                pointer to the start of the list.
//                accountnumber (int) : Holds the account number 
//                associated with the record.
//                
// RETURN VALUES: 0 : If successful.
//                -1 : If record not found.
//
//****************************************************************/

int printRecord (struct record * start, int accountnumber)
{
	int isfound = -1;

	struct record *currentrecord = start;
	
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("printRecord has been called.\n");
		printf ("%p has been passed to \"start\".\n", start);
		printf ("%d has been passed to \"accountnumber\".\n", accountnumber);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
	
	printf ("------------------------------------------------\n");
	while (currentrecord != NULL)
	{
		if (currentrecord->accountno == accountnumber)
		{
			char currentc = currentrecord->name[j];

			printf ("Account Number: %d\n", currentrecord->accountno);
			
			printf ("Account Name: ");
            for (int i = 0; currentc != '\0'; i++)
			{
				printf ("%c", currentc);

				currentc = currentrecord->name[i];
			}
			printf ("\n");

			j = 0;
			currentc = currentrecord->address[j];
			printf ("Account Address: ");
			while (currentc != '\0')
			{
				printf ("%c", currentc);

				j++;
				currentc = currentrecord->address[j];
			}
			printf ("\n");
			
			printf ("Account Year of Birth: %d\n", currentrecord->yearofbirth);

			if (currentrecord->next != NULL)
			{
				if ((currentrecord->next)->accountno == accountnumber)
				{
					printf ("\n");
				}
			}

			isfound = 0;
		}
		
		currentrecord = currentrecord->next;
	}
	printf ("------------------------------------------------\n");

	return isfound;
}

/*****************************************************************
//
// FUNCTION NAME: modifyRecord
//
// DESCRIPTION:   Modifys a specific record's address 
//                information based on the account number given.
//
// PARAMETERS:    start (struct record *) : Holds the 
//                pointer to the start of the list.
//                accountnumber (int) : Holds the account number
//                associated with the record.
//                address (char []) : Holds the new address to 
//                be associated with the record.
//
// RETURN VALUES: 0 : If successful.
//                -1 : If record not found.
//
//****************************************************************/

int modifyRecord (struct record * start, int accountnumber, char address [])
{
	int isfound = -1;

	struct record *currentrecord = start;
	
	if (debugmode == 1)
	{
		int j = 0;

		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("modifyRecord has been called.\n");
		printf ("%p has been passed to \"start\".\n", start);
		printf ("%d has been passed to \"accountnumber\".\n", accountnumber);
		
		while (address[j] != '\0')
		{
			printf ("%c", address[j]);
			j++;
		}
		printf (" has been passed to \"address\".\n");
		printf ("******DEBUG OUTPUT END******\n\n");
	}

	while (currentrecord != NULL)
	{
		if (accountnumber == currentrecord->accountno)
		{
			int k = 0;

			while (address[k] != '\0')
			{
				currentrecord->address[k] = address[k];
				k++;
			}
			currentrecord->address[k] = '\0';

			isfound = 0;
		}
		
		currentrecord = currentrecord->next;
	}
	
	return isfound;
}

/*****************************************************************
//
// FUNCTION NAME: printAllRecords
//
// DESCRIPTION:   Prints every current element in the linked list
//                of records.
//
// PARAMETERS:    start (struct record *) : Holds the 
//                pointer to the starting record of the list.
//
// RETURN VALUES: None. 
//
//****************************************************************/

void printAllRecords (struct record * start)
{
	struct record *currentrecord = start;
	
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("printAllRecords has been called.\n");
		printf ("%p has been passed to \"start\".\n", start);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
	
	printf ("------------------------------------------------\n");
	while (currentrecord != NULL)
	{
		int j = 0;
		char currentc = currentrecord->name[j];

		printf ("Account Number: %d\n", currentrecord->accountno);
		
		printf ("Account Name: ");
		while (currentc != '\0')
		{
			printf ("%c", currentc);

			j++;
			currentc = currentrecord->name[j];
		}
		printf ("\n");

		j = 0;
		currentc = currentrecord->address[j];
		printf ("Account Address: ");
		while (currentc != '\0')
		{
			printf ("%c", currentc);

			j++;
			currentc = currentrecord->address[j];
		}
		printf ("\n");
		
		printf ("Account Year of Birth: %d\n", currentrecord->yearofbirth);
		
		currentrecord = currentrecord->next;

		if (currentrecord != NULL)
		{
			printf ("\n");
		}
	}
	printf ("------------------------------------------------\n");
}

/*****************************************************************
//
// FUNCTION NAME: deleteRecord
//
// DESCRIPTION:   Deletes all elements with the matching account
//                number and unreserves their allocated memory
//                from the linked list.
//
// PARAMETERS:    startplace (struct record **) : Holds the
//                pointer to the struct record pointer that holds
//                the starting point of the linked list.
//                accountnumber (int) : Holds the account number
//                associated with the record.
//
// RETURN VALUES: 0 : If successful.
//                -1 : If record not found.
//
//****************************************************************/

int deleteRecord (struct record ** startplace, int accountnumber)
{
	struct record *currentrecord = *startplace;
	struct record *previousrecord = NULL;
	struct record *startrecord = *startplace;
	
	int isfound = -1;
	int isstart = -1;
	
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("deleteRecord has been called.\n");
		printf ("%p has been passed to \"startplace\".\n", startplace);
		printf ("%d has been passed to \"accountnumber\".\n", accountnumber);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
	
	while (*startplace != NULL && currentrecord != NULL)
	{
		if (accountnumber == currentrecord->accountno)
		{
			/* in middle, delete and relink list */
			if (currentrecord != startrecord)
			{
				previousrecord->next = currentrecord->next;
				free (currentrecord);

				currentrecord = previousrecord;
			}
			
			/* at beginning, change start of list pointer */
			else if (currentrecord == startrecord)
			{
				startrecord = currentrecord->next;
				free (currentrecord);

				/* recheck start position */
				currentrecord = startrecord;
				isstart = 0;
			}
			
			isfound = 0;
		}

		if (isstart == -1)
		{
			previousrecord = currentrecord;
			currentrecord = currentrecord->next;
		}
		else
		{
			isstart = -1;
		}
	}
	
	*startplace = startrecord;
	
	return isfound;
}

/*****************************************************************
//
// FUNCTION NAME: readfile
//
// DESCRIPTION:   Copies records in a file to an array of struct
//                accounts. Assume that the linked list is empty.
//
// PARAMETERS:    startplace (struct record **) : Holds the pointer
//                to the pointer to the start of the list.
//                filename (char []) : Holds the pointer to the
//                filename string. This file will be the one
//                read.
//
// RETURN VALUES:  0 : If successful.
//                -1 : If filename is not found.
//
//****************************************************************/

int readfile (struct record ** startplace, char filename [])
{
	FILE * infilebuffer;
	char currentc = 'a';
	int doesfileexist = 0;

	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("readfile has been called.\n");
		printf ("%p has been passed to \"startplace\".\n", startplace);
		printf ("%s has been passed to \"filename\".\n", filename);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
	
	infilebuffer = fopen (filename, "r");

	if (infilebuffer == NULL)
	{
		doesfileexist = -1;
	}
	
	while (currentc != EOF && doesfileexist == 0)
	{
		int i = 0;
		char previousc = '\0';
		struct record temp;

		fscanf (infilebuffer, "%d", &(temp.accountno)); 
		fgetc (infilebuffer);		
		
		currentc = fgetc (infilebuffer);
		while (currentc != '\n')
		{
			temp.name[i] = currentc;
			currentc = fgetc (infilebuffer);
			i++;
		}
		temp.name[i] = '\0';

		i = 0;
		currentc = fgetc (infilebuffer);
		while ((currentc != '\n' || currentc != previousc))
		{
			temp.address[i] = currentc;
			previousc = currentc;
			currentc = fgetc (infilebuffer);
			i++;
		}
		temp.address[i - 1] = '\0';

		fscanf (infilebuffer, "%d", &(temp.yearofbirth));
		
		/* skip over new lines */
		fgetc (infilebuffer);		
		currentc = fgetc (infilebuffer); 

		addRecord (startplace, temp.accountno, temp.name, temp.address, temp.yearofbirth);
	}

	if (infilebuffer != NULL)
	{
		fclose(infilebuffer);
	}

	return doesfileexist;
}

/*****************************************************************
//
// FUNCTION NAME: writefile
//
// DESCRIPTION:   Writes an array of records to a file in a
//                a certain format.
//
// PARAMETERS:    start (struct account []) : Holds the pointer
//                to the start of the list.
//                filename (char []) : Holds the pointer to the
//                filename string. This file will be the one
//                written to.
//
// RETURN VALUES: None.
//
//****************************************************************/

void writefile (struct record start [], char filename [])
{
	FILE *outfilebuffer;
	struct record *currentrecord = start;
	
	if (debugmode == 1)
	{
		printf ("\n******DEBUG OUTPUT START******\n");
		printf ("writefile has been called.\n");
		printf ("%p has been passed to \"start\".\n", start);
		printf ("%s has been passed to \"filename\".\n", filename);
		printf ("******DEBUG OUTPUT END******\n\n");
	}
	
	if (start != NULL)
	{
		/* this will overwrite an existing file with the same name */
		outfilebuffer = fopen(filename, "w");
	}

	while (currentrecord != NULL)
	{
		int i = 0;
		char currentc = currentrecord->name[i];
		
		fprintf (outfilebuffer, "%d\n", currentrecord->accountno);
		
		while (currentc != '\0')
		{
			fprintf (outfilebuffer, "%c", currentc);

			i++;
			currentc = currentrecord->name[i];
		}
		fprintf (outfilebuffer, "\n");

		i = 0;
		currentc = currentrecord->address[i];
		while (currentc != '\0')
		{
			fprintf (outfilebuffer, "%c", currentc);

			i++;
			currentc = currentrecord->address[i];
		}
		fprintf (outfilebuffer, "\n\n");

		fprintf (outfilebuffer, "%d\n", currentrecord->yearofbirth);
		
		currentrecord = currentrecord->next;
		
		/* only append newline if not at end of list */
		if (currentrecord != NULL)
		{
			fprintf(outfilebuffer, "\n");
		}
	}

	if (start != NULL)
	{
		fclose (outfilebuffer);
	}
	else
	{
		remove (filename);
	}
}

/*****************************************************************
//
// FUNCTION NAME: cleanup
//
// DESCRIPTION:   Unreserves all allocated memory for the linked 
//                list.
//
// PARAMETERS:    start (struct record *) : Holds the struct record 
//                pointer that holds the starting point of the
//                linked list.
//
// RETURN VALUES: None.
//
//****************************************************************/

void cleanup (struct record * start)
{
	struct record * currentrecord = start;
	struct record * nextrecord;

	if (debugmode == 1)
	{
		printf("\n******DEBUG OUTPUT START******\n");
		printf("cleanup has been called.\n");
		printf("%p has been passed to \"start\".\n", start);
		printf("******DEBUG OUTPUT END******\n\n");
	}

	while (currentrecord != NULL)
	{
		nextrecord = currentrecord->next;
		free(currentrecord);
		currentrecord = nextrecord;
	}
}
