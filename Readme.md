

    In the current directory there are 5 algorithms implemented for finding the shortest path from a source node
to all the other vertices in a graph, together with a program to run all the tests for each specific algorithm.

    The generator creates the windows powershell command to run the tests in the current directory.
    Bellman-Ford algorithms run all the tests, Dijkstras don't run the first 6 tests, and Dial only runs
the tests from 7 to 12.

    Dijkstra uses a priority queue with a comparator comparing by the second parameter(which is the cost). The graph is
declared using adjency matrices. After reading the graph, we first initialise the cost of each node to infinite, then we
initialise the cost of the neighbors of the source node and we insert them in the priority queue. We set the cost of the source node as 0 and we mark it as visited. Then, while the pq still has nodes in it, we obtain the first element from the pq, check if it has already been visited and if it isn't, we check if a new path can be created through this node to obtain a smaller cost to a neighbor. If it could, we add the next node in the priority queue and we repeat the process. At the end, we print the distances.
    Dijkstra without priority queue is almost the same, but instead of using the priority queue to always find the smallest node
in the graph, we iterate through them to find it, resulting in a bigger time complexity.

    Bellman-Ford algorithm without queue stores each node of the graph in a vector of touples with the format (start_node,
    end_node, weight). Then, "vertices" times, it tries to relax the path to all nodes. At each step "k", we obtain the path with
the distance "k". If at any given "k" step, the paths aren;t relaxed, the algorithm stops. If there are still paths that can be relaxed after the algorithm ends, it means that a cycle can be found, which is obviously a negative cycle that is detected.
    Bellman-Ford with a queue is rather similar to Dijkstra than the classic Bellman-Ford, but it used a queue instead of a priority queue. After initializations, while the queue still has elements in it, it removes the top, marks it as not in the queue and tries to relax it's neighbors. IF the relaxed neighbor is not in the queue, it adds it, otherwise it doesn't. The algorithm stops either after finding a negative cycle, or when the queue is empty(the smallest paths are found)

    Dial's algorithm uses buckets to store nodes at a given time. Each bucket's value represents a cost. The biggest cost of a bucket is equal to the biggest weight of a edge times the number of nodes in the graph(maximum path distance).
    First, we add the neighbors of the source in the buckets of the distance from the source to them. Then, we iterate through all the buckets from the start to end. For each bucket, we pull out every node, and if the node has not been labeled, we label it and we try to find better path to its neighbors. The algorithm is very efficient for small costs.

    Dial and Dijkstra don't work properly with negative costs.