/* ECE 209 - Program 2
   
   bglite -- a backgammon-like game

   User interface code (main function) is provided by G. Byrd.

   ***** YOUR NAME GOES HERE *****
Name: Tri Nguyen 
This program consists of 6 functions that set the game, check for posible move, check if the user enter a legal move,
execute the move, move a piece out of jail and check for a winner.

User enter a random number to start the game, each turn enter a prediction of the dice number. if the prediction is correct the user 
can execute the move twice. 

User then enter a starting position to execute the move. 
   October 2016
*/

#include <stdio.h>
#include <stdlib.h>

/* functions that you must write */

void initBoard(int *);  /* initialize the board */
int isWinner(int, int *);  /* check if player wins */
int anyLegalMoves(int, int *, int);  /* check for any move */
int isLegalMove(int, int *, int, int); /* check a specific move */
void doMove(int, int *, int, int);  /* perform a move */
void jailBreak(int, int*, int);   /* get one checker out of jail */

/* functions provided */
void printBoard(int *board);
void printPlayer(int player);
void printCheckers(int checkers);
int isInJail(int player, int *board);

#ifndef NOMAIN    /* ignore this line -- will explain later */


int main() 
{
  int mPlayer;   /* current player: +1 = Red, -1 = Blue */
  int mBoard[16];  /* board array -- see spec */

  int seed;      /* seed for random number generator */
  int roll;      /* result of rolling one six-sided die */
  int guess;     /* predicted roll */
  int move;      /* move counter */
  int start;     /* user-entered start position for move */
  int winner;    /* flag for winning */

  printf("Welcome to BG-Lite\n\n");
  printf("Enter an arbitrary seed value: ");
  scanf("%d", &seed);
  srand(seed);   /* seed the random number generator */

  initBoard(mBoard);   /* initialize the playing board */

  mPlayer = -1; /* set to Blue, will flip in the loop */
  winner = 0;

  do {  /* loop will end when winner found */

    mPlayer *= -1;   /* alternate player */
    
    printBoard(mBoard);  /* print the board */
    printf("**** ");
    printPlayer(mPlayer);
    printf("'s turn\n");

    printf("Enter a prediction: ");
    scanf("%d", &guess);

    roll = 1 + rand() % 6;  /* number between 1 and 6 */
    printf("Roll is %d.\n", roll);

    if (roll == guess) {
      printf("Congratulations!! You get two moves.\n");
      move = 2;
    }
    else {
      printf("Better luck next time.\n");
      move = 1;
    }

    while (!winner && (move > 0)) {
      
      if (! anyLegalMoves(mPlayer, mBoard, roll)) {
	printf("There are no legal moves for that roll.\n");
	break;  /* break out of outer loop */
      }

      if (isInJail(mPlayer, mBoard)) {
	printf("\n======== JAIL BREAK! ========\n");
	jailBreak(mPlayer, mBoard, roll);
      }
      else {
	while (1) {
	  printf("Enter starting position of your move: ");
	  scanf("%d", &start);
	  if (isLegalMove(mPlayer, mBoard, roll, start)) {
	    doMove(mPlayer, mBoard, roll, start);
	    break;  /* completed move break out of inner loop */
	  }
	  else {
	    printf("Move is not legal -- try again.\n");
	  }
	}
      }

      /* check to see if player has won */
      winner = isWinner(mPlayer, mBoard);
      move--;
      /* if pending move, print board */
      if (move) printBoard(mBoard);
    }

  } while (!winner);  /* until a winner is found */

  printPlayer(mPlayer);
  printf(" WINS!!!\n\n");

  return EXIT_SUCCESS;
}

#endif    /* ignore this line -- will explain later */

/* printBoard -- print an ASCII representation of the playing board */
/* input: 16-element board array                                    */
/* output: none                                                     */

void printBoard(int *board) {
  int pos;  /* position */

  printf("\n");

  /* print checkers in each spot */
  for (pos = 0; pos <= 13; pos++) {
    printCheckers(board[pos]);
    printf("  ");
  }
  printf("\n");

  /* print label for each spot:
     BH = blue home, RH = red home */
  printf("BH   ");
  for (pos = 1; pos <= 12; pos++) {
    printf("%02d   ", pos);
  }
  printf("RH\n");

  /* print JAIL */
  printf("JAIL: ");
  if (board[14]) {
    printCheckers(board[14]);
    if (board[15]) printf(",");
  }
  if (board[15]) {
    printCheckers(board[15]);
  }

  printf("\n\n");
  return;
}

/* printCheckers -- print number and color of checkers   */
/* input: number of checkers; pos = red, neg = blue      */
/* output: none                                          */
/* prints as three characters, left-justified            */

void printCheckers(int checkers) {
  char color = 'R';
  if (checkers < 0) {
    checkers = -checkers;   /* convert to positive */
    color = 'B';            /* and chance color */
  }
  if (checkers == 0) printf("   ");
  else if (checkers <= 8) printf("%d%c ", checkers, color);
  else printf("%d%c", checkers, color);
  return;
}

