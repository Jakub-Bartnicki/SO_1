#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
int licznik=0;
void* napis (void *arguments)
{
  	int index = *((int *)arguments);
	int k = rand () % 10001;
	int j;
	for (j=0; j<k; j++)
	{
		printf ("Wątek %d iteracja %d\n", index, j);
		licznik++;
	}
}
int main (void)
{
	srand((unsigned int)time(NULL));
	pthread_t watki[10];
	int watki_args[10];
	int i;
	int result_code;
	for (i=0; i<10; i++)
	{
		watki_args[i] = i;
		result_code = pthread_create (&watki[i], NULL, napis, &watki_args[i]);
		assert(!result_code);
	}
	for (i=0; i<10; i++)
	{
		result_code = pthread_join (watki[i], NULL);
		assert (!result_code);
	}
	printf ("Liczba wszystkich iteracji wywolanej przez wszysktie wątki: %d\n", licznik);
	return 0;
}
