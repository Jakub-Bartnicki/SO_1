#ifndef HISTORY_H_
#define HISTORY_H_

typedef struct ListElement {
    char* data;
    struct ListElement * next;

} ListElement_type;

void showHistory();

void addHistoryElement(ListElement_type **headOfHistoryList, char* text);

#endif