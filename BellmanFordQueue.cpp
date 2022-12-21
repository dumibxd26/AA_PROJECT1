#include <fstream>
#include <queue>
#include <vector>
#include <tuple>
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("test2.in");
ofstream g("test.out");

int main(void) {

    vector<vector<pair<int,int>>> graph;
    queue<int> current_nodes;
    vector<bool> in_queue;
    vector<long long> cost;

    int vertices, edges_nr, source;

    f >> vertices >> edges_nr >> source;

    cost.resize(vertices);
    in_queue.resize(vertices);
    graph.resize(vertices);

    int start_node, end_node;
    long long weight;

    // initialise the graph
    for(int i = 0; i < edges_nr; i++) {
        f >> start_node >> end_node >> weight;
        graph[start_node].push_back({end_node, weight});
    }

    for(int i = 0; i < vertices; i++) {
        cost[i] = INF;
    }

    cost[source] = 0;
    current_nodes.push(source);
    in_queue[source] = true;
    int iterations = 0;

    // Push the source into the queue and start the algorithm
    while(!current_nodes.empty()) {
        int current_node = current_nodes.front();
        current_nodes.pop();
        in_queue[current_node] = false;

        // if the neighbor neighbor's cost cand be improved
        // change the cost 
        // if the neighbor is not in the queue, push it
        for (int i = 0; i < graph[current_node].size(); i++) {
            int next_node = graph[current_node][i].first;
            long long weight = graph[current_node][i].second;

            if (cost[current_node] != INF && cost[current_node] + weight < cost[next_node]) {
                cost[next_node] = cost[current_node] + weight;

                if (!in_queue[next_node]) {
                    current_nodes.push(next_node);
                    in_queue[next_node] = true;
                }
            }
        }

        iterations++;
        // Worst possible case for detecting a negative cycle is O(V * E)
        // Other options are just assumptions which are not really valid
        // But there can also be other implementations where you can literally
        // detect the cycle, but its complexity is debatable.
        if (iterations >= vertices * edges_nr) {
            g << "Ciclu negativ";
            return 0;
        }
    }

    for (int i = 0; i < vertices; i++) {
        if (cost[i] == INF) {
            g << -1 << " ";
        } else {
            g << cost[i] << " ";
        }
    }

    f.close();
    g.close();
    return 0;
}
