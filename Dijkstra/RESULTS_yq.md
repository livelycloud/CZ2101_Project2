### To implement
1. allow disconnected graph (hyp: D_list will outrun D_mat)
2. add for loop for value of E
3. analyse why is O(ElogV)
4. understand binary heap

### Graph
- fix V=256, V = 1024
- E = 0, E = V-1, E = V(V-1)/2


### Changing factors
- value of V 
- value of E
- value of weight
- number of repetitions

### Hypothesis
Adj_matrix -> O(V^2)
List with priority queue -> O(ElogV)

> Dijkstra's algo with adjacency list and priority queue (D_list), dijkstra's algo with adjacency matrix and array (D_mat)

1. D_list will be slower than D_mat when E is big

2. Around the same when 40 < V < 100

3. When E is maintained at V-1, D_list always outperforms D_mat (when V > 100?)





### Average case
- when the number of edges are between n-1 and n(n-1)/2
- D_list performs slower after V>200

[Complexity graph](https://www.geogebra.org/calculator/b2kcb4nf)

### Observation

When edges is n-1, the ratio is 10 (list faster than mat)

