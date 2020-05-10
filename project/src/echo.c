#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Polecenie wypisujące na standardowym wyjściu podane argumenty (argv[>0])
int main(int argc, const char* argv[]) {
    int i;
    if (argc == 1) perror("Add command line arguments");
    for (i = 1; i < argc; i++) printf("%s ", argv[i]);
    
    putchar('\n');
    return 0;
}
