#include <bits/stdc++.h>
#define NINF INT_MIN

using namespace std;

/*  Given a Weighted Directed Acyclic Graph (DAG) and a source vertex s in it,
    find the longest distances from s to all other vertices in the given graph. */

class AdjListNode {
    int v;
    int weight;

    public:
        AdjListNode(int _v, int _w) {
            v = _v;
            weight = _w;
        }

        int getV() { return v; }
        int getWeight() { return weight; }
};

/* This class represents a directed graph using adjacency list representation. */
class Graph {
    int V;                      /* Number of vertices */
    list<AdjListNode> *adj;     /* Pointer to array containing adjacency lists */
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

    public:
        Graph(int V);               /* Constructor */
        void addEdge(int u, int v, int weight); /* Function to add an edge to graph */
        void longestPath(int s); /* Finds longest distances from given source vertex */
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight) {
    AdjListNode node(v, weight);
    adj[u].push_back(node);
}

/* A recursive function used by longest path */
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) {
    /* Mark the current node as visited */
    visited[v] = true;

    /* Recur for all the vertices adjacent to this vertex */
    list<AdjListNode>::iterator i;

    for(i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if(!visited[node.getV()]) topologicalSortUtil(node.getV(), visited, Stack);
    }

    /* Push current vertex to stack which stores topological sort */
    Stack.push(v);
}

/*  The function to find longest distances from a given vertex. It uses
    recursive topologicalSortUtil() to get topological sorting. */
void Graph::longestPath(int s) {
    stack<int> Stack;
    int dist[V];

    /* Mark all the vertices as not visited */
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++) visited[i] = false;

    /*  Call the recursive helper function to store Topological Sort
        starting from all vertices one by one */
    for(int i = 0; i < V; i++)
        if(visited[i] == false) topologicalSortUtil(i, visited, Stack);

    /*  Initialize distances to all vertices as infinite and distance to source as 0 */
    for(int i = 0; i < V; i++) dist[i] = NINF;
    dist[s] = 0;

    /* Process vertices in topological order */
    while(Stack.empty() == false) {
        /* Get the next vertex from topological order */
        int u = Stack.top();
        Stack.pop();

        /* Update distances of all adjacent vertices */
        list<AdjListNode>::iterator i;
        if(dist[u] != NINF) {
          for(i = adj[u].begin(); i != adj[u].end(); ++i)
             if(dist[i->getV()] < dist[u] + i->getWeight())
                dist[i->getV()] = dist[u] + i->getWeight();
        }
    }

    /* Print the calculated longest distances */
    for(int i = 0; i < V; i++) {
        if(dist[i] == NINF) printf("INF ");
        else printf("%d ", dist[i]);
    }
}

int main() {
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int s = 1;
    printf("Following are longest distances from source vertex %d\n", s);
    g.longestPath(s);

    return 0;
}