#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "szach.h"


int main(int argc, char** argv) {
    char** board;
    move ruch;
    FILE* gameFile;
    srand(time(0));
    board = makeBoard();
    if (!board)
        return 1;
    start(board);
    if (argc == 2){
        gameFile = fopen(argv[1], "a+");
        if(gameFile == NULL){
            printf("blad pliku :(\n");
            return 1;
        }
        if(reproduce(gameFile, board) == 0)
            return 0;
    }
    while(1) {
        printBoard(board);
        if(checkMate(board, WTURN) == 1){
            printf("koniec 8===D\n");
            return 0;
        }
        printf("ruch bialych\n");
        ruch = bot(board, WTURN);
        makeMove(board, ruch);
        printBoard(board);
        if(checkMate(board, BTURN) == 1){
            printf("koniec 8===D\n");
            return 0;
        }
        printf("ruch czarnych\n");
        ruch = bot(board, WTURN);
        makeMove(board, ruch);
    }
}