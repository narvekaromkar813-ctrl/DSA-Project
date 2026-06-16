#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <climits>
#include <algorithm>
#include <utility>

// Border Patrol Network (Module 6).
// Represents border areas as a weighted, undirected graph and supports
// BFS Traversal, DFS Traversal, and Dijkstra's Shortest Path.
class Graph {
private:
    std::vector<std::string> locations;
    std::unordered_map<std::string, int> indexOf;
    std::vector<std::vector<std::pair<int, int>>> adj; // adj[u] = list of {neighbor, distance}

    int getIndex(const std::string& loc) const {
        auto it = indexOf.find(loc);
        return (it == indexOf.end()) ? -1 : it->second;
    }

    void dfsHelper(int u, std::vector<bool>& visited, std::vector<std::string>& order) const {
        visited[u] = true;
        order.push_back(locations[u]);
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            if (!visited[v]) dfsHelper(v, visited, order);
        }
    }

public:
    Graph() {
        // Pre-load the standard set of border patrol locations required by the spec.
        const std::vector<std::string> defaultLocations = {
            "Base Camp", "Sector A", "Sector B", "Sector C",
            "Border Point 1", "Border Point 2", "Watch Tower"
        };
        for (const auto& l : defaultLocations) addLocation(l);
    }

    void addLocation(const std::string& loc) {
        if (indexOf.count(loc)) return;
        indexOf[loc] = static_cast<int>(locations.size());
        locations.push_back(loc);
        adj.emplace_back();
    }

    bool addEdge(const std::string& from, const std::string& to, int weight) {
        int u = getIndex(from), v = getIndex(to);
        if (u == -1 || v == -1) {
            std::cout << "[Graph] Invalid location(s) for edge: " << from << " <-> " << to << "\n";
            return false;
        }
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
        return true;
    }

    int locationCount() const { return static_cast<int>(locations.size()); }

    int edgeCount() const {
        int total = 0;
        for (const auto& list : adj) total += static_cast<int>(list.size());
        return total / 2; // each undirected edge counted twice
    }

    void displayLocations() const {
        std::cout << "Border Network Locations:\n";
        for (int i = 0; i < static_cast<int>(locations.size()); ++i) {
            std::cout << "  " << i << ". " << locations[i] << "\n";
        }
    }

    void displayNetwork() const {
        std::cout << "---- Border Patrol Network (adjacency list) ----\n";
        for (int i = 0; i < static_cast<int>(locations.size()); ++i) {
            std::cout << locations[i] << " -> ";
            for (const auto& edge : adj[i]) {
                std::cout << locations[edge.first] << "(" << edge.second << "km) ";
            }
            std::cout << "\n";
        }
    }

    // BFS Traversal starting from a given location.
    std::vector<std::string> bfs(const std::string& start) const {
        std::vector<std::string> order;
        int s = getIndex(start);
        if (s == -1) { std::cout << "[Graph] Start location not found.\n"; return order; }

        std::vector<bool> visited(locations.size(), false);
        std::queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(locations[u]);
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                if (!visited[v]) { visited[v] = true; q.push(v); }
            }
        }
        return order;
    }

    // DFS Traversal starting from a given location.
    std::vector<std::string> dfs(const std::string& start) const {
        std::vector<std::string> order;
        int s = getIndex(start);
        if (s == -1) { std::cout << "[Graph] Start location not found.\n"; return order; }

        std::vector<bool> visited(locations.size(), false);
        dfsHelper(s, visited, order);
        return order;
    }

    // Dijkstra's Shortest Path between two locations.
    // Returns {path (as location names), totalDistance}. totalDistance == -1 if unreachable.
    std::pair<std::vector<std::string>, int> dijkstra(const std::string& start, const std::string& end) const {
        std::vector<std::string> path;
        int s = getIndex(start), e = getIndex(end);
        if (s == -1 || e == -1) {
            std::cout << "[Graph] Invalid start/end location.\n";
            return {path, -1};
        }

        int n = static_cast<int>(locations.size());
        std::vector<int> dist(n, INT_MAX);
        std::vector<int> prev(n, -1);
        std::vector<bool> visited(n, false);
        dist[s] = 0;

        using PQItem = std::pair<int, int>; // {distance, node}
        std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;
            if (d > dist[u]) continue;

            for (const auto& edge : adj[u]) {
                int v = edge.first, w = edge.second;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[e] == INT_MAX) return {path, -1};

        std::vector<int> reversed;
        for (int at = e; at != -1; at = prev[at]) reversed.push_back(at);
        std::reverse(reversed.begin(), reversed.end());
        for (int idx : reversed) path.push_back(locations[idx]);

        return {path, dist[e]};
    }
};

#endif // GRAPH_H
