#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void touch(char *zrodlo, char *cel)
// {
// 	char *path;
// 	path = (char*) malloc (300 * sizeof (char));
// 	strcpy(path, "touch ");
// 	strcat(path, cel);
// 	strcat(path, " ");
// 	strcat(path, zrodlo);
// 	system(path);
// }


// void kopiowanie (FILE *plik1, FILE *plik2, int rozmiar, int aktualny)
// {	

// }

int main (int argc, char *argv[])
{
	char *copy, *source, *goal;
	int size;
	FILE *file1, *file2;
	copy = (char*) malloc (100 * sizeof (char));
	source = (char*) malloc (100 * sizeof (char));
	goal = (char*) malloc (100 * sizeof (char));

	printf ("Kopiuj, zrodlo, cel, rozmiar\n");
	scanf ("%s %s %s %d", copy, source, goal, &size);

	strcat(source, goal);
	file1 = fopen (copy, "r");
	file2 = fopen (source, "a+");
	if( file1 == NULL)
	{
		printf ("Nie mozna otworzyc pliku do oczytu");
		exit(1);
	}
	if( file2 == NULL)
	{
		printf ("Nie mozna otworzyc pliku do oczytu");
		exit(1);
	}

	size  = size - size % 4;
	void *ptr = (char*) malloc (sizeof(file1));


	fread(ptr, size, size/sizeof(char), file1);
	printf("%s", ptr);
	fwrite(ptr, size, 1, file2);

	fclose(file1);
	fclose(file2);
	free (copy);
	free (source);
	free (goal);

	return 0;
}
