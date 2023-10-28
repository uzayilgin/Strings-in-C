#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
# define BUFFER_SIZE 16384

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
int isLine(char *line, char *word){
	int count = 0;
	char *ptr = line;
	stringToLower(ptr);
	while ((ptr = strstr(ptr, word)) != NULL) {
		if ((ptr == line || isWord(*(ptr-1))) && isWord(*(ptr + strlen(word)))) {
	 		++count;
		}
		++ptr;	
	}	
	return count;
}

// In the main part of the task1, I asked the word and checked it for all lines in the txt file by calling wordCount function.
int task1() {
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
			spamCount += isLine(line, word);
		}
		else if (strncmp(line, "ham", 3) == 0) {
			nonSpamCount += isLine(line,word);
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
// I created a struct to keep a count of unique words and their occurances.
struct WordCount {
	char word[BUFFER_SIZE];
	int count;
};
// I created an array to keep a count of unique words.
struct WordCount wordArray[BUFFER_SIZE];
int wordCount = 0;
int i;

// findWord function checks that given *word is in the wordArray if so gives its index.
int findWord(char *word) {
	for (i=0; i < wordCount; ++i) {
		if (strcmp(wordArray[i].word, word) == 0) {
			return i;
		}
	}
	return -1;
}

// I created a sorting funciton in order to display result in descending order.
void sort(struct WordCount array[], int n) {
	int i;
	int j;
	for(i=0; i < n; ++i) {
		int max = i;
		for(j = i+1; j < n; ++j) {
			if(array[j].count > array[max].count) {
				max = j;
			}
		}
		struct WordCount temp = array[i];
		array[i] = array[max];
		array[max] = temp;
	}
}

// In the main part of the task2, I checked all words in the spam lines. If the word is added the array before I increase the occurance of it, else if it has not added the list before, I add the list and increase its occurance. Lastly, I print the requested output.
int task2(){
	FILE *file = fopen("preprocessed_dataset.txt", "r");
	char line[BUFFER_SIZE];
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "spam", 4) == 0) {	
			char *word = strtok(line + 5, " ,.-!?()\n");
			while (word) {					
				word[strcspn(word, "\n")] = 0;
				stringToLower(word);
				int index = findWord(word);
				if (index != -1) {
					wordArray[index].count ++;
				}
				else{
					strcpy(wordArray[wordCount].word, word);
					wordArray[wordCount].count = 1;
					++wordCount;
				}
				word = strtok(NULL, " ,.-!?()\n");
			}
		}
	}
	fclose(file);
	sort(wordArray, wordCount);
	printf("Top 10 occuring words in spam messages: \n");
	int j;
	for (j=0; j < 10 && j < wordCount; ++j) {
		printf("%s: %d times\n", wordArray[j].word, wordArray[j].count);
	}
	return 0;
	}


int main() {
	task1();
	task2();
}
