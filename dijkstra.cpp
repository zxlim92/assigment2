#include <iostream>
#include <list>
#include <utility> // for pair()
// pair is a simple container of two heterogeneous objects
// which can be accessed by dot operator followed by 
// first or second keyword
#include "heap.h"
#include "dijkstra.h"
void dijkstra(const WDigraph& graph, int startVertex, 
    unordered_map<int, PIL>& searchTree) {
    // create binary heap events
    BinaryHeap<pair<int, int> ,long long> events;
    // create starting pair for vertex
    pair<int, int> start(startVertex, startVertex);
    // insert the vertex to events
    events.insert(start, 0);
    while(events.size() > 0) {
        // create temporary storage for min
        auto temp = events.min();   
        // set the edge for item
        pair<int, int> edge = temp.item;
        // set the weight
        long long weight = temp.key;
        // set u, v
        int u = edge.first;
        int v = edge.second;
        // pop min
        events.popMin();
        if(searchTree.find(v) == searchTree.end()) {
            // create pair for weight and u
            searchTree[v] = make_pair(weight, u);
            for (auto i = graph.neighbours(v); i != graph.endIterator(v); i++) {
                pair<int, int> temp(v, *i);
                // get the cost 
                long long cost = graph.getCost(v, *i);
                // insert weight + cost
                events.insert(temp, weight + cost);
            }
        }
    }
}