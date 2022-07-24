#include <stdio.h>
#include <stdlib.h>
#define PLAYER_1 'A'
#define PLAYER_2 'B'
#define KAV ' '
/* All the functions that i used*/
char** alloc2dArray(int rows , int cols);
void Check(int rows, int cols);
void print_welcome_size(char** board,int rows,int cols);
void printBoard(char** board, int rows,int cols);
void update_player(int* current_player);
char** putXorO(char** board, int rows, int cols,int CurrentPlayer);
void check_row_win(char** board, int rows, int cols);
void check_diameter1_win(char** board, int rows, int cols);
void check_col_win(char** board, int rows, int cols);
void check_diameter2_win(char** board, int rows, int cols);
void myfree(char** board, int rows, int cols);

int main()
{
    /*lines 22-31 giving integers and char double array board and also scanning the rows,cols */
   int rows,cols,rowsplay,colsplay,maxRounds,CurrentPlayer,roundsPlayed=0;
   CurrentPlayer=PLAYER_1;
   char** board;
   printf("Enter the dimensions of the board: ");
   scanf("%d",&rows);
   scanf("%d",&cols);
   Check(rows,cols);
   maxRounds=rows*cols;
   board=alloc2dArray(rows,cols); /* allocating memory*/
   print_welcome_size(board,rows,cols);
   while(roundsPlayed!=maxRounds) /* if this while ends with no result the FINAL result will be tie because the whole board is filled*/
   {

       printf("\nThe turn of %c, type your choice (row col): ",CurrentPlayer);
       scanf("%d",&rowsplay); /* scanning two new integers the player puts*/
       scanf("%d",&colsplay);
       if(rowsplay>rows||rowsplay<0||colsplay>cols||colsplay<0||colsplay==cols||rowsplay==rows) /* checking if the input is legal*/
       {
           printf("\nInput Error!");
           myfree(board,rows,cols);
           exit(1);
       }
       /* lines 45-50 functions*/
       putXorO(board,rowsplay,colsplay,CurrentPlayer);
       printBoard(board,rows,cols);
       check_row_win(board,rows,cols);
       check_col_win(board,rows,cols);
       check_diameter1_win(board,rows,cols);
       check_diameter2_win(board,rows,cols);
       update_player(&CurrentPlayer); /* switching between player a and b*/
       roundsPlayed++;
   }
   printf("\nTIE");
   myfree(board,rows,cols); /* freeing memory*/
   exit(0);



}
char** alloc2dArray(int rows , int cols) /*function that allocates memory for the char double array board*/
{
    char** Board;
    int i;
    Board= (char**)malloc(rows*sizeof(char*));
    if(Board == NULL)
    {
        printf("Allocation failed!\n");
        exit(1);
    }
    for(i=0; i<cols; i++)
    {
        Board[i]=(char*)malloc(cols*sizeof(char));
        if(Board[i] == NULL)
        {
            printf("Allocation failed!\n");
            exit(1);
        }
    }
    return Board;
}
void Check(int rows, int cols) /* function to check if the first input is legal*/
{
    if(rows!=cols)
    {
        printf("\nInput Error!");
        exit(1);
    }
    if(rows<3&&cols<3)
    {
        printf("\nInput Error!");
        exit(1);
    }
}
void print_welcome_size(char** board,int rows,int cols) /* function that prints out welcome board after a legal input*/
{
    for (int i= 0; i< rows; i++)
    {
        for (int j= 0; j< cols; j++)
        {
            board[i][j]= KAV; /* KAV is defined as ' '*/
        }
    }
    printBoard(board,rows,cols);
}
void printBoard(char** board, int rows,int cols) /* function to print the board after a legal input*/
{
    printf("\n");
    int i,j;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            printf("[%c] ",board[i][j]);
        }
    printf("\n");
    }
}

void update_player(int* CurrentPlayer) /* function that switches between player a and b*/
{
  if(*CurrentPlayer==PLAYER_1)
  {
      *CurrentPlayer=PLAYER_2;
  }
  else
  {
     if(*CurrentPlayer==PLAYER_2)
     {
        *CurrentPlayer=PLAYER_1;
     }
  }
}



