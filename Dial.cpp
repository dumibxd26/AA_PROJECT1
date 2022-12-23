#include <fstream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int main(int argc, char *argv[]) {

    ifstream f(argv[1]);
    ofstream g(argv[2]);

    vector <vector<pair<int,long long>>> graph;
    vector<vector<int>> buckets;
    vector<long long> cost;

    int vertices, edges , source;
    long long biggest_cost = -INF;

    f >> vertices >> edges >> source;

    graph.resize(vertices + 1);
    cost.resize(vertices + 1);

    int start_node, end_node;
    long long weight;

    for(int i = 0; i < edges; i++) {

        f >> start_node >> end_node >> weight;

        graph[start_node].push_back({end_node, weight});

        if (weight > biggest_cost) {
            biggest_cost = weight;
        }
    }

    for (int i = 0; i < vertices; i++) {
        cost[i] = INF;
    }
    
    buckets.resize(biggest_cost * vertices + 1);

    // add the neighbors of the source to the buckets
    for(int i = 0; i < graph[source].size(); i++) {
        int next_node = graph[source][i].first;
        long long weight = graph[source][i].second;

        cost[next_node] = weight;
        
        buckets[weight].push_back(next_node);
    }

    cost[source] = 0;

    // Iterate over all the buckets and for each bucket, 
    // update the cost of the neighbors of the nodes in the bucket
    for(int bucket = 0; bucket < biggest_cost * vertices; bucket++) {
        for(int i = 0; i < buckets[bucket].size(); i++) {
            int current_node = buckets[bucket][i];

            for(int j = 0; j < graph[current_node].size(); j++) {
                int next_node = graph[current_node][j].first;
                long long weight = graph[current_node][j].second;

                if (cost[current_node] + weight < cost[next_node]) {
                    cost[next_node] = cost[current_node] + weight;
                    buckets[cost[next_node]].push_back(next_node);
                }
            }
        }
       buckets[bucket].clear();
    }

    for(int i = 0; i < vertices; i++)
        if (cost[i] > biggest_cost * vertices)
            g << "NaN" << " ";
        else
            g << cost[i] << " ";

    f.close();
    g.close();
    return 0;
}
