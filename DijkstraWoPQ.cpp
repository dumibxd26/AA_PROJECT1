#include <fstream>
#include <vector>
#include <set>
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("input.txt");
ofstream g("output.txt");

int main(void) {

    vector <vector<pair<int,int>>> graph;
    vector<int> cost;
    vector<bool> visited;

    int vertices, edges , source;
    f >> vertices >> edges >> source;

    graph.resize(vertices);
    cost.resize(vertices);
    visited.resize(vertices);
    int start_node, end_node, weight;

     // initialise the graph
    for(int i = 0; i < edges; i++) {
        
        f >> start_node >> end_node >> weight;

        // If the graph is undirected, the tests must include both directions of the edge
        graph[start_node].push_back({end_node, weight});
    }

    // initialise all distances to infinity
    for(int i = 0; i < vertices; i++) {
        cost[i] = INF;
    }

    // set the cost of the neighbors of the source
    for(int i = 0; i < graph[source].size(); i++) {
        int next_node = graph[source][i].first;
        int weight = graph[source][i].second;
        
        cost[next_node] = weight;
    }

    cost[source] = 0;
    visited[source] = true;

    // vertices - 1 steps because all the nodes but the source
    // must be visited at a time => so * (vertices - 1) operations
    for(int step = 0; step < vertices - 1; step++) {
        
        int min_distance =  INF;
        int current_node = -1;
    
    // Find the node with the smallest distance yet
        for(int i = 0; i < vertices; i++) {
            if (!visited[i] && cost[i] <= min_distance) {
                min_distance = cost[i];
                current_node = i;
            }
        }

        visited[current_node] = true;
        
    // Update the cost of the neighbors of the current node
        for(int i = 0; i < graph[current_node].size(); i++) {
            int next_node = graph[current_node][i].first;
            int weight = graph[current_node][i].second;

            if (!visited[next_node] && cost[current_node] + weight < cost[next_node]) {
                cost[next_node] = cost[current_node] + weight;
            }
        }
    }

    for(int i = 0; i < vertices; i++) {
        if (visited[i]) {
            g << cost[i] << " ";
        } else {
            g << "NaN";
        }
    }

    return 0;
}
