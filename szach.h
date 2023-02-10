//
// Created by Igor on 01.02.2023.
//
#ifndef UNTITLED2_SZACH_H
#define UNTITLED2_SZACH_H

#include <string.h>
#include <math.h>

#define WHITE "RQNBKP"
#define BLACK "rqnbkp"
#define WTURN 1
#define BTURN 0

struct move{
    int what[2];
    int where[2];
};
typedef struct move move;

struct moveList{
    struct moveList* next;
    move legalMove;
};
typedef struct moveList moveList;

void start(char **board);
void printBoard(char** );
void makeMove(char **board, move x);
int checkMove(char **board, move x, int kto);
void getMove(move* x);
char** makeBoard();
char** copyBoard(char **board);
void search(char** gdzie,char kogo, move* zapis);
int checkAll(char **board, move x, int kto);
moveList* getLegal(char** board, int kto);
moveList* pawnLegal(char** board,int column, int row);

#include "checks.h"
#include "szach_listy.h"

void start(char **board){
    board[0][7] = 'r';
    board[7][7] = 'r';
    board[1][7] = 'n';
    board[6][7] = 'n';
    board[2][7] = 'b';
    board[5][7] = 'b';
    board[3][7] = 'q';
    board[4][7] = 'k';
    for(int i = 0; i < 8; i++){
        board[i][6] = 'p';
    }
    for(int i = 0; i < 8; i++){
        for(int j = 2; j < 6; j++){
            board[i][j] = ' ';
        }
    }
    board[0][0] = 'R';
    board[7][0] = 'R';
    board[1][0] = 'N';
    board[6][0] = 'N';
    board[2][0] = 'B';
    board[5][0] = 'B';
    board[3][0] = 'Q';
    board[4][0] = 'K';
    for(int i = 0; i < 8; i++){
        board[i][1] = 'P';
    }
}

void printBoard(char** board){
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8 ;j++) {
            printf("%2c", board[j][i]);
        }
        printf("\n");
    }
}

void makeMove(char **board, move x) {
    char figura;
    figura = board[x.what[0]][x.what[1]];
    board[x.what[0]][x.what[1]] = ' ';
    board[x.where[0]][x.where[1]] = figura;
}

int checkMove(char **board, move x, int kto){
    int ok = 0;
    if(boundaryCheck(x) == 0)
        return 0;
    char figura = board[x.what[0]][x.what[1]];
    if(strchr(WHITE, figura) != NULL){
        if(kto != 1)
            return 0;
    }
    if(strchr(BLACK, figura) != NULL){
        if(kto != 0)
            return 0;
    }
    switch (figura) {
        case 'P':
            ok = wPawnCheck(board, x);
            break;
        case 'p':
            ok = bPawnCheck(board, x);
            break;
        case 'B':
            ok = wBishopCheck(board, x);
            break;
        case 'b':
            ok = bBishopCheck(board, x);
            break;
        case 'N':
            ok = wHorseCheck(board, x);
            break;
        case 'n':
            ok = bHorseCheck(board, x);
            break;
        case 'R':
            ok = wRookCheck(board, x);
            break;
        case 'r':
            ok = bRookCheck(board, x);
            break;
        case 'Q':
            if(wRookCheck(board,x) == 1 || wBishopCheck(board, x) == 1)
                ok = 1;
            break;
        case 'q':
            if(bRookCheck(board,x) == 1 || bBishopCheck(board, x) == 1)
                ok = 1;
            break;
        case 'K':
            ok = wKingCheck(board, x);
            break;
        case 'k':
            ok = bKingCheck(board, x);
    }
    return ok;
}

