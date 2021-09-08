#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int main() {
    ofstream outfile;
    outfile.open("test.csv");
    outfile << "row" << "," << "column" << "," << "value" << endl;
    int V;
    cin >> V;
    vector<vector<int>> graph2(V, vector<int> (V, 0));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph2[i][j] = i + j;
            outfile << i << "," << j << "," << graph2[i][j] << endl;
        }
        
    }
}