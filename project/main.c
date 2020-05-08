#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h> 

// #define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define INPUT_MAX_LENGTH 200
#define PATH "./"

typedef struct ListElement {
    char* data;
    struct ListElement * next;

} ListElement_type;

// pthread_mutex_t accum_mutex = PTHREAD_MUTEX_INITIALIZER;

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

void showHistory(ListElement_type *headOfHistoryList) {
    if(headOfHistoryList == NULL) {
        puts("List is empty");
        return;
    }

    ListElement_type *current = headOfHistoryList;
    int i = 1;

    do {
        printf("%d. %s\n", i++, current->data);
        current = current->next;
    } while (current != NULL);
}

int historySize(ListElement_type *headOfHistoryList)
{
    int counter = 0;
    if (headOfHistoryList == NULL) return counter;
    else {
        ListElement_type *current = headOfHistoryList;
            do {
            counter++;
            current = current->next;
            } while (current != NULL);
    }
    return counter;
}
	
void addHistoryElement(ListElement_type **headOfHistoryList, char* text)
{	

	if(*headOfHistoryList == NULL) {
		*headOfHistoryList = (ListElement_type *) malloc(sizeof(ListElement_type));
        (*headOfHistoryList)->data = (char*) malloc(INPUT_MAX_LENGTH);
   		strcpy((*headOfHistoryList)->data, text);
    	(*headOfHistoryList)->next = NULL;
	} else {
        if (historySize(*headOfHistoryList) >= 20) {
            ListElement_type * newListHead = NULL;
 
            newListHead = (*headOfHistoryList)->next;
            free(*headOfHistoryList);
            *headOfHistoryList = newListHead;	
        }
		ListElement_type *current = *headOfHistoryList;
	
	    while (current->next != NULL) {
	        current = current->next;
	    }

	    current->next = (ListElement_type * )malloc(sizeof(ListElement_type));
        current->next->data = (char*) malloc(INPUT_MAX_LENGTH);
	    strcpy(current->next->data, text);
	    current->next->next = NULL;	
	}
}

void readCommand(ListElement_type **headOfHistoryList, char* option, char* readed) {
    readed = (char*) malloc(INPUT_MAX_LENGTH);

    int inputStatus = getLine('>', readed, INPUT_MAX_LENGTH);

    if (inputStatus == NO_INPUT) return;
    if (inputStatus == TOO_LONG) {
        puts("Input is too long.");
        return;
    }

    option = (char*) malloc(INPUT_MAX_LENGTH);
    strcpy(option, readed);
    if (!checkInput(option, "history") && !checkInput(option, "help") && !checkInput(option, "exit")) 
        strtok(option, " ");

    if (checkInput(option, "exit")) exitProgram();
    else if (checkInput(option, "sum")) runCommand(readed);
    else if (checkInput(option, "counter")) runCommand(readed);
    else if (checkInput(option, "history")) showHistory(*headOfHistoryList);
    else if (checkInput(option, "help")) runCommand(readed);
    else printf("%s: command not found\n", readed);

    addHistoryElement(&*headOfHistoryList, readed); 
    free(option);
    free(readed);
}

int main(int argc, const char* argv[]) {
    char* option;
    char* readed;
    ListElement_type *headOfHistoryList = NULL;

    if (argc > 1) puts("Unnecessary arguments have been ignored");

    while (1) {
        readCommand(&headOfHistoryList, option, readed);
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
