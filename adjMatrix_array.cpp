#include <bits/stdc++.h>
using namespace std;

//assume all path weight are integer values, and the total length will not exceed long long 
//use array for priority queue, insert O(n) (insertion sort/bubble from the end of the queue), getMin O(1);

#define MAXN 1003

typedef long long ll;

typedef pair<ll, int> pi; //pi.first is the distance to  node pi.second


int adjM[MAXN][MAXN]; //adjacency matrix adjM[i][j] means the weight of a path from i to j


pi pq[MAXN*MAXN]; //priority queue for min distance

int l, r; //index for start and end of pq, pq[l] is the min while pq[r - 1] is last elemetn in the queue

bool flag[MAXN]; //indicate if the shortest distance to node i is found;
ll dis[MAXN]; //record the final distances

pi getMin(pi pq[]) {
    if(r > l) return pq[l++];
    else return make_pair(-1, -1);
}

void enqueue(pi pq[], pi pair) {
    int i = r;
    pq[r++] = pair;

    while(r > l && pq[i] < pq[i - 1]) { //insertion sort
        pi tmp = pq[i];
        pq[i] = pq[i - 1];
        pq[i - 1] = tmp;
    }
}

bool isEmpty(pi pq[]) {
    return r <= l;
}


//find shortest distance from s to e
//V: number of nodes
ll K_array(int adjM[][MAXN], int V, int s, int e) 
{
    //initialise pq
    l = 0, r = 0;
    memset(flag, false, V);

    for(int i = 0; i < V; i++) {
        if(adjM[s][i] != 0){
            enqueue(pq, make_pair(adjM[s][i], i));
        }
    }
    flag[s] = true;
    dis[s] = 0;

    while(!flag[e] && !isEmpty(pq)) {
        pi cur = getMin(pq);
        ll w = cur.first;
        int node = cur.second;
        flag[node] = true;
        dis[node] = w;
        for(int i = 0; i < V; i++) { //O(n)
            if(!flag[i] && adjM[node][i] != 0){
                enqueue(pq, make_pair(w + adjM[node][i], i));
            }
        }
    }

    if(flag[e]) return dis[e];
    else return -1; //if no path, return -1

}

int main() {
    int V, E;
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
    }


    ll ans = K_array(adjM, V, s, e);

    printf("%d\n",ans);

    return 0;

}