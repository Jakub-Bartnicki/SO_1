#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int checkLastSymbol(char array[]) {
    char c = '&';

    if (array[strlen(array) - 1]) {
        printf("%s", "It works\n");
        return 0;
    } else {
        printf("%s", "Error\n");
        return 1;
    }
}

int main(int argc, const char* argv[]) {

    int i, sum = 0;
    char option[200];
    int currChar = 0;

    if (argc > 1) {
        printf("Unnecessary arguments have been ignored\n");
    }

    while (1) {
        char readed[200];
        char x;

        // TODO: Poprawić, cos nie tak z getc
        // if (x = getc(stdin) == '\033' || x == '\033') { 
        // getc
        //     switch(x) {
        //         case 'A':
        //             system("history-search-backward");
        //             break;
        //         case 'B':
        //             system("hitory-search-forward");
        //             break;
        //     } 
        // } else { 

        gets(readed);

        strcpy(option, readed);
        if (strcmp(option, "history") != 0 && strcmp(option, "help") != 0 && strcmp(option, "exit") != 0) {
            strtok(option, " ");
        }

        if (!(strcmp(option, "exit"))) {
            printf("%s", "exitting...\n");
            exit(0);
        } else if (!(strcmp(option, "sum"))) {
            checkLastSymbol(option);
            char command[202];  
            strcpy(command, "./");
            strcat(command, readed);

            printf("command: %s\n", command);

            system(command);
        } else if (!(strcmp(option, ""))) {

        } else if (!(strcmp(option, ""))) {
            // TODO: Klikanie strzałki w gore daje poprzednia komende

        } else if (!(strcmp(option, ""))) {
            

        } else if (!(strcmp(option, "history"))) {
            // TODO: Wyswietlanie historii

        } else if (!(strcmp(option, "help"))) {
            puts("\nhelp - show this help list\n"                       \
            "sum [x y z ...] - sum 2 (or more) numbers\n"               \
            "history - show history of commands\n"                      \
            "exit - exit this interpreter\n");        
        } else {
            printf("%s", "Choose another option");
        }

    }
    return 0;
}
