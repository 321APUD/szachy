#include <stdio.h>
#include <stdlib.h>
#include "szach.h"

int main() {
    char** board;
    board = makeBoard();
    if (!board)
        return 1;
    move ruch;
    ruch.what[0] = 0;
    ruch.what[1] = 0;
    ruch.where[0] = 1;
    ruch.where[1] = 1;
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