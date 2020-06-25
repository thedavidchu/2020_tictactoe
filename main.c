#include <stdio.h>
#include <stdlib.h>

int print_board(char *board);
int init_board(char **board);
int get_move(char *move);

int print_board(char *board){
  printf(" %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n", board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);
  return 0;
}

int init_board(char **board){
  int i=0;
  *board = (char *)malloc(9);
  
  for(i=0;i<9;i++){
    (*board)[i]=(char)(i+'0'); /* *board[i] doesn't work; (*board)[i] works*/
  }
  return 0;
}

int get_move(char *move){
  int r=0;
  printf("Enter move: ");
  fgets(move);
  printf("move: %c\n", *move);
  return 0;
}

int check_move()

int main(){
  int r=0;
  char *board=NULL;
  char move;

  printf("Welcome to tic tac toe!\n");

  r=init_board(&board);
  printf("init_board: %d\n", r);
  r=print_board(board);
  printf("print_board: %d\n", r);
  scanf(" %c",&move);
  printf("Value: %c\n",move);
  r=get_move(&move);
  printf("get_move: %c\n",move);
  return 0;
}
