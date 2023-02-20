//
// Created by igo-j on 05.02.2023.
//

#ifndef UNTITLED_CHECKS_H
#define UNTITLED_CHECKS_H
int boundaryCheck(move x){
    if(x.what[0] < 0 || x.what[0] > 7)
        return 0;
    if(x.what[1] < 0 || x.what[1] > 7)
        return 0;
    if(x.where[0] < 0 || x.where[0] > 7)
        return 0;
    if(x.where[1] < 0 || x.where[1] > 7)
        return 0;
    return 1;
}

int wBishopCheck(char** board, move x) {
    int i, j, pion, poziom, granicaPion, granicaPoziom;
    if (x.where[0] > x.what[0]) {
        poziom = 1;
        granicaPoziom = 8;
    } else {
        poziom = -1;
        granicaPoziom = -1;
    }

    if (x.where[1] > x.what[1]) {
        pion = 1;
        granicaPion = 8;
    } else {
        pion = -1;
        granicaPion = -1;
    }

    j = x.what[1];
    for (i = x.what[0] + poziom; i != granicaPoziom; i += poziom) {
        j += pion;
        if (j == granicaPion)
            return 0;
        if (i == x.where[0] && j == x.where[1]) {
            if (strchr(WHITE, board[i][j]) == NULL)
                return 1;
        } else {
            if (board[i][j] != ' ')
                return 0;
        }
    }
    return 0;
}
int bBishopCheck(char** board, move x) {
    int i, j, pion, poziom, granicaPion, granicaPoziom;
    if (x.where[0] > x.what[0]) {
        poziom = 1;
        granicaPoziom = 8;
    } else {
        poziom = -1;
        granicaPoziom = -1;
    }
    if (x.where[1] > x.what[1]) {
        pion = 1;
        granicaPion = 8;
    } else {
        pion = -1;
        granicaPion = -1;
    }

    j = x.what[1];
    for (i = x.what[0] + poziom; i != granicaPoziom; i += poziom) {
        j += pion;
        if (j == granicaPion)
            return 0;
        if (i == x.where[0] && j == x.where[1]) {
            if (strchr(BLACK, board[i][j]) == NULL)
                return 1;
        } else {
            if (board[i][j] != ' ')
                return 0;
        }
    }
    return 0;
}

int wPawnCheck(char** board, move x){
    if(x.what[0] == x.where[0]){
        if(x.where[1] == x.what[1] + 1 && board[x.where[0]][x.where[1]] == ' '){
            return 1;
        }
        if(x.where[1] == x.what[1] + 2 &&
           x.what[1] == 1 &&
           board[x.where[0]][x.where[1]] == ' ' &&
           board[x.where[0]][x.where[1] - 1] == ' '){
            return 1;
        }
    }
    if(x.what[0] == x.where[0] + 1 || x.what[0] == x.where[0] - 1){
        if(x.where[1] == x.what[1] + 1 && strchr(BLACK, board[x.where[0]][x.where[1]]) != NULL){
            return 1;
        }
    }
    return 0;
}
int bPawnCheck(char** board, move x){
    if(x.what[0] == x.where[0]){
        if(x.where[1] == x.what[1] - 1 && board[x.where[0]][x.where[1]] == ' '){
            return 1;
        }
        if(x.where[1] == x.what[1] - 2 &&
           x.what[1] == 6 &&
           board[x.where[0]][x.where[1]] == ' ' &&
           board[x.where[0]][x.where[1] + 1] == ' '){
            return 1;
        }
    }
    if(x.what[0] == x.where[0] + 1 || x.what[0] == x.where[0] - 1){
        if(x.where[1] == x.what[1] - 1 && strchr(WHITE, board[x.where[0]][x.where[1]]) != NULL){
            return 1;
        }
    }
    return 0;
}
int wHorseCheck(char** board, move x){
    int haha;
    haha = abs((x.what[0] - x.where[0]) * (x.what[1] - x.where[1]));
    if(haha == 2 && strchr(WHITE, board[x.where[0]][x.where[1]]) == NULL)
        return 1;
    return 0;
}
int bHorseCheck(char** board, move x){
    int haha;
    haha = abs(x.what[0] - x.where[0]) * abs(x.what[1] - x.where[1]);
    if(haha == 2 && strchr(BLACK, board[x.where[0]][x.where[1]]) == NULL)
        return 1;
    return 0;
}

