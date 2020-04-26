#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
typedef struct Lista {
	char nazwa[200];
	struct Lista *next;
}Lista_type;
void show (Lista_type *head)
{
	printf ("\n");
	if (head==NULL)
	{
		printf ("Lista jest pusta\n");
	}
	else
	{
		Lista_type *current = head;
		do
		{
			printf ("%s", current->nazwa);
			printf ("\n");
			current = current->next;
		} while (current != NULL); 
	}
}
int list_size (Lista_type *head)
{
	int licznik=0;
	if (head==NULL)
	{
		return licznik;
	}
	else
	{
		Lista_type *current = head;
		do
		{
			licznik++;
			current = current->next;
		} while (current != NULL);
	}
	return licznik;
}
void push_front (Lista_type **head, char *name)
{
	Lista_type *current;
	current=(Lista_type *) malloc (sizeof (Lista_type));
	strcpy (current->nazwa, name);
	current->next=(*head);
	*head=current;
}
void push_back (Lista_type **head, char *name)
{
	if(*head==NULL)
	{
		*head = (Lista_type *)malloc(sizeof(Lista_type));
		strcpy ((*head)->nazwa, name);
    	(*head)->next = NULL;
	}
	else
	{
		Lista_type *current=*head;
	    while (current->next != NULL) 
		{
	        current = current->next;
	    }
	    current->next = (Lista_type *)malloc(sizeof(Lista_type));
	    strcpy (current->next->nazwa, name);
	    current->next->next = NULL;	
	}
}
void push_by_index (Lista_type **head, char *name, int position)
{
	if (position==0)
	{
		push_front (head, name);
	}
	else
	{
		if (position == list_size(*head))
		{
			push_back (head, name);
		}
		else
		{
			Lista_type *current = *head;
			Lista_type *tmp;
			int i=0;
			while ((current->next != NULL) && (i<position-1))
			{
				current = current->next;
				i++;
			}
			tmp = current->next;
			current->next = (Lista_type *) malloc (sizeof (Lista_type));
			strcpy (current->next->nazwa, name);
			current->next->next = tmp;
		}
	}
}
void pop_front(Lista_type **head)
{
    Lista_type * tmp=NULL;
 
    if (*head!=NULL) 
	{
   		tmp=(*head)->next;
   	 	free(*head);
   	 	*head=tmp;	
	}
}
void pop_back (Lista_type **head)
{
	if ((*head)->next == NULL)
	{
		*head = NULL;
	}
	else
	{
		Lista_type *current = *head;
		while (current->next->next != NULL)
		{
			current = current->next;
		}
		free (current->next);
		current->next = NULL;
	}
}
void pop_by_index(Lista_type **head, int position)
{
	if (position==0) pop_front(head);
	else
	{
		Lista_type *current=*head;
	    Lista_type *tmp;
		int i=0;
		while (current->next != NULL && i<position-1) 
		{
	        current=current->next;
			i++;    
		}	
		tmp = current->next;
	    current->next = tmp->next;
	    free(tmp);	
	}
}
void delete_all (Lista_type **head)
{
    Lista_type * tmp=NULL;
    while (*head!=NULL) 
	{
   		tmp=(*head)->next;
   	 	free(*head);
   	 	*head=tmp;	
	}
}
int main ()
{
	char napis[200];
	Lista_type *head;
	head = (Lista_type *) malloc (sizeof (Lista_type));
	head = NULL;
	int opcja = -1;
	int numer = -1;
	int index = -1;
	while (opcja != 0)
	{
		system("cls");
		printf("\nAktualny stan listy: ");
		show (head);
		printf ("\n\nDrogi uzytkowniku! Co chcesz zrobic?\n");
		printf ("1. Dodaj element na poczatek listy.\n");
		printf ("2. Dodaj element na koniec listy.\n");
		printf ("3. Dodaj element zgodnie z wybranym indeksem\n");
		printf ("4. Usun element z poczatku listy\n");
		printf ("5. Usun element z konca listy\n");
		printf ("6. Usun element o podanym indeksie\n");
		printf ("7. Usun liste od poczatkowego elementu\n");
		printf ("8. Usun liste od ostatniego elementu\n");
		printf ("0. Zakoncz program\n");
		scanf ("%d", &opcja);
		switch (opcja)
		{
			case 0:
				return 0;
				break;
			case 1:
				printf ("Podaj element, jaki chcesz dodac\n");
				scanf ("%s", &napis);
				push_front (&head, napis);
				break;
			case 2:
				printf ("Podaj element, jaki chcesz dodac\n");
				scanf ("%s", &napis);
				push_back (&head, napis);
				break;
			case 3:
				printf ("Podaj element, jaki chcesz dodac\n");
				scanf ("%s", &napis);
				printf ("Podaj pozycje, gdzie ma zostac umieszczony element\n");
				scanf ("%d", &index);
				push_by_index (&head, napis, index);
				break;
			case 4:
				pop_front (&head);
				break;
			case 5:
				pop_back (&head);
				break;
			case 6:
				printf ("Podaj pozycje, gdzie znajduje sie element do usuniecia z listy\n");
				scanf ("%d", &index);
				pop_by_index (&head, index);
				break;
			case 7:
				delete_all (&head);
				break;
			case 8:
				while (head!=NULL)
    			{
    				pop_back (&head);
				}
				break;
			default:
				printf ("Podaj wlasciwa opcje\n");
				Sleep(2000);
				break;
		}
	}
	return 0;
}