/* printPlayer -- prints name of player, all caps */
/* input: player = 1 if red, -1 if blue           */
/* output: none                                   */

void printPlayer(int p) {
  if (p == 1) printf("RED");
  else if (p == -1) printf("BLUE");
  return;
}

/* isInJail -- checks whether player has any checkers in Jail */
/* input: player = 1 if Red, -1 if Blue           */
/*        board = board array                     */
/* output: 1 if in Jail, 0 if not                 */

int isInJail(int p, int *b) {
  return 
    ((p > 0) && (b[14] != 0))
    || ((p < 0) && (b[15] != 0));
}


/****************************************************************/
/***  YOUR CODE GOES BELOW THIS LINE                            */
/***  DO NOT WRITE ABOVE THIS LINE                              */
/****************************************************************/

/*This function initialize the values of the board
Input: the board
Output: none 
*/
void initBoard(int array[]){
	array[0]=   0; /* initiate the base value of the board*/
	array[1]=   5; 
	array[2]=   0; 
	array[3]=   0;
	array[4]=   0; 
	array[5]=   3;
	array[6]=  -2; 
	array[7]=   2;
	array[8]=  -3; 
	array[9]=   0;
	array[10]=  0; 
	array[11]=  0;
	array[12]= -5; 
	array[13]=  0;
	array[14]=  0;
	array[15]=  0; 
}
	
/*This Function check if there is any possible move can be made with one specific roll of dice.
Input: player, board, roll of dice
Output: 1 if there is any legal move
	0 if there is no legal move
*/
int anyLegalMoves(int player, int array[], int dice){
int count,t, point, check, check1;
t=0;/*output*/ 
check = 0; /*check if any piece is behind a piece on the home half of the board( use for rule 7)*/
check1= 0; /* check if any piece is on the first half (for rule 5)*/
if( player ==1 ){ /* red*/
	for (count =1 ; count <7; count++){   /* check for posible move in the first half of the board*/
		if (array[count] >0) /*check if any piece is in the first half of the board, will be used to check if a piece can move home */
			check1 = check1 + 1;
		if((array[count]> 0) && (array[count + dice] >= -1)){ /*check if any move can be made on the first half of the board*/
			point =1; 
			t= t+ point;
			}
		}
	for (count =7 ; count <13; count++){/* check for posible move in the second half of the board*/
		if((array[count]> 0) && (array[count + dice] >= -1)&& ((dice + count) < 13)){ /* condition for a move that does not go home*/
			point =1; 
			t= t+ point;
			}
		}

	for (count =1 ; count <13; count++){/* check if a piece can move home*/
		if (array[count] >0) 
			check = check + 1;
		if((check1==0) &&((count + dice) >=13)&& (check ==1)) /* a move that go more than home( rule 7)*/
			t= 1;
		if ((check1==0) && ((count + dice)==13)) /* a move that go to home exactly*/
			t=1;
		}
	if ((array[14] >0) && (array[dice]<-1)) /* check if any piece in jail and can the roll move it out*/
		t=0;			
	if (t > 0)
		t= 1;  
}
else if( player ==-1 ){/* blue*/
	for (count =12 ; count >6; count= count -1){  /* check for posible move in the first half of the board*/
		if (array[count] <0) /*check if any piece is in the first half of the board, will be used to check if a piece can move home */
			check1 = check1 + 1; 
		if((array[count]< 0) && (array[count - dice] <= 1)){/*check if any move can be made on the first half of the board*/
			point =1; 
			t= t+ point;
			}
		}
	for (count =6 ; count >0; count= count -1){/* check for posible move in the second half of the board*/
		if((array[count]< 0) && (array[count - dice] <= 1)&& ((count-dice) > 0)){/* condition for a move that does not go home*/
			point =1; 
			t= t+ point;
			}
		}

	for (count =12 ; count >0; count =count -1){ /* check if a piece can move home*/
		if (array[count] <0) 
			check = check + 1;
		if((check1==0) &&((count - dice) <=0)&& (check ==1))/* a move that go more than home( rule 7)*/
			t= 1;
		if ((check1==0) && ((count - dice)==0))/* a move that go to home exactly*/
			t=1;
		}
	if ((array[15] <0) && (array[13-dice]>1)) /* check if any piece in jail and can the roll move it out*/
		t=0;
	if (t > 0)
		t= 1; 
}
return t;
}