int wRookCheck(char** board, move x){
    int kierunek, i, ograniczenie;
    if(x.what[0] == x.where[0]){ //ruch w pionie
        if(x.what[1] < x.where[1]) {
            kierunek = 1;
            ograniczenie = 8;
        } else {
            kierunek = -1;
            ograniczenie = -1;
        }
        for(i = x.what[1] + kierunek; i != ograniczenie; i += kierunek){
            if (i == x.where[1]) {
                if (strchr(WHITE, board[x.what[0]][i]) == NULL)
                    return 1;
            } else {
                if (board[x.what[0]][i] != ' ')
                    return 0;
            }
        }
    } else if(x.what[1] == x.where[1]){ // ruch w poziomie
        if(x.what[0] < x.where[0]) {
            kierunek = 1;
            ograniczenie = 8;
        } else {
            kierunek = -1;
            ograniczenie = -1;
        }
        for(i = x.what[0] + kierunek; i != ograniczenie; i += kierunek){
            if (i == x.where[0]) {
                if (strchr(WHITE, board[i][x.what[1]]) == NULL)
                    return 1;
            } else {
                if (board[i][x.what[1]] != ' ')
                    return 0;
            }
        }
    }
    return 0;
}

int bRookCheck(char** board, move x){
    int kierunek, i, ograniczenie;
    if(x.what[0] == x.where[0]){ //ruch w pionie
        if(x.what[1] < x.where[1]) {
            kierunek = 1;
            ograniczenie = 8;
        } else {
            kierunek = -1;
            ograniczenie = -1;
        }
        for(i = x.what[1] + kierunek; i != ograniczenie; i += kierunek){
            if (i == x.where[1]) {
                if (strchr(BLACK, board[x.what[0]][i]) == NULL)
                    return 1;
            } else {
                if (board[x.what[0]][i] != ' ')
                    return 0;
            }
        }
    } else if(x.what[1] == x.where[1]){ // ruch w poziomie
        if(x.what[0] < x.where[0]) {
            kierunek = 1;
            ograniczenie = 8;
        } else {
            kierunek = -1;
            ograniczenie = -1;
        }
        for(i = x.what[0] + kierunek; i != ograniczenie; i += kierunek){
            if (i == x.where[0]) {
                if (strchr(BLACK, board[i][x.what[1]]) == NULL)
                    return 1;
            } else {
                if (board[i][x.what[1]] != ' ')
                    return 0;
            }
        }
    }
    return 0;
}
int wKingCheck(char** board, move x){
    int pion = abs(x.what[0] - x.what[0]);
    int poziom = abs(x.what[1] - x.what[1]);
    if(pion <= 1 && poziom <= 1){
        if((pion + poziom) != 0 && strchr(WHITE, board[x.where[0]][x.where[1]]) == NULL){
            return 1;
        }
    }
    return 0;
}

int bKingCheck(char** board, move x){
    int pion = abs(x.what[0] - x.what[0]);
    int poziom = abs(x.what[1] - x.what[1]);
    if(pion <= 1 && poziom <= 1){
        if((pion + poziom) != 0 && strchr(BLACK, board[x.where[0]][x.where[1]]) == NULL){
            return 1;
        }
    }
    return 0;
}

int checkCheck(char** board, int kto){
    move ruch;
    char kogo;
    if (kto == 1)
        kogo = 'K';
    else
        kogo = 'k';
    search(board, kogo, &ruch);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; ++j) {
            ruch.what[0] = i;
            ruch.what[1] = j;
            if(checkMove(board, ruch, !kto) == 1)
                return 1;
        }
    }
    return 0;
}


#endif //UNTITLED_CHECKS_H
