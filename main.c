#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
# define BUFFER_SIZE 8192

// In the stringToLower function, I define a function that converts the given word into the lowercase letters.
void stringToLower(char *str) {
	while (*str != '\0') {
		*str = tolower((unsigned char)*str);
		str++;
	}
}

// In the isWord function, I checked if c is whitespace or punctuation or null.
bool isWord(char c){
  	return isspace((unsigned char)c) || ispunct((unsigned char)c) || c == '\0';
}

// In the wordCount function, I checked if the given word is in the line or not.
int wordCount(char *line, char *word){
	int count = 0;
	char *ptr = line;
	stringToLower(ptr);
	while ((ptr = strstr(ptr, word)) != NULL) {
		if (((isWord(*(ptr-1))) && isWord(*(ptr + strlen(word))))) {
	 		++count;
		}
		++ptr;	
	}	
	return count;
}

// In the main part, I asked the word and checked it for all lines in the txt file by calling wordCount function.
int main() {
	FILE *file = fopen("preprocessed_dataset.txt", "r");
	char word[BUFFER_SIZE];
	printf("Please enter a word to search for: ");
	fgets(word, BUFFER_SIZE, stdin);
	word[strcspn(word, "\n")] = 0;
	stringToLower(word);
	char line[BUFFER_SIZE];
	int spamCount = 0;
	int nonSpamCount = 0;

	while (fgets(line, sizeof(line), file) != NULL) {
		if (strncmp(line, "spam", 4) == 0) {
			spamCount += wordCount(line, word);
		}
		else if (strncmp(line, "ham", 3) == 0) {
			nonSpamCount += wordCount(line,word);
		}
	}
 	if ((nonSpamCount == 0)	&& (spamCount == 0)){
		char message[] = "This word doesn't occur in the text! \n";
		printf("%s", message);
	}
	else {
		printf("The word '%s' appears %d times in ham messages and %d times in spam messages. \n", word, nonSpamCount, spamCount);
	}
	fclose(file);
	return 0;
}
	
