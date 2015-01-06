#include <bits/stdc++.h>

using namespace std;

/* Find if there is a path between two vertices in a directed graph */


/* This class represents a directed graph using adjacency list representation. */
class Graph {
    int V;              /* Number of vertices */
    list<int> *adj;     /* Pointer to array containing adjacency lists */

    public:
        Graph(int V);               /* Constructor */
        void addEdge(int v, int w); /* Function to add an edge to graph */
        bool is_path(int s, int d); /* Returns true if there is a path from s to d */
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); /* Add w to v list. */
}

/* A BFS based function to check whether d is reachable from s. */
bool Graph::is_path(int s, int d) {
    if(s == d) return true;

    /* Mark all the vertices as not visited */
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++) visited[i] = false;

    list<int> queue; /* Create a queue for BFS */

    /* Mark the current node as visited and enqueue it */
    visited[s] = true;
    queue.push_back(s);

    list<int>::iterator i; /* It will be used to get all adjacent vertices of a vertex */

    while(!queue.empty()) {
        /* Dequeue a vertex from queue and print it */
        s = queue.front();
        queue.pop_front();
        printf("%d ", s);

        /*  Get all adjacent vertices of the dequeued vertex s.
            If a adjacent has not been visited, then mark it visited and enqueue it. */

        for(i = adj[s].begin(); i != adj[s].end(); ++i) {
            /*  If this adjacent node is the destination node, then return true.
                Else, continue to do BFS. */

            if(*i == d) {
                printf("%d - ", d);
                return true;
            }

            if(!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }

    return false;
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    int u = 1, v = 3;
    if(g.is_path(u, v)) printf("There is a path from %d to %d.\n", u, v);
    else printf("There is no path from %d to %d.\n", u, v);

    u = 3, v = 1;
    if(g.is_path(u, v)) printf("There is a path from %d to %d.\n", u, v);
    else printf("There is no path from %d to %d.\n", u, v);

    return 0;
}
