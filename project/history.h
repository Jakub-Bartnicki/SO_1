#ifndef HISTORY_H_
#define HISTORY_H_

typedef struct ListElement {
    char* data;
    struct ListElement * next;

} ListElement_type;

void showHistory();
// void showHistory(ListElement_type *headOfHistoryList);

// void addHistoryElement(char* text);
void addHistoryElement(ListElement_type **headOfHistoryList, char* text);

#endif