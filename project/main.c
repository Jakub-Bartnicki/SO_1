#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h> 
#include <signal.h>
#include "src/history.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define INPUT_MAX_LENGTH 200
#define RUN_PATH "./"

// obsługa sygnału - wypisuje historię
void handleSigint(int sig) { 
    showHistory();
}

// funkcja wypisująca znak '>' oraz wczytująca linijkę tekstu z terminala, wartość zwracana do tablicy znaków text
static int getLine (char sign, char *text, size_t textSize) {
    char character;

    if (sign != '\0') putchar(sign);

    if (strlen(fgets(text, textSize + 1, stdin)) <= 1) return NO_INPUT;

    if (text[strlen(text) - 1] != '\n') 
        while (((getchar()) != '\n') && (character != EOF)) return TOO_LONG;
    
    text[strlen(text) - 1] = '\0';
    return OK;
}

// funkcja usuwająca spacje na początku tablicy znaków text podanej jako argument
char* removeSpaces(char* text) {
    char* string = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));
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

// funkcja sprawdzająca liczbę powtórzeń znaku '|' w podanej tablicy znaków i zwracająca tę liczbę
int checkSignAmount(char* readed)
{
	int counter;
	int signAmount = 0;
	for (counter = 0; readed[counter] != '\0'; counter++) {
	    if (readed[counter] == '|') signAmount++;
    }

	return signAmount;
}

// funkcja sprawdzająca czy podana tablica znaków jest literą, zwraca True/False
bool isLetter(char character) {
    return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

// funkcja sprawdzająca czy podane argumenty są identyczne, zwraca True/False
bool checkInput(char* option, char* input) {
    return !(strcmp(option, input));
}

// funkcja tworząca i zwracająca gotowe polecenie do wykonania na podstawie podanej tablicy znaków
char* createCommand(char* readedCommand) {
    char* command = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));
    strcpy(command, RUN_PATH);
    strcat(command, removeSpaces(readedCommand));
    return command;
}

// funkcja uruchamiająca podaną w argumentach komendę
void runCommand(char* command) {
    if (system(createCommand(command))) perror("Command not found");
}

// funkcja zamykająca interpreter
void exitProgram() {
    puts("exitting...");
    exit(0);
}

// funkcja oddzielająca polecenia oddzielone znakiem '|', wywołaniem funkcji runCommand uruchamia te polecenia oddzielnie
void connectStreams(char* readed) {
    int partcount = checkSignAmount(readed) + 1;
    char *foundPipe, *newReaded;
    int i, j;

    newReaded = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));
    strcpy(newReaded, readed);

    char** commandArray = (char**) malloc(INPUT_MAX_LENGTH * sizeof(char));
    for (i = 0; i < partcount; i++) 
        commandArray[i] = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));

    for(i = 0; (foundPipe = strsep(&newReaded, "|")) != NULL; i++) 
        strcpy(commandArray[i], foundPipe);
    
    for(i = 0; i < partcount; i++) {
        char* command, *exitCommand;
        command = createCommand(commandArray[i]);

        exitCommand = commandArray[i];
        strtok(exitCommand, " ");
        if (checkInput(removeSpaces(exitCommand), "exit")) exitProgram();

        runCommand(command);
        free(exitCommand);
        free(command);
    }

    free(foundPipe);
    free(newReaded);
    free(commandArray);
}

// funkcja, która ma za zadanie sprawdzać czy podana funkcja występuje w liście dostępnych poleceń
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

// funkcja, w której wczytana zostaje komenda poprzez getLine(), i wydawane są polecenia uruchamiania poleceń i dodawania ich do historii poleceń
void readCommand(ListElement_type **headOfHistoryList, char* option, char* readed) {
    readed = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));

    int inputStatus = getLine('>', readed, INPUT_MAX_LENGTH * sizeof(char));

    if (inputStatus == NO_INPUT) return;
    if (inputStatus == TOO_LONG) {
        perror("Input is too long.");
        return;
    }

    option = (char*) malloc(INPUT_MAX_LENGTH * sizeof(char));
    strcpy(option, readed);
    if (!checkInput(option, "history") && !checkInput(option, "help") && !checkInput(option, "exit")) 
        strtok(option, " ");

    strcpy(readed, removeSpaces(readed));

    if (checkSignAmount(readed) > 0) connectStreams(readed);
    else chooseOption(option, readed);

    addHistoryElement(&(*headOfHistoryList), readed);

    free(option);
    free(readed);
}

//funkcja główna programu, służy głównie do deklaracji najważniejszych zmiennych i uruchamianiu pętli z poleceniem readCommand
int main(int argc, const char* argv[]) {
    ListElement_type** headOfHistoryList = (ListElement_type**) malloc(sizeof(ListElement_type*));
    char* option;
    char* readed;

    if (argc > 1) perror("Unnecessary arguments have been ignored");

    signal(SIGINT, handleSigint);

    while (1) {
        readCommand(headOfHistoryList, option, readed);
    }

    free(headOfHistoryList);
    return 0;
}
