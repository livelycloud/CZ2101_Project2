### Weight 10k, repeat 100

*factors to consider: |V|, |E|, weight*

### Hypothesis
Adj_matrix -> O(V^2)
List with priority queue -> O(ElogV)

Connected graph with extra edges, ratio of time_mat to time_list = 0.5-0.7
Time: 0.4, 0.3

Connected graph with no extra edges, ratio 0.5-0.9
time: 0.3, 0.16

When edges is n-1, the ratio is 10 (list faster than mat)