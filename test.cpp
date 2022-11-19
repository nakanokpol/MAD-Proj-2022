#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

bool readState[8][8][2]; // [row][col][0:old, 1:new] //read from stm32f7xx_it.c
// bool bufferState[8][8];

int stateChangeCount = 0;
bool errorState = false;

int row_rise = 16;
int col_rise = 16;

bool round_player = false; // true = player_1, false = player_1
int chess[2][8][8] =   {{{2, 3, 5, 4, 6, 5, 3, 2}, // chess[row][col][player_id] = type ;// 0 is null
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {1, 1, 1, 1, 1, 1, 1, 1},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0}},

                        {{0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {1, 1, 1, 1, 1, 1, 1, 1},
                         {0, 0, 0, 0, 0, 0, 0, 0},
                         {2, 3, 5, 6, 4, 5, 3, 2}}};

bool stateChange[8][8] ={{false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false}};

// bool positionError[8][8];     
                         
bool tableCanGo[8][8] = {{false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false},
                         {false, false, false, false, false, false, false, false}};

/*

        0       1       2       3       4       5       6       7
7   [7][0]  [7][1]  [7][2]  [7][3]  [7][4]  [7][5]  [7][6]  [7][7]
6   [6][0]  [6][1]  [6][2]  [6][3]  [6][4]  [6][5]  [6][6]  [6][7]
5   [5][0]  [5][1]  [5][2]  [5][3]  [5][4]  [5][5]  [5][6]  [5][7]
4   [4][0]  [4][1]  [4][2]  [4][3]  [4][4]  [4][5]  [4][6]  [4][7]
3   [3][0]  [3][1]  [3][2]  [3][3]  [3][4]  [3][5]  [3][6]  [3][7]
2   [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  [2][5]  [2][6]  [2][7]
1   [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  [1][5]  [1][6]  [1][7]
0   [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  [0][5]  [0][6]  [0][7]

*/

