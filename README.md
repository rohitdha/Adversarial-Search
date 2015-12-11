## <u>MANCALA GAME PLAYING AGENT - ADVERSARIAL SEARCH</u>
---------------------------------------------------------

### Introduction:
-----------------

Write a program to determine the next move for a player in the <b>Mancala game</b> using <b>Greedy, Minimax, and Alpha-Beta pruning algorithm</b>. The rules of the Mancala game can be found at https://en.wikipedia.org/wiki/Mancala [1] and you can also try playing it online at http://play-mancala.com/ [2] to get a better understanding of the game.

Mancala is a two-player game from Africa in which players moves stones around a board, trying to capture as many as possible. In the board here, player 1 owns the bottom row of stones and player 2 owns the top row. There are also two special pits on the board, called Mancalas, in which each player accumulates his or her captured stones (player 1's Mancala is on the right and player 2's Mancala is on the left).
On a player's turn, he or she chooses one of the pits on his or her side of the board (not the Mancala) and removes all of the stones from that pit. The player then places one stone in each pit, moving counterclockwise around the board, starting with the pit immediately next to the chosen pit, including his or her Mancala but NOT his or her opponents Mancala, until he or she has run out of stones. If the player's last stone ends in his or her own Mancala, the player gets another turn. If the player's last stone ends in an empty pit on his or her own side, the player captures all of the stones in the pit directly across the board from where the last stone was placed (the opponents stones are removed from the pit and placed in the player's Mancala) as well as the last stone placed (the one placed in the empty pit). The game ends when one player cannot move on his or her turn, at which time the other player captures all of the stones remaining on his or her side of the board.

### Tasks:
----------

Write a program to determine the next move by implementing the following algorithms:
* Greedy
* Minimax
* Alpha-Beta

### End game:
-------------

If a player cannot make any valid move, i.e. all of his pits (except Mancala) are empty, the game ends and the remaining stones are moved to the other player’s Mancala.

### Evaluation function:
------------------------

The goal of the game is to collect maximum number of stones by the end of the game and to win the game; you need to collect more stones than your opponent. So, the evaluation function for any legal move is computed as the difference between the numbers of stones in both players’ Mancala if that move is chosen.
<b>E(p) = #Stones_player - #Stones_opponent</b>
For example, for the current board position shown above, if Player-1 chooses pit B5 as his/her move, then the value of the evaluation function would E(B5) = (1-0) = 1. Note: You can hence assume that your agent is always the “max” player. Similarly, E(B2) = (0-0) = 0.

### Tie breaking and Expand order:
----------------------------------

Ties between pits are broken by selecting the node that is first in the position order on the figure above. For example, if all legal moves for Player-1 (B2, B3, B4, B5, B5, B6, and B7) have the same evaluated values, the program must pick B2 according to tie breaker rule. Same rule applies for Player-2(A2, A3, A4, A5, A6, and A7) should select A2.
Your traverse order must be in the positional order also. For example, your program will traverse on B2, B3, B4, B5, B6, and B7 branch in order.

### Board size:
---------------

The board size will be 2xN along with a mancala for each player, where N represents the number of pits for a player and 3≤N≤10. The board size for the mancala board shown above would be 2x6. The initial number of stones in each pit can be maximum 1000.

### Input:
----------

Given a file <b>input.txt</b> that describes the current state of the game.
* \<Task#\> Greedy=1, MiniMax=2, Alpha-Beta=3, Competition=4
* \<Your player: 1 or 2\>
* \<Cutting off depth\>
* \<Board state for player-2\>
* \<Board state for player-1\>
* \<#stones in player-2’s mancala\>
* \<#stones in player-1’s mancala\>
