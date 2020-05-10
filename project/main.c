#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h> 
#include <signal.h>
#include "history.h"

// #define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define INPUT_MAX_LENGTH 200
#define RUN_PATH "./"

void handleSigint(int sig) { 
    showHistory();
}

static int getLine (char sign, char *text, size_t textSize) {
    char character;

    if (sign != '\0') putchar(sign);

    if (strlen(fgets(text, textSize + 1, stdin)) <= 1) return NO_INPUT;

    if (text[strlen(text) - 1] != '\n') {
        while (((getchar()) != '\n') && (character != EOF)) return TOO_LONG;
    }

    text[strlen(text) - 1] = '\0';
    return OK;
}

char* removeSpaces(char* text) {
    char* string = (char*) malloc(INPUT_MAX_LENGTH);
    int i, j = 0;

    strcpy(string, text);

    for(i=0; string[i]==' ' || string[i]=='\t'; i++);
 
	for(j=0; string[i]; i++)
	{
		string[j++] = string[i];
	}
	string[j]='\0';
	for(i=0; string[i] != '\0'; i++)
	{
		if(string[i] != ' ' && string[i] != '\t')
				j = i;
	}
	string[j+1] = '\0';

    return string;
}

int check(char* array)
{
	const char znak = '|';
	int licznik;
	int licznik2 = 0;
	for(licznik = 0; array[licznik]!='\0'; licznik++){
	    if(array[licznik]==znak) licznik2++;
    }

	return licznik2;
}

bool isLetter(char character) {
    return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

bool checkInput(char* option, char* input) {
    return !(strcmp(option, input));
}

char* createCommand(char* readedCommand) {
    char* command = (char*) malloc(INPUT_MAX_LENGTH);
    strcpy(command, RUN_PATH);
    strcat(command, removeSpaces(readedCommand));
    return command;
}

void runCommand(char* command) {
    system(createCommand(command));
}

void exitProgram() {
    puts("exitting...");
    exit(0);
}

void connectStreams(char* readed) {
    int partcount = check(readed) + 1;
        char *foundPipe, *newReaded;
        int i, j;

        newReaded = (char*) malloc(sizeof(char) * INPUT_MAX_LENGTH);
        strcpy(newReaded, readed);

        char** commandArray = (char**) malloc(INPUT_MAX_LENGTH * sizeof(char*));
        for (i = 0; i < partcount; i++) 
            commandArray[i] = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));

        for(i = 0; (foundPipe = strsep(&newReaded,"|")) != NULL; i++) 
            strcpy(commandArray[i], foundPipe);
        
        for(i = 0; i < partcount; i++) {
            char* command, *exitCommand;
            command = createCommand(commandArray[i]);

            exitCommand = commandArray[i];
            strtok(exitCommand, " ");
            if (checkInput(removeSpaces(exitCommand), "exit")) exitProgram();

            runCommand(command);
            free(command);
        }

        free(commandArray);
}

void chooseOption(char* option, char* readed) {
    if (checkInput(option, "exit")) exitProgram();
    else if (checkInput(option, "sum")) runCommand(readed);
    else if (checkInput(option, "counter")) runCommand(readed);
    else if (checkInput(option, "help")) runCommand(readed);
    else if (checkInput(option, "rectangle")) runCommand(readed);
    else if (checkInput(option, "remainder")) runCommand(readed);
    else if (checkInput(option, "echo")) runCommand(readed);
    else printf("%s: command not found\n", readed);
}

void readCommand(ListElement_type **headOfHistoryList, char* option, char* readed) {
    readed = (char*) malloc(INPUT_MAX_LENGTH);

    int inputStatus = getLine('>', readed, INPUT_MAX_LENGTH);

    if (inputStatus == NO_INPUT) return;
    if (inputStatus == TOO_LONG) {
        perror("Input is too long.");
        return;
    }

    option = (char*) malloc(INPUT_MAX_LENGTH);
    strcpy(option, readed);
    if (!checkInput(option, "history") && !checkInput(option, "help") && !checkInput(option, "exit")) 
        strtok(option, " ");

    strcpy(readed, removeSpaces(readed));

    if (check(readed) > 0) connectStreams(readed);
    else chooseOption(option, readed);

    addHistoryElement(&(*headOfHistoryList), readed);

    free(option);
    free(readed);
}

int main(int argc, const char* argv[]) {
    char* option;
    char* readed;
    ListElement_type** headOfHistoryList = (ListElement_type**) malloc(sizeof(ListElement_type*));

    if (argc > 1) puts("Unnecessary arguments have been ignored");

    signal(SIGINT, handleSigint);
    while (1) {
        readCommand(headOfHistoryList, option, readed);
    }
    return 0;
}

// dodanie wątkow - wykonywanie w tle       &
// laczenie polecen                         |
