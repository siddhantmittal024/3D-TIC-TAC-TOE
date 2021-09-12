**3D TIC TAC TOE & MAGIC CUBE**   


1. **Algorithm to generate 3D Magic Cube:**

1. The numbers from 1 to 27 in a magic cube are found to be following a pattern. The function *createMagicCube()* makes use of this pattern to find the next position of insertion each time and thus insert every number at the required position in the magic cube.
1. The position of 1 is found from observation to always lie in a certain position in the cube, and the rest of the numbers follow a pattern which depends on this initial position
1. From observation, it was found that the initial position, that is the position of 1 in the cube, is (n/2, 0, n/2), where n is the size of the cube.
   1. *height* indicates the surface level in the cube- 0 being the highest and n-1 being the lowest.
   1. *row* indicates the row number on each surface- 0 being furthest at the back and n-1 being at the front of the cube.
   1. *col* indicates the column number on each surface- 0 being furthest at the left and n-1 being furthest at the right.
1. The pattern is as follows-
   1. ‘i’ is inserted at the found position in the cube and then incremented, allowing the insertion of all numbers from 1 to n\*n\*n in the cube.
   1. If the required position in the cube is already occupied, from observation it is found that the position is instead shifted to the next surface (lower surface), and the previous row (the row at the back).
   1. If the row, column or height is less than 0, i.e it goes out of bounds and is not valid, it is made to wrap around and come to n-1. Similarly if it becomes greater than n-1, it is made to wrap around and come to 0.
   1. If the required position in the cube is again found to be occupied, from observation it is found that the position is instead shifted to the next column (to the right), and the previous surface (upper surface).
   1. If the row, column or height is less than 0, i.e it goes out of bounds and is not valid, it is made to wrap around and come to n-1. Similarly if it becomes greater than n-1, it is made to wrap around and come to 0.
   1. Once the correct position is found, the current number, which is i, is inserted at this position in the cube.
   1. From observation it is found that the next position is found from the current position- it is shifted to the previous row (the row to the back), and the previous column (to the left).
   1. If the row, column or height is less than 0, i.e it goes out of bounds and is not valid, it is made to wrap around and come to n-1. Similarly if it becomes greater than n-1, it is made to wrap around and come to 0.

`      `**B.   TIC TAC TOE**

**           Global Variables Used :

- *magicCubePosition:* Map data structure used to map the number on the magicCube to                                  its coordinates
- i*nputMap:* Map data structure used to map the positions on a cube (1-27) with the number on the magicCube
- *currBoard*: 3D vector for initializing the game board (initially blank and filled with '-')
- humanWins  & computerWins: Variables to store the count of user and computer wins
- *human* & *computer*: Char variables to initialize the user and computer moves as 'X'/'O' accordingly
- *n*: Size of the magicCube and 3d tic tac toe board initialized to 3
- *humanList* & *computerList*: Stores the number on the magicCube corresponding to the position on the gameBoard according to the user and computer moves. (eg: if the user plays at position 1 the number corresponding to it on the magicCube is 8).
- *humanInputList* & *computerInputList:* Stores the positions of the gameBoard played by the user and computer accordingly.
- *humanLists* and *computerLists*: These are used to store the sequences of 3 numbers played by the user and computer accordingly (number of magicCube corresponding to the positions) which satisfies the conditions for winning (sum = 42 and collinearity of the numbers)
- *turnsCount:* variable that stores the number of moves played and is incremented on every valid move (if totalMoves==27 game is over!)
- *winningPosition*: Variable that is used to stores the position on the gameBoard where the computer need to play so as to win (after passing all the conditions to win)
- *humanCanWin* & *computerCanWin*: Bool variables that store if the user can win or human can win (the values are updated accordingly in the checkCanWin() function)




`        `**Execution-**

1) *int main()*
   1) The execution of the program starts from the main function.
   1) It calls *createMagicCube()* function to generate the magic cube of order n=3.
   1) It then calls the *startGame()* function.

1) *startGame()*
   1) This function initializes the game.
   1) It displays the rules of the game.
   1) It calls the function to *displayIntialBoard()*
   1) It then asks the user whether or not they want to play first, and assigns an X to the player going first and an O to the other.
   1) It calls *createGameBoard()* function to initialize the board.
   1) It calls *humanTurn()* and *computerTurn()* function accordingly
   1) The game goes on until either the board is filled, or the user or the computer completes 10 wins.
   1) In the end it displays the final score, and declares a winner.

