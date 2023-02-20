//
// Created by igo-j on 17.02.2023.
//

#ifndef UNTITLED_LEGAL_MOVES_H
#define UNTITLED_LEGAL_MOVES_H
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
        head->legalMove = ruch;
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
        head->legalMove = ruch;
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
        head->legalMove = ruch;
        head->next = p;
    }

    ruch.where[0] = column - 1;
    ruch.where[1] = row + forward;
    if (checkAll(board,ruch , forward == 1 ? 1 : 0) == 1){
        p = head;
        head = (moveList*)malloc(sizeof(moveList));
        if (!head){
            removeList(p);
            return NULL;
        }
        head->legalMove = ruch;
        head->next = p;
    }
    if(head == NULL){
        head = (moveList*)malloc(sizeof(moveList));
        if(!head)
            return NULL;
        ruch.what[0] = -1;
        head->legalMove = ruch;
        head->next = NULL;
    }
    return head;
}

moveList* rookLegal(char** board,int column, int row){
    move ruch;
    moveList *head = NULL, *p;
    int i,kolor;
    char kolorv[7];
    ruch.what[0] = column;
    ruch.what[1] = row;
    if(strchr(WHITE, board[column][row]) != NULL){
        strcpy(kolorv, WHITE);
        kolor = 1;
    } else {
        strcpy(kolorv,BLACK);
        kolor = 0;
    }

    for(i = 1; column + i < 8; i++) {
        ruch.where[0] = column + i;
        ruch.where[1] = row;
        if (board[column + i][row] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    for(i = -1; column + i >= 0; i--){
        ruch.where[0] = column + i;
        ruch.where[1] = row;
        if (board[column + i][row] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    for(i = 1; row + i < 8; i++){
        ruch.where[0] = column;
        ruch.where[1] = row + i;
        if (board[column][row + i] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    for(i = -1; row + i >= 0; i--){
        ruch.where[0] = column;
        ruch.where[1] = row + i;
        if (board[column][row + i] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }

    if(head == NULL){
        head = (moveList*)malloc(sizeof(moveList));
        if(!head)
            return NULL;
        ruch.what[0] = -1;
        head->legalMove = ruch;
        head->next = NULL;
    }
    return head;
}

moveList* bishopLegal(char** board,int column, int row){
    move ruch;
    moveList *head = NULL, *p;
    ruch.what[0] = column;
    ruch.what[1] = row;
    int i = 0, j = 0, kolor;
    if(strchr(WHITE, board[column][row]) != NULL)
        kolor = 1;
    else
        kolor = 0;
    while(column + i < 7 && row + j < 7){
        i++;
        j++;
        ruch.where[0] = column +i;
        ruch.where[1] = row + j;
        if (board[column + i][row + j] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    i = 0; j = 0;
    while(column + i < 7 && row + j > 0){
        i++;
        j--;
        ruch.where[0] = column +i;
        ruch.where[1] = row + j;
        if (board[column + i][row + j] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    i = 0; j = 0;
    while(column + i > 0 && row + j < 7){
        i--;
        j++;
        ruch.where[0] = column +i;
        ruch.where[1] = row + j;
        if (board[column + i][row + j] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    i = 0; j = 0;
    while(column + i > 0 && row + j > 0){
        i--;
        j--;
        ruch.where[0] = column +i;
        ruch.where[1] = row + j;
        if (board[column + i][row + j] == ' ') {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        } else {
            if (checkAll(board, ruch, kolor) == 1) {
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
                break;
            }
        }
    }
    if(head == NULL){
        head = (moveList*)malloc(sizeof(moveList));
        if(!head)
            return NULL;
        ruch.what[0] = -1;
        head->legalMove = ruch;
        head->next = NULL;
    }
    return head;
}

moveList* horseLegal(char** board,int column, int row){
    move ruch;
    moveList *head = NULL, *p;
    int i = 2,j = 1, kolor;
    ruch.what[0] = column;
    ruch.what[1] = row;
    if(strchr(WHITE, board[column][row]) != NULL)
        kolor = 1;
    else
        kolor = 0;
    while(i != -6){
        while (j != -3) {
            ruch.where[0] = column + i;
            ruch.where[1] = row + j;
            if(checkAll(board, ruch, kolor) == 1){
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
            j -= 2;
        }
        i -= 4;
        j = 1;
    }
    i = 2;
    while(i != -6){
        while (j != -3) {
            ruch.where[0] = column + i;
            ruch.where[1] = row + j;
            if(checkAll(board, ruch, kolor) == 1){
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
            j -= 2;
        }
        i -= 4;
        j = 1;
    }

    if(head == NULL){
        head = (moveList*)malloc(sizeof(moveList));
        if(!head)
            return NULL;
        ruch.what[0] = -1;
        head->legalMove = ruch;
        head->next = NULL;
    }
    return head;
}

moveList* kingLegal(char** board,int column, int row){
    move ruch;
    moveList *head = NULL, *p;
    int i, j, kolor;
    ruch.what[0] = column;
    ruch.what[1] = row;
    if(strchr(WHITE, board[column][row]) != NULL)
        kolor = 1;
    else
        kolor = 0;
    for (i = -1; i < 2; i++){
        for (j = -1; j < 2; ++j) {
            ruch.where[0] = column + i;
            ruch.where[1] = row + j;
            if(checkAll(board, ruch, kolor) == 1){
                p = head;
                head = (moveList *) malloc(sizeof(moveList));
                if (!head) {
                    removeList(p);
                    return NULL;
                }
                head->legalMove = ruch;
                head->next = p;
            }
        }
    }
    if(head == NULL){
        head = (moveList*)malloc(sizeof(moveList));
        if(!head)
            return NULL;
        ruch.what[0] = -1;
        head->legalMove = ruch;
        head->next = NULL;
    }
    return head;
}
#endif //UNTITLED_LEGAL_MOVES_H
