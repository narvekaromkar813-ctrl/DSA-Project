#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>

// A registered personnel / equipment asset.
struct Asset {
    int assetId;
    std::string personnelName;
    std::string department;
    std::string rank;
};

// Asset Identification System (Module 7).
// A hash-table-backed registry (using std::unordered_map) for O(1) average
// case Insert / Search / Delete of personnel & equipment records.
class AssetManager {
private:
    std::unordered_map<int, Asset> assets;

public:
    bool insertAsset(int id, const std::string& name, const std::string& dept, const std::string& rank) {
        if (assets.count(id)) {
            std::cout << "[Asset] Asset ID " << id << " already exists.\n";
            return false;
        }
        assets[id] = Asset{id, name, dept, rank};
        std::cout << "[Asset] Asset " << id << " (" << name << ") registered.\n";
        return true;
    }

    Asset* search(int id) {
        auto it = assets.find(id);
        return (it == assets.end()) ? nullptr : &it->second;
    }

    bool remove(int id) {
        return assets.erase(id) > 0;
    }

    void displayAll() const {
        if (assets.empty()) { std::cout << "[Asset] No assets registered.\n"; return; }
        std::cout << std::left << std::setw(10) << "AssetID" << std::setw(20) << "Name"
                   << std::setw(18) << "Department" << std::setw(12) << "Rank" << "\n";
        std::cout << std::string(60, '-') << "\n";
        for (const auto& pair : assets) {
            const Asset& a = pair.second;
            std::cout << std::left << std::setw(10) << a.assetId << std::setw(20) << a.personnelName
                       << std::setw(18) << a.department << std::setw(12) << a.rank << "\n";
        }
    }

    int size() const { return static_cast<int>(assets.size()); }
};

#endif // ASSET_MANAGER_H
