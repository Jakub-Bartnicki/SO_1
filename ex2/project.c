#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
	char copy[100], source[100];
	int size, size_h = 1, actual = 0;
	int file1, file2;

	printf ("Kopiuj, zrodlo rozmiar\n");
	scanf ("%s %s %s %d", copy, source &size);

	char buf[size];

	file1 = open(copy, O_RDONLY);
	file2 = open(source, O_CREAT | O_WRONLY);
	if( file1 < 0 || file2 < 0 )
	{
		printf ("Nie mozna otworzyc pliku do oczytu");
		exit(1);
	}

	size_h = read(actual, buf, size);
    printf("%d", size_h);
    write(file2, buf, size_h);

	close(file1);
	close(file2);

	return 0;
}
