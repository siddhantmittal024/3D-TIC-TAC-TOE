#include <bits/stdc++.h>
using namespace std;

/*
The numbers from 1 to n^3 in a magic cube are found to be following a pattern. 
The program below makes use of this pattern to find the next position of insertion each time and thus insert 
every number at the required position in the magic cube.The position of 1 is found from observation to always 
lie in a certain position in the cube, and the rest of the numbers follow a pattern which depends on this 
initial position.
*/

int main()
{
	//size of the magic cube
	int n;

	//take only odd vales like 3,5,7.. for perfect results
	cout << "Enter the size of cube: ";
	cin >> n;

	//arr is used to store the 3D Magic Cube
	int arr[n][n][n];

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

	//i is inserted at the found position in the cube and then incremented, allowing the insertion of all numbers from 1 to n*n*n in the cube.
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

	cout << endl;

	cout << "Magic Cube: " << endl;
	cout << endl;

	//Printing our generated 3D Magic Cube to see the results
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				cout << setw(3) << arr[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

//PS: THIS CODE ONLY WORKS FOR ODD VALUES ON N like N=3,5,7...