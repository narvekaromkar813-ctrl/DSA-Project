/*
 * Smart Defense Surveillance & Border Security Intelligence System
 * ------------------------------------------------------------------
 * A menu-driven C++17 console application demonstrating classic data
 * structures & algorithms applied to a defense-intelligence domain.
 *
 * Modules:
 *   1. Surveillance Intelligence Database (BST + AVL Tree)
 *   2. Threat Prioritization (Bubble / Selection / Merge Sort)
 *   3. Intelligence Search System (Linear / Binary Search)
 *   4. Mission Recovery System (STL Stack)
 *   5. Security Alert Processing (STL Queue)
 *   6. Border Patrol Network (Graph: BFS / DFS / Dijkstra)
 *   7. Asset Identification System (unordered_map hash table)
 *   8. Dashboard (summary statistics across all modules)
 */

#include "Threat.h"
#include "BST.h"
#include "AVLTree.h"
#include "SortingAlgorithms.h"
#include "SearchAlgorithms.h"
#include "MissionStack.h"
#include "AlertQueue.h"
#include "Graph.h"
#include "AssetManager.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// ===================== Input Handling Utilities =====================
// Centralized here so every module gets consistent, validated input.

// Called whenever the input stream itself has been closed (e.g. EOF via
// Ctrl+D, or piped input running out). Without this guard, a closed stream
// would make every subsequent read fail instantly, spinning the validation
// loops forever. Exiting cleanly here is the correct, safe behavior.
void exitOnClosedInput() {
    if (cin.eof()) {
        cout << "\n[System] Input stream closed. Shutting down Intelligence System safely.\n";
        exit(0);
    }
}

// Reads an integer safely; re-prompts on invalid (non-numeric) input.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        exitOnClosedInput();
        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads a full line of text (may be empty).
string readLine(const string& prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    exitOnClosedInput();
    return line;
}

// Reads a line of text, re-prompting until it is non-empty.
string readNonEmptyLine(const string& prompt) {
    string line;
    while (true) {
        line = readLine(prompt);
        if (!line.empty()) return line;
        cout << "Input cannot be empty. Please try again.\n";
    }
}

