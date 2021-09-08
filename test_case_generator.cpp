#include <bits/stdc++.h>
using namespace std;

#define MAXN 1003

int adjM[MAXN][MAXN];

int main() {

    srand(2561);
    int V = rand() % 30 + 10;
    int E = 0.3 * V * V;

    printf("%d %d\n", V, E);

    int s = rand() % V;
    int e = rand() % V;

    if(e == s) e = rand() % V;
    printf("%d %d\n", s, e);

    int num = 0;
    while(num < E) {
        int j = rand() % V;
        int k = rand() % V;
        int w = rand() % 50 + 5;
        if(adjM[j][k] == 0 && j != k) {
            printf("%d %d %d\n",j, k, w);
            adjM[j][k] = w;
            adjM[k][j] = w;
            num++;
        }
    }

    return 0;
}