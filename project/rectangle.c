#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Polecenie "rysujące" prostokąt o podanych wymiarach (wysokość: argv[1], szerokość: argv[2])
int main(int argc, const char* argv[]) {
    if (argc != 3) {
    	perror("Please add 2 command line arguments");
    	return 0;
	}

	int i, j;
	int high = atoi(argv[1]);
	int width = atoi(argv[2]);

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) printf("*");
		printf("\n");
	}

    return 0;
}
