#include <stdlib.h>
#include <stdio.h>

#define typename(x) _Generic((x), int: "int")

// Polecenie wypisujące sumę podanych argumentów (argv[>1])
int main(int argc, const char* argv[]) {
    
    int i, sum = 0;
    char* type;

    if (argc == 1) {
        perror("Please provide the command line arguments");
    }

    for (i = 1; i < argc; i++) {
        typeof(argv[i]) type = argv[i];
        
        sum += atoi(argv[i]);
    }

    printf("%d\n", sum);
    
    return 0;
}