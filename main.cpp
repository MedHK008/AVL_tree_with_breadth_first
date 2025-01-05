#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

class Dijkstra {
private:
    
    vector<vector<unsigned int>> adj_matrix;// using a matrix to represent the relation between nodes
    vector<vector<unsigned int>> distance;// distance[0] is the distance from the source node, distance[1] is the parent node

    unsigned int n;

    inline unsigned int heapParent(unsigned int i) { return (i - 1) / 2; } // get the parent node of the current node
    inline unsigned int heapLeft(unsigned int i) { return 2 * i + 1; } // get the left child node of the current node
    inline unsigned int heapRight(unsigned int i) { return 2 * i + 2; } // get the right child node of the current node

    /***
     * Min heapify the heap at index i
     * @param heap: the heap to be min heapified
     * @param i: the index to start min heapify
     * @param heapSize: the size of the heap
     * 
     * @return void
     ***/
    void minHeapify(vector<pair<unsigned int, unsigned int>> &heap, unsigned int i, unsigned int heapSize) {
        unsigned int left = heapLeft(i); // get the left child node
        unsigned int right = heapRight(i); // get the right child node
        unsigned int smallest = i; // set the smallest node to the current node

        // check if the left child node is smaller than the current node
        if (left < heapSize && heap[left].first < heap[i].first) {
            smallest = left;
        }
        // check if the right child node is smaller than the current node
        if (right < heapSize && heap[right].first < heap[smallest].first) {
            smallest = right;
        }
        // if the smallest node is not the current node, swap the current node with the smallest node
        if (smallest != i) {
            swap(heap[i], heap[smallest]); // swap the current node with the smallest node
            minHeapify(heap, smallest, heapSize); // recursively min heapify the heap
        }
    }

    /***
     * Build a min heap from the given heap
     * @param heap: the heap to be min heapified
     * @param heapSize: the size of the heap
     * 
     * @return void
     ***/
    void buildMinHeap(vector<pair<unsigned int, unsigned int>> &heap, unsigned int heapSize) {
        for (int i = heapSize / 2 - 1; i >= 0; --i) {
            // min heapify the heap from the middle to the beginning
            minHeapify(heap, i, heapSize);
        }
    }

    /***
     * Extract the minimum value from the heap
     * @param heap: the heap to extract the minimum value from
     * @param heapSize: the size of the heap
     * @param nodeIndex: the index of the node in the heap
     * 
     * @return the minimum value in the heap
     ***/
    unsigned int heapExtractMin(vector<pair<unsigned int, unsigned int>> &heap, unsigned int &heapSize, unsigned int &nodeIndex) {
        // check if the heap is empty
        if (heapSize < 1) {
            cerr << "Heap underflow error!\n";
            return UINT_MAX;
        }
        // get the minimum value from the heap
        unsigned int min = heap[0].first;
        // get the index of the node in the heap
        nodeIndex = heap[0].second;

        // swap the minimum value with the last value in the heap
        heap[0] = heap[heapSize - 1];
        // decrease the size of the heap
        --heapSize;
        // min heapify the heap since we replace the minimum value with the last value
        minHeapify(heap, 0, heapSize);
        // return the minimum value
        return min;
    }

    /***
     * Decrease the key of the node in the heap
     * @param heap: the heap to decrease the key
     * @param node: the node to decrease the key
     * @param newWeight: the new weight of the node
     * @param heapSize: the size of the heap
     * 
     * @return void
     ***/
    void heapDecreaseKey(vector<pair<unsigned int, unsigned int>> &heap, unsigned int node, unsigned int newWeight, unsigned int heapSize) {
        for (unsigned int i = 0; i < heapSize; ++i) {
            // check if the node is found in the heap
            if (heap[i].second == node) {
                // decrease the key of the node
                heap[i].first = newWeight;
                // move the node up the heap
                unsigned int parent = heapParent(i);
                // while the parent node is greater than the current node, swap the parent node with the current node
                while (i > 0 && heap[parent].first > heap[i].first) {
                    // swap the parent node with the current node
                    swap(heap[i], heap[parent]);
                    // move the current node to the parent node
                    i = parent;
                    // get the new parent node
                    parent = heapParent(i);
                }
                break;
            }
        }
    }

    /***
     * Swap two nodes in the heap
     * @param a: the first node to swap
     * @param b: the second node to swap
     * 
     * @return void
     ***/
    void relax(vector<pair<unsigned int, unsigned int>> &heap, unsigned int u, unsigned int v, unsigned int weight, unsigned int heapSize) {
        // check if the new weight is less than the current weight
        unsigned int newWeight = distance[u][0] + weight;
        if (distance[v][0] > newWeight) {
            // update the distance of the node
            distance[v][0] = newWeight;
            // update the parent node of the node
            distance[v][1] = u;
            // decrease the key of the node in the heap
            heapDecreaseKey(heap, v, newWeight, heapSize);
        }
    }

public:
    // Constructor
    Dijkstra(unsigned int nodes) : n(nodes) {
        adj_matrix.assign(n, vector<unsigned int>(n, UINT_MAX));
        distance.assign(n, vector<unsigned int>(2, UINT_MAX));
    }
    // add an edge to the graph
    void ajouterEtape(unsigned int u, unsigned int v, unsigned int weight, bool directed = false) {
        // add the edge to the graph
        adj_matrix[u][v] = min(adj_matrix[u][v], weight);
        // if the graph is undirected, add the edge from v to u
        if (!directed) {
            adj_matrix[v][u] = min(adj_matrix[v][u], weight);
        }
    }

