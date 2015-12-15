
#ifndef _mancala_h_included_
#define _mancala_h_included_

using namespace std;
	
class adversarialSearch {
	string bs_p1, bs_p2; // Board State of Player1 and Player2
	int task; // Greedy, MinMax, Alpha-Beta
	int c_o_depth; // variable to store "Cut of Depth"
	int p_turn; // variable to store "Players turn"- Player1 or Player2
	int p1_mancala, p2_mancala; // variable to store board state of Player1 and Player2
	int size_of_the_board; // Variable to store the dimensions of the board
	map<int,int> board; // Map that stores the initial board configuration
public:
	adversarialSearch();
 	void setData(vector<string> &line);
	int getTask();
	string get_bstate_player1();
	string get_bstate_player2();
	int get_p1_mancala();
	int get_p2_mancala();
	int get_whose_turn();
	int get_c_o_depth();
	void greedy();
	int max_value_greedy(map<int,int>,int ,string ,int ,int ,int);
	int min_value_greedy(map<int,int>,int ,string ,int ,int ,int);
	void minimax(ofstream&);
	int max_value(map<int,int>,int,string,int,int,int,ofstream&);
	int min_value(map<int,int>,int,string,int,int,int,ofstream&);
	void minimax_alphabeta(ofstream&);
	int max_value_alphabeta(map<int,int>,int,string,int,int,int,int,int,ofstream&);
	int min_value_alphabeta(map<int,int>,int,string,int,int,int,int,int,ofstream&);
	int max(int,int);
	int min(int,int);
	void fill_up_board();
	int check_eval();
	int * checkeval(map<int,int>,int,int);
	int play_move(int);
	map<int,int> playmove(map<int,int>,int,int);
	int checkEndCondition(map<int,int>,int);
    	string estimate_value(int);
	~adversarialSearch();
};

#endif
