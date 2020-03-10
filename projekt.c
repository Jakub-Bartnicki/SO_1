#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	char copy[100], source[100], goal[100];
	int size, size_h;
	FILE *file1, *file2;

	printf ("Kopiuj, zrodlo, cel, rozmiar\n");
	scanf ("%s %s %s %d", copy, source, goal, &size);

	char buf[size];

	//sprawdzic czy source konczyc sie na '/'
	strcat(source, goal);

	file1 = fopen (copy, "r");
	file2 = fopen (source, "a+");
	if( file1 == NULL || file2 == NULL )
	{
		printf ("Nie mozna otworzyc pliku do oczytu");
		exit(1);
	}

	while( !feof(file1))
	{
		fread((void *) buf, size, 1, file1);
		//buf[size-1] = '\0';
		printf("%d", size_h);
		fwrite((void *) buf, size, 1, file2);
	}

	fclose(file1);
	fclose(file2);

	return 0;
}
