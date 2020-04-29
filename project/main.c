#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void checkLastSymbol(char array[]) {
    char c = '&';

    if (array[strlen(array) - 1]) {
        printf("%s", "It works\n");
    } else {
        printf("%s", "Error\n");
    }
}

typedef struct ListElement {
    char data[200];
    struct ListElement * next;

} ListElement_type;
	
void pushBack(ListElement_type **head, char* text)
{	
	if(*head==NULL) {
		*head = (ListElement_type *)malloc(sizeof(ListElement_type));
   		strcpy((*head)->data, text);
    	(*head)->next = NULL;
	} else {
		ListElement_type *current=*head;
	
	    while (current->next != NULL) {
	        current = current->next;
	    }
	
	    current->next = (ListElement_type *)malloc(sizeof(ListElement_type));
	    strcpy(current->next->data, text);
	    current->next->next = NULL;	
	}
}
	
void show(ListElement_type *head) {
    int i = 1;

    printf("\n");
    if(head==NULL) {
        printf("List is empty");
        return;
    }

    ListElement_type *current=head;

    do {
        printf("%d. %s\n", i, current->data);
        current = current->next;
        i++;
    } while (current != NULL);
 
}

int main(int argc, const char* argv[]) {

    ListElement_type *head;
    head = (ListElement_type *)malloc(sizeof(ListElement_type));
    head=NULL;

    int i, sum = 0;
    char option[200];
    int currChar = 0;

    if (argc > 1) {
        printf("Unnecessary arguments have been ignored\n");
    }

    while (1) {
        char readed[200];
        char x;

        // TODO: Poprawić, cos nie tak z getc
        // if (x = getc(stdin) == '\033' || x == '\033') { 
        // getc
        //     switch(x) {
        //         case 'A':
        //             system("history-search-backward");
        //             break;
        //         case 'B':
        //             system("hitory-search-forward");
        //             break;
        //     } 
        // } else { 

        gets(readed);

        strcpy(option, readed);
        if (strcmp(option, "history") != 0 && strcmp(option, "help") != 0 && strcmp(option, "exit") != 0) {
            strtok(option, " ");
        }

        if (!(strcmp(option, "exit"))) {
            printf("%s", "exitting...\n");
            exit(0);
        } else if (!(strcmp(option, "sum"))) {
            checkLastSymbol(option);
            char command[202];  
            strcpy(command, "./");
            strcat(command, readed);

            printf("command: %s\n", command);

            system(command);
        } else if (!(strcmp(option, ""))) {

        } else if (!(strcmp(option, ""))) {
            // TODO: Klikanie strzałki w gore daje poprzednia komende

        } else if (!(strcmp(option, ""))) {
            

        } else if (!(strcmp(option, "history"))) {
            // TODO: Wyswietlanie historii
            
            show(head);

        } else if (!(strcmp(option, "help"))) {
            puts("\nhelp - show this help list\n"                       \
            "sum [x y z ...] - sum 2 (or more) numbers\n"               \
            "history - show history of commands\n"                      \
            "exit - exit this interpreter\n");        
        } else {
            printf("%s", "Choose another option");
            break;
        }

        pushBack(&head, readed);
    }
    return 0;
}
