// Author (of inputChar, inputString): Natasha Kvavle
// Date: 10/22/2017
// Random Testing Quiz


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

 
// inputChar - Randomly selects a number between 1 and 126, returns as char. Assumes that srand has already been called with a valid seed.
char inputChar()
{
	char randomChar;
	int randomNum = rand() % 126 + 1;	// Find a number between 1 and 126 (acceptable ASCII character range) 
	randomChar = randomNum; 
      	return randomChar;
}

// inputString - Using inputChar, creates a null terminated, randomly generated, 6-character string and returns a pointer to the array holding that 
// string. Function limits the generation of random characters to lower case characters to enforce better branch coverage of testme(). 
char *inputString()
{
	char randomString[6]; 
	int i; 
	char character = inputChar();

	// Find a 5 random lowercase characters for each position in string  
	for (i = 0; i < 5; i++) {
		while (character > 122 || character < 97) { 
			character = inputChar(); 
		}
	
		randomString[i] = character;
		character = 0; 
	}

	// Null terminate the string 
	randomString[5] = '\0'; 

    	return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
