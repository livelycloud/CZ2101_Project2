#include <bits/stdc++.h>
using namespace std;


#define MAXN 1003


//use heap for priority queue, enque O(logn), getMin O(log n)

typedef long long ll;

typedef pair<ll, int> pi; //pi.first is the distance to  node pi.second

vector<pi> adjList[MAXN];

pi pq[MAXN * MAXN]; //priority queue with heap, the first element is at pq[1]
int pq_size;

ll dis[MAXN];

void shiftDown(pi H[], pi k) { //O(logn)
    int Size = pq_size;
    int j = 1, cj = 2;
    while(cj <= Size) {
        if(cj < Size && H[cj] > H[cj + 1]) cj++; //get the smaller child
        if(k <= H[cj]) break;
        H[j] = H[cj];
        j = cj;
        cj = 2 * j;
    }
    H[j] = k;
}

void shiftUp(pi H[], pi k) { //O(logn)
    int j = ++pq_size, pj = j / 2;
    while(pj >= 1) {
        if(k >= H[pj]) break;
        else {
            H[j] = H[pj];
            j = pj;
            pj = j / 2;
        }
    }
    H[j] = k;
}

void enqueue(pi pq[], pi k) {
    shiftUp(pq, k);
}   

pi getMin(pi pq[]) {
    pi tmp = pq[1];
    shiftDown(pq, pq[pq_size--]);
    return tmp;
}

//find shortest distance from s to e
//V: number of nodes
ll K_heap(vector<pi> adjList[], int V, int s, int e) 
{
    //initialise pq
    pq_size = 0;
    memset(dis, -1, sizeof(ll) * V);

    for(int i = 0; i < adjList[s].size(); i++) {
        enqueue(pq, make_pair(adjList[s][i].first, adjList[s][i].second));
    }
    

    dis[s] = 0;

    while(dis[e] < 0 && pq_size > 0) {
        pi cur = getMin(pq);
        ll w = cur.first;
        int node = cur.second;
        if(dis[node] == -1) {
            dis[node] = w;
            
            for(int i = 0; i < adjList[node].size(); i++) {
                enqueue(pq, make_pair(adjList[node][i].first + w, adjList[node][i].second));
            }
        }
    }

    return dis[e];

}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    int s, e;
    scanf("%d %d", &s, &e);


    for(int i = 0; i < E; i++) {
        int j, k, w;
        scanf("%d %d %d", &j, &k, &w);
        adjList[j].push_back(make_pair(w, k));
        adjList[k].push_back(make_pair(w, j));
    }


    ll ans = K_heap(adjList, V, s, e);

    printf("%d\n", ans);

    return 0;   

}


// //Test Heap
// int main() {

//     int n = 20;
//     srand(23);

//     for(int i = 0; i < n; i++)  {
//         int k = rand() % 31;
//         enqueue(pq,  make_pair(k, 0));
//         printf("%d ", k);
//     }

//     printf("\n");

//     for(int i = 0; i < n; i++)  {
//         pi k = getMin(pq);
//         printf("%d ", k.first);
//     }

// }
