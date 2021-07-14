//Tiago Menezes
//Pedro Carreiro

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <regex>

int recursioncounter = 0;
int initialsquares = 0;
int number_of_cases = 0;
int helper = 0;
int best = 0;
int moves = 0;
int size = 0;
int auxvalues[51][21][21];

//Check if matrix after move is equal to before
int isEqual(int moveAtual){
    //Return 0 - Not equal
    //Return 1 - Equal
    if (moveAtual != 0)
    {
        for (int i = 0; i < size; i++)
        {
        for (int j = 0; j < size; j++)
        {
            if (auxvalues[moveAtual][i][j] != auxvalues[moveAtual-1][i][j])
            {
                return 0;
            }
            
        }
        
        }
        return 1;
    }
    
    return 0;
    
}

//Moves

int moveLeft2(int move){
    //Returns number of squares that exist after the move
    int count = 0;
    
    for (int i = 0; i < size; i++)
    {   
        int temp = 0;
        int indexToWriteIn = 0;
        for (int j = 0; j < size; j++)
        {
            int flag = 0;

            if (auxvalues[move][i][j] != 0 && temp == auxvalues[move][i][j])
            {
                auxvalues[move+1][i][indexToWriteIn] = temp * 2;
                indexToWriteIn++;
                temp = 0;
                flag = 1;
            }

            if (auxvalues[move][i][j] != 0 && temp != auxvalues[move][i][j] && temp!=0)
            {
                auxvalues[move+1][i][indexToWriteIn] = temp;
                indexToWriteIn++;
                temp = auxvalues[move][i][j];
                count ++;
                flag = 1;
            }

            if (auxvalues[move][i][j] != 0 && flag == 0)
            {
                temp = auxvalues[move][i][j];
                count ++;
            } 

        }
       
        auxvalues[move+1][i][indexToWriteIn] = temp;

        for (int j = indexToWriteIn+1; j < size; j++)
        {
            auxvalues[move+1][i][j] = 0;
        }
        
    } 

    return count;
   
}

int moveUp2(int move){
    //Returns number of squares that exist after the move
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        int temp = 0;
        int indexToWriteIn = 0;

        for (int j = 0; j < size; j++)
        {
            int flag = 0;

            if (auxvalues[move][j][i] != 0 && temp == auxvalues[move][j][i])
            {
                auxvalues[move+1][indexToWriteIn][i] = temp * 2;
                indexToWriteIn++;
                temp = 0;
                flag = 1;
            }

            if (auxvalues[move][j][i] != 0 && temp != auxvalues[move][j][i] && temp!=0)
            {
                auxvalues[move+1][indexToWriteIn][i] = temp;
                indexToWriteIn++;
                temp = auxvalues[move][j][i];
                flag = 1;
                count ++;
            }

            if (auxvalues[move][j][i] != 0 && flag == 0)
            {
                temp = auxvalues[move][j][i];
                count ++;
            } 
        }

        auxvalues[move+1][indexToWriteIn][i] = temp;

        for (int j = indexToWriteIn+1; j < size; j++)
        {
            auxvalues[move+1][j][i] = 0;
        }
        
    }
    
    return count;
}

int moveRight2(int move){
    //Returns number of squares that exist after the move
    int count = 0;
    for (int i = size-1; i >= 0; i--)
    {   
        int temp = 0;
        int indexToWriteIn = size-1;
        for (int j = size-1; j >= 0; j--)
        {
            int flag = 0;

            if (auxvalues[move][i][j] != 0 && temp == auxvalues[move][i][j])
            {
                auxvalues[move+1][i][indexToWriteIn] = temp * 2;
                indexToWriteIn--;
                temp = 0;
                flag = 1;
            }

            if (auxvalues[move][i][j] != 0 && temp != auxvalues[move][i][j] && temp!=0)
            {
                auxvalues[move+1][i][indexToWriteIn] = temp;
                indexToWriteIn--;
                temp = auxvalues[move][i][j];
                flag = 1;
                count ++;
            }

            if (auxvalues[move][i][j] != 0 && flag == 0)
            {
                temp = auxvalues[move][i][j];
                count ++;
            } 

        }
       
        auxvalues[move+1][i][indexToWriteIn] = temp;

        for (int j = indexToWriteIn-1; j >= 0; j--)
        {
            auxvalues[move+1][i][j] = 0;
        }
    } 

    return count;
}

