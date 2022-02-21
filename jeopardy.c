/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
	int SizeTksAry = 0; //used for token array size
// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens){ //index tokens array wth i, also keep track of array size
	char *splitPoint = strtok(input," ");//initial split 
	splitPoint[strlen(splitPoint) -1] = '\0';
	int i = 0;
	while(splitPoint != NULL){
		tokens[i++] = splitPoint;// capture users input after split
		splitPoint = strtok(NULL," ");//cont give pieces of last string
		//setting to null will split once at space and then up to end of line
	}
	printf("\n");
	SizeTksAry = i; // set the size of the input array tokens for determing how many times to validiate answer
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

void Player_In(player *players, char *N){
	int i = 0;
	while(i < NUM_PLAYERS){ // takes 4 name inputs 
	printf("Enter in Player Name: ");
	//scanf("%s",N);
	fgets(N,BUFFER_LEN,stdin);// use fgets for spaces 
	N[strlen(N) -1] = '\0'; // makeing null is in the right place
	strcpy((players[i].name),N); // initialize each of the players in the array
	players[i].score = 0;       
	i++;
    	}
}

int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
	
    // Display the game introduction and initialize the questions
    system("clear");// clear(s) is being used to chnage displays in the terimal
    initialize_game();// states the game and how to play

    // Prompt for players names  
    char Name[BUFFER_LEN];
    Player_In(players,Name); // call user name input function
	system("clear");
    // Perform an infinite loop getting command input from users until game ends
    char category[BUFFER_LEN],name[BUFFER_LEN],answer[BUFFER_LEN]; int value,num_players,score;
	int QCount = 1;// setting a Q counter to exit out of main while loop
    while (QCount <= 12) //(fgets(buffer,BUFFER_LEN,stdin) != NULL)
    {
		system("clear");
    	display_categories();//call and create the dsiplay of question values 
    	for (int i = 0; i<NUM_PLAYERS ;i++){ printf("[Player %d: ",i+1); printf("%s $%d]",players[i].name,players[i].score);  }
    	printf("\n"); // the for loop is used to print out Players name and scores at the bottom of the question values
		int num,lower = 1,upper = 5; // used for rand sel a player to type in their name
		num = rand()%(upper-lower)+1;
		char bufReplace[BUFFER_LEN];// used for clearing out garbage
		memset(bufReplace,'\0',sizeof(char)*BUFFER_LEN); // set the above with all nulls
		printf("Type in your name Player %d: ",num);// promt user to type in their name
		for (;;){
			strcpy(buffer,bufReplace);// replce the buffer array on line 58  to get rid of garbage
			fgets(buffer,BUFFER_LEN,stdin);// get teh user input 
			buffer[strlen(buffer) -1] = '\0'; // make sure that null is in the right place 
			if (player_exists(players, NUM_PLAYERS, buffer) == 1 && strcmp(players[num-1].name,buffer) == 0){
				system("clear"); // make sure the the player inputed is the player playing 
				display_categories(); // redisplay with user playing 
				printf("\nPlayer %d please type a Category <CATEGORY OPTIONS:  P,A,D > " ,num);
				while(1){ // ask for what category that will want to choose then he value from that category
					for(;;){ // infinte for loops used for makign sure the sure sel correctly
						fgets(category,BUFFER_LEN,stdin); // get user input and make sure it is correct
						category[strlen(category) - 1] = '\0';
						category[0] = toupper(category[0]);
						if(strcmp(category,"P")==0 || strcmp(category,"A")==0 || strcmp(category,"D")==0 ){
							break;
						}else{printf("\nPlease type a category P,A,D: ");}
						strcpy(category,bufReplace);
					}
					printf("\nPlayer %d please type a value from category %s > " ,num,category);
					for(;;){
						char strInt[BUFFER_LEN]; // gettign user value as a string teh using atoi to make it int
						//scanf("%d",&value);    // from tthere the int is used to check for right val sel 
						strcpy(buffer,bufReplace);
						fgets(strInt,BUFFER_LEN,stdin);
						strInt[strlen(strInt) -1] = '\0';
						value = atoi(strInt);
						if (value == 400 || value == 800 || value == 1200 || value == 1600){
							break;
						}else{printf("\nPlease type in a number that listed above for category %s: ", category);}
					}
					if(already_answered(category, value) == false){ break; // make sure that user sel a not answered question
					} else { 
					printf("\nSry that has already been taken, Player %d please type a Category <CATEGORY OPTIONS:  P,A,D > " ,num); 
					}
				}
				fflush(stdin); // flush out left over input
				display_question(category, value); // display teh question teh user selected
				printf("\nWhat is your answer Player %d :", num); // Ask for answerfrom user
				strcpy(buffer,bufReplace);
				fgets(buffer,BUFFER_LEN,stdin); // get user input and make sure that the null is in the right place
				buffer[strlen(buffer) -1] = '\0';
				char *array[BUFFER_LEN + 1]; // allocated memeory for pointer to point
				char **Tks = array;// holding pieces of text for input with space 
				tokenize(buffer,Tks);// call tokenizen for distroying user input and creating a array of inputs
				int t = 0; bool Y = false; // use a bool to determine when a answer is correct and conitne otherwise
				                           // with checikng until the end of the array of inputs
				for(t = 0; t < SizeTksAry ;t++){
					if (valid_answer(category, value, Tks[t]) == false){continue;} 
					else{Y = true; break;}
				}
				if (Y == false){system("clear");printf("\n---SORRY THAT'S INCORRECT---");}
				else {  // when Y is false the user did not get teh correct answer, when true 
					system("clear"); // proceed to updating player socre
					printf("\n!!!CORRECT!!!"); 
					update_score(players,NUM_PLAYERS, players[num-1].name,value); 
				}
				printf("\n");
				sleep(1);
				num = rand()%(upper-lower)+1;// used for getting teh player number
				break;// break to allow for the next player to play
			// Call functions from the questions and players source files

			// Execute the game until all questions are answered

			// Display the final results and exit
			} else { printf("Name Inncorrect please try again Player %d: ",num);}// this outputs when teh user does not input a name corretcly 
		}
		QCount++;// counter teh Q count for exiting loop when 12 questions have reached
    }
	system("clear");// clear for the end results 
	printf("\n");
	printf("\nEND GAME RESULTS:\n");
	int indexs[4];
	int k  = 0 ;
	while(k < 4){ // used for finding the max and printing it out whil also remeber not to check that number 
		int max = 0,ind = 0;
		bool x = false;
		for(int i = 0;i<4;i++){ // loop each player 
				for (int j;j<4;j++){ // if players score index is in indexs then skip doign any checks with this index 
					if (i == indexs[j]){x = true; break;}
				}
				if ( x == false && max < players[i].score){max = players[i].score; ind = i;} //  used for replacing the 
				                      // current max and max index 
		}
		indexs[k] = ind;// addign max index to indexs array for ignoring in other checks 
		k++;
	}
	for (int i = 0;i<4;i++){
		printf("\n%s %d",players[indexs[i]].name,players[indexs[i]].score);// printing out the player and user score
	}
	printf("\n");
    return EXIT_SUCCESS;
}
