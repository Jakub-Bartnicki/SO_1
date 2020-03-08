#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void touch(char *zrodlo, char *cel)
{
	char *path;
	path = (char*) malloc (300 * sizeof (char));
	strcpy(path, "touch ");
	strcat(path, cel);
	strcat(path, " ");
	strcat(path, zrodlo);
	system(path);
}
void kopiowanie (char *kopiuj, char* zrodlo, char *cel, char *tablica)
{
	FILE *plik;
	if(plik = fopen ("plik1.txt", "r")==NULL)
	{
	printf ("Nie mozna otworzyc pliku do oczytu");
	exit(1);
	}
	
}



int main (int argc, char *argv[])
{
	char *copy, *source, *goal, *pom;
	int size;
	copy = (char*) malloc (100 * sizeof (char));
	source = (char*) malloc (100 * sizeof (char));
	goal = (char*) malloc (100 * sizeof (char));
	printf ("Kopiuj, zrodlo, cel, rozmiar\n");
	scanf ("%s %s %s %d", copy, source, goal, &size);
	pom = (char*) malloc (size * sizeof (char));
	touch (source, goal);

	return 0;
}
