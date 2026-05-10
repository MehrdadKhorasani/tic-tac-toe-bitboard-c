#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROW1 0x007  
#define ROW2 0x038  
#define ROW3 0x1C0  
#define COL1 0x049  
#define COL2 0x092  
#define COL3 0x124  
#define DIAG1 0x111 
#define DIAG2 0x054 

const int WIN_MASKS[8] = {ROW1, ROW2, ROW3, COL1, COL2, COL3, DIAG1, DIAG2};
#define FULL_BOARD 0x1FF

void printBoard(int player1, int player2);
void playerTurn(int *playerBits, int otherPlayerBits);
void cpuTurn(int *cpuBits, int humanBits);
bool checkWin(int playerBits);
bool isMoveValid(int player1, int player2, int move);
int getRandomMove(int player1, int player2);

int main(void)
{
    int player1 = 0;  
    int player2 = 0;  
    bool isPlayer1Turn = true;
    int movesCount = 0;
    bool gameOver = false;
    
    srand(time(NULL));
    
    printf("*** TIC TAC TOE - Bitwise Version ***\n");
    printf("cells numbers:\n");
    printf("0 1 2\n3 4 5\n6 7 8\n\n");
    
    while(!gameOver) {
        printBoard(player1, player2);
        
        if(isPlayer1Turn) {
            printf("\n X player's turn:\n");
            playerTurn(&player1, player2);
        } else {
            printf("\n CPU's turn (O):\n");
            cpuTurn(&player2, player1);
        }
        movesCount++;
        
        if(isPlayer1Turn) {  
            if(checkWin(player1)) {
                printBoard(player1, player2);
                printf("\n*** (X) Won! ***\n");
                gameOver = true;
            }
        } else {  
            if(checkWin(player2)) {
                printBoard(player1, player2);
                printf("\n*** CPU (O) Won! ***\n");
                gameOver = true;
            }
        }
        
        if(!gameOver && (player1 | player2) == FULL_BOARD) {
            printBoard(player1, player2);
            printf("\n*** Draw! ***\n");
            gameOver = true;
        }
        
        isPlayer1Turn = !isPlayer1Turn;
    }
    
    return 0;
}

void printBoard(int player1, int player2)
{
    printf("\n");
    for(int i = 0; i < 9; i++) {
        if(player1 & (1 << i))
            printf(" X ");
        else if(player2 & (1 << i))
            printf(" O ");
        else
            printf(" %d ", i);
        
        if((i + 1) % 3 == 0)
            printf("\n");
    }
}

void playerTurn(int *playerBits, int otherPlayerBits)
{
    int move;
    bool validMove = false;
    
    while(!validMove) {
        printf("Please Choose the number of cell (0-8): ");
        scanf("%d", &move);
        
        if(move >= 0 && move <= 8 && isMoveValid(*playerBits, otherPlayerBits, move)) {
            *playerBits |= (1 << move);
            validMove = true;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

void cpuTurn(int *cpuBits, int humanBits)
{
    int move;
    printf("CPU thinking...\n");
    
    move = getRandomMove(*cpuBits, humanBits);
    *cpuBits |= (1 << move);
    printf("CPU chose the cell number %d.\n", move);
}

bool checkWin(int playerBits)
{
    for(int i = 0; i < 8; i++) {
        if((playerBits & WIN_MASKS[i]) == WIN_MASKS[i])
            return true;
    }
    return false;
}

bool isMoveValid(int player1, int player2, int move)
{
    int mask = 1 << move;
    return !((player1 & mask) || (player2 & mask));
}

int getRandomMove(int player1, int player2)
{
    int availableMoves[9];
    int count = 0;
    
    for(int i = 0; i < 9; i++) {
        if(isMoveValid(player1, player2, i)) {
            availableMoves[count++] = i;
        }
    }
    
    if(count > 0) {
        return availableMoves[rand() % count];
    }
    
    return -1; 
}
