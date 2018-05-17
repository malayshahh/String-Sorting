# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>

char** addString(int* nthString, int* numStrings, int start, int end, char** argv, char** strArr)
{
	int k = 0;
	char** newStrArr = strArr;
	//check if there even are chars between argv[1][start] and argv[1][end]
	//if there aren't any, skip it. Otherwise, add it to strArr
	if(start != end)
	{
		//length stores the length of the string, strHold will store the string
		int length = end - start;
		char* strHold = (char*) malloc((length+1) * sizeof(char));

		if(strHold == NULL) //check if malloc worked
		{
			printf("Error: Malloc did not work. Program will return\n");
			return NULL;
		}
		strHold[length] = '\0'; //add the null terminator
		
		//copy the string from the terminal into hold
		for(k = 0; k < length; k++)
		{
			strHold[k] = argv[1][start + k];
		}
		
		//check if strArr has enough space to store the new string
		if((*nthString + 1) > *numStrings)
		{
			//reallocate and increase size of strArr by ten, into newStrArr
			newStrArr = (char**) realloc(strArr, (10 + *numStrings) * sizeof(char*)); 
			
			if(newStrArr == NULL) //check if malloc worked
			{
				printf("Error: malloc did not work. Program will return\n");
				return NULL;
			}
			*numStrings = *numStrings + 10;  //update numStrings
		}
		
		newStrArr[*nthString] = strHold; //add the nth string to the nth position in strArr
		(*nthString)++;               //update nthString
	}
	
	return newStrArr; //update strArr
}

int main(int argc, char**argv)
{
	
	if(argc == 1) //check if no input parameters
	{
		return 0;
	}
	
	if(argc > 2) //check is too many input parameters, print usage string
	{
		printf("Error, too many input parameters. Program will return\n");
		return 0;
	}
	
	//strArr is an array of all strings
	//allocating space for "numString" number of pointers to char arrays (initially ten) 
	int numStrings = 10;
	char** strArr = (char**) malloc(numStrings * sizeof(char*));
	
	if(strArr == NULL) //check if malloc worked
	{
		printf("Error: Malloc did not work. Program will return\n");
		return 0;
	}
		
	//variable declarations and initializations
	int i = 0;
	int j = 0;
	int nthString = 0;        //the number of the string to be added
	char inChar = argv[1][j]; //stores the current char
	int start = j;            //starting index of potential string
	int end = start;          //last index of potential string
	
	//while end of input string is not reached...
	while(inChar != '\0')
	{
		int ascii = (int)inChar;

		if(isalpha(ascii) == 0) //check if inChar is NOT alphabetic
		{
			//a method that adds the string before the non-alphabetic char and updates strArr
			strArr = addString(&nthString, &numStrings, start, end, argv, strArr);
			
			if(strArr == NULL) //if this is true, something went wrong with malloc in addString()
			{
				return 0;
			}			
			
			//move start and end after the string
			start = j + 1;
			end = start;
		}
		else
		{
			end++; //inChar was alphabetic, so increase the last index of current string
		}
		
		//update inChar to read next char
		j++;
		inChar = argv[1][j];
		
	}
	//at this point the end of the input string has been reached
	//we run the method again just in case there was no delimiter
	strArr = addString(&nthString, &numStrings, start, end, argv, strArr);
	
	
	//bubblesort
	//This isn't the best sorting algorithm considering runtime,
	//but it is one of the easier ones to implement
	char* temp = NULL;
	for(i = 0; i < nthString; i++)
	{
		for(j = 0; j < nthString; j++)
		{
			//switch pointers if first string is less than the second
			if(strcmp(strArr[i], strArr[j]) < 0)
			{
				temp = strArr[i];
            strArr[i] = strArr[j];
            strArr[j] = temp;

			}
		}
	}
	
	//printing the sorted array of strings
	for(i = 0; i < nthString; i++)
	{
		printf("%s\n", strArr[i]);
	}
	
	//freeing all dynamically allocated memory through malloc
	for(i = 0; i < numStrings; i++)
	{
		free(strArr[i]);
	}
	free(strArr);
	
	//fin
	return 0;
}