// Reads and validates a Threat Level, normalizing capitalization.
string readThreatLevel() {
    while (true) {
        string level = readNonEmptyLine("Threat Level (Low/Medium/High/Critical): ");
        string lower = level;
        transform(lower.begin(), lower.end(), lower.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        if (lower == "low")      return "Low";
        if (lower == "medium")   return "Medium";
        if (lower == "high")     return "High";
        if (lower == "critical") return "Critical";
        cout << "Invalid level. Must be one of: Low, Medium, High, Critical.\n";
    }
}

// Produces a "YYYY-MM-DD HH:MM" timestamp for new records.
string currentTimestamp() {
    time_t now = time(nullptr);
    tm* lt = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", lt);
    return string(buf);
}

// ===================== Main Application Class =====================

class SurveillanceSystem {
private:
    BST bst;                     // Module 1 - BST storage
    AVLTree avl;                 // Module 1 - AVL storage
    vector<Threat> allThreats;   // Master list backing prioritization & search
    MissionStack missionStack;   // Module 4
    AlertQueue alertQueue;       // Module 5
    Graph graph;                 // Module 6
    AssetManager assetManager;   // Module 7
    int nextThreatId = 1001;     // Auto-incrementing ID generator
    bool borderNetworkReady = false;

    // ---------------- Module 1: Surveillance Intelligence Database ----------------

    void addThreatRecord() {
        cout << "\n--- Add New Intelligence Record ---\n";
        string name     = readNonEmptyLine("Threat Name: ");
        string level    = readThreatLevel();
        string location = readNonEmptyLine("Location: ");
        string status   = readNonEmptyLine("Status (e.g. Active/Monitoring/Resolved): ");
        string stamp    = currentTimestamp();

        Threat t(nextThreatId, name, level, location, status, stamp);
        bst.insert(t);
        avl.insert(t);
        allThreats.push_back(t);
        missionStack.push("Added Threat [ID:" + to_string(t.id) + ", " + t.threatName + "]");
        cout << "Record added successfully. Assigned ID: " << nextThreatId << "\n";
        nextThreatId++;
    }

    void deleteThreatRecord() {
        cout << "\n--- Delete Intelligence Record ---\n";
        int id = readInt("Enter Threat ID to delete: ");

        bool removedFromBst = bst.remove(id);
        bool removedFromAvl = avl.remove(id);

        auto it = find_if(allThreats.begin(), allThreats.end(),
                           [id](const Threat& t) { return t.id == id; });
        if (it != allThreats.end()) {
            missionStack.push("Deleted Threat [ID:" + to_string(id) + ", " + it->threatName + "]");
            allThreats.erase(it);
        }

        if (removedFromBst || removedFromAvl) cout << "Record with ID " << id << " deleted.\n";
        else cout << "No record found with ID " << id << ".\n";
    }

    void searchInDatabase() {
        int id = readInt("Enter Threat ID to search: ");

        cout << "\n[BST Search Result]\n";
        Threat* fromBst = bst.search(id);
        if (fromBst) { Threat::displayHeader(); fromBst->display(); }
        else cout << "Not found in BST.\n";

        cout << "\n[AVL Tree Search Result]\n";
        Threat* fromAvl = avl.search(id);
        if (fromAvl) { Threat::displayHeader(); fromAvl->display(); }
        else cout << "Not found in AVL Tree.\n";
    }

    void updateThreatStatus() {
        int id = readInt("Enter Threat ID to update status: ");
        auto it = find_if(allThreats.begin(), allThreats.end(),
                           [id](const Threat& t) { return t.id == id; });
        if (it == allThreats.end()) { cout << "Record not found.\n"; return; }

        string newStatus = readNonEmptyLine("Enter new status: ");
        it->status = newStatus;

        // Keep both trees in sync (search() returns a pointer to live node data).
        if (Threat* b = bst.search(id)) b->status = newStatus;
        if (Threat* a = avl.search(id)) a->status = newStatus;

        missionStack.push("Updated Status [ID:" + to_string(id) + " -> " + newStatus + "]");
        cout << "Status updated.\n";
    }

    void moduleDatabase() {
        int choice;
        do {
            cout << "\n===== Surveillance Intelligence Database =====\n";
            cout << "1. Insert Record\n";
            cout << "2. Delete Record\n";
            cout << "3. Search Record by ID\n";
            cout << "4. Update Status\n";
            cout << "5. Display All (BST - sorted by ID)\n";
            cout << "6. Display All (AVL Tree - sorted by ID)\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose option: ");
            switch (choice) {
                case 1: addThreatRecord(); break;
                case 2: deleteThreatRecord(); break;
                case 3: searchInDatabase(); break;
                case 4: updateThreatStatus(); break;
                case 5: cout << "\n-- BST Records --\n"; bst.displayAll(); break;
                case 6: cout << "\n-- AVL Tree Records --\n"; avl.displayAll(); break;
                case 0: break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Module 2: Threat Prioritization ----------------

    void modulePrioritization() {
        if (allThreats.empty()) {
            cout << "No threats available yet. Add records via Module 1 first.\n";
            return;
        }
        int choice;
        do {
            cout << "\n===== Threat Prioritization =====\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Selection Sort\n";
            cout << "3. Merge Sort\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose sorting method: ");

            vector<Threat> sortedCopy = allThreats; // operate on a copy
            switch (choice) {
                case 1: SortingAlgorithms::bubbleSort(sortedCopy); break;
                case 2: SortingAlgorithms::selectionSort(sortedCopy); break;
                case 3: SortingAlgorithms::mergeSort(sortedCopy); break;
                case 0: continue;
                default: cout << "Invalid choice.\n"; continue;
            }

            cout << "\n-- Threats Sorted by Priority (Critical > High > Medium > Low) --\n";
            Threat::displayHeader();
            for (const auto& t : sortedCopy) t.display();
        } while (choice != 0);
    }

    // ---------------- Module 3: Intelligence Search System ----------------

    void moduleSearch() {
        if (allThreats.empty()) {
            cout << "No threats available yet. Add records via Module 1 first.\n";
            return;
        }
        int choice;
        do {
            cout << "\n===== Intelligence Search System =====\n";
            cout << "1. Linear Search by Threat ID\n";
            cout << "2. Linear Search by Threat Name\n";
            cout << "3. Linear Search by Location\n";
            cout << "4. Binary Search by Threat ID\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose option: ");

            int idx = -1;
            switch (choice) {
                case 1: {
                    int id = readInt("Enter Threat ID: ");
                    idx = SearchAlgorithms::linearSearchById(allThreats, id);
                    break;
                }
                case 2: {
                    string name = readNonEmptyLine("Enter Threat Name (or part of it): ");
                    idx = SearchAlgorithms::linearSearchByName(allThreats, name);
                    break;
                }
                case 3: {
                    string loc = readNonEmptyLine("Enter Location (or part of it): ");
                    idx = SearchAlgorithms::linearSearchByLocation(allThreats, loc);
                    break;
                }
                case 4: {
                    // Binary search requires a vector sorted ascending by ID.
                    vector<Threat> byId = allThreats;
                    sort(byId.begin(), byId.end(),
                         [](const Threat& a, const Threat& b) { return a.id < b.id; });
                    int id = readInt("Enter Threat ID: ");
                    int foundIdx = SearchAlgorithms::binarySearchById(byId, id);
                    if (foundIdx != -1) {
                        cout << "\nRecord Found:\n";
                        Threat::displayHeader();
                        byId[foundIdx].display();
                    } else {
                        cout << "Record not found.\n";
                    }
                    continue; // already handled display for this case
                }
                case 0: continue;
                default: cout << "Invalid choice.\n"; continue;
            }

            if (idx != -1) {
                cout << "\nRecord Found:\n";
                Threat::displayHeader();
                allThreats[idx].display();
            } else {
                cout << "Record not found.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Module 4: Mission Recovery System ----------------

    void moduleMissionRecovery() {
        int choice;
        do {
            cout << "\n===== Mission Recovery System =====\n";
            cout << "1. Push Custom Operation\n";
            cout << "2. Undo Last Operation\n";
            cout << "3. Display Stack History\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose option: ");
            switch (choice) {
                case 1: {
                    string op = readNonEmptyLine("Describe operation (e.g. 'Added Threat'): ");
                    missionStack.push(op);
                    break;
                }
                case 2: missionStack.undo(); break;
                case 3: missionStack.display(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Module 5: Security Alert Processing ----------------

    void moduleAlertProcessing() {
        int choice;
        do {
            cout << "\n===== Security Alert Processing =====\n";
            cout << "1. Add Alert\n";
            cout << "2. Process Alert (FIFO)\n";
            cout << "3. Display Pending Alerts\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose option: ");
            switch (choice) {
                case 1: {
                    string type     = readNonEmptyLine("Threat Type: ");
                    string priority = readThreatLevel();
                    string location = readNonEmptyLine("Location: ");
                    alertQueue.addAlert(type, priority, location);
                    break;
                }
                case 2: alertQueue.processAlert(); break;
                case 3: alertQueue.display(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Module 6: Border Patrol Network ----------------

    void setupDefaultBorderNetwork() {
        if (borderNetworkReady) return;
        graph.addEdge("Base Camp", "Sector A", 5);
        graph.addEdge("Base Camp", "Sector B", 8);
        graph.addEdge("Sector A", "Sector C", 4);
        graph.addEdge("Sector B", "Sector C", 3);
        graph.addEdge("Sector A", "Border Point 1", 6);
        graph.addEdge("Sector C", "Border Point 2", 5);
        graph.addEdge("Border Point 1", "Watch Tower", 2);
        graph.addEdge("Border Point 2", "Watch Tower", 3);
        graph.addEdge("Sector B", "Watch Tower", 9);
        borderNetworkReady = true;
    }

    void moduleBorderPatrol() {
        setupDefaultBorderNetwork();
        int choice;
        do {
            cout << "\n===== Border Patrol Network =====\n";
            cout << "1. Display Network\n";
            cout << "2. BFS Traversal\n";
            cout << "3. DFS Traversal\n";
            cout << "4. Dijkstra Shortest Path\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose option: ");
            switch (choice) {
                case 1: graph.displayNetwork(); break;
                case 2: {
                    graph.displayLocations();
                    string start = readNonEmptyLine("Enter start location: ");
                    vector<string> order = graph.bfs(start);
                    if (!order.empty()) {
                        cout << "BFS Traversal Order: ";
                        for (size_t i = 0; i < order.size(); ++i)
                            cout << order[i] << (i + 1 < order.size() ? " -> " : "\n");
                    }
                    break;
                }
                case 3: {
                    graph.displayLocations();
                    string start = readNonEmptyLine("Enter start location: ");
                    vector<string> order = graph.dfs(start);
                    if (!order.empty()) {
                        cout << "DFS Traversal Order: ";
                        for (size_t i = 0; i < order.size(); ++i)
                            cout << order[i] << (i + 1 < order.size() ? " -> " : "\n");
                    }
                    break;
                }
                case 4: {
                    graph.displayLocations();
                    string start = readNonEmptyLine("Enter start location: ");
                    string end   = readNonEmptyLine("Enter destination location: ");
                    pair<vector<string>, int> result = graph.dijkstra(start, end);
                    if (result.second == -1) {
                        cout << "No path found between the given locations.\n";
                    } else {
                        cout << "Shortest Route: ";
                        for (size_t i = 0; i < result.first.size(); ++i)
                            cout << result.first[i] << (i + 1 < result.first.size() ? " -> " : "\n");
                        cout << "Minimum Distance: " << result.second << " km\n";
                    }
                    break;
                }
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Module 7: Asset Identification System ----------------

    void moduleAssetID() {
        int choice;
        do {
            cout << "\n===== Asset Identification System =====\n";
            cout << "1. Insert Asset\n";
            cout << "2. Search Asset\n";
            cout << "3. Delete Asset\n";
            cout << "4. Display All Assets\n";
            cout << "0. Back to Main Menu\n";
            choice = readInt("Choose option: ");
            switch (choice) {
                case 1: {
                    int id      = readInt("Asset ID: ");
                    string name = readNonEmptyLine("Personnel Name: ");
                    string dept = readNonEmptyLine("Department: ");
                    string rank = readNonEmptyLine("Rank: ");
                    assetManager.insertAsset(id, name, dept, rank);
                    break;
                }
                case 2: {
                    int id = readInt("Asset ID to search: ");
                    Asset* a = assetManager.search(id);
                    if (a) {
                        cout << "Found -> ID: " << a->assetId << " | Name: " << a->personnelName
                             << " | Department: " << a->department << " | Rank: " << a->rank << "\n";
                    } else {
                        cout << "Asset not found.\n";
                    }
                    break;
                }
                case 3: {
                    int id = readInt("Asset ID to delete: ");
                    if (assetManager.remove(id)) cout << "Asset deleted.\n";
                    else cout << "Asset not found.\n";
                    break;
                }
                case 4: assetManager.displayAll(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Module 8: Dashboard ----------------

    void moduleDashboard() {
        setupDefaultBorderNetwork();
        int totalThreats = static_cast<int>(allThreats.size());
        int criticalThreats = static_cast<int>(count_if(
            allThreats.begin(), allThreats.end(),
            [](const Threat& t) { return t.threatLevel == "Critical"; }));
        int pendingAlerts = alertQueue.size();
        int totalAssets   = assetManager.size();

        cout << "\n===================================================\n";
        cout << "   SMART DEFENSE SURVEILLANCE - COMMAND DASHBOARD\n";
        cout << "===================================================\n";
        cout << "Total Threats Recorded   : " << totalThreats << "\n";
        cout << "Critical Threats         : " << criticalThreats << "\n";
        cout << "Pending Alerts in Queue   : " << pendingAlerts << "\n";
        cout << "Border Patrol Network    : " << graph.locationCount()
             << " locations, " << graph.edgeCount() << " patrol routes (Active)\n";
        cout << "Total Registered Assets   : " << totalAssets << "\n";
        cout << "Mission Log Entries       : " << missionStack.size() << "\n";
        cout << "===================================================\n";
    }

public:
    void run() {
        int choice;
        do {
            cout << "\n#####################################################\n";
            cout << "   SMART DEFENSE SURVEILLANCE & BORDER SECURITY\n";
            cout << "               INTELLIGENCE SYSTEM\n";
            cout << "#####################################################\n";
            cout << "1. Surveillance Intelligence Database\n";
            cout << "2. Threat Prioritization\n";
            cout << "3. Intelligence Search System\n";
            cout << "4. Mission Recovery System\n";
            cout << "5. Security Alert Processing\n";
            cout << "6. Border Patrol Network\n";
            cout << "7. Asset Identification System\n";
            cout << "8. Dashboard\n";
            cout << "0. Exit\n";
            choice = readInt("Select a module: ");

            switch (choice) {
                case 1: moduleDatabase(); break;
                case 2: modulePrioritization(); break;
                case 3: moduleSearch(); break;
                case 4: moduleMissionRecovery(); break;
                case 5: moduleAlertProcessing(); break;
                case 6: moduleBorderPatrol(); break;
                case 7: moduleAssetID(); break;
                case 8: moduleDashboard(); break;
                case 0: cout << "Shutting down Intelligence System. Stay vigilant.\n"; break;
                default: cout << "Invalid selection. Please choose a valid module.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    SurveillanceSystem app;
    app.run();
    return 0;
}
