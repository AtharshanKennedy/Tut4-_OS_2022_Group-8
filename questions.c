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
	printf("Welcome To Jeopardy\n"); // Beginning statments // VV Questions,Answers,Value bank
	printf("Please type in all four players names to proceed: \n");
	char Q[NUM_QUESTIONS][MAX_LEN] = {"What is Programming?","What is an int?","What is system.out.println?","What is .exe",
										"Who is Alan Turing?","What is O<n^2>?","What is merger sort?","What is upperbound?",
										"Who is created db?","What is a db?","What is a db sofware?","What is a server?"};
	char A[NUM_QUESTIONS][MAX_LEN] = {"coding","int","printing","excutable",
										"mathematician","quadractic","divide","BigTheta",
										"Edgar","collection","mysql","Network"};
	int s[] = {400,800,1200,1600,400,800,1200,1600,400,800,1200,1600,400,800,1200,1600};
	int j = 0 , i = 0; // i for categoriesindexing and j for question indexing 
	while( j < 12 ){ // switch i when j reaches a max of four quetsions and exit while when j = 12
		if (j%4 == 0 && j != 0){ // increamnet i when j is a mul of 4 and not 0 to avoid errors
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
	printf("                                    JEOPARDY\n"); // Game layout
	printf("Radomly selected player types name in  then chooses a question value to answer: \n");
	printf("Question Board: \n");
	int mul = 0;   // uses this for the inner loop when changing categories to display q values for each categories
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
	printf("\n");
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value){
	int offset = 0; // use switch statment  to determing where to offset i for displaying the sel question
	switch(category[0]){ case 'A': offset = 4; break; case 'D': offset = 8; break; default: break;}
	for( int i = offset; i < (offset + 4);i++){
		if (questions[i].value == value){  //out put category,question,value to user 
			printf("\n%s: %s--|value<%d>|: ",questions[i].category,questions[i].question,questions[i].value);
			break;
		}			
	}
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer){
    int offset = 0; // switch used for offset i when checking for valid answer form a category
	switch(category[0]){ case 'A': offset = 4; break; case 'D': offset = 8; break; default: break;}
	for( int i = offset; i < (offset + 4);i++){
		if (questions[i].value == value){ // Once question value and user value match for a category
			if (strcmp(questions[i].answer,answer) == 0){ // check if answers match
				questions[i].answered = true;  return true; // if so return true and set the question as true
			} else {questions[i].answered = true;} // if not still set question as true 
		}		// when set true it's value will not be displayed next time when display_question() is called
	}
	// Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value){
	int offset = 0;// use switch statment to offset i for seeing from a category of the question the user selected 
	                // was already answered. If return false  and if not return true
					// for allowing user to not proceed and choose another question or to proceed with the question
	switch(category[0]){ case 'A': offset = 4; break; case 'D': offset = 8; break; default: break;}
	for( int i = offset; i < (offset + 4);i++){
		if (questions[i].value == value){ 
			if (questions[i].answered == true){ return true;}
		}			
	}
    // lookup the question and see if it's already been marked as answered
    return false;
}
