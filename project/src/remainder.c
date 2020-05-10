#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Polecenie wypisujące resztę z dzielenia dwóch liczb (argv[1] % argv[2])
int main(int argc, const char* argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if (argc != 3) {
        perror("Please add 2 command line arguments");
        return 0;
    }
    
	printf("%d\n", a % b);
    
    return 0;
}
