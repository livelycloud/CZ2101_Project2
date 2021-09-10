#include <bits/stdc++.h>
using namespace std;

//assume all path weight are integer values, and the total length will not exceed long long 
//use array for priority queue, insert O(n) (insertion sort/bubble from the end of the queue), getMin O(1);

#define MAXN 1003
#define POS_INF 1152921504606846976

typedef long long ll;

int adjM[MAXN][MAXN]; //adjacency matrix adjM[i][j] means the weight of a path from i to j
bool visited[MAXN]; //indicate if the shortest distance to node i is found;
ll dis[MAXN]; //record the distances of nodes
int V, E;


int getMin() { //return the index of the unvisited node with the shortest distance
    int curmin = -1, minIndex = -1;
    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            if(dis[i] < curmin || curmin == -1) {
                curmin = dis[i];
                minIndex = i;
            }
        }
    }
    return minIndex;
}


//find shortest distance from s to e
//V: number of nodes
ll K_array(int s, int e) 
{
    //initialise pq
    memset(visited, false, V);
    

    for(int i = 0; i < V; i++) {
        if(adjM[s][i] != 0){
            dis[i] = adjM[s][i];
        } else {
            dis[i] = POS_INF;
        }
    }

    visited[s] = true;
    dis[s] = 0;

    int numOfRounds = 0;

    while(!visited[e] && numOfRounds < V - 1 ) {
        numOfRounds++; //need to complete V - 1 Rounds
        int node = getMin(); //get  the index of the unvisited node with the shortest distance

        visited[node] = true;
        ll distance = dis[node];
        for(int i = 0; i < V; i++) { //O(n)
            if(!visited[i] && adjM[node][i] != 0){
                dis[i] = min(dis[i], adjM[node][i] + distance);
            }
        }
        
    }

    return dis[e]; //if no path, return -1
}

int main() {

    scanf("%d %d", &V, &E);
    int s, e;
    scanf("%d %d", &s, &e);

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++)
            adjM[i][j] = 0;
    }

    for(int i = 0; i < E; i++) {
        int j, k, w;
        scanf("%d %d %d", &j, &k, &w);
        adjM[j][k] = w;
        adjM[k][j] = w;
    }


    ll ans = K_array(s, e);

    printf("%d\n",ans);

    return 0;

}