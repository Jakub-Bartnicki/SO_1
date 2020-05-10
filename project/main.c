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
#define PATH "./"

void handle_sigint(int sig) 
{ 
    if (fork() == 0) showHistory();
    else putchar('>');
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

bool isLetter(char character) {
    return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

bool checkInput(char* option, char* input) {
    return !(strcmp(option, input));
}

char* createCommand(char* readedCommand) {
    char* command = (char*) malloc(INPUT_MAX_LENGTH);
    strcpy(command, PATH);
    strcat(command, readedCommand);
    return command;
}

void runCommand(char* command) {
    system(createCommand(command));
}

void exitProgram() {
    puts("exitting...");
    exit(0);
}

void choseOption(ListElement_type **headOfHistoryList, char* option, char* readed) {
    if (checkInput(option, "exit")) exitProgram();
    else if (checkInput(option, "sum")) runCommand(readed);
    else if (checkInput(option, "counter")) runCommand(readed);
    // else if (checkInput(option, "history")) showHistory(headOfHistoryList);
    else if (checkInput(option, "help")) runCommand(readed);
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

    choseOption(headOfHistoryList, option, readed);

    addHistoryElement(&(*headOfHistoryList), readed);

    free(option);
    free(readed);
}

int main(int argc, const char* argv[]) {
    char* option;
    char* readed;
    ListElement_type** headOfHistoryList = (ListElement_type**) malloc(sizeof(ListElement_type*));

    if (argc > 1) puts("Unnecessary arguments have been ignored");

    signal(SIGINT, handle_sigint);
    while (1) {
        readCommand(headOfHistoryList, option, readed);
    }
    return 0;
}

// dodanie wątkow - wykonywanie w tle       &
// laczenie polecen                         |
// oddzielny program do historii            >>


// void checkLastSymbol(char array[]) {
//     char ch = '&';
//     if (array[strlen(array) - 1] == c) puts("It works");
//     else puts("Error");
// }
