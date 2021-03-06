#include <bits/stdc++.h>
using namespace std;


#define MAXN 1003
#define POS_INF 1152921504606846976


//use heap for priority queue, enque O(logn), getMin O(log n)

typedef long long ll;

typedef pair<ll, int> pi; //pi.first is the distance to  node pi.second

vector<pi> adjList[MAXN];

int V2pq[MAXN]; //record the index in pq of node i

pi H[MAXN + 3]; //priority queue with heap, the first element is at pq[1]

int pq_size;

ll dis[MAXN];
bool visited[MAXN];

int V, E;

void initializePriorityQueue() {
    for(int i = 0; i < V; i++) {
        V2pq[i] = i + 1;
        H[i+1] = make_pair(POS_INF, i);
    }
    pq_size = V;
}

void shiftDown(pi k) { //O(logn) k.first is distance; k.second is the current node
    int Size = pq_size;
    int j = 1, cj = 2; //cj index of child of j
    while(cj <= Size) {
        if(cj < Size && H[cj] > H[cj + 1]) cj++; //get the smaller child
        if(k <= H[cj]) break;

        //move child of j to j pos, and change current index to cj
        V2pq[H[cj].second] = j; //update the index of cj to j
        H[j] = H[cj];
        j = cj;
        cj = 2 * j;
    }
    H[j] = k;
    V2pq[k.second] = j;
}

void shiftUp(pi k) { //O(logn)
    int j = V2pq[k.second], pj = j / 2;
    while(pj >= 1) { //parent of j is within bound
        if(k >= H[pj]) break; //if k is larger than its parent, stop
        else {
            // move pj to j
            V2pq[H[pj].second] = j;
            H[j] = H[pj];
            j = pj;
            pj = j / 2;
        }
    }
    H[j] = k;
    V2pq[k.second] = j;
}

void update(pi k) {
    int indexInpq = V2pq[k.second];
    if(H[indexInpq] <= k) return;
    else H[indexInpq] = k;
    shiftUp(k);
}   

pi getMin() {
    pi tmp = H[1];
    shiftDown(H[pq_size--]);
    return tmp;
}

//find shortest distance from s to e
//V: number of nodes
ll K_heap(vector<pi> adjList[], int V, int s, int e) 
{
    //initialise pq
    pq_size = 0;
    memset(dis, -1, sizeof(ll) * V);
    initializePriorityQueue();

    update(make_pair(0, s));

    while(dis[e] < 0 && pq_size > 0) {
        pi cur = getMin();
        ll w = cur.first;
        int node = cur.second;
        if(dis[node] == -1) {
            dis[node] = w;
            visited[node] = true;
            for(int i = 0; i < adjList[node].size(); i++) {
                if(!visited[adjList[node][i].second])
                    update(make_pair(adjList[node][i].first + w, adjList[node][i].second));
            }
        }
    }

    return dis[e];

}

int main() {
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


//Test Heap
// int main() {

//     int n = 10;
//     srand(5);
//     V = n;
//     initializePriorityQueue();

//     for(int i = 0; i < n; i++)  {
//         int k = rand() % 31;
//         update(make_pair(k, i));
//         printf("%d ", k);
//     }

//     printf("\n");

//     for(int i = 0; i < n; i++)  {
//         pi k = getMin();
//         printf("%d %d \n", k.first, k.second);
//     }

// }
