#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int checkLastSymbol(char array[]) {
    char c = '&';

    if (array[strlen(array) - 1]) {
        printf("%s", "It works");
        return 0;
    } else {
        printf("%s", "Error");
        return 1;
    }
}

int main(int argc, const char* argv[]) {

    int i, sum = 0;
    char option[200];

    // if (argc == 1) {
    //     printf("Please provide the command line arguments\n");
    // }

    while (1) {
        getchar();

        fgets(option, 200, stdin);
        puts(option);
        printf("%d\n", strcmp(option, "exit"));

        if (strcmp(option, "exit")) {
            printf("%s", "exitting...\n");
            exit(0);
        } else if (strcmp(option, "sum")) {
            checkLastSymbol(option);

            static char *argvx[]={"sum","5", "6"};
            execv("./", argvx);
        } else {
            exit(1);
        }
    }

    return 0;
}
