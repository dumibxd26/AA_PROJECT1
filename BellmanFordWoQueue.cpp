// Copyright Bogdan Dumitrescu 322CA

#include <fstream>
#include <vector>
#include <tuple>
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("test2.in");
ofstream g("test.out");

int main(void)
{
    vector<tuple<int,int,long long>> edges;
    vector<long long> cost;

    int vertices, edges_nr, source;

    f >> vertices >> edges_nr >> source;

    int start_node, end_node;
    long long weight;

    // Read all the edges from the input
    for(int i = 0; i < edges_nr; i++) {
        f >> start_node >> end_node >> weight;
        edges.push_back(make_tuple(start_node, end_node , weight));
    }

    cost.resize(edges_nr);
    for(int i = 0; i < edges_nr; i++) {
        cost[i] = INF;
    }

    cost[source] = 0;

    // After each step(distance from the source) we check if we can improve the cost of the nodes
    int i;
    for(i = 0; i < vertices; i++) {

        int changed = 0;
        
        // Edge relaxation
        for(int j = 0; j < edges_nr; j++) {
            int start_node = get<0>(edges[j]);
            int end_node = get<1>(edges[j]);
            long long weight = get<2>(edges[j]);

            if (cost[start_node] != INF && cost[start_node] + weight < cost[end_node]) {
                cost[end_node] = cost[start_node] + weight;
                changed = 1;
            }
        }

        // If we didn't improve the cost of any node, we can stop the algorithm
        if (!changed) {
            break;
        }
    }

    if (i == vertices) {
        g << "Negative cycle detected!";
        return 0;
    }

    // // Check if there is a negative cycle
    // for(int i = 0; i < edges_nr;  i++) {
    //     int start_node = get<0>(edges[i]);
    //     int end_node = get<1>(edges[i]);
    //     int weight = get<2>(edges[i]);

    //     if (cost[start_node] != INF && cost[start_node] + weight < cost[end_node]) {
    //         g << "Negative cycle detected!";
    //         return 0;
    //     }
    // }

    for(int i = 0; i < vertices; i++) {
        if (cost[i] == INF) {
            g << "NaN" << " ";
        } else {
            g << cost[i] << " ";
        }
    }

    f.close();
    g.close();
    return 0;   
}
