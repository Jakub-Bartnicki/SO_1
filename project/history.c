#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "history.h"

#define INPUT_MAX_LENGTH 200
#define CHUNK 1024

void showHistory() {
    FILE *historyFile = fopen("history.txt", "r");
    if (historyFile == NULL) {
        perror("Unable to open file");
        return;
    }

    int character;

    while( (character = fgetc(historyFile)) != EOF && character != '\0')
	{
		putchar(character);
	}
    putchar('\n');

    fclose(historyFile);
}



int getHistorySize(ListElement_type *headOfHistoryList)
{
    int counter = 0;
    if (headOfHistoryList == NULL) return counter;
    else {
        ListElement_type *current = headOfHistoryList;
            do {
            counter++;
            current = current->next;
            } while (current != NULL);
    }
    return counter;
}

void updateHistory(ListElement_type *headOfHistoryList) {
    FILE *historyFile = fopen("history.txt", "w");
    ListElement_type *current;
    if (headOfHistoryList != NULL)
         current = headOfHistoryList;
    else return;
    int i = 1;

    while (current->next != NULL) {
        fprintf(historyFile, "\n%d. %s", i, current->data);
        current = current->next;
        i++;
    }
    
    fclose(historyFile);
}

void addHistoryElement(ListElement_type **headOfHistoryList, char* text)
{	
	if(*headOfHistoryList == NULL) {
		*headOfHistoryList = (ListElement_type *) malloc(sizeof(ListElement_type));
        (*headOfHistoryList)->data = (char*) malloc(sizeof(char) * INPUT_MAX_LENGTH);
   		strcpy((*headOfHistoryList)->data, text);
    	(*headOfHistoryList)->next = NULL;
	} else {
        if (getHistorySize(*headOfHistoryList) >= 20) {
            ListElement_type * newListHead = NULL;
 
            newListHead = (*headOfHistoryList)->next;
            free(*headOfHistoryList);
            *headOfHistoryList = newListHead;	
        }
		ListElement_type *current = *headOfHistoryList;
	
	    while (current->next != NULL) {
	        current = current->next;
	    }

	    current->next = (ListElement_type * )malloc(sizeof(ListElement_type));
        current->next->data = (char*) malloc(INPUT_MAX_LENGTH);
	    strcpy(current->next->data, text);
	    current->next->next = NULL;	    
	}
    // TODO: NIE WPISUJE KURWA OSTATNIEGO ELEMENTU HISTORII
    updateHistory(*headOfHistoryList);
}

// void showHistory(ListElement_type *headOfHistoryList) {
//     if(headOfHistoryList == NULL) {
//         puts("List is empty");
//         return;
//     }

//     ListElement_type *current = headOfHistoryList;
//     int i = 1;

//     do {
//         printf("%d. %s\n", i++, current->data);
//         current = current->next;
//     } while (current != NULL);
// }

// int getHistorySize()
// {
//     FILE *history = fopen("history.txt", "r");
//     int counter = 0;
    
//     while(!feof(history))
//     {
//         if(fgetc(history) == '\n')
//         {
//             counter++;
//         }
//     }

//     fclose(history);

//     return counter;
// }

// void addHistoryElement(ListElement_type **headOfHistoryList, char* text)
// {	
// 	if(*headOfHistoryList == NULL) {
// 		*headOfHistoryList = (ListElement_type *) malloc(sizeof(ListElement_type));
//         (*headOfHistoryList)->data = (char*) malloc(sizeof(char) * INPUT_MAX_LENGTH);
//    		strcpy((*headOfHistoryList)->data, text);
//     	(*headOfHistoryList)->next = NULL;
// 	} else {
//         if (getHistorySize(*headOfHistoryList) >= 20) {
//             ListElement_type * newListHead = NULL;
 
//             newListHead = (*headOfHistoryList)->next;
//             free(*headOfHistoryList);
//             *headOfHistoryList = newListHead;	
//         }
// 		ListElement_type *current = *headOfHistoryList;
	
// 	    while (current->next != NULL) {
// 	        current = current->next;
// 	    }

// 	    current->next = (ListElement_type * )malloc(sizeof(ListElement_type));
//         current->next->data = (char*) malloc(INPUT_MAX_LENGTH);
// 	    strcpy(current->next->data, text);
// 	    current->next->next = NULL;	
// 	}
// }