    // traverse the graph
    void parcourir(unsigned int source) {
        // create a heap to store the nodes
        vector<pair<unsigned int, unsigned int>> heap(n);
        // create a set to store the visited nodes
        vector<unsigned int> S(n, 0);

        // initialize the distance of the nodes
        for (unsigned int i = 0; i < n; ++i) {
            // set the distance of the nodes to infinity
            distance[i][0] = UINT_MAX;
            // set the parent node of the nodes to infinity
            distance[i][1] = UINT_MAX;
            // set the heap to infinity
            heap[i] = {UINT_MAX, i};
        }
        // set the distance of the source node to 0
        distance[source][0] = 0;
        // set the parent node of the source node to 0
        heap[source].first = 0;

        // build a min heap from the heap
        unsigned int heapSize = n;
        // build the min heap
        buildMinHeap(heap, heapSize);

        // traverse the graph
        while (heapSize > 0) {
            // extract the minimum value from the heap
            unsigned int u = UINT_MAX;
            // get the minimum value from the heap
            unsigned int minVal = heapExtractMin(heap, heapSize, u);
            // check if the minimum value is infinity
            if (u == UINT_MAX) {
                break;
            }
            // set the node as visited
            S[u] = 1;


            for (unsigned int v = 0; v < n; ++v) {
                // check if the node is not visited and there is an edge between the nodes
                if (adj_matrix[u][v] != UINT_MAX && !S[v]) {
                    // relax the nodes
                    relax(heap, u, v, adj_matrix[u][v], heapSize);
                }
            }
        }
    }
    // this method is self-explanatory
    void afficherResultat() {
        for (unsigned int i = 0; i < n; ++i) {
            cout << "Node " << i + 1 << " Distance: " << (distance[i][0] == UINT_MAX ? -1 : distance[i][0]) << "\n";
        }
    }

    // friend void drawGraph(sf::RenderWindow &window, const Dijkstra &dijkstra, unsigned int source);
};

// void drawGraph(sf::RenderWindow &window, const Dijkstra &dijkstra, unsigned int source) {
//     // Define some constants for drawing
//     const float radius = 20.0f;
//     const float offsetX = 100.0f;
//     const float offsetY = 100.0f;
//     const float spacing = 150.0f;

//     // Create circles for nodes
//     vector<sf::CircleShape> nodes(dijkstra.n);
//     for (unsigned int i = 0; i < dijkstra.n; ++i) {
//         nodes[i].setRadius(radius);
//         nodes[i].setFillColor(sf::Color::Green);
//         nodes[i].setPosition(offsetX + (i % 3) * spacing, offsetY + (i / 3) * spacing);
//     }

//     // Create lines for edges
//     vector<sf::VertexArray> edges;
//     for (unsigned int u = 0; u < dijkstra.n; ++u) {
//         for (unsigned int v = 0; v < dijkstra.n; ++v) {
//             if (dijkstra.adj_matrix[u][v] != UINT_MAX) {
//                 sf::VertexArray line(sf::Lines, 2);
//                 line[0].position = nodes[u].getPosition() + sf::Vector2f(radius, radius);
//                 line[0].color = sf::Color::White;
//                 line[1].position = nodes[v].getPosition() + sf::Vector2f(radius, radius);
//                 line[1].color = sf::Color::White;
//                 edges.push_back(line);
//             }
//         }
//     }

//     // Draw everything
//     window.clear();
//     for (const auto &edge : edges) {
//         window.draw(edge);
//     }
//     for (const auto &node : nodes) {
//         window.draw(node);
//     }
//     window.display();
// }

int main() {
    // Example graph
    Dijkstra exampleDijkstra(5);
    exampleDijkstra.ajouterEtape(0, 1, 10);
    exampleDijkstra.ajouterEtape(0, 4, 5);
    exampleDijkstra.ajouterEtape(1, 2, 1);
    exampleDijkstra.ajouterEtape(1, 4, 2);
    exampleDijkstra.ajouterEtape(2, 3, 4);
    exampleDijkstra.ajouterEtape(3, 0, 7);
    exampleDijkstra.ajouterEtape(3, 2, 6);
    exampleDijkstra.ajouterEtape(4, 1, 3);
    exampleDijkstra.ajouterEtape(4, 2, 9);
    exampleDijkstra.ajouterEtape(4, 3, 2);

    unsigned int sourceNode = 0;
    exampleDijkstra.parcourir(sourceNode);
    exampleDijkstra.afficherResultat();

    // // Create a window
    // sf::RenderWindow window(sf::VideoMode(800, 600), "Dijkstra Visualization");

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }

    //     drawGraph(window, exampleDijkstra, sourceNode);
    // }

    return 0;
}
