// ttt.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_board(int *board, int length);
void get_move(int *board, int length, int player);
void toggle_player(int *player);
int check_board(int *board, int length);
void copy_board(int *board, int length, int *copy);
int AI_player(int *board, int length, int player, int difficulty);

void print_board(int *board, int length){
	/*
	Board of form:
	 0 | 1 | 2 
	-----------
	 3 | 4 | 5
	-----------
	 6 | 7 | 8
	*/
	char b[length];
	int i = 0;
	for(i=0;i<length;i++){
		switch(board[i]){
			case 0:
				b[i] = (char)(i + 48);
				break;
			case 1:
				b[i] = 'X';
				break;
			case 2:
				b[i] = 'O';
				break;
			default:
				b[i] = '?';
				break;
		}
	}
	printf(" %c | %c | %c\n-----------\n %c | %c | %c\n-----------\n %c | %c | %c\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8]);
}


void get_move(int *board, int length, int player){
    int move = -1;
    int escape = 0;
    while(!escape){
        printf("\tChoose your move: ");
        scanf("%d", &move);
        if(move >= 0 && move <= 8 && !board[move]){
            board[move] = player;
            escape = 1;
        }
    }
}


void toggle_player(int *player){
    if(*player == 1){
        *player = 2;
    }else if(*player == 2){
        *player = 1;
    }else{
        *player = 3;
    }
}


int check_board(int *board, int length){
    int i = 0;
    int full = 1;
    
    // Check win
    /*  */if(board[0]==board[1] && board[0]==board[2] && board[0]!=0){
		return board[0];
	}else if(board[3]==board[4] && board[3]==board[5] && board[3]!=0){
		return board[3];
	}else if(board[6]==board[7] && board[6]==board[8] && board[6]!=0){
		return board[6];
	}else if(board[0]==board[3] && board[0]==board[6] && board[0]!=0){
		return board[0];
	}else if(board[1]==board[4] && board[1]==board[7] && board[1]!=0){
		return board[1];
	}else if(board[2]==board[5] && board[2]==board[8] && board[2]!=0){
		return board[2];
	}else if(board[0]==board[4] && board[0]==board[8] && board[0]!=0){
		return board[0];
	}else if(board[2]==board[4] && board[2]==board[6] && board[2]!=0){
		return board[2];
	}
	
	// Check draw
	for(i=0;i<length;i++){
	    if(!board[i]){
	        full = 0;
	    }
	}
	if(full){
	    return 3;
	}else{
	    return 0;
	}
}


void copy_board(int *board, int length, int *copy){
    int i = 0;
    for(i=0;i<length;i++){
        copy[i] = board[i];
    }
}


int random_number(int lower, int upper){
    // Generates random numbers in range [lower, upper]. 
    int rnum = (rand() % (upper - lower + 1)) + lower;
    return rnum;
}


int gen_random_move(int *board, int length){
	int i = 0;
	int empty[9], j = 0, move = 0;
	srand(time(0));

	for(i=0;i<length;i++){
		if(board[i] == 0){
			empty[j] = i;
			j++;
		}
	}

	if(j == 0){
		return -1;
	}else{
		i = random_number(0, j);
		return empty[i];
	}


}


int AI_player(int *board, int length, int player, int difficulty){
    int i = 0, check = 0, state;
    int b[length], empty_square = -1;
    
    copy_board(board, length, b);
    
    // Check on board
    for(i=0;i<length;i++){
        // Check for empty square
        if(!b[i]){
            
            copy_board(board, length, b);
            
            // Check if winning move
            b[i] = player;
            state = check_board(b, length);
            if(state == player){
            	printf("ATTACK!\n");
                return i;
            }
        }
    }

    for(i=0;i<length;i++){
    	if(!b[i]){

    		copy_board(board, length, b);
            // Check if losing move
            if(player == 1){
                b[i] = 2;
            }else if(player == 2){
                b[i] = 1;
            }
            state = check_board(b, length);
            if(state != player && state){
            	printf("DEFEND!\n");
                return i;
            }
        }
    }

    empty_square = gen_random_move(board, length);
    printf("RANDOM!\n");

    return empty_square;
}


int main(void){
	int length = 9;
	int board[length];
	int i = 0;
	int player = 1;
	int state = 0;
	int computer_move = -1;
	for(i=0;i<length;i++){
	    board[i] = 0;
	}
	
	for(i=0;i<length;i++){
	    if(player == 1){
	    	print_board(board, length);
    	    get_move(board, length, player);
	    }else if(player == 2){
	        computer_move = AI_player(board, length, player, 0);
	        printf("\tComputer's move: %d\n", computer_move);
	        if(computer_move == -1){
	            state = check_board(board, length);
	            break;
	        }
	        board[computer_move] = player;
	    }
    	
    	toggle_player(&player);
    	state = check_board(board, length);
    	if(state){
    	    break;
    	}
	}

	if(state == 3){
		printf("\n\tCat's Game!\n");
	}else{
		printf("\n\tThe winner is Player %d!\n", state);
	}
	print_board(board, length);

	return 0;
}
