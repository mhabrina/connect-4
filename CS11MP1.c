#include <stdio.h>
#include <stdlib.h>


/*
My game has 3 functions:

1. function for the game itself. when a player picks a column, this function places the players symbol into that said column. symbols are stacked until the topmost row. if the row is already filled, the function tells the player to choose another one that is available

2. this function checks whether a player has already won. it checks every time a player makes a turn

3. this function is the one that checks if the game is a tie


My program uses the <stdlib.h> header for the exit() function. once a player wins or the game is a tie, the game terminates via exit() function
*/


void game(char a[6][7], int co, char sym);
int winner(char beb[6][7], char symbol);
void tie(char b[6][7], char sy, char symb);


int main(){
	char arr[6][7];
	int i,j;
	char sym1, sym2;

	printf("Welcome to Connect-4 Game!\n");


//for loop to assign "-" to every element of arr[6][7]

	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			arr[i][j] = '-' ;

		}
	}


//for loop to print initial state of game	

	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			printf("%c\t", arr[i][j]);
		}
		printf("\n");
	}


//Here players enter their symbol that is not equivalent to "-" and they must not be equal	

	printf("Player 1, enter your symbol:");
	scanf("%c", &sym1);

	while(sym1=='-'){
		printf("Invalid symbol. Try again.\nPlayer 1, enter your symbol:");
		scanf("%c", &sym1);
	}

	printf("Player 2, enter your symbol:");
	scanf("%c", &sym2);

	while(sym1==sym2||sym2=='-'){
		printf("Invalid symbol. Try again.\nPlayer 2, enter your symbol:");
		scanf("%c", &sym2);
	}

	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			printf("%c\t", arr[i][j]);
		}
		printf("\n");
	}

//the game proper. in do-while form so that the game repeats until a player wins

	int col,win;

	do{
		printf("Player 1, choose a column:");
		scanf("%d", &col);

		while(col<1&&col>7){
			printf("Invalid column number. Try again.\nPlayer 1, choose a column:");
			scanf("%d", &col);
		}

/*every time a player makes a turn, the main function makes three function calls. one, to update the game, two, to check if someone wins and three, to check if there is a tie*/	

		game(arr, col, sym1);
		win=winner(arr, sym1);
		tie(arr, sym1, sym2);

/*the winner function returns a value to check whether a player has won. if the functikn returns a zero, the game continues since no player has won. if the function returns a one, it means a player has won and the game terminates*/

		if(win==1){
			printf("Player 1 has won the game.\n");
			exit(0);
		}
		else
			continue;

//player 2 mechnics same as player 1's

		printf("Player 2, choose a column:");
		scanf("%d", &col);

		while(col<1&&col>7){
			printf("Invalid column number. Try again.\nPlayer 2, choose a column:");
			scanf("%d", &col);
		}

		game(arr, col, sym2);
		win=winner(arr, sym2);
		tie(arr, sym2, sym1);

		if(win==1){
			printf("Player 2 has won the game.\n");
			exit(0);
		}
		else
			continue;	

	}while(col>0||col<7);

return 0;

}

void game(char a[6][7], int co, char sym){

	int k, l;

//do-while loop for filled in rows	

	do{
		if(a[0][co-1]!='-'){
			printf("Invalid column number. Try again.\nChoose a column:");
			scanf("%d", &co);
		}
	}while(a[0][co-1]!='-');


//for loop to change board game from "-" to player's symbol

	for(k=5;k>=0;k--){
		if(a[k][co-1]=='-'){
			a[k][co-1]=sym;
			    k=-1;
	    }
		else
		    continue;
	}

//for loop to print updated board game

	for(k=0;k<6;k++){
		for(l=0;l<7;l++){
			printf("%c\t", a[k][l]);
		}
		printf("\n");
	}

}


int winner(char beb[6][7], char symbol){

//this function is divided into four parts to determine the winner

//horizontal

	int h, i, cone;


/*for loop that starts from bottom row 1st column. it checks the first 4 elements from each row if it is equal to three consective elements to the right. if it is the player has won.*/

	for(h=5; h>=0; h--){
		for(i=0; i<4;i++){
			if(beb[h][i]==symbol){
				if((((beb[h][i]==beb[h][i+1])&&beb[h][i]==beb[h][i+2])&&beb[h][i]==beb[h][i+3])){
        			return 1;
     			}
				else if((beb[h][i+1]=='-'||beb[h][i+2]=='-')||beb[h][i+3]=='-')
					continue;
			}
    		else if(beb[h][i]=='-')
				continue;
		}
	}

/*vertical. it checks the last 3 rows of each column if it is equal to three consecutive elements above it.if four consecutive elements are equal, player has won*/

	for(h=5; h>=3; h--){
		for(i=0; i<7;i++){
			if(beb[h][i]==symbol){
				if((((beb[h][i]==beb[h-1][i])&&beb[h][i]==beb[h-2][i])&&beb[h][i]==beb[h-3][i])){
        			return 1;
    			}
				else if((beb[h-1][i]=='-'||beb[h-2][i]=='-')||beb[h-3][i]=='-')
					continue;
			}
			else if(beb[h][i]=='-')
				continue;
		}
	}

/*diagonal to the right. it checks the last 3 rows of the first 4 columns for four equal consecutive elements diagonally to the right. if a diahonal exists,a player has won*/

	for(h=5; h>=3; h--){
		for(i=0; i<4;i++){
		    if(beb[h][i]==symbol){
			    if((((beb[h][i]==beb[h-1][i+1])&&beb[h][i]==beb[h-2][i+2])&&beb[h][i]==beb[h-3][i+3])){
			        return 1;
			    }
			    else if((beb[h-1][i+1]=='-'||beb[h-2][i+2]=='-')||beb[h-3][i+3]=='-')
        			continue;
			}
		    else if(beb[h][i]=='-')
				continue;
		}
	}

/*diagonal to the left. it checks the last 3 rows of the last 4 columns for four equal consecutive elements diagonally to the left. if a diagonal exists, a player has won*/

	for(h=5; h>=3; h--){
		for(i=3; i<7;i++){
		    if(beb[h][i]==symbol){
				if((((beb[h][i]==beb[h-1][i-1])&&beb[h][i]==beb[h-2][i-2])&&beb[h][i]==beb[h-3][i-3])){
			        return 1;
			    }
			    else if((beb[h-1][i-1]=='-'||beb[h-2][i-2]=='-')||beb[h-3][i-3]=='-')
			        continue;
			}
    else if(beb[h][i]=='-')
	    continue;
		}
	}

return 0;

}


void tie(char b[6][7], char sy, char symb){


/*if statement to check if there is a tie. the elements of the first row is checked if it is not equal to "-". if all elements is not equal to "-"(meaning it is changed to the player's symbol) and no player has won, then the game is a tie*/

	if(b[0][0]!='-'){
		if((((((b[0][1]!='-'&&b[0][2]!='-')&&b[0][3]!='-')&&b[0][4]!='-')&&b[0][5]!='-')&&b[0][6]!='-')){
			printf("Tie game.");
			exit(0);
		}
	}

}