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
moveList* rookLegal(char** board,int column, int row);
int checkMate(char** board, int kto);
void weld(moveList **head, moveList *pomocnik);
int reproduce(FILE* file, char** board);
void translate(char line[6], move* ruch);

#include "checks.h"
#include "szach_listy.h"
#include "legal_moves.h"

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
    int co = 0;
    figura = board[x.what[0]][x.what[1]];
    board[x.what[0]][x.what[1]] = ' ';
    board[x.where[0]][x.where[1]] = figura;
    if(figura == 'P' && x.where[1] == 7){
        printf("na co zmienić pionka? \nkrólowa: 1\nwierza: 2\ngoniec: 3\nkoń: 4)\n");
        while (co != 1 && co != 2 && co != 3 && co != 4) {
            scanf("%d", &co);
        }
        switch (co) {
            case 1:
                board[x.where[0]][x.where[1]] = 'Q';
                break;
            case 2:
                board[x.where[0]][x.where[1]] = 'R';
                break;
            case 3:
                board[x.where[0]][x.where[1]] = 'B';
                break;
            case 4:
                board[x.where[0]][x.where[1]] = 'N';
                break;
        }
    }

    if(figura == 'p' && x.where[1] == 0){
        printf("na co zmienić pionka? \nkrólowa: 1\nwierza: 2\ngoniec: 3\nkoń: 4)\n");
        while (co != 1 && co != 2 && co != 3 && co != 4) {
            scanf("%d", &co);
        }
        switch (co) {
            case 1:
                board[x.where[0]][x.where[1]] = 'q';
                break;
            case 2:
                board[x.where[0]][x.where[1]] = 'r';
                break;
            case 3:
                board[x.where[0]][x.where[1]] = 'b';
                break;
            case 4:
                board[x.where[0]][x.where[1]] = 'n';
                break;
        }
    }
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
    if(figura == ' ')
        return 0;
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

int checkMate(char** board, int kto){
    moveList* sloppy;
    sloppy = getLegal(board, kto);
    if ((sloppy->legalMove).what[0] == -1){
        free(sloppy);
        return 1;
    }
    removeList(sloppy);
    return 0;
}


void weld(moveList **head, moveList *pomocnik) {
    moveList* kolejnyPomocnik = NULL;
    if ((*head)->legalMove.what[0] == -1){
        free((*head));
        *head = pomocnik;
    } else {
        kolejnyPomocnik = getLast(*head);
        if (kolejnyPomocnik == NULL)
            *head = pomocnik;
        else
            kolejnyPomocnik->next = pomocnik;
    }
}

moveList* getLegal(char** board, int kto){
    moveList* head = NULL;
    moveList* pomocnik = NULL;

    if (kto == 1){
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                switch (board[i][j]) {
                    case 'P':
                        pomocnik = head;
                        head = pawnLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'R':
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'B':
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'Q':
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'N':
                        pomocnik = head;
                        head = horseLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'K':
                        pomocnik = head;
                        head = kingLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                }
            }
        }
    } else {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                switch (board[i][j]) {
                    case 'p':
                        pomocnik = head;
                        head = pawnLegal(board, i,j);
                        if (head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'r':
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'b':
                        pomocnik = head;
                        head = bishopLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'q':
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        pomocnik = head;
                        head = rookLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'n':
                        pomocnik = head;
                        head = horseLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                    case 'k':
                        pomocnik = head;
                        head = kingLegal(board, i,j);
                        if ( head == NULL){
                            return NULL;
                        }
                        weld(&head, pomocnik);
                        break;
                }
            }
        }
    }
    if (head == NULL){
        head = (moveList*)malloc(sizeof(moveList));
        if (head == NULL){
            return NULL;
        }
        head->legalMove.what[0] = -1;
    }
    return head;
}

int reproduce(FILE* file, char** board){
    move ruch;
    int i = 0;
    char line[6];
    while(fgets(line,8, file)){
        i++;
        translate(line, &ruch);
        if (checkAll(board, ruch, i%2) == 1){
            makeMove(board, ruch);
            printBoard(board);
        } else {
            printf("illegal move\n");
            return 0;
        }
        if(checkMate(board,(i + 1)%2) == 1){
            printf("koniec, wygrywa kolor: ");
            if (i%2 == 1){
                printf("bialy\n");
            } else {
                printf("corny");
            }
            return 0;
        }
        printf("\n");
    }
    return 1;
}
void translate(char line[6], move* ruch){
    ruch->what[0] = line[0] - 'a';
    ruch->what[1] = line[1] - '1';

    ruch->where[0] = line[3] - 'a';
    ruch->where[1] = line[4] - '1';
}

move bot(char **board, int kto){
    move ruch;
    moveList *head, *p;
    int numerek;
    head = getLegal(board, kto);
    if (head == NULL){
        ruch.what[0] = 1;
        return ruch;
    }
    numerek = countList(head);
    numerek = (rand() % (numerek - 1)) + 1;
    p = head;
    while(numerek != 0){
        ruch = p->legalMove;
        p = p->next;
        numerek--;
    }
    return ruch;
}
#endif //UNTITLED2_SZACH_H