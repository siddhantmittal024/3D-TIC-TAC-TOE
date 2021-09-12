#include <bits/stdc++.h>
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i = j; i < k; i += in)
#define RFOR(i, j, k, in) for (int i = j; i >= k; i -= in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

void generatingMagicSquare(int n)
{
    int magicSquare[n][n];
    int i = n / 2;
    int j = n - 1;

    REP(k, n)
    {
        REP(l, n)
        {
            magicSquare[k][l] = 0;
        }
    }

    int num = 1;

    while (num <= n * n)
    {
        if (i == -1 && j == n)
        {
            i = 0;
            j = n - 2;
        }
        else
        {
            if (j == n)
            {
                j = 0;
            }
            if (i < 0)
            {
                i = n - 1;
            }
        }

        if (magicSquare[i][j])
        {
            j = j - 2;
            i += 1;
            continue;
        }
        else
        {
            magicSquare[i][j] = num++;
        }
        j++;
        i--;
    }

    REP(k, n)
    {
        REP(l, n)
        {
            cout << setw(2) << magicSquare[k][l] << " ";
        }
        cout << endl;
    }
}

int main()
{
    clock_t start = clock();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout << fixed << setprecision(9);
    //int t = 1;
    int t;
    cin >> t;

    REP(tc, t)
    {
        int n;
        cin >> n;
        cout << "Magic Square has sum of each row/col/diag = " << n * (n * n + 1) / 2 << endl;
        generatingMagicSquare(n);
        cout << endl;
    }
#ifndef ONLINE_JUDGE
    clock_t end = clock();
    cout << "\nExecution Time: " << (double)(end - start) / double(CLOCKS_PER_SEC)
         << "s";
#endif
    return 0;
}
