#include <vector>
#include <algorithm>
#include "condition.hpp"

class MaxHeap {
private:
    std::vector<Condition*> heap;
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapify_up(int i) {
        if (i != 0 && heap[parent(i)]->get_value() < heap[i]->get_value()) {
            std::swap(heap[i], heap[parent(i)]);
            heapify_up(parent(i));
        }
    }

    void heapify_down(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < size && heap[l]->get_value() > heap[i]->get_value())
            largest = l;
        if (r < size && heap[r]->get_value() > heap[largest]->get_value())
            largest = r;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }

public:
    MaxHeap() : size(0) {}

    void insert(Condition* condition) {
        heap.push_back(condition);
        int i = size++;
        heapify_up(i);
    }

    Condition* extract_max() {
        Condition* max = heap[0];
        heap[0] = heap[--size];
        heapify_down(0);
        return max;
    }

    bool empty() {
        return size == 0;
    }
};
