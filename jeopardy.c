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
	SizeTksAry = i;
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

void Player_In(player *players, char *N){
	int i = 0;
	while(i < NUM_PLAYERS){
	printf("Enter in Player Name: ");
	//scanf("%s",N);
	fgets(N,BUFFER_LEN,stdin);
	N[strlen(N) -1] = '\0';
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
    system("clear");
    initialize_game();

    // Prompt for players names  
    char Name[BUFFER_LEN];
    Player_In(players,Name); 
	system("clear");
    // Perform an infinite loop getting command input from users until game ends
    char category[BUFFER_LEN],name[BUFFER_LEN],answer[BUFFER_LEN]; int value,num_players,score;
	int QCount = 1;
    while (QCount <= 12) //(fgets(buffer,BUFFER_LEN,stdin) != NULL)
    {
		system("clear");
    	display_categories();
    	for (int i = 0; i<NUM_PLAYERS ;i++){ printf("[Player %d: ",i+1); printf("%s $%d]",players[i].name,players[i].score);  }
    	printf("\n");
		int num,lower = 1,upper = 5;
		num = rand()%(upper-lower)+1;
		char bufReplace[BUFFER_LEN];
		memset(bufReplace,'\0',sizeof(char)*BUFFER_LEN);
		printf("Type in your name Player %d: ",num);
		for (;;){
			strcpy(buffer,bufReplace);
			fgets(buffer,BUFFER_LEN,stdin);
			buffer[strlen(buffer) -1] = '\0';
			if (player_exists(players, NUM_PLAYERS, buffer) == 1 && strcmp(players[num-1].name,buffer) == 0){
				system("clear");
				display_categories();
				printf("\nPlayer %d please type a Category <CATEGORY OPTIONS:  P,A,D > " ,num);
				while(1){
					for(;;){
						fgets(category,BUFFER_LEN,stdin);
						category[strlen(category) - 1] = '\0';
						category[0] = toupper(category[0]);
						if(strcmp(category,"P")==0 || strcmp(category,"A")==0 || strcmp(category,"D")==0 ){
							break;
						}else{printf("\nPlease type a category P,A,D: ");}
						strcpy(category,bufReplace);
					}
					printf("\nPlayer %d please type a value from category %s > " ,num,category);
					for(;;){
						char strInt[BUFFER_LEN];
						//scanf("%d",&value);
						strcpy(buffer,bufReplace);
						fgets(strInt,BUFFER_LEN,stdin);
						strInt[strlen(strInt) -1] = '\0';
						value = atoi(strInt);
						if (value == 400 || value == 800 || value == 1200 || value == 1600){
							break;
						}else{printf("\nPlease type in a number that listed above for category %s: ", category);}
					}
					if(already_answered(category, value) == false){ break;
					} else { 
					printf("\nSry that has already been taken, Player %d please type a Category <CATEGORY OPTIONS:  P,A,D > " ,num); 
					}
				}
				fflush(stdin);
				display_question(category, value);
				printf("\nWhat is your answer Player %d :", num);
				strcpy(buffer,bufReplace);
				fgets(buffer,BUFFER_LEN,stdin);
				buffer[strlen(buffer) -1] = '\0';
				char *array[BUFFER_LEN + 1]; // allocated memeory for pointer to point
				char **Tks = array;// holding pieces of text for input with space 
				tokenize(buffer,Tks);
				int t = 0; bool Y = false;
				for(t = 0; t < SizeTksAry ;t++){
					if (valid_answer(category, value, Tks[t]) == false){continue;} 
					else{Y = true; break;}
				}
				if (Y == false){system("clear");printf("\n---SORRY THAT'S INCORRECT---");}
				else {
					system("clear");
					printf("\n!!!CORRECT!!!"); 
					update_score(players,NUM_PLAYERS, players[num-1].name,value); 
				}
				printf("\n");
				sleep(3);
				num = rand()%(upper-lower)+1;
				break;
			// Call functions from the questions and players source files

			// Execute the game until all questions are answered

			// Display the final results and exit
			} else { printf("Name Inncorrect please try again Player %d: ",num);}
		}
		QCount++;
    }
	system("clear");
	printf("\n");
	printf("\nEND GAME RESULTS:\n");
	int indexs[4];
	int k  = 0 ;
	while(k < 4){
		int max = 0,ind = 0;
		bool x = false;
		for(int i = 0;i<4;i++){
				for (int j;j<4;j++){
					if (i == indexs[j]){x = true; break;}
				}
				if ( x == false && max < players[i].score){max = players[i].score; ind = i;}
		}
		indexs[k] = ind;
		printf("\n%s %d",players[ind].name,players[ind].score);
		k++;
	}
	printf("\n");
    return EXIT_SUCCESS;
}
