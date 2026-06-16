#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "Threat.h"
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

// Provides Linear Search and Binary Search utilities used by the
// Intelligence Search System (Module 3).
class SearchAlgorithms {
public:
    // Linear Search by exact Threat ID. Returns index or -1.
    static int linearSearchById(const std::vector<Threat>& v, int id) {
        for (int i = 0; i < static_cast<int>(v.size()); ++i) {
            if (v[i].id == id) return i;
        }
        return -1;
    }

    // Linear Search by Threat Name (case-insensitive substring match). Returns index or -1.
    static int linearSearchByName(const std::vector<Threat>& v, const std::string& name) {
        std::string target = toLower(name);
        for (int i = 0; i < static_cast<int>(v.size()); ++i) {
            if (toLower(v[i].threatName).find(target) != std::string::npos) return i;
        }
        return -1;
    }

    // Linear Search by Location (case-insensitive substring match). Returns index or -1.
    static int linearSearchByLocation(const std::vector<Threat>& v, const std::string& loc) {
        std::string target = toLower(loc);
        for (int i = 0; i < static_cast<int>(v.size()); ++i) {
            if (toLower(v[i].location).find(target) != std::string::npos) return i;
        }
        return -1;
    }

    // Binary Search by Threat ID. REQUIRES the vector to already be sorted
    // ascending by id. Returns index in that (sorted) vector, or -1.
    static int binarySearchById(const std::vector<Threat>& v, int id) {
        int low = 0, high = static_cast<int>(v.size()) - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (v[mid].id == id) return mid;
            if (v[mid].id < id)  low  = mid + 1;
            else                  high = mid - 1;
        }
        return -1;
    }

private:
    static std::string toLower(const std::string& s) {
        std::string r = s;
        std::transform(r.begin(), r.end(), r.begin(),
                        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return r;
    }
};

#endif // SEARCH_ALGORITHMS_H
