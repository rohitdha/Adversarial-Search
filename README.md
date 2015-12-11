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
