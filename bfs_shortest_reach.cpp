#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Graph {
	vector< vector<bool> > matrix_graph;
	int number_nodes;
	queue<int> start_nodes;
	queue<int> current_distance;
	vector<int> shortest_reach_arr;
	vector<int> visited_nodes;
	
    public:
        Graph(int n) {
        	for (int i = 0; i < n; i++) {
        		vector<bool> temp_column;
        		for (int j = 0; j < n; j++) {
        			temp_column.push_back(0);
        		}
        		matrix_graph.push_back(temp_column);
        		shortest_reach_arr.push_back(-1);
        		visited_nodes.push_back(0);
        	}
        	number_nodes = n;
        }
    
        void add_edge(int u, int v) {
        	if (u != v) {
        		matrix_graph[u][v] = 1;
        		matrix_graph[v][u] = 1;
        	}
        }
    
        vector<int> shortest_reach(int start) {
        	find_shortest_reach(start, 6);
           
           return shortest_reach_arr;
        }
        
        void find_shortest_reach(int start, int distance) {
        	
        	for (int i = 0; i < number_nodes; i++) {
            	if ((matrix_graph[start][i] || matrix_graph[i][start]) && !visited_nodes[i]) {
            		matrix_graph[start][i] = 0;
            		matrix_graph[i][start] = 0;
            		visited_nodes[i] = 1;
            		start_nodes.push(i + 1);
            		current_distance.push(distance + 6);
            		shortest_reach_arr[i] = distance;
            	}
            }
            
           while (!start_nodes.empty()) {
           		int temp_start_nodes = start_nodes.front();
           		start_nodes.pop();
           		int temp_current_distance = current_distance.front();
           		current_distance.pop();
           		find_shortest_reach(temp_start_nodes - 1, temp_current_distance);
           }
        }
    
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
      int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
      int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
