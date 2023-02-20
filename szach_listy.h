//
// Created by igo-j on 10.02.2023.
//
#ifndef UNTITLED_SZACH_LISTY_H
#define UNTITLED_SZACH_LISTY_H
void removeList(moveList* head);
moveList* getLast(moveList* head);
int countList(moveList* head);


void removeList(moveList* head){
    moveList* pomocnik;
    while(head != NULL){
        pomocnik = head;
        head = head ->next;
        free(pomocnik);
    }
}
moveList* getLast(moveList* head){
    moveList* zawodnik = NULL;
    while(head != NULL){
        zawodnik = head;
        head = head->next;
    }
    return zawodnik;
}

int countList(moveList* head){
    int i = 0;
    while (head != NULL){
        i++;
        head = head->next;
    }
    return i;
}
#endif //UNTITLED_SZACH_LISTY_H