char** putXorO(char** board, int rows, int cols,int CurrentPlayer) /* function that checks if the place the user enters is not taken and puts X or O in it and if the place is taken it will print an error*/
{
   if(board[rows][cols]==KAV)
   {
       if(board[rows][cols]!='X'||board[rows][cols]!='O')
       {

           if(CurrentPlayer==PLAYER_1)
           {
              board[rows][cols]='X';
           }
           else
           {
              board[rows][cols]='O';
           }

       }
       else
       {
           printf("\nInput Error!");
           myfree(board,rows,cols);
           exit(1);
       }
   }
   else
   {
       printf("\nInput Error!");
       myfree(board,rows,cols);
       exit(1);
   }
   return board;
}

void check_row_win(char** board, int rows, int cols) /*function that checks if the player  A or B has won*/
{
    /* this function works by checking if the whole row is filled with the same symbol*/
    int i,j,counterX=0,counterO=0;
    for(i=0; i<rows; i++)
    {
        counterX = 0; /* if the whole row is not filled with the same symbol it makes the counter 0 so we can check the next row*/
        counterO = 0;
        for(j=0; j<cols; j++)
        {
            if(board[i][j]=='X')
            {
                counterX++;
            }
            if(board[i][j]=='O')
            {
                counterO++;
            }
        }
        if(counterX==cols) /* if the counter is equal to the number of cols then we have found a winner*/
        {
            printf("\nPlayer %c won the game!",PLAYER_1);
            myfree(board,rows,cols);
            exit(0);
        }
        if(counterO==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_2);
            myfree(board,rows,cols);
            exit(0);
        }
    }

}

void check_diameter1_win(char** board, int rows, int cols) /* this function checks if the left diameter is filled with the same symbol*/
{
    /* the way this function works is by checking when the row and col number is equal and goes to check if it is filled with X or O because the diameter one has the same numbers, for example 00,11,22*/
    int i,j,counterX=0,counterO=0;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<rows; j++)
        {
            if(i==j)
            {
                if(board[i][j]=='X')
                {
                   counterX++;
                }
                if(board[i][j]=='O')
                {
                   counterO++;
                }
            }

        }
        if(counterX==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_1);
            myfree(board,rows,cols);
            exit(0);
        }
        if(counterO==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_2);
            myfree(board,rows,cols);
            exit(0);
        }
    }

}
void check_col_win(char** board, int rows, int cols) /* this function works by checking if the who col is filled with the same symbol,similar to the row function*/
{
    /* this function works by checking if the whole col is filled with the same symbol*/
    int i,j,counterX=0,counterO=0;
    for(i=0; i<rows; i++)
    {
        counterX = 0; /* if the whole col is not filled with the same symbol it makes the counter 0 so we can check the next col*/
        counterO = 0;
        for(j=0; j<cols; j++)
        {
            if(board[j][i]=='X')
            {
                counterX++;
            }
            if(board[j][i]=='O')
            {
                counterO++;
            }
        }
        if(counterX==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_1);
            myfree(board,rows,cols);
            exit(0);
        }
        if(counterO==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_2);
            myfree(board,rows,cols);
            exit(0);
        }
    }

}
void check_diameter2_win(char** board, int rows, int cols) /* this function checks if diameter 2 is filled with same symbol(right diameter)*/
{
    /*in the tictactoe board the right diameter from up to down always equal the numbers of rows or cols but in our case we start from 0 to we check rows-1,for example 0 2, 1 1 , 2 0 they always equal 2 */
    int i,j,counterX=0,counterO=0;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<rows; j++)
        {
            if(i+j==rows-1)
            {
                if(board[i][j]=='X')
                {
                   counterX++;
                }
                if(board[i][j]=='O')
                {
                   counterO++;
                }
            }

        }
        if(counterX==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_1);
            myfree(board,rows,cols);
            exit(0);
        }
        if(counterO==cols)
        {
            printf("\nPlayer %c won the game!",PLAYER_2);
            myfree(board,rows,cols);
            exit(0);
        }
    }

}
void myfree(char** board, int rows, int cols) /*function that frees the memory*/
{
    int i=0;
    while( i<rows )
     free(board[i++]);
    free(board);
    return;

}
