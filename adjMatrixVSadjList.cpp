#include <bits/stdc++.h>
#include<sys/time.h>
using namespace std;

//assume all path weight are integer values, and the total length will not exceed long long 
//use array for priority queue, insert O(n) (insertion sort/bubble from the end of the queue), getMin O(1);

#define MAXN 2021
#define POS_INF 1152921504606846976

typedef long long ll;

typedef pair<ll, int> pi; //pi.first is the distance to  node pi.second

//adjMatrix + array
int adjM[MAXN][MAXN]; //adjacency matrix adjM[i][j] means the weight of a path from i to j
bool visited[MAXN]; //indicate if the shortest distance to node i is found;
ll dis[MAXN]; //record the distances of nodes
int V, E;


int getMinM() { //return the index of the unvisited node with the shortest distance
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
ll dijkstraMatrix(int s, int e) 
{
    //initialise
    memset(visited, false, V);
    memset(dis, POS_INF, sizeof(ll) * V); //initialization O(V)


    dis[s] = 0;
    int numOfRounds = 0;

    //!visited[e] &&
    while(numOfRounds < V) { //
        numOfRounds++; //need to complete V - 1 Rounds
        int node = getMinM(); //get  the index of the unvisited node with the shortest distance

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






// adjList + Heap
vector<pi> adjList[MAXN];

int V2pq[MAXN]; //record the index in pq of node i

pi H[MAXN + 3]; //priority queue with heap, the first element is at H[1] (left child 2i, right child 2i+1)

int pq_size;

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

void update(pi k) { //inside heap
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
ll dijkstraList(int s, int e) 
{
    //initialise pq
    pq_size = 0;

    //here use distance used to record final distance
    //if == -1, means the shortest distance has not been found
    memset(dis, -1, sizeof(ll) * V); 
    memset(visited, false, V);
    initializePriorityQueue();

    update(make_pair(0, s));


    // (dis[e] < 0 &&
    while (pq_size > 0) {
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

    timeval begin, end;
    ofstream outFile;

    srand(2055);

    outFile.open("Application4_without_earlystopping.csv");

    outFile<<"numOfTest"<<","<<"numOfNode"<<","<<"averageTime(Matrix)"<<","<<"averageTime(List)"<<endl;
    
    int numOfTests = 100;
    
    int numOfNodes = 100;

    int start = 0, last = 1000, step = 10;

    for(int numOfNodes = start; numOfNodes <= last; numOfNodes += step) {
        
        int averageTime1 = 0;
        int averageTime2 = 0;
        V = numOfNodes;
        
        

        for(int epoch = 0; epoch < numOfTests; epoch++) {

            E = 0;
            for(int i = 0; i < V; i++){
                adjList[i].clear();
                memset(adjM[i], 0, sizeof(int) * V);
            }


            // Application1.csv
            //generate test case for real life application (only places close to each other have a diret path (edge))
            // total edge about 10V
            for(int i = 0; i < V; i++) {
                for(int j = i; j < i + 10 && j < V; j++) {
                    int w = rand() % 11 + 1;
                    adjM[i][j] = w;
                    adjM[j][i] = w;

                    adjList[i].push_back(make_pair(w, j));
                    adjList[j].push_back(make_pair(w, i));
                    E++;
                }
            }



            //Application2 & application 3 (with high way)
            //generate test case for real life application (2D, only places close to each other have a direct path)
            //(i, j) connect to (i, j +- 1), (i, j +- 2)，(i +- 1, j), (i +- 2, j)   +-5 along i, +-5 along j; total 20; 
            //total edge about 10V

            //Map[width][width] //Map[i][j]: node index = V * i + j
            // int width = sqrt(numOfNodes);
            // for(int i = 0; i < width; i++) {
            //     for(int j = 0; j < width; j++) {
            //         for(int k = j + 1; k <= j + 5; k++) { //(i, j) to (i, k)
            //             int v = i * width + j;
            //             int u = i * width + k;

            //             int w = rand() % 11 + 1;
            //             adjM[v][u] = w;
            //             adjM[u][v] = w;

            //             adjList[u].push_back(make_pair(w, v));
            //             adjList[v].push_back(make_pair(w, u));
            //             E++;
            //         }

            //         for(int k = i + 1; k <= i + 5; k++) { //(i, j) to (k, j)
            //             int v = i * width + j;
            //             int u = k * width + j;

            //             int w = rand() % 11 + 1;
            //             adjM[v][u] = w;
            //             adjM[u][v] = w;

            //             adjList[u].push_back(make_pair(w, v));
            //             adjList[v].push_back(make_pair(w, u));
            //             E++;
            //         }



            //     }
            // }


            // //ap3
            // //add high way for application 3
            // for(int i = 0; i < width; i++) {
            //     int v = i;
            //     int u = (width - 1) * width + i;
            //     if(adjM[v][u] == 0) {
            //         int w = rand() % 11 + 1;
            //         adjM[v][u] = w;
            //         adjM[u][v] = w;

            //         adjList[u].push_back(make_pair(w, v));
            //         adjList[v].push_back(make_pair(w, u));
            //         E++;
            //     }
            // }


            int uu, vv;
            //ap4
            if(V != 0){
                uu = rand() % V;
                vv = rand() % V;
            } else {
                uu = vv = 0;
            }
            gettimeofday(&begin, NULL);

            // //ap1
            // int matrixAns = dijkstraMatrix(0, V - 1);

            //ap2
            // int matrixAns = dijkstraMatrix(0, width * width - 1);



            int matrixAns = dijkstraMatrix(vv, uu);

            gettimeofday(&end, NULL);

            int sec = end.tv_sec - begin.tv_sec; //second
            int usec = end.tv_usec - begin.tv_usec; //microsecond
            int t1 = sec * 1000000 + usec;
            // printf("time used: %.2fms\n", t);
            averageTime1 += t1;



            gettimeofday(&begin, NULL);

            // //ap1
            // int listAns = dijkstraList(0, V - 1);

            //ap2
            // int listAns = dijkstraList(0, width * width - 1);

            //ap4
            int listAns = dijkstraList(vv, uu);

            gettimeofday(&end, NULL);

            sec = end.tv_sec - begin.tv_sec; //second
            usec = end.tv_usec - begin.tv_usec; //microsecond
            int t2 = sec * 1000000 + usec;
            // printf("time used: %.2fms\n", t);
            averageTime2 += t2;
            // printf("Epoch %d, Matrix ans: %d, Time %dms; List ans: %d, Time %dms.\n", epoch, matrixAns, t1, listAns, t2);
        }
        averageTime1 /= numOfTests;
        averageTime2 /= numOfTests;
        printf("Number of Nodes: %d \tMatrix TIme: %dms \tList Time %dms\n", numOfNodes, averageTime1, averageTime2);
        outFile<<numOfTests<<","<<numOfNodes<<","<<averageTime1<<","<< averageTime2<<endl;
    }

}