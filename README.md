Monte Carlo Tree Search Review<br/>
C++ Version Breakdown<br/>
Mcts.* are the files used to implement mcts. bot has a utilizes a think method which implements each step of mcts which are to traverse, expand, rollout, and backpropogate. <br/>
The the board class is a container for my version of a tic tac toe game. The class facilitates the game between the playe rand the ai, and interfaces with the board_state class.<br/>
The board_state class is the tic tac toe game itself. It contains the board, a way to set spaces in the board, and is able to check if the game is finished.<br/>
The current c++ folder implements a tic tac toe game in command prompt. The program runs an mcts bot to play the game against the player. The mcts bot is basic and prioritizes winning over defending. This program is personal review for implementing mcts.<br/>
The follow images show how the bot will take a win it can get, as well as the bot ignoring a loss. In both example the bot is 'X'.<br/>
![](img/offense_example.gif)
![](img/defense_example.gif)<br/>