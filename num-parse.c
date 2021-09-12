#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// parses a given number and checks if it is valid or invalid
bool parse_num(const char* string) {
	size_t i=0;
	/* d_count is the amount of times the '.' exists
	   pm_count is the amount of times the '+' and '-' exists
	   if any of the following symbols occurs more than once
	   then the given number is invalid
	*/
	int d_count = 0, pm_count = 0;
	while(string[i]) {
		if(isdigit(string[i])) {
			// reads digits in the string until it encounters a character which is not a digit
			while(isdigit(string[i])) {
				i++;
			}
			i--;
		} else if(string[i]  == '.') {
			// the previous character so we can know if the previous one has a digit or not
			char prev = string[i-1];
			/* reads the decimal point until it encounters a character which is not a decimal point increments the d_count variable
			   by 1 if the d_count variable is greater than 1 the number is invalid returns false.
			*/
			while(string[i] == '.') {
				d_count++; i++;
				if(d_count > 1) return false;
			}
			// checks if the next character is not a digit and the previous character before . is not a digit returns false
			if(!isdigit(string[i])) {
				if(!isdigit(prev)) {
					return false;
				}
			}
			i--;
		} else if(string[i] == '+' || string[i] == '-') {
			// read the + or - until it encounters a character which is not + or -
			// if pm_count is greater than 1 returns false
			while(string[i] == '+' || string[i] == '-') {
				pm_count++; i++;
				if(pm_count > 1) return false;
			}
			bool expr = string[i] == '.' || isdigit(string[i]);
			if(!expr) return false;
			i--;
		} else {
			return false;
		}
		i++;
	}
	if(i == 0) return false;
	return true;
}

char* input(const char* prompt) {
	char c, *buff = calloc(1, sizeof(char*));
	size_t size=0;
	printf("%s", prompt);
	while((c = fgetc(stdin))) {
		if(c == '\n') break;
		buff[size++] = c;
		char* temp = buff;
		buff = calloc(size+1, sizeof(char*));
		strcpy(buff, temp);
		free(temp);
	}
	return buff;
}

int main() {
	while(1) {
		char* number = input("Enter a number to parse: ");
		if(parse_num(number)) {
			printf("%s is a number.\n", number);
		} else {
			printf("%s is not a number.\n", number);
		}
		free(number);
	}
	return 0;
}
