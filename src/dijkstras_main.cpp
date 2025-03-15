#include "dijkstras.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "No file given." << endl;
        return 1;
    }

    Graph G;
    file_to_graph(argv[1], G);
    
    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int destination = 0; destination < G.numVertices; destination++) {
        vector<int> path = extract_shortest_path(distances, previous, destination);
        print_path(path, distances[destination]);
    }
    return 0;
}