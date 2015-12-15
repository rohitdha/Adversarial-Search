/*
	Author: Rohit Dhawan
	Project: Adversarial Search - Game Playing Agent
	Domain: Artificial Intelligence
	Algorithm: Greedy, MiniMax, Alpha-Beta Pruning 
	
	Sample Input:
		1							< Algorithm to run - {1- Greedy, 2- MiniMax 3- Alpha-Beta}>
		1							<Player's turn>
		3							<Cut Off Depth>
		0 0 0 1 1						<Player 2 Board State>
		1 0 0 0 1						<Player 1 Board State>
		0							<Player 2 Mancala's>
		0							<Player 1 Mancala's>
		
	More Details in README.md
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include "mancala.h"

using namespace std;

map<int,int> final_state;
map<int,int> final_state_root;
map<int,int> final_state_level;

//Default Constructor
adversarialSearch::adversarialSearch() {
}

// Reading the data and storing it into vector
void adversarialSearch::setData(vector<string> &line) {
	vector<string>::iterator read_it;
	read_it = line.begin();
	this->task = atoi((*read_it).c_str());
	read_it++;
	this->p_turn = atoi((*read_it).c_str());
	read_it++;
	this->c_o_depth = atoi((*read_it).c_str());
	read_it++;
	this->bs_p2 = *read_it;
	read_it++;
	this->bs_p1 = *read_it;
	read_it++;
	this->p2_mancala = atoi((*read_it).c_str());
	read_it++;
	this->p1_mancala = atoi((*read_it).c_str());
}

// Returns the Task: Greddy, MiniMax or Alpha-Beta
int adversarialSearch::getTask() {
	return this->task;
}

// Returns the Player1's Board State
string adversarialSearch::get_bstate_player1() {
	return this->bs_p1;
}

// Returns the Player2's Board State
string adversarialSearch::get_bstate_player2() {
	return this->bs_p2;
}

// Returns the Player1's Mancala 
int adversarialSearch::get_p1_mancala() {
	return this->p1_mancala;
}

// Returns the Player2's Mancala
int adversarialSearch::get_p2_mancala() {
	return this->p2_mancala;
}

// Returns whose turn is to play
int adversarialSearch::get_whose_turn() {
	return this->p_turn;
}

// Returns the Cut Off Depth as per input file
int adversarialSearch::get_c_o_depth() {
	return this->c_o_depth;
}

// Storing the Complete Board into a map after reading the Player1's and Player2's board state
void adversarialSearch::fill_up_board() {
	
	string board1 = this->bs_p1;
    	string board2 = this->bs_p2;
	int mancala_p1 = this->p1_mancala;
	int mancala_p2 = this->p2_mancala;
	
	int i = 0, j = 0; // Count Variables 
	string board_pieces ="";
	
	vector<int> pieces;
		
	while(board1[i]) {
		if(isspace(board1[i])) {
			this->board[j] = atoi(board_pieces.c_str());
			board_pieces = "";
			j++;
			i++;
		}
		board_pieces += board1[i];
		i++;
	}
		
	this->board[j] = atoi(board_pieces.c_str());
	
	board_pieces  = ""; j++;
	
	this->board[j] = mancala_p1;
		
	i = 0, j++;
		
	while(board2[i]) {
		if(isspace(board2[i])) {
			pieces.push_back(atoi(board_pieces.c_str()));
			board_pieces = "";
			i++;
		}
		board_pieces += board2[i];
		i++;
	}
	pieces.push_back(atoi(board_pieces.c_str()));
	
	while (!pieces.empty()) {
		this->board[j] = pieces.back();
		pieces.pop_back();
		j++;
	}
	
	board_pieces = ""; 
	this->board[j] = mancala_p2;
	this->size_of_the_board = this->board.size();
		
}

// Function to evaluate next move based on the player's turn and the index played
int * adversarialSearch::checkeval(map<int,int> board, int index, int turn) {
	
	map<int,int> temp = board;
	map<int,int> orig = board;
	map<int,int>::iterator it;
	
	int size = this->size_of_the_board;
	int start,end;
	int p1_man = (size/2)-1;
	int p2_man = size-1;
	
	if(turn == 1) {
		start = 0;
		end = size/2 -1;
	} else {
		start = size/2;
		end = size-1;
	}
	
	int coins=0,j,k=0;
		
	coins = temp[index];
	temp[index] = 0;
	j = index + 1;
	
	while(coins) {
		
		if(turn == 1 && j == size-1){
			j=0;
			continue;
		} 
		
		if(turn == 2 && j == size) {
			j=0;
		}
		
		if(turn == 2 && j == (size/2-1)) {
			j++;
		}
		temp[j] = temp[j] + 1;
		j++;
		
		coins--;
	}
	j--;
	int check = (size-2)-j;
	if(temp[j] == 1 && j >=start && j<end) {
		if( j < p1_man ) {
				temp[p1_man] = temp[p1_man] + temp[j] +temp[(size-2)-j];
				temp[j] = temp[(size-2)-j] =0;
		} else if( j < p2_man) {
				temp[p2_man] = temp[p2_man] + temp[j] +temp[(size-2)-j];
				temp[j] = temp[(size-2)-j] =0;
		}
	}
		
	int count =0, count1=0;
	for(int i = 0; i< size/2 -1; i++) {
		if(temp[i] == 0) {
			count++;
			continue;
		}
	}
	for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
		if(temp[i] == 0) {
			count1++;
			continue;
		}
	}
	
	if(count == size/2-1 || count1 == size/2-1) {
		
		for(int i = size-2,j=2; i> (size/2) -1; i--) {
			temp[p2_man] += temp[i];
			temp[i] =0;
		}
		
		for(int i = 0; i< size/2 -1; i++) {
			temp[p1_man] += temp[i];
			temp[i] =0;
		}
	}
		
	int *eval = (int *)malloc(sizeof(int)*2);
	int evalu;
	*(eval+0) = j;
	if(this->p_turn == 1) {
		evalu = temp[p1_man] - temp[p2_man];
	} else {
		evalu = temp[p2_man] - temp[p1_man];
	}
	*(eval+1) = evalu;
	return eval;
}

// Function that plays the next move based on the index and the player's turn
map<int,int> adversarialSearch::playmove(map<int,int> board,int index, int turn) {
	
	map<int,int> temp = board;
	map<int,int>::iterator it;
	
	int size = this->size_of_the_board;
	int start,end;
	int p1_man = (size/2)-1;
	int p2_man = size-1;

	if(turn == 1) {
		start = 0;
		end = size/2 -1;
	} else {
		start = size/2;
		end = size-1;
	}
	
	int coins=0,j,k=0;
	
		coins = temp[index];
		temp[index] = 0;
		j = index + 1;
		int test = 0;
		while(coins) {
			
			if(turn == 1 && j == size-1){
				j=0;
				continue;
			} 
			
			if(turn == 2 && j == size) {
				j=0;
			}
			
			if(turn == 2 && j == (size/2-1)) {
				j++;
			}
			temp[j] = temp[j] + 1;
			j++;
			coins--;
		}
		
		if(temp[--j] == 1 && j >=start && j<end) {
			
			if( j < p1_man ) {
					
					temp[p1_man] = temp[p1_man] + temp[j] +temp[(size-2)-j];
					temp[j] = temp[(size-2)-j] =0;
			} else if( j < p2_man) {
					
					temp[p2_man] = temp[p2_man] + temp[j] +temp[(	size-2)-j];
					temp[j] = temp[(size-2)-j] =0;
			}
		}
		
		int count =0, count1=0;
		for(int i = 0; i< size/2 -1; i++) {
			if(temp[i] == 0) {
				count++;
				continue;
			}
		}
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(temp[i] == 0) {
				count1++;
				continue;
			}
		}
		if(count == size/2-1 || count1 == size/2-1) {
			
			for(int i = size-2,j=2; i> (size/2) -1; i--) {
				temp[p2_man] += temp[i];
				temp[i] =0;
			}
			
			for(int i = 0; i< size/2 -1; i++) {
				temp[p1_man] += temp[i];
				temp[i] =0;
			}
		}	
		return temp;
}

// Function to check if board has reached terminal state
int adversarialSearch::checkEndCondition(map<int,int> board,int turn) {
	int size = this->size_of_the_board;
	int count = 0, count1 = 0;
		for(int i = 0; i< size/2 -1; i++) {
			if(board[i] == 0) {
				count++;
				continue;
			}
		}
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				count1++;
				continue;
			}
		}
	if(count == size/2-1 || count1 == size/2-1){
		return 1;
	} else 
		return 0;
}

// Function to check max between 2 numbers
int adversarialSearch::max(int a, int b) {
	return a > b ? a: b;
}

// Function to check min between 2 numbers
int adversarialSearch::min(int a, int b) {
	return a > b ? b: a;
}

// Function that returns the string based on the state value of the board
string adversarialSearch::estimate_value(int value) {
	string return_type;
	if(value == -9999 || value == -9000)
		return_type = "-Infinity";
	else if(value == 9999 || value == 9000)
		return_type = "Infinity";
	else {
		stringstream answer_string;
		answer_string << value;
		return_type += answer_string.str();
	}
		
	return return_type;
}

int val_test = -9999;
int value_test = -9999;
int valuey_test = -9999;
int end_cond =0;

///// Greedy STARTS HERE /////
void adversarialSearch::greedy() {
	this->fill_up_board();
	int depth =0;
	int player = this->p_turn;
	int value = max(-9999,max_value_greedy(this->board,depth,"root",0,0,player));
}

// Greedy Function for Max Player{Player1 or Player2 depends on the input}
int adversarialSearch::max_value_greedy(map<int,int> board,int a_depth, string name,int pos,int retainedTurn,int player){
			
	int value = -9999;
	int size = this->size_of_the_board;
	int turn;
	int next_player = player-1? player-1:player+1;
	
	if(retainedTurn) {
		turn = player;
	} else {
		turn = next_player;
	}
	
	int checkendcondition = checkEndCondition(board,turn);
	
	if((checkendcondition) == 1) {
		int val1;
		if(player == 1)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(a_depth == 1 && val1 > valuey_test) {
			valuey_test = val1;
			final_state = board;
		}
		
		return val1;
	}
	
	if(1 == a_depth){
		int val1;
		if(player == 1)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(retainedTurn) {
		}
		
		if(!retainedTurn) {
			if(val1 > val_test) {
				val_test = val1;
				final_state = board;
			}
			return val1;
		}
	} else {
	}
	
	if(player == 2) {
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);// 2- player 1 turn 
		
			string tempname = "A";
			stringstream ss;
			ss << j;
			tempname += ss.str();
		
			if(*(index+0) == size-1) {
			
				value = max(value,max_value_greedy(test, retainedTurn ? a_depth : a_depth+1,tempname,i,1,player));
				
			} else {
			    
				value = max(value,min_value_greedy(test, retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player));
		
			}
			
			if( a_depth ==0 && value > value_test) {
				value_test = value;
				val_test = -9999;
				valuey_test = -9999;
				final_state_root = final_state;
			}
			
			if (a_depth == 1 && value > valuey_test) {
				valuey_test = value;
				final_state = test;
			}
			
		}
	} else {
		
			for(int i = 0; i < (size/2) -1; i++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);
		
			string tempname = "B";
			stringstream ss;
			ss << i+2;
			tempname += ss.str();
		
			if(*(index+0) == size/2-1) {
				
				value = max(value,max_value_greedy(test,retainedTurn ? a_depth : a_depth+1,tempname,i,1,player));
				
			} else {
				
				value = max(value,min_value_greedy(test,retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player));
		
			}
	
			if( a_depth ==0 && value > value_test) {
				value_test = value;
				val_test = -9999;
				valuey_test = -9999;
				final_state_root = final_state;
			}
			
			if (a_depth == 1 && value > valuey_test) {
				valuey_test = value;
				final_state = test;
			}
		}
	}
	return value;
}

// Greedy Function for Min Player{Player1 or Player2 depends on the input}
int adversarialSearch::min_value_greedy(map<int,int> board,int a_depth,string name,int pos,int retainedTurn,int player){
	int value = 9999;
	int size = this->size_of_the_board;
	int start, end;
	int turn;
	int next_player = player-1? player-1:player+1;
	
	if(retainedTurn) {
		turn = player;
	} else {
		turn = next_player;
	}
	
	int checkendcondition = checkEndCondition(board,turn);
	
	if((checkendcondition) == 1) {
		int val1;
		if(player == 2)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(a_depth == 1 && val1 > val_test) {
			val_test = val1;
			final_state = board;
		}
		return val1;
	}
	
	if(1 == a_depth){
		int val1;
		if(player == 2)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(retainedTurn) {
		}

		if(!retainedTurn) {
			if(val1 > val_test) {
				val_test = val1;
				final_state = board;
			}
			return val1;
		}
	
	} else {
		
	}
	
	if(player == 2) {
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);
		
			string tempname = "A";
			stringstream ss;
			ss << j;
			tempname += ss.str();
		
			if(*(index+0) == size-1) {
			
				value = min(value,min_value_greedy(test, retainedTurn ? a_depth : a_depth+1,tempname,i,1,player));
		
			} else {
			
				value = min(value,max_value_greedy(test, retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player));
		
			}
			
			if(a_depth == 1 && value > val_test) {
				val_test = value;
				final_state = board;
			}
		}
	} else {
			for(int i = 0; i < (size/2) -1; i++) {
				if(board[i] == 0) {
					continue;
				}
		
				int *index = checkeval(board,i,player);
				map<int,int> test = playmove(board,i,player);
		
				string tempname = "B";
				stringstream ss;
				ss << i+2;
				tempname += ss.str();
		
				if(*(index+0) == size/2-1) {
		
					value = min(value,min_value_greedy(test,retainedTurn ? a_depth : a_depth+1,tempname,i,1,player));
		
				} else {
			
					value = min(value,max_value_greedy(test,retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player));
		
				}
				
				if(a_depth == 1 && value > val_test) {
					val_test = value;
					final_state = board;
				}
			}
	}
	
	return value;
}


///// GREEDY ENDS HERE /////
///// MINIMAX STARTS HERE /////

void adversarialSearch::minimax(ofstream& answer) {
	this->fill_up_board();
	int depth = 0;
	int player = this->p_turn;
	answer << "Node,Depth,Value"<<endl;
	int value = max(-9999,max_value(this->board,depth,"root",0,0,player,answer));
}


// Minimax Function for Max Player{Player1 or Player2 depends on the input}
int adversarialSearch::max_value(map<int,int> board,int a_depth, string name,int pos,int retainedTurn,int player, ofstream& answer){
	int value = -9999;
	int size = this->size_of_the_board;
	int turn;
	int next_player = player-1? player-1:player+1;
	int p1_man = (size/2)-1;
	int p2_man = size-1;
	
	if(retainedTurn) {
		turn = player;
	} else {
		turn = next_player;
	}
	
	int checkendcondition = checkEndCondition(board,turn);
	
	if((checkendcondition) == 1) {
		int val1;
		if(player == 1)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(a_depth == 1 && val1 > valuey_test) {
			valuey_test = val1;
			final_state = board;
		}
		
		answer << name<<","<<a_depth<<","<<estimate_value(val1)<<endl;
		return val1;
	}
	
	if(this->c_o_depth == a_depth){
		int val1;
		if(player == 1)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(retainedTurn) {
			answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
		}
		
		if(!retainedTurn) {
			if((a_depth == 1) && (val1 > val_test)) {
				val_test = val1;
				final_state = board;
			}
			answer << name<<","<<a_depth<<","<<estimate_value(val1)<<endl;
			return val1;
		}
	} else {
		answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
	}
	
	if(player == 2) {
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);// 2- player 1 turn 
		
			string tempname = "A";
			stringstream ss;
			ss << j;
			tempname += ss.str();
			if(*(index+0) == size-1) {
			
				value = max(value,max_value(test, retainedTurn ? a_depth : a_depth+1,tempname,i,1,player,answer));
								
			} else {
			    
				value = max(value,min_value(test, retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player,answer));
		
			}
			answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
			
			if(a_depth ==0 && value > value_test) {
				value_test = value;
				final_state_root = final_state;
				val_test = -9999;
				valuey_test = -9999;
			}		
			
			if (a_depth == 1 && value > valuey_test) {
				valuey_test = value;
				final_state = test;
			}
		}
	} else {
		
		for(int i = 0; i < (size/2) -1; i++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);
		
			string tempname = "B";
			stringstream ss;
			ss << i+2;
			tempname += ss.str();
			
			if(*(index+0) == size/2-1) {
				
				value = max(value,max_value(test,retainedTurn ? a_depth : a_depth+1,tempname,i,1,player,answer));
				
			} else {
				
				value = max(value,min_value(test,retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player,answer));
		
			}
			answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;

			if (a_depth == 0 && value > value_test) {
				value_test = value;
				final_state_root = final_state;
				val_test = -9999;
				valuey_test = -9999;
			}
			
			if (a_depth == 1 && value > valuey_test) {
				valuey_test = value;
				final_state = test;
			}
		}
	}
	return value;
}

// MiniMax Function for Min Player{Player1 or Player2 depends on the input}
int adversarialSearch::min_value(map<int,int> board,int a_depth,string name,int pos,int retainedTurn,int player,ofstream& answer){
	int value = 9999;
	int size = this->size_of_the_board;
	int start, end;
	int turn;
	int next_player = player-1? player-1:player+1;
	int p1_man = (size/2)-1;
	int p2_man = size-1;
	
	if(retainedTurn) {
		turn = player;
	} else {
		turn = next_player;
	}
	
	int checkendcondition = checkEndCondition(board,turn);
	
	if((checkendcondition) == 1) {
		int val1;
		if(player == 2)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(a_depth == 1 && val1 > val_test) {
			val_test = val1;
			final_state = board;
		}
		
		answer << name<<","<<a_depth<<","<<estimate_value(val1)<<endl;
		return val1;
	}
	
	if(this->c_o_depth == a_depth) {
		int val1;
		if(player == 2)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(retainedTurn) {
			answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
		}

		if(!retainedTurn) {
			if((a_depth == 1) && val1 > val_test) {
				val_test = val1;
				final_state = board;
			}
			answer << name<<","<<a_depth<<","<<estimate_value(val1)<<endl;
			return val1;
		}
	
	} else {
		answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
	}
	
	if(player == 2) {
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);
		
			string tempname = "A";
			stringstream ss;
			ss << j;
			tempname += ss.str();
		
			if(*(index+0) == size-1) {
			
				value = min(value,min_value(test, retainedTurn ? a_depth : a_depth+1,tempname,i,1,player,answer));
		
			} else {
			
				value = min(value,max_value(test, retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player,answer));
		
			}
			answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
			
			if (a_depth == 1 && value > val_test) {
					val_test = value;
					final_state = board;
			}
			
		}
	} else {
			for(int i = 0; i < (size/2) -1; i++) {
				if(board[i] == 0) {
					continue;
				}
		
				int *index = checkeval(board,i,player);
				map<int,int> test = playmove(board,i,player);
		        
				string tempname = "B";
				stringstream ss;
				ss << i+2;
				tempname += ss.str();

				if(*(index+0) == size/2-1) {
		
					value = min(value,min_value(test,retainedTurn ? a_depth : a_depth+1,tempname,i,1,player,answer));
		
				} else {
			
					value = min(value,max_value(test,retainedTurn ? a_depth : a_depth+1,tempname,i,0,next_player,answer));
		
				}
				answer << name<<","<<a_depth<<","<<estimate_value(value)<<endl;
				
				if (a_depth == 1 && value > val_test) {
					val_test = value;
					final_state = board;
				}
			}
	}
	
	return value;
}


///// MINIMAX ENDS HERE /////

///// ALPHA BETA STARTS HERE /////

void adversarialSearch::minimax_alphabeta(ofstream& answer) {
	this->fill_up_board();
	int depth = 0;
	int player = this->p_turn;
	answer << "Node,Depth,Value,Alpha,Beta"<<endl;
	int value = max(-9999,max_value_alphabeta(this->board,depth,"root",0,0,-9000,9000,player,answer));
}

// Alphabeta Function for Max Player{Player1 or Player2 depends on the input}
int adversarialSearch::max_value_alphabeta(map<int,int> board,int a_depth, string name,int pos,int retainedTurn,int alpha, int beta,int player,ofstream& answer){
	
	int value = -9999;
	int size = this->size_of_the_board;
	int turn;
	int next_player = player-1? player-1:player+1;
	
	if(retainedTurn) {
		turn = player;
	} else {
		turn = next_player;
	}
	
	int checkendcondition = checkEndCondition(board,turn);
	
	if((checkendcondition) == 1) {
		
		int val1;
		
		if(player == 1)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(a_depth == 1 && val1 > valuey_test) {
			valuey_test = val1;
			final_state = board;
		}
		
		answer <<name<<","<<a_depth<<","<<estimate_value(val1)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
		return val1;
	}
	
	if(this->c_o_depth == a_depth){
		int val1;
		
		if(player == 1)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(retainedTurn) {
			answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
		}
		
		if(!retainedTurn) {
			if((a_depth == 1) && (val1 > val_test)) {
				val_test = val1;
				final_state = board;
			}
			answer <<name<<","<<a_depth<<","<<estimate_value(val1)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
			return val1;
		}
	} else {
		answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
	}
	
	if(player == 2) {
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);
		
			string tempname = "A";
			stringstream ss;
			ss << j;
			tempname += ss.str();
		
			if(*(index+0) == size-1) {
			
				value = max(value,max_value_alphabeta(test, retainedTurn ? a_depth : a_depth+1,tempname,i,1,alpha,beta,player,answer));
				
			} else {
				
				value = max(value,min_value_alphabeta(test, retainedTurn ? a_depth : a_depth+1,tempname,i,0,alpha,beta,next_player,answer));
		
			}
			if(value >= beta) {
				
				if (a_depth == 0 && value > value_test) {
					value_test = value;
					final_state_root = final_state;
					val_test = -9999;
					valuey_test = -9999;
				}
				
				if (a_depth == 1 && value > valuey_test) {
					valuey_test = value;
					final_state = test;
				}
				
				answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
				return value;
			}
			alpha = max(value,alpha);
			
			if (a_depth == 0 && value > value_test) {
				value_test = value;
				final_state_root = final_state;
				val_test = -9999;
				valuey_test = -9999;
			}
			
			if (a_depth == 1 && value > valuey_test) {
				valuey_test = value;
				final_state = test;
			}
			
			answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
		}
	} else {
			for(int i = 0; i < (size/2) -1; i++) {
				if(board[i] == 0) {
					continue;
				}
		
				int *index = checkeval(board,i,player);
				map<int,int> test = playmove(board,i,player);
		
				string tempname = "B";
				stringstream ss;
				ss << i+2;
				tempname += ss.str();
		
				if(*(index+0) == size/2-1) {
					
					value = max(value,max_value_alphabeta(test,retainedTurn ? a_depth : a_depth+1,tempname,i,1,alpha,beta,player,answer));
					
				} else {
					value = max(value,min_value_alphabeta(test,retainedTurn ? a_depth : a_depth+1,tempname,i,0,alpha,beta,next_player,answer));
		
				}
				
				if(value >= beta) {
					
					if (a_depth == 0 && value > value_test) {
						value_test = value;
						final_state_root = final_state;
						val_test = -9999;
						valuey_test = -9999;
					}
					
					if (a_depth == 1 && value > valuey_test) {
						valuey_test = value;
						final_state = test;
					}
					
					answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
					return value;
				}
				alpha = max(value,alpha);
				
				if (a_depth == 0 && value > value_test) {
					value_test = value;
					final_state_root = final_state;
					val_test = -9999;
					valuey_test = -9999;
				}
				
				if (a_depth == 1 && value > valuey_test) {
					valuey_test = value;
					final_state = test;
				}
				
				answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
			}
	}
	
	return value;
}

// Alphabeta Function for Min Player{Player1 or Player2 depends on the input}
int adversarialSearch::min_value_alphabeta(map<int,int> board,int a_depth,string name,int pos,int retainedTurn,int alpha,int beta,int player,ofstream& answer){
	int value = 9999;
	int size = this->size_of_the_board;
	int start, end;
	int turn;
	int next_player = player-1? player-1:player+1;
	
	if(retainedTurn) {
		turn = player;
	} else {
		turn = next_player;
	}
	int checkendcondition = checkEndCondition(board,turn);
	
	if((checkendcondition) == 1) {
		
		int val1;
		if(player == 2)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(a_depth == 1 && val1 > val_test) {
			val_test = val1;
			final_state = board;
		}
		
		answer <<name<<","<<a_depth<<","<<estimate_value(val1)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
		return val1;
	}
	
	if(this->c_o_depth == a_depth) {
		int val1;
		if(player == 2)
			val1 = board[size/2-1] - board[size-1];
		else
			val1 = board[size-1] - board[size/2-1];
		
		if(retainedTurn) {
			answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
		}

		if(!retainedTurn) {
			 if((a_depth == 1) && (val1 > val_test)) {
				val_test = val1;
				final_state = board;
			}
			answer <<name<<","<<a_depth<<","<<estimate_value(val1)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
			return val1;
		}
	
	} else {
		answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
	}
	
	if(player == 2) {
		for(int i = size-2,j=2; i> (size/2) -1; i--,j++) {
			if(board[i] == 0) {
				continue;
			}
		
			int *index = checkeval(board,i,player);
			map<int,int> test = playmove(board,i,player);// 2- player 1 turn 
		
			string tempname = "A";
			stringstream ss;
			ss << j;
			tempname += ss.str();
		
			if(*(index+0) == size-1) {
			
				value = min(value,min_value_alphabeta(test, retainedTurn ? a_depth : a_depth+1,tempname,i,1,alpha,beta,player,answer));
		
			} else {
			
				value = min(value,max_value_alphabeta(test, retainedTurn ? a_depth : a_depth+1,tempname,i,0,alpha,beta,next_player,answer));
		
			}
			
			if(value <= alpha) {
				
				if (a_depth == 1 && value > val_test) {
					val_test = value;
					final_state = board;
				}

				answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
				return value;
			}
			beta = min(value,beta);
			
			if (a_depth == 1 && value > val_test) {
				val_test = value;
				final_state = board;
			}
			
			answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
		}
	} else {
			for(int i = 0; i < (size/2) -1; i++) {
				if(board[i] == 0) {
					continue;
				}
		
				int *index = checkeval(board,i,player);
				map<int,int> test = playmove(board,i,player);
		
				string tempname = "B";
				stringstream ss;
				ss << i+2;
				tempname += ss.str();
		
				if(*(index+0) == size/2-1) {
		
					value = min(value,min_value_alphabeta(test,retainedTurn ? a_depth : a_depth+1,tempname,i,1,alpha,beta,player,answer));
		
				} else {
			
					value = min(value,max_value_alphabeta(test,retainedTurn ? a_depth : a_depth+1,tempname,i,0,alpha,beta,next_player,answer));
		
				}
				if(value <= alpha) {
					
					if (a_depth == 1 && value > val_test) {
						val_test = value;
						final_state = board;
					}
					
					answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
					return value;
				}
				beta = min(value,beta);
				
				if (a_depth == 1 && value > val_test) {
					val_test = value;
					final_state = board;
				}
				
				answer <<name<<","<<a_depth<<","<<estimate_value(value)<<","<<estimate_value(alpha)<<","<<estimate_value(beta)<<endl;
			}
	}
	return value;
}
///// ALPHA BETA ENDS HERE ////

//Main Function
int main(int argc, char **argv) {
	
	//Reading the file from commandline
	ifstream file(argv[2]);
	string mystr;
	
	// Creating output file to display nextState
	ofstream outfile1;
	outfile1.open("next_state.txt");
	
	vector<string> line;

	while(getline(file,mystr)) {
		mystr.erase(0, mystr.find_first_not_of(" \t\n\r\f\v"));
		mystr.erase(mystr.find_last_not_of(" \n\r\t")+1);
		line.push_back(mystr);
	}

	adversarialSearch test_case;
	test_case.setData(line);
	
	if(test_case.getTask() == 1) {
		test_case.greedy();
	} else if(test_case.getTask() == 2) {
		ofstream outfile;
		// Creating output file to display Traverse logs
		outfile.open("traverse_log.txt");
		test_case.minimax(outfile);
		outfile.close();
	} else {
		ofstream outfile;
		// Creating output file to display Traverse logs
		outfile.open("traverse_log.txt");
		test_case.minimax_alphabeta(outfile);
		outfile.close();
	} 
		
	int size = final_state_root.size();
	int i=0;
	vector<int> pieces;
	list<int> player1;

	while(i < size/2-1) {
		player1.push_back(final_state_root[i]);
		i++;
	}
	int p1_man = final_state_root[i];
	i = size/2;
	while(i != (size)-1) {
		pieces.push_back(final_state_root[i]);
		i++;
	}
	while (!pieces.empty()) {
		outfile1 << pieces.back() <<" " ;
		pieces.pop_back();
	}
	outfile1 << endl;
	while (!player1.empty()) {
		outfile1 << player1.front() <<" " ;
		player1.pop_front();
	}
	outfile1 << endl;
	outfile1 << final_state_root[i]<<endl;
	outfile1 << p1_man<<endl;
	
	outfile1.close();
	return EXIT_SUCCESS;
}
