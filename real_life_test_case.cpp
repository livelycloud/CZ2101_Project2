#include <bits/stdc++.h>
using namespace std;

#define MAXN 1003

int adjM[MAXN][MAXN];

int main() {

    int V = 500;

    int E = 0;
    srand(2033);
    for(int i = 0; i < V; i++) {
        for(int j = i; j < i + 10 && j < V; j++) {
            adjM[i][j] = rand() % 11 + 1;
            E++;
        }
    }
    ofstream outFile;   
    outFile.open("test_case.txt");

    outFile<<V<<" "<<E<<endl;
    outFile<<0<<" "<<V - 1<<endl;
    printf("%d %d\n", V, E);
    printf("%d %d\n", 0, V - 1);

    for(int i = 0; i < V; i++) {
        for(int j = i; j < i + 10 && j < V; j++) {
            printf("%d %d %d\n", i, j, adjM[i][j]);
            E--;
            outFile<<i<<" "<<j<<" "<<adjM[i][j]<<endl;
        }
    }

    printf("%d\n", E);


    return 0;
}