1) *displayIntialBoard()*
   1) *displayInitialBoard() is a 3D game board which is displayed in the game rules sections and contains the numbers(positions: 1-27).* 
   1) *It is displayed for the user to easily understand how to start the game and where and how to make the next move according to the vacant position on the board.* 

1) *createGameBoard()*
   1) Used to initialize a new *gameBoard* before the game begins.
   1) It fills the board with '-' which indicates empty places on the board.
1) *humanTurn()*
   1) *humanTurn()* is used to complete the user's turn.
      1) The vector *humanCoords* is used to store the coordinates of the position entered by the user: 
      1) ` `*inputMap* gives the number from the Magic Cube which corresponds to the entered position.
      1) ` `*magicCubePosition* then gives a vector which has stored in it the x, y, and z coordinates of this number on the magic cube.
   1) If the entered position is already filled, the user is prompted to enter another position.
   1) If the entered position is empty, the entered position is added to the list of positions played by the user, and the position is filled on the gameboard.
   1) *winCheck()* is called to check whether the user succeeded in making a line after this move. 
   1) The current game board is displayed by calling the *displayGameBoard()* function
   1) The current number of wins and list of positions played by the user and the computer respectively is displayed.

1) *winCheck()*
   1) This function is used to check if there is a win using the list of moves that have been played.
   1) The *user* variable is used to determine if the player is human or computer and call the function *makeSubsequences()* which is being used to check if there is a win accordingly.
   1) Vector *subarr* is used by the makeSubsequences() function.
   1) If the number of moves played is less than order of cube then win is not possible and it exists otherwise it calls *makeSubsequences()* function.

1) *makeSubsequences()*
   1) *makeSubsequences()* is a recursive function to generate all possible sequences of order n from the list of moves played and check if their sum is equal to the magic number and if they are collinear using the function *checkLine()* and increment the wins of the player playing. *makeSubsequences()* is called recursively to make all possible subsequences:
      1) *index* is used to recursively make subsequences of *ar*r until *index* equals *n*, indicating that all possible subsequences have been made. We recursively keep calling *checkCanWin()*, once without including element at the current *index*, and once including element at current *index* by adding it to *subarr*.
      1) vector *arr* is either *computerList* or *humanList-* which contains the numbers on the magic cube corresponding to all the positions that the player has marked.
      1) *magicNumber* stores the required sum for each line of the magic cube.
      1) *subarr* is used to store the subarr currently being formed.
      1) ` `*player* is used to indicate the current player whose list is being checked- whether it's the user or the computer- 0 indicates computer and 1 indicates the user.
      1) l variable stores the length of the subsequence.
   1) Once *index* equals n, indicating that all the elements of the array have been covered, iIf the size of *subarr* is equal to n, that is it has the number of elements required to make a line and win, there is a possibility that the player could make a line and win a point.
   1) To check whether the player won, the sum of the elements of subarr is calculated in the variable *sum.* Since *arr* stored all the numbers on the magic cube corresponding to positions played, *subarr* stores these same numbers.
   1) If the sum is equal to the magic number, there is a possibility that the player has made a line and won a point.
   1) If the sum is not equal to the magic number, it exits the function as win is not possible.
   1) *checkLine()* is called to check if the three positions in the subsequence are collinear. If false is returned, we exit the function as it is not a win.
   1) If so, it means that the player has successfully made a line and won.
   1) *humanLists* is used to store all the subarrays which have resulted in a line and hence won the player a point.
   1) The current position is checked with the existing successful subarrays inserted in *humanLists* and *computerLists* according to the value of *player*, to ensure that it is not already inserted, hence avoiding duplicates.
   1) If it does not already exist, it is added to *humanLists* or *computerLists* according to the value of *player* (0=computer, 1-user), and humanWins or computerWins are also accordingly incremented.

1) *checkLine()*
   1) *checkLine()* function is basically used to check the collinearity of the three numbers on our magic cube.
   1) It takes 3 numbers in order starting from position *(i=0,j=1,k=2)* in our array where all the numbers are stored and keep on incrementing the positions*(i,j,k)* by 1 until we reach the last number in the list.
   1) 2. It then finds the coordinates of the chosen 3 numbers from the magic cube (eg. 8 has coordinates (0,0,0) in our magicCube).
   1) It stores the x,y,z coordinates respectively in the different variables so as to perform the calculations.
   1) It then calculates the distances between the numbers (dist1: dist between number 1 and 2, dist2: dist between 2 and 3, dist 3: distance between 1 and 3)
   1) It checks if the sum of dist1 and dist2 is equal to dist3 or not. If yes then the function would return true stating that the chosen three numbers are collinear on the magic cube. If dist1+dist2!=dist3 then function returns false.



