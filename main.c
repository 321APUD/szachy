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
        printf("ruch bialych\n");
        do {
            getMove(&ruch);
        }while(checkAll(board, ruch, WTURN) != 1);
        makeMove(board, ruch);
        printBoard(board);
        printf("ruch czarnych\n");
        do {
            getMove(&ruch);
        }while(checkAll(board, ruch, BTURN) != 1);
        makeMove(board, ruch);
    }
}