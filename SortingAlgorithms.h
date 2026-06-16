#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "Threat.h"
#include <vector>
#include <utility>

// Provides classic sorting algorithms used to prioritize threats so that
// Critical threats always surface above High, Medium, then Low (descending order).
class SortingAlgorithms {
public:
    // ---- Bubble Sort: O(n^2) ----
    static void bubbleSort(std::vector<Threat>& v) {
        int n = static_cast<int>(v.size());
        for (int i = 0; i < n - 1; ++i) {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; ++j) {
                if (v[j].priorityValue() < v[j + 1].priorityValue()) {
                    std::swap(v[j], v[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break; // already sorted, stop early
        }
    }

    // ---- Selection Sort: O(n^2) ----
    static void selectionSort(std::vector<Threat>& v) {
        int n = static_cast<int>(v.size());
        for (int i = 0; i < n - 1; ++i) {
            int maxIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (v[j].priorityValue() > v[maxIdx].priorityValue()) maxIdx = j;
            }
            if (maxIdx != i) std::swap(v[i], v[maxIdx]);
        }
    }

    // ---- Merge Sort: O(n log n) ----
    static void mergeSort(std::vector<Threat>& v) {
        if (v.size() <= 1) return;
        mergeSortHelper(v, 0, static_cast<int>(v.size()) - 1);
    }

private:
    static void mergeSortHelper(std::vector<Threat>& v, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortHelper(v, left, mid);
        mergeSortHelper(v, mid + 1, right);
        merge(v, left, mid, right);
    }

    static void merge(std::vector<Threat>& v, int left, int mid, int right) {
        std::vector<Threat> temp;
        temp.reserve(right - left + 1);
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            if (v[i].priorityValue() >= v[j].priorityValue()) temp.push_back(v[i++]);
            else temp.push_back(v[j++]);
        }
        while (i <= mid)   temp.push_back(v[i++]);
        while (j <= right) temp.push_back(v[j++]);
        for (int k = 0; k < static_cast<int>(temp.size()); ++k) v[left + k] = temp[k];
    }
};

#endif // SORTING_ALGORITHMS_H