void getMove(move* x){
    printf("czym ruszasz?\npodaj nr kolumny: ");
    scanf("%d", &(x->what[0]));
    printf("podaj numer wiersza: ");
    scanf("%d", &(x->what[1]));

    printf("gzie ruszasz?\npodaj nr kolumny: ");
    scanf("%d", &(x->where[0]));
    printf("podaj numer wiersza: ");
    scanf("%d", &(x->where[1]));
    printf("\n");
}
char** makeBoard(){
    char** newBoard;
    int i;
    newBoard = (char**)malloc((sizeof(char*)) * 8);
    if(!newBoard)
        return NULL;
    for(i = 0; i < 8; i++){
        newBoard[i] = (char*) malloc(sizeof(char) * 8);
        if(!newBoard[i]){
            while(i > 0){
                i--;
                free(newBoard[i]);
            }
            free(newBoard);
            return NULL;
        }
    }
    return newBoard;
}

char** copyBoard(char **board){
    char** newBoard;
    int i;
    newBoard = (char**)malloc((sizeof(char*)) * 8);
    if(!newBoard)
        return NULL;
    for(i = 0; i < 8; i++){
        newBoard[i] = (char*) malloc(sizeof(char) * 8);
        if(!newBoard[i]){
            while(i > 0){
                i--;
                free(newBoard[i]);
            }
            free(newBoard);
            return NULL;
        }
    }
    for (i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            newBoard[i][j] = board[i][j];
    return newBoard;
}

void search(char** gdzie,char kogo, move* zapis){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (gdzie[i][j] == kogo){
                zapis->where[0] = i;
                zapis->where[1] = j;
                return;
            }
        }
    }
    zapis->where[0] = -1;
    zapis->where[1] = -1;
}

int checkAll(char **board, move x, int kto){
    char** newBoard;
    if(checkMove(board, x, kto) == 0)
        return 0;
    newBoard = copyBoard(board);
    makeMove(newBoard, x);
    if (checkCheck(board, kto) == 1)
        return 0;
    return 1;
}

moveList* getLegal(char** board, int kto){
    moveList* head = NULL;
    moveList* pomocnik;
    moveList* kolejnyPomocnik;
    if (kto == 1){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                pomocnik = head;
                switch (board[i][j]) {
                    case 'P':
                        head = pawnLegal(board, i, j);
                        break;
                }
                kolejnyPomocnik = getLast(head);
                kolejnyPomocnik->next = pomocnik;
            }
        }
    } else {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                pomocnik = head;
                switch (board[i][j]) {
                    case 'p':
                        head = pawnLegal(board, i, j);
                        break;
                }
                kolejnyPomocnik = getLast(head);
                kolejnyPomocnik->next = pomocnik;
            }
        }
    }
    return head;
}

moveList* pawnLegal(char** board, int column, int row){
    int forward;
    moveList* head = NULL;
    moveList* p;
    move ruch;
    ruch.what[0] = column;
    ruch.what[1] = row;
    forward = board[column][row] == 'P' ? 1 : -1;
    ruch.where[0] = column;
    ruch.where[1] = row + forward;
    if (checkAll(board,ruch , forward == 1 ? 1 : 0) == 1){
        head = (moveList*)malloc(sizeof(moveList));
        if (!head)
            return NULL;
        head->next = NULL;
    }

    ruch.where[0] = column;
    ruch.where[1] = row + 2*forward;
    if (checkAll(board,ruch , forward == 1 ? 1 : 0) == 1){
        p = head;
        head = (moveList*)malloc(sizeof(moveList));
        if (!head){
            removeList(p);
            return NULL;
        }
        head->next = p;
    }

    ruch.where[0] = column + 1;
    ruch.where[1] = row + forward;
    if (checkAll(board,ruch , forward == 1 ? 1 : 0) == 1){
        p = head;
        head = (moveList*)malloc(sizeof(moveList));
        if (!head){
            removeList(p);
            return NULL;
        }
        head->next = p;
    }

    ruch.where[0] = column - 1;
    ruch.where[1] = row + forward;
    if (checkAll(board,ruch , forward == 1 ? 1 : 0) == 1){
        p = head;
        head = (moveList*)malloc(sizeof(moveList));
        if (!head){
            removeList(head);
            return NULL;
        }
        head->next = p;
    }
}
#endif //UNTITLED2_SZACH_H