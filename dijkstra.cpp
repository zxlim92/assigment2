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
    searchTree = {};
    BinaryHeap<pair<int, int> ,long long> events;
    pair<int, int> start(startVertex, startVertex);
    events.insert(start, 0);
    while(events.size() > 0) {
        auto temp = events.min();   
        pair<int, int> edge = temp.item;
        long long weight = temp.key;
        int u = edge.first;
        int v = edge.second;
        events.popMin();
        if(searchTree.find(v) == searchTree.end()) {
            searchTree[v] = make_pair(weight, u);
            for (auto i = graph.neighbours(v); i != graph.endIterator(v); i++) {
                pair<int, int> temp(v, *i);
                long long cost = graph.getCost(v, *i);
                events.insert(temp, weight + cost);
            }
        }
    }
}