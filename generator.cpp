#include <fstream>
#include <random>
#include <cstring>
#include <time.h>
#include <map>

using namespace std;

ofstream g("test4.in");

void generateGraph(int argc, char const *argv[]) {
    map<int,int> nodes_used;

    int start_cost = 1;
    int end_cost = 100000;
    int edges_max = 500000;

    if (argc > 1) {
        if (strcmp(argv[1], "BF") == 0){
            start_cost = -100000;
        } else if (strcmp(argv[1], "Dial") == 0) {
            end_cost = 50;
        }
    }

    int vertices_number = rand() % 100000 + 1;

    if (argc > 2) {
        if (strcmp(argv[2], "rare") == 0) {
            edges_max = vertices_number * 2;
        } else if (strcmp(argv[2], "dense") == 0) {
            edges_max = vertices_number * 20;

            if (edges_max > 500000) {
                edges_max = 500000;
            }
        }
    }

    int edges_number = rand() % edges_max + 1;

    int source = rand() % vertices_number + 1;

    g << vertices_number << " " << edges_number << " " << source << endl;

    int counter = 0;
    nodes_used[0] = source;
    
    for(int i = 0; i < edges_number; i++) {
        
        int destination = rand() % vertices_number + 1;

        int next_node;
        if(counter == 0 || counter == 1) {
            next_node = 0;
        } else {
            next_node = rand() % (counter + 1);
        }

        int cost = rand() % (end_cost - start_cost + 1) + start_cost;
        int direction = rand() % 2;

        if(direction == 0) {
            g << nodes_used[next_node] << " " << destination << " " << cost << endl;
        } else {
            g << destination << " " << nodes_used[next_node] << " " << cost << endl;
        }

        counter++;
        nodes_used[counter] = destination;

    }
}

int main(int argc, char const *argv[]) {

    srand((unsigned) time(NULL));
    g << rand() % 50 << endl;

    generateGraph(argc, argv);

    g.close();
    return 0;
}