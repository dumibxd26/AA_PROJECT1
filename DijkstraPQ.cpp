#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("input.txt");
ofstream g("output.txt");

auto cmp = [] (pair<int,int> x, pair<int,int> y)
{
    return x.second > y.second;
};

int main(void)
{
    priority_queue <pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
    vector <vector<pair<int,int>>> graph;
    vector<int> cost;
    vector<bool> visited;

    int vertices, edges , source;

    f >> vertices >> edges >> source;

    graph.resize(vertices);
    cost.resize(vertices);
    visited.resize(vertices);

    // initialise the graph
    for(int i = 0; i < edges; i++) {
        int start_node, end_node, weight;
        f >> start_node >> end_node >> weight;

        // If the graph is undirected, the tests must include both directions of the edge
        graph[start_node].push_back({end_node, weight});
    }

    // inisialise all distances to infinity
    for(int i = 0; i < vertices; i++) {
        cost[i] = INF;
    }

    // initialise the priority queue with the distance from the first node to its neighbors
    for(int i = 0; i < graph[source].size(); i++) {
        int next_node = graph[source][i].first;
        int weight = graph[source][i].second;
        
        cost[next_node] = weight;
        pq.push({next_node, weight});
    }

    cost[source] = 0;
    visited[source] = true;

    while(!pq.empty()) {
        // get the node with the smallest distance yet(top of the priority queue)
        int current_node = pq.top().first;
        int weight = pq.top().second;
        pq.pop();

        // if it was already visited, skip it
        if (visited[current_node]) {
            continue;
        }

        visited[current_node] = true;

        // update the distances to the neighbors of the current node
        for(int i = 0; i < graph[current_node].size(); i++) {
            int next_node = graph[current_node][i].first;
            int weight = graph[current_node][i].second;

            if (cost[next_node] > cost[current_node] + weight) {
                cost[next_node] = cost[current_node] + weight;
                pq.push({next_node, cost[next_node]});
            }
        }
    }

    for(int i = 0; i < vertices; i++) {
        if (visited[i]) {
            g << cost[i] << " ";
        } else {
            g << "NaN" << " ";
        }
    }

    return 0;
}
