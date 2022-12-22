#include <fstream>
#include <random>
#include <cstring>
#include <time.h>
#include <map>
#include <set>

using namespace std;


void generateGraph(int argc, char const *argv[]) {
    
    ofstream g(argv[1]);

    map<int,int> nodes_used;
    set<pair<int,int>> duplicates;

    int vertices_max = 100000;
    int end_cost = 100000;
    int edges_max = 250000;

    if (argc > 2) {
        if (strcmp(argv[2], "BF") == 0){
            edges_max = 500000;
        }
        if (strcmp(argv[2], "Dial") == 0) {
            end_cost = 5;
            vertices_max = 10000;
        }
    }

    int vertices_number = rand() % vertices_max + 1;

    if (argc > 3) {
        if (strcmp(argv[3], "rare") == 0) {
            edges_max = vertices_number * 2;
        } else if (strcmp(argv[3], "dense") == 0) {
            edges_max = vertices_number * 20;

            if (edges_max > 500000) {
                edges_max = 500000;
            }
        }
    }

    int edges_number = rand() % edges_max + 1;

    int source = rand() % vertices_number;

    if (!(argc > 2 && strcmp(argv[2], "BF") == 0)) 
        edges_number *= 2;

    g << vertices_number << " " << edges_number << " " << source << endl;

    int counter = 0;
    nodes_used[0] = source;
    
    for(int i = 0; i < edges_number; i++) {
        
        int destination = rand() % vertices_number;

        int next_node;
        if(counter == 0 || counter == 1) {
            next_node = 0;
        } else {
            next_node = rand() % (counter + 1);
        }

        if (nodes_used[next_node] == destination || duplicates.find({nodes_used[next_node], destination}) != duplicates.end()) {
            i--;
            continue;
        }

        duplicates.insert({nodes_used[next_node], destination});

        int cost = rand() % end_cost;

        // other ways of implementing the BF case resulted in eronated graphs
        // used %5 to have a smaller chance of having negative costs
        // not to get negative cycles
        if (argc > 2 && strcmp(argv[2], "BF") == 0) {
            int sign = rand() % 5;
            if (sign == 0) {
                cost = -cost;
            }

            int direction = rand() % 2;

            if(direction == 0) {
                g << nodes_used[next_node] << " " << destination << " " << cost << endl;
            } else {
                g << destination << " " << nodes_used[next_node] << " " << cost << endl;
            }
        } else {
            // undirected
            g << nodes_used[next_node] << " " << destination << " " << cost << endl;
            g << destination << " " << nodes_used[next_node] << " " << cost << endl;
            i++;
        }

        counter++;
        nodes_used[counter] = destination;

    }

    g.close();
}

int main(int argc, char const *argv[]) {

    srand((unsigned) time(NULL));

    generateGraph(argc, argv);

    return 0;
}