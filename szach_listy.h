//
// Created by igo-j on 10.02.2023.
//
#ifndef UNTITLED_SZACH_LISTY_H
#define UNTITLED_SZACH_LISTY_H
void removeList(moveList* head);
moveList* getLast(moveList* head);

void removeList(moveList* head){
    moveList* pomocnik;
    while(head != NULL){
        pomocnik = head;
        head = head ->next;
        free(pomocnik);
    }
}
moveList* getLast(moveList* head){
    moveList* zawodnik;
    while(head != NULL){
        zawodnik = head;
        head = head->next;
    }
    return zawodnik;
}


#endif //UNTITLED_SZACH_LISTY_H
