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
#include "questions.h"
#define MAX_LEN 256
#define NUM_QUESTIONS 12

// Initializes the array of questions for the game
void initialize_game(void){
	printf("Welcome To Jeopardy\n");
	printf("Please type in all four players names to proceed: \n");
	char Q[NUM_QUESTIONS][MAX_LEN] = {"pQ1","pQ2","pQ3","pQ4","aQ1","aQ2","aQ3","aQ4","dQ1","dQ2","dQ3","dQ4"};
	char A[NUM_QUESTIONS][MAX_LEN] = {"pA1","pA2","pA3","pA4","aA1","aA2","aA3","aA4","dA1","dA2","dA3","dA4"};
	int s[] = {400,800,1200,1600,400,800,1200,1600,400,800,1200,1600,400,800,1200,1600};
	int j = 0 , i = 0;
	while( j < 12 ){
		if (j%4 == 0 && j != 0){
		i++;
		}
		strcpy(questions[j].category,categories[i]);
		strcpy(questions[j].question,Q[j]);
		strcpy(questions[j].answer,A[j]);
		questions[j].value = s[j];
		questions[j].answered = false;
		j++;
	}
    // initialize each question struct and assign it to the questions array
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{	
	printf("                                    JEOPARDY\n");
	printf("Radomly selected player types name in  then chooses a question value to answer: \n");
	printf("Question Board: \n");
	int mul = 0;
	for(int i = 0;i<3;i++){
		printf("%s >",categories[i]);
		for(int j = 0 + mul; j<4+mul ;j++){
			if (questions[j].answered == false){
				printf("[ $%d ]",questions[j].value);
			}
		}
		mul = mul + 4;
		printf("\n");
	}
	
	/*
	int mul = 0;
	char C[3];
	char ANS;
	for(int i = 0;i < 3;i++){
		for (int j = 0; j < 4 ;j++){
			if(questions[j+mul].answered == true){
				ANS = 'T';
			} else { ANS = 'F';}
		}
		mul = mul + 4;
		if (ANS == 'T'){ C[i] ='T'; } else { C[i] ='F'; }
	}
	mul = 0;
	for(int i = 0;i < 3;i++){
		if (C[i] == 'F'){
			printf("%s >",categories[i]);
			for (int j = 0; j < 4;j++){
				if (questions[j+mul].answered == false){
					printf("[ $%d ] ",questions[j+mul].value);
				}
				
			}
			printf("\n");
		}
		mul = mul + 4;
	}
	*/
	printf("\n");
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value){
	int offset = 0;
	switch(category[0]){ case 'A': offset = 4; break; case 'D': offset = 8; break; default: break;}
	for( int i = offset; i < (offset + 4);i++){
		if (questions[i].value == value){ 
			printf("\n%s: %s--|value<%d>|: ",questions[i].category,questions[i].question,questions[i].value);
			break;
		}			
	}
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer){
    int offset = 0;
	switch(category[0]){ case 'A': offset = 4; break; case 'D': offset = 8; break; default: break;}
	for( int i = offset; i < (offset + 4);i++){
		if (questions[i].value == value){ 
			if (strcmp(questions[i].answer,answer) == 0){
				questions[i].answered = true;  return true;
			} else {questions[i].answered = true;}
		}		
	}
	// Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value){
	int offset = 0;
	switch(category[0]){ case 'A': offset = 4; break; case 'D': offset = 8; break; default: break;}
	for( int i = offset; i < (offset + 4);i++){
		if (questions[i].value == value){ 
			if (questions[i].answered == true){ return true;}
		}			
	}
    // lookup the question and see if it's already been marked as answered
    return false;
}
