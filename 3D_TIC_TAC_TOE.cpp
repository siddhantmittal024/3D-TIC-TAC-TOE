#include <bits/stdc++.h>
using namespace std;

//Global Variables

//map data structure used to map the number on the magicCube to it's coordinates
map<int, vector<int>> magicCubePosition;

//map data structure used to map the positions on a cube (1-27) with the number on the magicCube
map<int, int> inputMap;

//variables to store the count of user and computer wins
int humanWins = 0, computerWins = 0;

//char variables to initialize the user and computer moves as 'X'/'O' accordingly
char human, computer;

//size of the magicCube and 3d tic tac toe board
int n = 3;

//3D vector for initializing the game board (initially blank and filled with '-')
vector<vector<vector<char>>> currBoard;

/*
Vectors (1D):

humanList & computerList: stores the number on the magicCube corresponding to the position on 
the gameBoard according to the user and computer moves.
(eg: if user plays at position 1 the number corresponding to it on the magicCube is 8).

humanInputList & computerInputList: stores the positions of the gameBoard played by the user and computer accordingly.
*/
vector<int> humanList, computerList, humanInputList, computerInputList;

/*
Vectors (2D):

humanLists and computerLists: these are used to store the sequences of 3 numbers played by the user and computer
accordingly (number of magicCube corresponding to the positions) which satisfies the conditions for 
winning (sum = 42 and collinearity of the numbers)
*/
vector<vector<int>> humanLists, computerLists;

//variable that stores the number of moves played and is incremented on every valid move (if totalMoves==27 game is over!)
int turnsCount = 0;

//bool variables that store if the user can win or human can win (the values are updated accordingly in the checkCanWin() function)
bool humanCanWin = false, computerCanWin = false;

//variable that is used to stores the position on the gameBoard where the computer need to play so as to win (after passing all the conditions to win)
int winningPosition;

/*
CREATE MAGIC CUBE

The numbers from 1 to 27 in a magic cube are found to be following a pattern. The function below makes use of this pattern to find the next position of insertion each time and thus insert every number at the required position in the magic cube.
The position of 1 is found from observation to always lie in a certain position in the cube, and the rest of the numbers follow a pattern which depends on this initial position.
*/
void createMagicCube()
{
    //arr is used to store the 3D Magic Cube
    int arr[n][n][n];

    //num is used in the creation of inputMap, to map the numbers from 1 to 27, which indicate positions on the gameboard, to the corresponding number in the magic cube
    int num = 1;

    /*
    From observation, it was found that the initial position, that is the position of 1 in the cube, is (n/2, 0, n/2), where n is the size of the cube.
    1. height indicates the surface level in the cube- 0 being the highest and n-1 being the lowest.
    2. row indicates the row number on each surface- 0 being furthest at the back and n-1 being at the front of the cube.
    3. col indicates the column number on each surface- 0 being furthest at the left and n-1 being furthest at the right.
    */
    int height = n / 2, row = 0, col = n / 2;

    /*
    Each element of the 3D cube is initialized with zero.
    */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                arr[i][j][k] = 0;
            }
        }
    }

    //i is inserted at the found position in the cube and then incremented, allowing the insertion of all numbers from 1 to 27 (n*n*n) in the cube.
    for (int i = 1; i <= n * n * n; i++)
    {
        /*
        If the required position in the cube is already occupied, from observation it is found that the position is instead shifted to the next surface (lower surface), and the previous row (the row at the back).
        If the row, column or height is less than 0, i.e it goes out of bounds and is not valid, it is made to wrap around and come to n-1. Similarly if it becomes greater than n-1, it is made to wrap around and come to 0.
        */
        if (arr[height][row][col] != 0)
        {
            height++;
            row--;
            if (row < 0)
                row = n - 1;
            else if (row == n)
                row = 0;
            if (height < 0)
                height = n - 1;
            else if (height == n)
                height = 0;
            if (col < 0)
                col = n - 1;
            else if (col == n)
                col = 0;

            /*
                If the required position in the cube is again found to be occupied, from observation it is found that the position is instead shifted to the next column (to the right), and the previous surface (upper surface).
                If the row, column or height is less than 0, i.e it goes out of bounds and is not valid, it is made to wrap around and come to n-1. Similarly if it becomes greater than n-1, it is made to wrap around and come to 0.
                */
            if (arr[height][row][col] != 0)
            {
                col++;
                height--;
                if (row < 0)
                    row = n - 1;
                else if (row == n)
                    row = 0;
                if (height < 0)
                    height = n - 1;
                else if (height == n)
                    height = 0;
                if (col < 0)
                    col = n - 1;
                else if (col == n)
                    col = 0;
            }
        }

        //Once the correct position is found, the current number, which is i, is inserted at this position in the cube.
        arr[height][row][col] = i;

        //The values in the map magicCubePosition are inserted alongside the construction of the cube. It maps the number in the magic cube to its corresponding x, y, and z coordinates.
        magicCubePosition[i] = {height, row, col};

        /*
        From observation it is found that the next position is found from the current position- it is shifted to the previous row (the row to the back), and the previous column (to the left).
        If the row, column or height is less than 0, i.e it goes out of bounds and is not valid, it is made to wrap around and come to n-1. Similarly if it becomes greater than n-1, it is made to wrap around and come to 0.
        */
        row--;
        col--;
        if (row < 0)
            row = n - 1;
        else if (row == n)
            row = 0;
        if (height < 0)
            height = n - 1;
        else if (height == n)
            height = 0;
        if (col < 0)
            col = n - 1;
        else if (col == n)
            col = 0;
    }

    //The creation of inputMap, to map the numbers from 1 to 27, which indicate positions on the gameboard, to the corresponding number in the magic cube.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                inputMap[num++] = arr[i][j][k];
            }
        }
    }
}

