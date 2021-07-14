//g++ -std=c++17 -Wall -Wextra -O2 n.cpp -lm
//Tiago Menezes
//Pedro Carreiro

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <regex>
#include <chrono>
#define MODVALUE 1000000007


int n = 0;  //Number of Pieces / Board Width
int h = 0;  //Height of the Blocks
int H = 0;  //Board Height
int diff = 0; //h-1
int board[2][501][60001];

int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
  return mod_add(a, -b, mod);
}

int solver(){
    int tempDown2 = 1;
    int sol = 0;
    int tempUp = 0;
    board[0][0][0] = 1;

    for (int i = 1; i < n; i++){
        
        tempUp = 0;
        for (int j = 0; j < H - diff && j - (n - i-1) * diff <= 0; j++)
        {
			
            int tempDown, index_to_minus, index_to_add;

            //Go Up
            tempDown = 0;
            index_to_minus = j-diff-1;
            index_to_add =  j - 1;

            if(j >= i){ 

                if(j == i ){
                  tempUp = board[0][i-1][j-1];
                } else {  
                    tempUp = mod_add(tempUp, board[0][i-1][index_to_add], MODVALUE);
                    
                    if (j >= i + diff)
                    { 
                      tempUp = mod_sub(tempUp, board[0][i-1][index_to_minus], MODVALUE);
                    }   
                }
            }

            board[0][i][j] = tempUp;
           
            //Go Down

            index_to_minus = j;
            index_to_add = std::min(j + diff, H);

            if(j == 0){
                tempDown = tempDown2;
                tempDown2 = 0;
            } else {
                tempDown = board[1][i][j-1];
            }
            
            tempDown = mod_add(tempDown, board[0][i-1][index_to_add], MODVALUE);
            tempDown = mod_sub(tempDown, board[0][i-1][index_to_minus], MODVALUE);

            tempDown = mod_add(tempDown, board[1][i-1][index_to_add], MODVALUE);
            tempDown = mod_sub(tempDown, board[1][i-1][index_to_minus], MODVALUE);
          
            board[1][i][j] = tempDown;

             if (j<diff)
            {
              tempDown2 = mod_add(tempDown2,board[0][i][j],MODVALUE);
              tempDown2 = mod_add(tempDown2,board[1][i][j],MODVALUE);
            }
        }
    }
    
    bool print_table = false;
    if(print_table){
        for (int z = 0; z < n; z++)
            {
                for (int k = 0; k < H; k++)
                {
                    printf("%d ", board[0][z][k]);
                }
                printf("\n");
            }

        printf("\n");
        for (int z = 0; z < n; z++)
        {
            for (int k = 0; k < H; k++)
            {
                printf("%d ", board[1][z][k]);
            }

            printf("\n");
        }
        printf("\n");        
    }

    for (int i = 2; i < n; i++){
        if (board[1][i][0] > 0){
           sol = mod_add(sol,board[1][i][0],MODVALUE);
        }
    }


    return mod_abs(sol,MODVALUE);
}

int main(){

    
    int ntests = 0;

    scanf("%d",&ntests);
    for (int i = 0; i < ntests; i++)
    {
        scanf("%d",&n); scanf("%d",&h); scanf("%d",&H);

        for (int z = 0; z <= n; z++){
          for (int k = 0; k <= H; k++){
            board[0][z][k] = 0; 
            board[1][z][k] = 0; 
          }
        }

        diff = h -1;
        
        printf("%d\n",mod_abs(solver(), MODVALUE));
      
    }

    return 0;
}