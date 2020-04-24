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

    // if (argc == 1) {
    //     printf("Please provide the command line arguments\n");
    // }

    while (1) {
        char readed[200];

        fgets(readed, 200, stdin);

        strcpy(option, readed);
        strtok(option, " ");

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
        } else if (!(strcmp(option, "history"))) {

        } else if (!(strcmp(option, "help"))) {

        } else {
            printf("%s", "Choose another option");
        }

        getchar();
    }

    return 0;
}
