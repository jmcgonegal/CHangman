/* Title: Hangman
 * Date: 9/9/2008
 * Description: Text based version of the popular game. Be sure to populate the dictionary with words before playing.
 * Version: 2008090901
 * Senior Programmer: John McGonegal
 * Programmer: Daniel Topar 
 * Programmer: Mark Camacho
 * Programmer: Christian Boyd
 */

#include <stdio.h>
#include <string.h>
#include <system.h>
#include <stdlib.h>

#define MAX_WRONG 6
#define NUMWORDS 50

void drawHangman(int); // christian
void drawGame(char*,char*,int); // john
int checkForWin(char*,char*); // john
char promptHangmanGuess(char*,int); // daniel
int checkHangmanGuess(char*,char); // daniel
char* getHangmanWord(FILE*,int); // mark

void main() // john
{
	FILE *fp;
	char* hangman_word;
	int wrongAnswers = 0;
	int guesses = 0;
	int win = 0;
	char used_letters[255];
	int i;
	int random;
	
	// seed random number
	srand(time());
	random = (rand() % NUMWORDS) +1;
	
	// wow fopen/fscanf/fread doesnt work in a function?
	fp = fopen("hangman.txt","r");
	
	// read in lines until we get the random one we want
	for(i=0;i<random;i++)
	{
		// read line
		fscanf(fp,"%s\n",hangman_word);
	}
	
	//hangman_word = getHangmanWord(fp,random);
	fclose(fp);
	
	// setup array with blanks
	for(i=0;i<26;i++)
	{
		used_letters[i] = ' ';
	}

	

	// play the game until we get too many incorrect guesses or we win
	while(wrongAnswers <= MAX_WRONG && win == 0) {
		// clear screen
		clrscr();
		
		// draw game
		drawHangman(wrongAnswers);
		drawGame(used_letters,hangman_word,guesses);
		
		// get user input
		used_letters[guesses] = promptHangmanGuess(used_letters,guesses);
		
		// win check
		win = checkForWin(used_letters,hangman_word);
		
		// did the get a wrong answer?
		if(!checkHangmanGuess(hangman_word,used_letters[guesses]))
		{
			wrongAnswers++;
		}
				
		// increment count
		guesses++;
	}
	
	// print game ending
	clrscr();
	drawHangman(wrongAnswers);
	drawGame(used_letters,hangman_word,guesses);
	if(win == 1)
	{

		printf("You win! ");
	}
	else
	{

		printf("You lose! ");
	}
	printf("The word was %s",hangman_word);
}

int checkHangmanGuess(char* word, char input)
{
	int match = 0;
	int i;
	// check every letter in the word to see if the guess matches
	for(i = 0; i<strlen(word); i++) {
		if(word[i] == input) match = 1;
	}
	return match;

}
char promptHangmanGuess(char* guesses, int guess_count)
{
     	char input;
      	int count;
      	int fail = 0;
      	printf("Guess a letter: ");
      	// loop forever
       	while(1==1)
       	{
		scanf("%c",&input);
		if(input >= 'a' && input <= 'z')
		{
			// buggy and not needed
			/*for(count=0; count < guess_count; count++)
			{
				// we already guessed that
				if(input == guesses[count])
				{
					fail = 1;
				}
			}
			if( fail == 0)
			{*/
				// valid input, quit looping
				return input;
			/*}
			else {
                       		printf("You already guessed that. ");
			}*/
		}
		else if(input == '\n')
		{
			// do nothing for newline
		}
		else {
                       	printf("Invalid input. ");
		}
	}
}


void drawGame(char* used_letters,char* word,int numGuess) {
	int i, j;
	char match;
	
	printf("You've used: ");
	for(i = 0; i<numGuess; i++) {
		printf("%c ",used_letters[i]);
	}
	
	
	printf("\nHangman: ",);
	// print hidden word
	for(i = 0; i<strlen(word); i++) {
		match = '_';
		for(j = 0; j<numGuess; j++) {
			if(word[i] == used_letters[j]) {
				match = used_letters[j];
			}
		}
		printf("%c ",match);
	}
	printf("\n");
}

int checkForWin(char* letters, char* word) {
	int i, j;
	int match;
	// every guessed letter should equal a letter in word
	for(i = 0; i<strlen(word); i++) {
		match = checkHangmanGuess(letters,word[i]);

		// letter from word was not found in guesses
		if(match!=1)
		{
			return 0;
		}
	}
	
	// all the letters match
	return 1;
	
}
/* // disabled because file reading doesnt work in functions, code moved to main
char* getHangmanWord(FILE *fp,int line)
{
	char* word;
	int i;


		// read in lines until we get the one we want
		for(i=0;i<=line;i++)
		{
			// read line
			fscanf(fp,"%s\n",word);
			printf("x%sx",word);
		}
		

	return word;
}
*/

// draw the hangman on screen
 void drawHangman(int wrongAnswers) {
 /* ______
 * | |
 * o |
 * \|/ |
 * | |
 * / \ |
 * ___|___
 * 6 wrong answers (head, body, left arm, right arm, left leg, right leg)
 */
 
	if(wrongAnswers == 0)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("         |\n");
	      printf("         |\n");
	      printf("         |\n");
	      printf("         |\n");
	      printf("      ___|___\n");
 
	}

	else if(wrongAnswers == 1)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf("         |\n");
	      printf("         |\n");
	      printf("         |\n");
	      printf("      ___|___\n");
 
	}
	else if(wrongAnswers == 2)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf("  |      |\n");
	      printf("  |      |\n");
	      printf("         |\n");
	      printf("      ___|___\n");
 
	}
	else if(wrongAnswers == 3)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf(" \\|      |\n");
	      printf("  |      |\n");
	      printf("         |\n");
	      printf("      ___|___\n");
 
	}
	else if(wrongAnswers == 4)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf(" \\|/     |\n");
	      printf("  |      |\n");
	      printf("         |\n");
	      printf("      ___|___\n");
 
	}

	else if(wrongAnswers == 5)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf(" \\|/     |\n");
	      printf("  |      |\n");
	      printf(" /       |\n");
	      printf("      ___|___\n");
 
	}
 
	else if (wrongAnswers == 6)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf(" \\|/     |\n");
	      printf("  |      |\n");
	      printf(" / \\     |\n");
	      printf("      ___|___\n");
 
	}
	else if (wrongAnswers == 7)
	{
	      printf("  _______\n");
	      printf("  |      |\n");
	      printf("  o      |\n");
	      printf("         |\n");
	      printf(" \\|/     |\n");
	      printf("  |      |\n");
	      printf(" / \\  ___|___\n");
 
	}

	 // draw hangman art based on wronganswers
	 printf("You have %d wrong answers\n",wrongAnswers);
 }