int moveDown2(int move){
    //Returns number of squares that exist after the move
    int count = 0;
    
    for (int i = size-1; i >= 0; i--)
    {
        int temp = 0;
        int indexToWriteIn = size-1;

        for (int j = size-1; j >= 0; j--)
        {
            int flag = 0;

            if (auxvalues[move][j][i] != 0 && temp == auxvalues[move][j][i])
            {
                auxvalues[move+1][indexToWriteIn][i] = temp * 2;
                indexToWriteIn--;
                temp = 0;
                flag = 1;
            }

            if (auxvalues[move][j][i] != 0 && temp != auxvalues[move][j][i] && temp!=0)
            {
                auxvalues[move+1][indexToWriteIn][i] = temp;
                indexToWriteIn--;
                temp = auxvalues[move][j][i];
                flag = 1;
                count ++;
            }

            if (auxvalues[move][j][i] != 0 && flag == 0)
            {
                temp = auxvalues[move][j][i];
                count ++;
            } 
        }

        auxvalues[move+1][indexToWriteIn][i] = temp;

        for (int j = indexToWriteIn-1; j >= 0; j--)
        {
            auxvalues[move+1][j][i] = 0;
        }

    }
    
    return count;
}

//Recursive function using backtracking, base to solve the problem
void recursive(int nmoves,int squares, bool left, bool right, bool up, bool down){
    //Changes best to minimum number of moves needed 
    int different = 0;
    bool left2, right2, up2, down2;
    recursioncounter += 1;


    //Base case
    
    if (squares == 1 && nmoves < best)
    {
        best = nmoves;
        return;
    }
    
    //Reject cases

    if(nmoves == moves || nmoves >= best){
        return;
    }

    //Recursao

    //Left Move
    
    if (left)
    {   
        helper = moveLeft2(nmoves);

        if (helper != squares)
        {
            left2 = true;
            different = 0;
        }

        else
        {
            left2 = false;
            different = isEqual(nmoves+1);
        }
        
        if (different == 0 )
        {
            recursive(nmoves +1, helper, left2, left2, true,true);
        }
    }
    

    //Up Move
    
    if (up)
    {   
        helper = moveUp2(nmoves);
        if (helper != squares)
        {
            up2 = true;
            different = 0;
        }

        else
        {
            up2 = false;
            different = isEqual(nmoves+1);
        }
            
        if (different == 0 )
        {
            recursive(nmoves +1, helper, true, true, up2, up2);
        }
    }

    //Right Move
    
    if (right)
    {   
        helper = moveRight2(nmoves);
        if (helper != squares)
        {
            right2 = true;
            different = 0;
        }

        else
        {
            right2 = false;
            different = isEqual(nmoves+1);
        }
        
        if (different == 0 )
        {
            recursive(nmoves +1, helper, right2, right2, true,true);
        }
    }
    
    //Down Move
   
    if (down)
    {   
        helper = moveDown2(nmoves);
        if (helper != squares)
        {
            down2 = true;
            different = 0;
        }
        else
        {
            down2 = false;
            different = isEqual(nmoves+1);
        }
        
        if (different == 0)
        {
            recursive(nmoves +1, helper, true, true, down2, down2);
        }
        
        
    }

}

//Checks if the problem can be solved using the sum of the values of every piece

int preAnalysis2(int sum){
    //Return 1 - Can not be solved
    //Return 0 - Can be solved
    float g = log2(sum);
    float rest = remainder(g,1);
    if (rest != 0)
    {
        return 1;
    }
    return 0;
}

//Main function
//Reads every test case and calls the recursive function used to solve the problem after checking if the can be solved using "preAnalysis2"
int main() {

    int n = 0;
	scanf("%d", &number_of_cases);
    int preflag = 0;
	int sumOfAll;
    for (int i = 0; i < number_of_cases; i++)
    {
        initialsquares = 0;
        scanf("%d", &size);
        scanf("%d", &moves);
        best = moves +1 ;
        sumOfAll = 0;

        for (int k = 0; k < size; k++)
        {
            for (int j = 0; j < size; j++)
            {
                scanf("%d", &n);
                auxvalues[0][k][j] = n;
            
                if (n!=0)
                {   
                    initialsquares ++;
                    sumOfAll += n;                
                }

            }
            
        }

        preflag = preAnalysis2(sumOfAll);
        
        if (preflag == 0)
        {
            if (initialsquares!= 1 && initialsquares!=0)
            {
                recursive(0, initialsquares, true, true, true, true);
            }

            else if (initialsquares == 1)
            {
                best = 0;
            }
 
            if (best < moves+1)
            {
            printf("%d\n",best);
            
            }

            else
            {
                printf("no solution\n");
            }
        }
        
        else
            {
                printf("no solution\n");
            }
     
    }                                                                                                                                

	return 0;

}