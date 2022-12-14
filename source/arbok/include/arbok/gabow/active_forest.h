#pragma once

#include <list>

#include <arbok/data_structures/compressed_tree.h>

struct FibHeapNode; // FWD

namespace arbok {

    class ActiveForest {
    public:
        explicit ActiveForest(CompressedTree<double>& _co);
        ~ActiveForest();

        void makeActive(int from, int to, double weight, int id);
        void deleteActiveEdge(int i);
        int getMin(int i); // returns min from heap of node i, does NOT delete it
        void mergeHeaps(int i, int j);

    private:
        // fheap methods
        std::list<FibHeapNode*>& home_heap(FibHeapNode* v);
        void removeFromCurrentList(FibHeapNode* v);
        void moveHome(FibHeapNode* v);
        void loseChild(FibHeapNode* v);
        double curWeight(FibHeapNode* v);

        CompressedTree<double>& co;
        std::vector<FibHeapNode*> active_edge; // for each node the active outgoing edge
        std::vector<std::list<FibHeapNode*>> active_sets; // for each node on path the active set heap represented by the root list
    };

}