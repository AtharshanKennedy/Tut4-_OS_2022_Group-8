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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name){
    int found = 0;    // using 0 or 1 for determing if a player was found or not
    for (int i = 0; i < num_players ;i++){ // loop and compare user enterned name to all names
    	if (strcmp(players[i].name,name) == 0){ found = 1; break; } // once found break and found is 1;
    }
    return found; // return 0 for no and 1 for yes
    //if (found == 0){return 0;} else {return 1;}
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score){
		for (int i = 0; i < num_players ;i++){ // for teh player that answered correctlyy
				if(players[i].name == name){// loop until the person is found and update their score
					players[i].score = players[i].score + score;
				}
		}
}