int main(){
    while (1){
        // stateChangeCount = 0;////////////////////////////////////////////////////////////////////////////////
        for(int r = 0; r < 8; r++){
            for(int c = 0; c < 8; c++){ 
                if(readState[r][c][0] != readState[r][c][1]){ // state has been changed
                    // stateChangeCount++;
                    stateChange[r][c] = true;

                    if(readState[r][c][0] == 1){ // 1 -> 0 // put that chess off the table
                        checkWhereCanGo(round_player, checkPlayer(r, c), r, c, checkChessType(r,c)); //change val to true if can go
                        row_rise = r; // collect the row state
                        col_rise = c; // collect the col state
                    }
                    else if(readState[r][c][0] == 0){ // 0 -> 1
                        if (row_rise == r && col_rise == c){ // place chess at the same place it's rised. 
                            row_rise = 16;
                            col_rise = 16;
                            // stateChangeCount-- ;
                            stateChange[r][c] = false;
                        }
                        else { //place chess at new place
                            if (tableCanGo[r][c] == true){
                                moveChest(checkPlayer(r, c), row_rise, col_rise, r, c);
                                reset_tableCanGo();
                                row_rise = 16;
                                col_rise = 16;
                                readState[r][c][0] = readState[r][c][1];
                            }
                            else{
                                errorState = true;///////////////////////////////////////
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

static bool moveChest(int player_id, int from_r, int from_c, int to_r, int to_c){
    if (chess[from_r][from_c][player_id] >= 1 && chess[from_r][from_c][player_id] <= 7){
        chess[to_r][to_c][player_id] = chess[from_r][from_c][player_id];
        chess[from_r][from_c][player_id] = 0;
        return true;
    }
    return false;
} 

static bool checkWhereCanGo(bool round_player, int player_id, int row, int col, int type){
	if(player_id != round_player){
		return false; //wrong player playing
	}
	else{//true player playing
        if(type == 1){ // beer
        /* position [beer] can go (above player)
            -  -  -  - -
            -  -  -  - -
            -  -  x  - -
            - e1 o1 e2 -
            -  -  -  - -

            position [beer] can go (below player)
            - -   -  - -
            - e3 o2 e4 -
            - -   x  - -
            - -   -  - -
            - -   -  - -
        */
            if (player_id == 0) { // above player
                if(row >= 1 && row <=7){
                    if(isEmpthy(row-1,col)){    // o1
                        tableCanGo[row-1][col] = true;
                    }
                    if(isEnemy(player_id, row-1, col-1) && col >= 1 && col <= 7){   //e1
                        tableCanGo[row-1][col-1] = true;
                    }
                    if(isEnemy(player_id, row-1, col+1) && col >= 0 && col <= 6){   //e2
                        tableCanGo[row-1][col+1] = true;
                    }
                }
                else { //change beer to beer ngai
                    type = 7;
                    chess[player_id][row][col] = 7;
                }
            }
            else if (player_id == 1){ //below player
                if(row >= 0 && row <= 6){
                    if(isEmpthy(row+1,col)){    // o2
                        tableCanGo[row+1][col] = true;
                    }
                    if(isEnemy(player_id, row+1, col-1) && col >= 1 && col <= 7){   //e3
                        tableCanGo[row+1][col-1] = true;
                    }
                    if(isEnemy(player_id, row+1, col+1) && col >= 0 && col <= 6){   //e4
                        tableCanGo[row+1][col+1] = true;
                    }
                }
                else { //change beer to beer ngai
                    type = 7;
                    chess[player_id][row][col] = 7;
                }
            }
        }
        else if (type == 2){ // boat
            for(int i = 0; i < 8; i++){
                if(canGo(player_id, row, i)){
                    tableCanGo[row][i] = true;
                }
                if(canGo(player_id, i, col)){
                    tableCanGo[i][col] = true;
                }
            }
        }
        else if (type == 3){ // horse
        /* position [horse] can go
            - 1 - 2 -
            8 - - - 3
            - - x - -
            7 - - - 4
            - 6 - 5 -
        */
            if(row>=0 && row<=5){                       //p1, p2
                if (col >= 1 && col <= 7 && canGo(player_id, row-2, col-1)){              //p1
                    tableCanGo[row-2][col-1] = true;
                }
                if (col >= 0 && col <= 6 && canGo(player_id, row-2, col+1)){              //p2
                    tableCanGo[row-2][col+1] = true;
                }
            }
            if(col>=0 && col<=5){                       //p3, p4
                if (row >= 0 && row <= 6 && canGo(player_id, row-1, col+2)){              //p3
                    tableCanGo[row-1][col+2] = true;
                }
                if (row >= 1 && row <= 7 && canGo(player_id, row+1, col+2)){              //p4
                    tableCanGo[row+1][col+2] = true;
                }
            }
            if(row>=2 && row<=7){                       //p5, p6
                if (col >= 0 && col <= 6 && canGo(player_id, row-2, col+1)){              //p5
                    tableCanGo[row-2][col+1] = true;
                }
                if (col >= 1 && col <= 7 && canGo(player_id, row-2, col+1)){              //p6
                    tableCanGo[row-2][col-1] = true;
                }
            }
            if(col>=2 && col<=7){                       //p7, p8
                if (row >= 1 && row <= 7 && canGo(player_id, row-1, col-2)){              //p7
                    tableCanGo[row-1][col-2] = true;
                }
                if (row >= 0 && row <= 6 && canGo(player_id, row+1, col-2)){              //p8
                    tableCanGo[row+1][col-2] = true;
                }
            }
        }
        else if (type == 4 || type == 5 || type == 6 || type == 7){ //[met (4) / beer_ngai (7)], [cone (5)], [kun (6)]
        /* position [met (4) / beer_ngai (7)] can go
            - - - - -
            - o - o -
            - - x - -
            - o - o -
            - - - - -

            position [cone (5)] can go
            - - - - -
            - o b o -
            - - x - -
            - o a o -
            - - - - -

            position [kun (6)] can go
            - - - - -
            - 1 5 2 -
            - 7 x 8 -
            - 4 6 3 -
            - - - - -

        */
            if ((row >= 0 && row <= 6)){              //p1, p2
                if ((col >= 1 && col <= 7)&& canGo(player_id, row+1, col-1)){              //p1
                    tableCanGo[row+1][col-1] = true;
                }
                if ((col >= 0 && col <= 6)&& canGo(player_id, row+1, col+1)){              //p2
                    tableCanGo[row+1][col+1] = true;
                }
                if ((type == 5 || type == 6) && canGo(player_id, row+1, col)){             //p5b
                    tableCanGo[row+1][col] = true;
                }
            }
            if ((row >= 1 && row <= 7)){              //p3, p4
                if ((col >= 0 && col <= 6)&& canGo(player_id, row-1, col+1)){              //p3
                    tableCanGo[row-1][col+1] = true;
                }
                if ((col >= 1 && col <= 7)&& canGo(player_id, row-1, col-1)){              //p4
                    tableCanGo[row-1][col-1] = true;
                }
                if (type == 6 && canGo(player_id, row-1, col)){                            //p6
                    tableCanGo[row-1][col] = true;
                } 
            }
            if (type == 6){
                if (col >= 1 && col <= 7 && canGo(player_id, row, col-1)){                 //p7
                    tableCanGo[row][col-1] = true;
                }
                if (col >= 0 && col <= 6 && canGo(player_id, row, col+1)){
                    tableCanGo[row][col+1] = true;
                }
            }
        }
	}
}

static int isEnemy(int player_id, int row, int col){ //is enemy of player_id?
	if (chess[player_id == 0 ? 1:0][row][col] > 0){
		return true;
	}
	return false;
}

static bool isEmpthy(int row, int col){
	if (chess[0][row][col] == 0 && chess[1][row][col] == 0){
		return true;
	}
	return false;
}

static int canGo (int player_id, int row, int col){ //is enemy of player_id?
	if (chess[player_id][row][col] > 0){
		return false;
	}
	return true;
}

static int checkPlayer(int row, int col){
    if (chess[row][col][0] != 0){
        return 0;
    }
    else if (chess[row][col][1] != 0){
        return 1;
    }
    return 2; // null player 
}
static int checkChessType(int row, int col){
    if (chess[row][col][0] != 0 && chess[row][col][1] != 0){
        return 8;
    }
    else if(chess[row][col][1] != 0 && chess[row][col][0] == 0){
        return chess[row][col][1];
    }
    else if(chess[row][col][0] != 0 && chess[row][col][1] == 0){
        return chess[row][col][0];
    }
    return 8;
}

static void reset_tableCanGo(void){
    // tableCanGo = {{false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false},
    //             {false, false, false, false, false, false, false, false}};
    for (int r = 0; r < 8; r++){
        for (int c = 0; c < 8; c++){
            tableCanGo[r][c] = false;
        }
    }
}

static  positionError(){

    return;
}