/* This function check if the player a legal starting position for 1 specific roll of dice.
Input : player, board, roll of dice, starting position
Output: 1 if legal, 0 if illegal.
*/
int isLegalMove(int player, int array[], int dice, int pos){
int t, count, check1, check;
t=0;/*output*/ 
check = 0; /*check if any piece is behind a piece on the home half of the board( use for rule 7)*/
check1= 0; /* check if any piece is on the first half (for rule 5)*/
if (player ==1){/*red*/
	if ((pos>0)&&(pos<7)){ /* if postion on the first half of the board, check if it is legal*/
		if ((array[pos+ dice] >=-1) && (array[pos] >0))
			t= 1;
	}
	else if ((pos>6)&&(pos<13)){ /* if postion on the second half of the board, check if it is legal*/
		for (count =1 ; count <7; count++)
			if (array[count] >0) /*check if any piece is in the first half of the board (rule5) */
			check1 = check1 + 1;
		for (count =7; count <= pos; count++) /* check if any piece is behind the moving piece( rule 7)*/
	     		if (array[count] >0) 
				check = check + 1;
		if ((array[pos+ dice] >=-1) && ((pos + dice)<13)&& (array[pos] >0))/* legal move that does not go to home*/
			t= 1;
		if((check1==0) &&((pos + dice) >=13)&& (check ==1)&& (array[pos] >0)) /* move that go further than home (rule7)*/
			t= 1;
		if ((check1==0) && ((pos + dice)==13)&& (array[pos] >0))/* move that go exactly home(rule5)*/
			t=1;
	}
	else t =0 ;
}
if (player ==-1){/*blue*/
	if ((pos>6)&&(pos<13)){ /* if postion on the first half of the board, check if it is legal*/
		if ((array[pos- dice] <=1) && (array[pos] <0))
			t= 1;
		}
	else if ((pos>0)&&(pos<7)){ /* if postion on the second half of the board, check if it is legal*/
		for (count =12 ; count >6; count= count -1)
			if (array[count] <0) /*check if any piece is in the first half of the board (rule5) */
			check1 = check1 + 1;
			
		for (count =6; count >= pos; count= count-1) /* check if any piece is behind the moving piece( rule 7)*/
			if (array[count] <0) 
			check = check + 1;
			
		if ((array[pos- dice] <=1) && ((pos - dice)>0)&&(array[pos] <0))/* legal move that does not go to home*/
			t= 1;
		if ((check1==0) &&((pos - dice) <=0)&& (check ==1)&&(array[pos] <0)) /* move that go further than home (rule7)*/
			t= 1;
		if ((check1==0) && ((pos - dice)==0)&&(array[pos] <0))/* move that go exactly home(rule5)*/
			t=1;
	}
	else t =0 ;
}
if (array[pos]==0) /* user enter an empty cell*/
	t=0;
return t;
}

/* This function modify the board according to the player entered starting position and the roll of the dice
Input: player, board, roll of dice, starting position
Output: none.
*/
void doMove(int player, int array[], int dice, int pos){
int homer,homeb;
if (player ==1){ /*red*/
	homer = pos + dice;
	if ((pos + dice)>13)
		homer = 13;
	if (array[pos + dice] >=0){ /* no piece of the other player in the cell*/
		array[pos] = array[pos]-1;
		array[homer] = array[homer] +1;
		}
	else if (array[homer] ==-1){ /* 1 piece of the other player in the cell*/
		array[pos] = array[pos]-1;
		array[homer] = 1;
		array[15] = array[15] -1;
		}
	}	
if (player ==-1){ /*blue*/
	homeb = pos - dice;
	if ((pos - dice)<0)
		homeb = 0;
	if (array[homeb] <=0){ /* no piece of the other player in the cell*/
		array[pos] = array[pos]+1;
		array[homeb] = array[homeb] -1;
		}
	else if (array[homeb] ==1){ /* 1 piece of the other player in the cell*/
		array[pos] = array[pos]+1;
		array[homeb] = -1;
		array[14] = array[14] +1;
		}
	}	
}



/*This function move a piece out of jail if possible
Input: player, board, roll of dice
Output: none
*/
void jailBreak(int player, int array[], int dice){
if (player==1){ /*red*/
	if(array[dice]>=0){ /* jail to an unoccupy or cel with same color*/	
		array[14] = array[14]-1;
		array[dice]= array[dice] +1;
		}
	else if(array [dice] ==-1){/* jail to a cel with 1  different color piece color*/
		array[14] = array[14]-1;
		array[15] = array[15]-1;/* move the opposing piece to jail*/
		array[dice]= 1;
		}
	}
if (player==-1){ /*blue*/
	if(array[13-dice]<=0){ /* jail to an unoccupy or cel with same color*/	
		array[15] = array[15]+1;
		array[13-dice]= array[13-dice] -1;
		}
	else if(array[13-dice] ==1){/* jail to a cel with 1  different color piece*/
		array[15] = array[15]+1;
		array[14] = array[14]+1;/* move the opposing piece to jail*/
		array[13-dice]= -1;
		}
	}
}



/* This function check if a player has 10 piece in their home
Input:player, board
Output: 1 if he has 10 pieces, 0 if not
*/
int isWinner(int player, int array[]){
int t;
t= 0;
if ((player ==1)&& (array[13]==10)) /*red home has 10*/
	t= 1;
if ((player ==-1)&& (array[0]==-10)) /*blue home has 10*/
	t= 1;
return t;
}	























