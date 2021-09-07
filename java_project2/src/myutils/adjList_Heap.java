package myutils;

import java.util.*;


public class adjList_Heap {

    public static final int MAXN = 10003;

    private static class Edge {
        int to;
        int weight;

        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    public static class Dist implements Comparable<Dist> {
        int distance;
        int vertex;

        public Dist(int d, int v) {
            distance = d;
            vertex = v;
        }

        public int compareTo(Dist d2) {
            return this.distance - d2.distance;
        }
    }



    private static class Heap {
        Dist[] H;
        int size;

        public Heap() {
            H = new Dist[MAXN * MAXN];
            H[0] = null;
            size = 0;
        }

        public void insert(Dist k) {
            int j = size++, pj = j / 2;
            while(pj >= 1) {
                if(k.compareTo(H[pj]) >= 0) break;
                else {
                    H[j] = H[pj];
                    j = pj;
                    pj = j / 2;
                }
            }
            H[j] = k;
        }

        public Dist getMin() {

            if(size <= 0) return null;

            Dist tmp = H[1];
            Dist k = H[size--];
            int j = 1, cj = 2;
            while(cj <= size) {
                if(cj < size && H[cj].compareTo(H[cj + 1]) > 0) cj++; //get the smaller child
                if(k.compareTo(H[cj]) <= 0) break;
                H[j] = H[cj];
                j = cj;
                cj = 2 * j;
            }
            H[j] = k;
            return tmp;
        }

        public boolean isEmpty() {
            return size <= 0;
        }
    }

    LinkedList<LinkedList<Edge>> adjL;
    int V, E;
    int[] shortestDistance;
    Heap pq;


    public adjList_Heap(int V, int E, int[] start, int[] end, int[] weight) {
        adjL = new LinkedList<>();
        this.V = V;
        this.E = E;

        pq = new Heap();
        //creating the adjacency List
        for(int i = 0; i < V; i++) {
            adjL.addLast(new LinkedList<Edge>());
        }
        for(int i = 0; i < E; i++) {
            adjL.get(start[i]).add(new Edge(end[i], weight[i]));
        }
    }

    public int solve(int s, int e) {
        shortestDistance = new int[MAXN];

        for(int i = 0; i < V; i++) { //clear shortest distance
            shortestDistance[i] = -1;
        }

        shortestDistance[s] = 0;

        for(Edge edge: adjL.get(s)) {
            pq.insert(new Dist(edge.weight, edge.to));
        }

        while(shortestDistance[e] < 0 && !pq.isEmpty()) {
            Dist d = pq.getMin();
            assert d != null;
            int dist = d.distance;
            int vertex = d.vertex;

            if(shortestDistance[vertex] >= 0) continue;

            shortestDistance[vertex] = dist;
            for(Edge edge: adjL.get(vertex)) {
                if(shortestDistance[edge.to] < 0)
                    pq.insert(new Dist(edge.weight + dist, edge.to));
            }
        }

        return shortestDistance[e];
    }

    public static void main(String args[]) {
        int V = 4;
        int E = 5;

        int[] start = {0, 0, 1, 1, 2};
        int[] end   = {1, 2, 2, 3, 3};
        int[] weight ={2, 6, 5, 3, 4};

        adjList_Heap LH = new adjList_Heap(V, E, start, end, weight);
        System.out.println(LH.solve(0, 3));
    }

}
