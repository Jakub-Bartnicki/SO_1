#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)
int licznik=0;
void* napis (int numer)
{
	int pom=0, k, j;
	k = rand () % 10001;
	for (j=0; j<k; j++)
	{
		printf ("Wątek %d iteracja %d\n", numer+1, j);
		licznik++;
	}
}
int main (void)
{
	srand((unsigned int)time(NULL));
	int i;
	pthread_t watki[10];
	for (i=0; i<10; i++)
	{
		errno =  pthread_create(&watki[i], NULL, napis(i), NULL)
		test_errno ("Failed pthread_create");
	}
	for (i=0; i<10; i++)
	{
		errno = pthread_join (watki[i], NULL);
		test_errno ("pthread_join");
	
	}
	printf ("Liczba wszystkich iteracji wywolanej przez wszysktie wątki: %d\n", licznik);
	return 0;
}