1) *displayGameBoard()*
   1) Used to the display 3D game board layer-wise according to the 3 layers of the cube.(Layer 1, Layer 2, Layer 3)

1) ` `*computerTurn()*
   1) This function is used to decide the position to be played by the computer and mark it on the board using the *goMake()* function.
   1) If the number of turns checked by variable *turnsCount* is just 1 then *make\_2()* function is called.
   1) The vector *subarr* is used by the function *checkCanWin()* to determine if winning is possible.
   1) The variables *humanCanWin* and *computerCanWin* are used to keep track if winning is possible.
   1) The computer first checks if it can win by calling *checkCanWin()* and plays on that position if true is returned.
   1) Otherwise it checks if the user can win by calling *checkCanWin* and blocks that position if true is returned.
   1) Else it calls *make\_2()* and marks the most favourable position.

1) ` `*make\_2()*
   1) This function checks if the position is empty or not by calling *check()* function. If true is returned i.e. it's empty, it returns that position.In case, the position is filled it checks for the next position.
   1) ` `It first checks for the center position of the cube.
   1) It then checks for the 8 extreme corner positions of the cube.
   1) It then checks for the remaining positions starting from the top surface and moving to the bottom one.

1) ` `*check()*
   1) This function is used to check if the position *pos* passed as a parameter to the array is empty or not.
      1) *checkCoords* vector contains the coordinates of the number(*pos*) according to the magic cube. 
   1) If the position on board is marked '-' i.e. its empty the function returns true.Else, it returns false

1) ` `*goMake()*
   1) *goMake()* is used to fill the position required by the computer.The position passed to the function is added to the list of positions played by the computer, and the position is filled on the *gameboard*.
      1) The vector *compCoords* is used to store the coordinates of the position passed by the computer.
      1) *inputMap* gives the number from the Magic Cube which corresponds to the position.
      1) *magicCubePosition* then gives a vector which has stored in it the x, y, and z coordinates of this number on the magic cube.
      1) *computerList* stores all the numbers on the magic cube corresponding to the positions filled by the computer.
   1) *winCheck()* is called to check whether the computer succeeded in making a line after this move.
   1) The current gameboard is displayed, and the current number of wins and list of positions played by the user and the computer respectively is displayed.


1) ` `*checkCanWIn()*
   1) *checkCanWin()* is used to check whether there is any position which would allow the player to win.It is called recursively to make all possible subsequences
      1) *magicNumber* stores the required sum for each line of the magic cube.
      1) *arr* is the passed vector- either *computerList* or *humanList*- which contains the numbers on the magic cube corresponding to all the positions that the player has marked.
      1) *index* is used to recursively make subsequences of arr until *index* equals *n*, indicating that all possible subsequences have been made. We recursively keep calling *checkCanWin()*, once without including element at the current *index*, and once including element at current i*ndex* by adding it to *subarr.*
      1) *subarr* is used to store the subsequence currently being formed.
      1) *player* is used to indicate the current player whose list is being checked- whether it's the user or the computer- 0 indicates computer and 1 indicates the user.
   1) Once *index* equals n, indicating that all the elements of the array have been covered, if the size of *subarr* is equal to n-1, that is it has one element less than the number required to make a line and win, there is a possibility that one more move could enable the player to win.
   1) To check for the required position to win, the sum of the elements of *subarr* is calculated. Since *arr* stored all the numbers on the magic cube corresponding to positions played, *subarr* stores these same numbers.
   1) If the difference between the above sum and *magicNumber* lies is something from 1 to 27, it means that there is a possibility that there is a position which the player could mark to make a line. If this is false both *computerCanWin*  and *humanCanWin* are made to be false.
   1) *diffCoords* is used to store the corresponding x, y and z coordinates of this number on the cube.
   1) If the position is not already taken, the next thing to check is if these numbers would form a line.To do so, *subarr* is copied to a duplicate vector, in which diff is also pushed.
   1) *checkLine()* is called to check whether the subarr along with diff together form a line.
   1) If so, it means that the player can make a move on this position to win a point. Accordingly, the variable *computerCanWin* or *humanCanWin* is made to be true, depending on the value of the player.
   1) *inputMap* is used to check the corresponding position from the number on the magic cube. This position is the next winning position for the player on the gameboard, and is hence stored in the variable *winningPosition*.








**Output Screenshots:**

1) Magic Cube


1) 3D Tic Tac Toe

- Rules




- Game in Progress




- Result on Game Completion






