#include <stdio.h>
#include <stdlib.h>
#include "szach.h"

int main() {
    char** board;
    board = makeBoard();
    if (!board)
        return 1;
    move ruch;
    start(board);
    while(1) {
        printBoard(board);
        if(checkMate(board, WTURN) == 1){
            printf("koniec 8===D\n");
        }
        printf("ruch bialych\n");
        do {
            getMove(&ruch);
        }while(checkAll(board, ruch, WTURN) != 1);
        makeMove(board, ruch);
        printBoard(board);
        if(checkMate(board, BTURN) == 1){
            printf("koniec 8===D\n");
        }
        printf("ruch czarnych\n");
        do {
            getMove(&ruch);
        }while(checkAll(board, ruch, BTURN) != 1);
        makeMove(board, ruch);
    }
}