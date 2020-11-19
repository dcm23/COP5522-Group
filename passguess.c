#include <stdio.h>
#include <microtime.h>
#include <string.h>
#include <stdlib.h>

char* makeGuess(char *guess, char *known, int length) {
	int i;
	int unknown = -1;

	// find the index of the first unknown character
	for(i = 0; i < length; i++) {
		if(known[i] == 0) {
			unknown = i;
			break;
		}
	}

	if(unknown > -1) {
		if(guess[unknown] >= 126) {
			// just in case
			guess[unknown] = 32;
		}
		else {
			guess[unknown]++;
		}
	}

	return guess;
}

char checkGuess(char *guess, char *pw, char *known, int length) {
	int i;
	char isCorrect = 1;

	for(i = 0; i < length; i++) {
		if(guess[i] == pw[i]) {
			// we found a matching character
			known[i] = 1;
		}
		else {
			// we found a charcter that did not match
			known[i] = 0;
			isCorrect = 0;
		}
	}
	
	return isCorrect;
}

char* init(int length) {
	char* arr;
	arr = malloc(length * sizeof(char));
	return arr;
}

int main(int argc, char **argv)
{
  if(argc != 3)
  {
    fprintf(stderr, "USAGE: %s Password Length\n", argv[0]);
    exit(1);
  }

  double t, time1, time2;
  long length = strtol(argv[2], NULL, 10);
  char solved = 0;
  char *pw, *guess, *known;

  pw = init(length);
  guess = init(length);
  known = init(length);

  int i;
  for(i = 0; i < length; i++) {
  	pw[i] = argv[1][i];
  }

  time1 = microtime();
  while(!solved) {
	  guess = makeGuess(guess, known, length);
	  solved = checkGuess(guess, pw, known, length);
  }
  time2 = microtime();

  t = time2-time1;
  printf("The password is %s\n", guess);
  printf("Time = %g us\tTimer Resolution = %g us\t\n\n", t, get_microtime_resolution());

  free(pw);
  free(guess);
  free(known);

  return 0;
}