/*
CREATE GAME BOARD

createGameBoard() is used to initialize a new gameBoard before the game begins.
It fills the board with '-' which indicates empty places on the board.
*/
void createGameBoard()
{
    int num = 1;
    for (int i = 0; i < n; i++)
    {

        vector<vector<char>> c1;
        for (int j = 0; j < n; j++)
        {
            vector<char> c2;
            for (int k = 0; k < n; k++)
            {
                c2.push_back('-');
            }

            c1.push_back(c2);
        }

        currBoard.push_back(c1);
    }
}

/*
DISPLAY GAME BOARD

displayGameBoard() is used to the display our 3D game board
layer-wise according to the each layers of the cube.
(Layer 1, Layer 2, Layer 3)
*/
void displayGameBoard()
{
    for (int i = 0; i < n; i++)
    {
        cout << setw(2) << " Layer " << i + 1 << endl;
        cout << endl;
        for (int j = 0; j < n; j++)
        {

            for (int k = 0; k < n; k++)
            {
                cout << setw(2) << currBoard[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
}

/*
DISPLAY INITIAL BOARD

displayInitialBoard() is a 3D game board which is displayed in the game rules sections and contains 
the numbers(positions: 1-27). It is displayed for the user to easily understand on how to start the game 
and where and how to make the next move according to the vacant position on the board. 
*/
void displayInitialBoard()
{
    int num = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            for (int k = 0; k < n; k++)
            {
                cout << setw(3) << num++ << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

/*
CHECK LINE

checkLine() function is basically used to check the collinearity of the three numbers on our magicCube.
1. It takes 3 numbers in order starting from position (i=0,j=1,k=2) in our array where all the numbers are stored 
and keep on incrementing the positions(i,j,k) by 1 until we reach the reach the last number in the list.
2. It then finds the coordinates of the chosen 3 numbers from the magicCube (eg. 8 has coordinates (0,0,0) in our magicCube).
3. It stores the x,y,z coordinates respectively in the different variables so as to perform the calculations.
4. It then calculates the distances between the numbers (dist1: dist between number 1 and 2, dist2: dist between 2 and 3, dist 3: distance between 1 and 3)
5. It checks that if the sum of dist1 and dist2 is equal to dist3 or not. If yes then the function would return true
stating that the chosen three numbers are collinear on the magicCube. If dist1+dist2!=dist3 then function returns false.  
*/
bool checkLine(vector<int> subarr)
{
    int i = 0, j = 1, k = 2;
    while (k < n)
    {
        vector<int> first = magicCubePosition[subarr[i]], second = magicCubePosition[subarr[j]], third = magicCubePosition[subarr[k]];
        int x1 = first[0], y1 = first[1], z1 = first[2], x2 = second[0], y2 = second[1], z2 = second[2], x3 = third[0], y3 = third[1], z3 = third[2];
        /*
        if (x3 - x1 == 0 || y3 - y1 == 0 || z3 - z1 == 0)
            return false;

        double lambda1 = (x2 - x1) / (x3 - x1);
        cout<<lambda1<<endl;
        double lambda2 = (y2 - y1) / (y3 - y1);
                cout<<lambda2<<endl;

        double lambda3 = (z2 - z1) / (z3 - z1);
                cout<<lambda3<<endl;

        cout << "lambdas " << lambda1 << " " << lambda2 << " " << lambda3 << endl;
        if (lambda1 != lambda2 || lambda2 != lambda3)
        {
            return false;
        }
        */
        double dist1, dist2, dist3;
        dist1 = pow(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2), 0.5);
        dist2 = pow(pow(x3 - x2, 2) + pow(y3 - y2, 2) + pow(z3 - z2, 2), 0.5);
        dist3 = pow(pow(x3 - x1, 2) + pow(y3 - y1, 2) + pow(z3 - z1, 2), 0.5);
        vector<double> distances;
        distances.push_back(dist1);
        distances.push_back(dist2);
        distances.push_back(dist3);
        sort(distances.begin(), distances.end());

        if (distances[0] + distances[1] != distances[2])
            return false;
        i++, j++, k++;
    }

    return true;
}

/* CHECK

This function is used to check if the position pos passed as a parameter to the array is empty or not.
checkCoords vector contains the coordinates of the number(pos) acoording to the magic cube. 
If the position in board is marked '-' i.e. its empty the function returns true.
*/
bool check(int pos)
{
    vector<int> checkCoords = magicCubePosition[inputMap[pos]];
    if (currBoard[checkCoords[0]][checkCoords[1]][checkCoords[2]] == '-')
    {
        return true;
    }
    else
        return false;
}

/* MAKE 2

This function checks if the position is empty or not by calling check() function. If true is returned i.e. it's empty, it returns that position.
in case, the position is filled it checks for the next position.
1. It first checks for the center position of the cube.
2. It then checks for the 8 extreme corner positions of the cube.
3.  It then checks for the remaining positions starting from the top surface and moving to the bottom one.
*/
int make_2()
{
    if (check(14) == true)
    {
        return 14;
    }
    else if (check(1) == true)
    {
        return 1;
    }
    else if (check(3) == true)
    {
        return 3;
    }
    else if (check(7) == true)
    {
        return 7;
    }
    else if (check(9) == true)
    {
        return 9;
    }
    else if (check(19) == true)
    {
        return 19;
    }
    else if (check(21) == true)
    {
        return 21;
    }
    else if (check(25) == true)
    {
        return 25;
    }
    else if (check(27) == true)
    {
        return 27;
    }
    if (check(10) == true)
    {
        return 10;
    }
    else if (check(12) == true)
    {
        return 12;
    }
    else if (check(16) == true)
    {
        return 16;
    }
    else if (check(18) == true)
    {
        return 18;
    }
    else if (check(2) == true)
    {
        return 2;
    }
    else if (check(4) == true)
    {
        return 4;
    }
    else if (check(5) == true)
    {
        return 5;
    }
    else if (check(6) == true)
    {
        return 6;
    }
    else if (check(8) == true)
    {
        return 8;
    }
    else if (check(11) == true)
    {
        return 11;
    }
    else if (check(13) == true)
    {
        return 13;
    }
    else if (check(15) == true)
    {
        return 15;
    }
    else if (check(17) == true)
    {
        return 17;
    }
    else if (check(20) == true)
    {
        return 20;
    }
    else if (check(22) == true)
    {
        return 22;
    }
    else if (check(23) == true)
    {
        return 23;
    }
    else if (check(24) == true)
    {
        return 24;
    }
    else if (check(26) == true)
    {
        return 26;
    }
    return 0;
}

/*
CHECK CAN WIN

checkCanWin() is used to check whether there is any position which would allow the player to win.

magicNumber stores the required sum for each line of the magic cube.

checkCanWin() is called recursively to make all possible subsequences:
1. arr is the passed vector- either computerList or humanList- which contains the numbers on the magic cube corresponding to all the positions that the player has marked.
2. index is used to recursively make subsequences of arr until index equals n, indicating that all possible subsequences have been made. We recursively keep calling checkCanWin(), once without including element at the current index, and once including element at current index by adding it to subarr.
3. subarr is used to store the subsequence currently being formed.
4. player is used to indicate the current player whose list is being checked- whether it's the user or the computer- 0 indicates computer and 1 indicates the user.

Once index equals n, indicating that all the elements of the array have been covered:
1. If the size of subarr is equal to n-1, that is it has one element less than the number required to make a line and win, there is a possibility that one more move could enable the player to win.
2. To check for the required position to win, the sum of the elements of subarr is calculated. Since arr stored all the numbers on the magic cube corresponding to positions played, subarr stores these same numbers.
3. If the difference between the above sum and magicNumber lies is something from 1 to 27, it means that there is a possibility that there is a position which the player could mark to make a line. If this is false both computerCanWin  and humanCanWin are made to be false.
4. diffCoords is used to store the corresponding x, y and z coordinates of this number on the cube.
5. If the position is not already taken, the next thing to check is if these numbers would form a line.
6. To do so, subarr is copied to a duplicate vector, in which diff is also pushed.
7. checkLine() is called to check whether the subarr along with diff together form a line.
8. If so, it means that the player can make a move on this position to win a point. Accordingly, the variable computerCanWin or humanCanWin is made to be true, depending on the value of player.
9. inputMap is used to check the corresponding position from the number on the magic cube. This position is the next winning position for the player on the gameboard, and is hence stored in the variable winningPosition.
*/
void checkCanWin(vector<int> arr, int index,
                 vector<int> subarr, int player)
{
    int magicNumber = n * (n * n * n + 1) / 2;

    if (index == arr.size())
    {
        int l = subarr.size();

        if (l != 0)
        {
            if (subarr.size() == n - 1)
            {
                int sum = 0;
                for (auto f : subarr)
                {
                    sum += f;
                }
                int diff = magicNumber - sum;
                if (diff > 0 && diff <= 27)
                {
                    vector<int> diffCoords = magicCubePosition[diff];
                    if (currBoard[diffCoords[0]][diffCoords[1]][diffCoords[2]] != '-')
                        return;
                    vector<int> duplicate = subarr;
                    duplicate.push_back(diff);
                    if (checkLine(duplicate) == true)
                    {
                        if (player == 0)
                            computerCanWin = true;
                        else
                            humanCanWin = true;
                        for (auto itr : inputMap)
                        {
                            if (itr.second == diff)
                            {
                                winningPosition = itr.first;
                            }
                        }
                    }
                }
                else
                {
                    computerCanWin = false;
                    humanCanWin = false;
                }
            }
        }
    }

    else
    {
        checkCanWin(arr, index + 1, subarr, player);

        subarr.push_back(arr[index]);

        checkCanWin(arr, index + 1, subarr, player);
    }
    return;
}

/*
MAKE SUBSEQUENCES

makeSubsequences() is a recursive function to generate all possible sequences of order n from the list of moves played and check if their sum is equal to the magic number and if they are collinear using the function checkLine() and increment the wins of the player playing. We recursively keep calling checkCanWin(), once without including element at the current index, and once including element at current index by adding it to subarr.

magicNumber stores the required sum for each line of the magic cube.

makeSubsequences() is called recursively to make all possible subsequences:
1. arr is the passed vector- either computerList or humanList- which contains the numbers on the magic cube corresponding to all the positions that the player has marked.
2. index is used to recursively make subsequences of arr until index equals n, indicating that all possible subsequences have been made. We recursively keep calling checkCanWin(), once without including element at the current index, and once including element at current index by adding it to subarr.
3. subarr is used to store the subarr currently being formed.
4. player is used to indicate the current player whose list is being checked- whether it's the user or the computer- 0 indicates computer and 1 indicates the user.
5. l variable stores the length of the subsequence.

Once index equals n, indicating that all the elements of the array have been covered:
1. If the size of subarr is equal to n, that is it has the number of elements required to make a line and win, there is a possibility that the player could make a line and win a point.
2. To check whether the player won, the sum of the elements of subarr is calculated in the variable sum. Since arr stored all the numbers on the magic cube corresponding to positions played, subarr stores these same numbers.
3. If the sum is equal to the magic number, there is a possibility that the player has made a line and won a point.
4. If the sum is not equal to magic number, it exits the function as win is not possible.
5. checkLine() is called to check if the three positions in the subsequence are collinear. If false is returned, we exit the function as it is not a win.
6. If so, it means that the player has successfully made a line and won.
7. humanLists is used to store all the subarrays which have resulted in a line and hence won the player a point.
8. The current position is checked with the existing successful subarrays inserted in humanLists and computerLists according to the value of player, to ensure that it is not already inserted, hence avoiding duplicates.
9. If it does not already exist, it is added to humanLists or computerLists according to the value of player (0=computer, 1-user), and humanWins or computerWins is also accordingly incremented.
*/
void makeSubsequences(vector<int> arr, int index,
                      vector<int> subarr, int player)
{
    int magicNumber = n * (n * n * n + 1) / 2;

    if (index == arr.size())
    {
        int l = subarr.size();

        if (l != 0)
        {
            if (subarr.size() == n)
            {
                int sum = 0;
                for (auto f : subarr)
                {
                    sum += f;
                }

                if (sum != magicNumber)
                {
                    return;
                }
                else
                {
                    if (checkLine(subarr) == false)
                    {
                        return;
                    }
                    else if (player == 1)
                    {
                        for (auto p : humanLists)
                        {
                            if (p[0] == subarr[0] && p[1] == subarr[1] && p[2] == subarr[2])
                            {
                                return;
                            }
                        }
                        humanLists.push_back(subarr);
                        humanWins++;
                    }
                    else
                    {
                        for (auto p : computerLists)
                        {
                            if (p[0] == subarr[0] && p[1] == subarr[1] && p[2] == subarr[2])
                            {
                                return;
                            }
                        }
                        computerLists.push_back(subarr);
                        computerWins++;
                    }
                }
            }
        }
    }

    else
    {

        makeSubsequences(arr, index + 1, subarr, player);

        subarr.push_back(arr[index]);

        makeSubsequences(arr, index + 1, subarr, player);
    }
    return;
}
/* WIN CHECK

This function is used to check if there is a win using the list of moves that have been played.
The user variable is used to determine if the player is human or computer and call the function makeSubsequences() which is being used to check if there is a win accordingly.
Vector subarr is used by the makeSubsequences() function.
If the number of moves played is less than order of cube then win is not possible and it exits otherwise it calls makeSubsequences() function.
*/
void winCheck(int user)
{
    if (user == 1)
    {
        if (humanList.size() < n)
        {
            return;
        }
        else
        {
            vector<int> subarr;
            makeSubsequences(humanList, 0, subarr, user);
        }
    }
    else
    {
        if (computerList.size() < n)
        {
            return;
        }
        else
        {
            vector<int> subarr;
            makeSubsequences(computerList, 0, subarr, user);
        }
    }
}

/*
GO MAKE

goMake() is used to fill the position required by the computer.

The position passed to the function is added to the list of positions played by the computer, and the position is filled on the gameboard.

The vector compCoords is used to store the coordinates of the position passed by the computer:
1. inputMap gives the number from the Magic Cube which corresponds to the position.
2. magicCubePosition then gives a vector which has stored in it the x, y, and z coordinates of this number on the magic cube.

computerList stores all the numbers on the magic cube corresponding to the positions filled by the computer.

winCheck() is called to check whether the computer succeeded in making a line after this move.

The current gameboard is displayed, and the current number of wins and list of positions played by the user and the computer respectively is displayed.
*/
void goMake(int pos)
{
    computerInputList.push_back(pos);
    turnsCount++;
    vector<int> compCoords = magicCubePosition[inputMap[pos]];
    int x = compCoords[0], y = compCoords[1], z = compCoords[2];

    currBoard[x][y][z] = computer;
    computerList.push_back(inputMap[pos]);
    winCheck(0);
    cout << endl;
    displayGameBoard();
    cout << "Number of wins by user: " << humanWins << endl;
    cout << endl;
    cout << "Positions played by user: [ ";
    for (int i = 0; i < humanInputList.size(); i++)
    {
        cout << humanInputList[i] << " ";
    }
    cout << "] " << endl;
    cout << endl;
    cout << "Number of wins by computer: " << computerWins << endl;
    cout << endl;
    cout << "Positions played by computer: ";
    cout << "[ ";
    for (int i : computerInputList)
    {
        cout << i << " ";
    }
    cout << "]" << endl;
    cout << endl;
}
/* 
COMPUTER TURN

This function is used to decide the position to be played by the computer and mark it on the board using the goMake() function.
1. If the number of turns checked by variable turnsCount is just 1 then make_2() function is called.

The vector subarr is used by the function checkCanWin() to determine if winning is possible.
The variables humanCanWin amd computerCanWin are used to keep track if winning is possible.

2. The computer first checks if it can win by calling checkCanWin() and plays on that position if true is returned.
3. Otherwise it checks if user can win by calling checkCanWin and blocks that position if true is returned.
4. Else it calls make_2() and marks the most favourable position 
*/
void computerTurn()
{
    if (turnsCount < 1)
    {
        int pos = make_2();
        goMake(pos);
    }
    else
    {
        humanCanWin = false;
        computerCanWin = false;
        vector<int> subarr;
        checkCanWin(computerList, 0, subarr, 0);
        if (computerCanWin == false)
        {
            checkCanWin(humanList, 0, subarr, 1);
            if (humanCanWin == false)
            {
                int pos = make_2();
                goMake(pos);
            }
            else
            {
                goMake(winningPosition);
            }
        }
        else
        {
            goMake(winningPosition);
        }
    }
}

/*
HUMAN TURN

humanTurn() is used to complete the user's turn.

The vector humanCoords is used to store the coordinates of the position entered by the user: 
1. inputMap gives the number from the Magic Cube which corresponds to the entered position.
2. magicCubePosition then gives a vector which has stored in it the x, y, and z coordinates of this number on the magic cube.

If the entered position is already filled, the user is prompted to enter another position.

If the entered position is empty:
1. The entered position is added to the list of positions played by the user, and the position is filled on the gameboard.
2. winCheck() is called to check whether the user succeeded in making a line after this move. 
3. The current gameboard is displayed.
4. The current number of wins and list of positions played by the user and the computer respectively is displayed.
*/
void humanTurn(int humanPosition)
{
    vector<int> humanCoords = magicCubePosition[inputMap[humanPosition]];
    int x = humanCoords[0], y = humanCoords[1], z = humanCoords[2];
    if (currBoard[x][y][z] != '-')
    {
        cout << "This position has already been filled! Please choose another one. -->";
        cin >> humanPosition;
        humanTurn(humanPosition);
    }
    else
    {
        humanInputList.push_back(humanPosition);
        currBoard[x][y][z] = human;
        humanList.push_back(inputMap[humanPosition]);
        winCheck(1);
        cout << endl;
        displayGameBoard();
        cout << "Number of wins by user: " << humanWins << endl;
        cout << endl;
        cout << "Positions played by user: [ ";
        for (int i = 0; i < humanInputList.size(); i++)
        {
            cout << humanInputList[i] << " ";
        }
        cout << "] " << endl;
        cout << endl;
        cout << "Number of wins by computer: " << computerWins << endl;
        cout << endl;
        cout << "Positions played by computer: ";
        cout << "[ ";
        for (int i : computerInputList)
        {
            cout << i << " ";
        }
        cout << "]" << endl;
        cout << endl;
        cout << endl;
    }
}

/*
START GAME

This function initializes the game-
1. It displays the rules of the game.
2. It then asks the user whether or not they want to play first, and assigns an X to the player going first and an O to the other.

The game goes on until either the board is filled, or the user or the computer completes 10 wins.

In the end it displays the final score, and declares a winner.
*/
void startGame()
{
    cout << "3D-TIC TAC TOE" << endl;
    cout << endl;
    cout << "The rules are as follows:" << endl;
    cout << endl;
    cout << "1. The player who makes the first move plays as 'X'. The other player plays as 'O'." << endl;
    cout << "2. You can choose your next position on the board by selecting a number from 1-27. The positions and the corresponding numbers are as follows: " << endl;
    cout << endl;
    displayInitialBoard();
    cout << endl;
    cout << "3. The first board represents the top surface of the cube, the second board represents the middle surface, and the third board represents the lowest surface." << endl;
    cout << "4. The winning lines can be rows, columns, pillars, or major diagonals." << endl;
    cout << "5. You get 1 point for every valid win." << endl;
    cout << "6. Whoever gets 10 points first wins. If the game ends without anyone reaching 10 points, the player with maximum points will win." << endl;
    cout << endl;
    int choice;
    bool computerFirst = false, humanFirst = false;
    createGameBoard();
    cout << "Do you want to play first? (0 for no, 1 for yes) --> ";
    cin >> choice;
    if (choice == 1)
    {
        humanFirst = true;
        human = 'X';
        computer = 'O';
    }
    else
    {
        computerFirst = true;
        computer = 'X';
        human = 'O';
    }
    cout << endl;
    cout << "You are player " << human << endl;
    cout << endl;

    while (humanWins < 10 && computerWins < 10 && turnsCount <= 27)
    {
        int humanPosition;
        if (humanFirst == true)
        {
            cout << "Where do you want to play? (choose a number from 1 to 27) --> ";
            cin >> humanPosition;
            cout << endl;
            turnsCount++;
            humanTurn(humanPosition);
        }

        if (humanWins > 10 || turnsCount == 27)
            break;

        computerTurn();
        if (computerWins > 10 || turnsCount == 27)
            break;

        if (humanFirst == false)
        {
            cout << "Where do you want to play? (choose a number from 1 to 27) --> ";
            cin >> humanPosition;
            cout << endl;
            turnsCount++;
            humanTurn(humanPosition);
        }
    }
    cout << endl;
    cout << "-------------------------------GAME OVER---------------------------------" << endl;
    cout << endl;
    cout << "Number of wins by computer: " << computerWins << endl;
    cout << "Number of wins by user: " << humanWins << endl;
    cout << endl;
    if (humanWins == computerWins)
    {
        cout << "It's a Draw." << endl;
    }
    else if (humanWins > computerWins)
    {
        cout << "Congratulation! You won. :)" << endl;
    }
    else if (computerWins > humanWins)
    {
        cout << "Sorry! You lost :(" << endl;
    }
    cout << endl;
}

//main
int main()
{
    createMagicCube();
    cout << endl;
    startGame();
    return 0;
}