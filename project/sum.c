#include <stdlib.h>
#include <stdio.h>

#define typename(x) _Generic((x), int: "int")

int main(int argc, const char* argv[]) {
    
    int i, sum = 0;
    char* type;

    if (argc == 1) {
        printf("%s", "Please provide the command line arguments\n");
    }

    for (i = 1; i < argc; i++) {
        typeof(argv[i]) type = argv[i];
        printf("%s\n", type);

        sum += atoi(argv[i]);
        getchar();
    }

    printf("%d\n", sum);
    
    return 0;
}