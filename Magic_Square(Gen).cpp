#include <bits/stdc++.h>
using namespace std;

int square[1000][1000];
bool isPossible[100];
bool flag = false;

bool checkRow(int n, int maxSum)
{
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        bool check = false;
        for (int j = 0; j < n; j++)
        {
            temp += square[i][j];
            if (square[i][j] == 0)
            {
                check = true;
            }
        }
        if (!check && temp != maxSum)
        {
            return false;
        }
    }
    return true;
}

bool checkCol(int n, int maxSum)
{
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        bool check = false;
        for (int j = 0; j < n; j++)
        {
            temp += square[j][i];
            if (square[j][i] == 0)
            {
                check = true;
            }
        }
        if (!check && temp != maxSum)
        {
            return false;
        }
    }
    return true;
}

bool checkDiag(int n, int maxSum)
{
    int temp1 = 0;
    int temp2 = 0;
    bool check = false;
    for (int i = 0; i < n; i++)
    {
        temp1 += square[i][i];
        temp2 += square[i][n - i - 1];
        if (square[i][i] == 0 || square[i][n - i - 1] == 0)
        {
            check = true;
        }
    }

    if (!check && (temp1 != maxSum || temp2 != maxSum))
    {
        return false;
    }

    return true;
}

void printMagicSquare(int n)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(3) << square[i][j] << " ";
        }
        cout << endl;
    }
}

void createMagicSquare(int n, int num, int row, int col)
{
    if (flag)
    {
        return;
    }
    int maxSum = n * (n * n + 1) / 2;

    if (!checkRow(n, maxSum) || !checkCol(n, maxSum) || !checkDiag(n, maxSum))
    {
        return;
    }

    if (row == n)
    {
        flag = true;
        printMagicSquare(n);
        return;
    }

    for (int i = 0; i < num; i++)
    {
        if (isPossible[i])
        {
            square[row][col] = i + 1;
            isPossible[i] = false;

            int nextCol = col + 1;
            int nextRow = row;
            if (nextCol == n)
            {
                nextRow++;
                nextCol = 0;
            }

            createMagicSquare(n, num, nextRow, nextCol);

            square[row][col] = 0;
            isPossible[i] = true;
        }
    }
}

int main()
{
    int n;
    cout << "Enter the size of square: ";
    cin >> n;

    cout << endl;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            square[i][j] = 0;

    int num = n * n;
    //isPossible[num];

    for (int i = 0; i < num; i++)
        isPossible[i] = true;

    // for (int i = 0; i < num; i++)
    //     cout << isPossible[i];

    createMagicSquare(n, num, 0, 0);

    //printMagicSquare(n);
    cout << endl;

    return 0;
}
