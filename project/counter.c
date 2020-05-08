#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    

    if ((argc > 3 && strcmp(argv[argc - 1], "&")) || (argc == 1 || argc > 2)) {
        printf("%s", "Please provide the command line 1 argument\n");
        return 0;
    } 

    int number = atoi(argv[1]);
    // if (argv[argc - 1] == "&") {
        while (number > 0) {
            printf("%d\n", number);
            sleep(1);
            number--;
        }
    // }
    return 0;
}