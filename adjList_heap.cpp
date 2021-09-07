#include <bits/stdc++.h>
using namespace std;


#define MAXN 1003


//use heap for priority queue, enque O(logn), getMin O(log n)

typedef long long ll;

typedef pair<ll, int> pi; //pi.first is the distance to  node pi.second


typedef struct _listnode
{
	int to;
    int w;
	struct _listnode *next;
} ListNode;			

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	

ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value, int w);

ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value, int w){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = (*ListNode) malloc(sizeof(ListNode));
		ll->head->to = value;
        ll->head->w = w;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = (*ListNode) malloc(sizeof(ListNode));
		pre->next->to = value;
        ll->head->w = w;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

void add(LinkedList *ll, int to, int w) {
    insertNode(ll, ll->size, to, w);
}

LinkedList adjL[MAXN];

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
    int j = pq_size++, pj = j / 2;
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
ll K_heap(LinkedList adjL[], int V, int s, int e) 
{
    //initialise pq
    pq_size = 0;
    memset(dis, -1, sizeof(ll) * V);

    ListNode* cur = adjL[s].head;

    while(cur != NULL) {
        enqueue(pq, make_pair(cur->w, cur->to));
        cur = cur->next;
    }

    dis[s] = 0;

    while(dis[e] < 0 && pq_size > 0) {
        pi cur = getMin(pq);
        ll w = cur.first;
        int node = cur.second;
        dis[node] = w;
        ListNode* curNode = adjL[node].head;
        while( curNode != NULL) {
            if(dis[curNode->to] < 0)
                enqueue(pq, make_pair(curNode->w + w, curNode->to));
            curNode = curNode->next;
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
        add(&(adjL[j]), k, w);
    }


    ll ans = K_heap(adjL, V, s, e);

    printf("%d\n", ans);

    return 0;   

}



