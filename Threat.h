#ifndef THREAT_H
#define THREAT_H

#include <string>
#include <iostream>
#include <iomanip>

// Represents a single intelligence / threat record used throughout the system.
class Threat {
public:
    int id;
    std::string threatName;
    std::string threatLevel;   // Low / Medium / High / Critical
    std::string location;
    std::string status;        // e.g. Active / Monitoring / Resolved
    std::string timestamp;

    Threat()
        : id(0), threatName(""), threatLevel(""), location(""), status(""), timestamp("") {}

    Threat(int id_, std::string name_, std::string level_, std::string loc_,
           std::string status_, std::string time_)
        : id(id_), threatName(std::move(name_)), threatLevel(std::move(level_)),
          location(std::move(loc_)), status(std::move(status_)), timestamp(std::move(time_)) {}

    // Converts the textual threat level into a numeric weight so it can be
    // compared/sorted: Critical > High > Medium > Low.
    int priorityValue() const {
        if (threatLevel == "Critical") return 4;
        if (threatLevel == "High")     return 3;
        if (threatLevel == "Medium")   return 2;
        if (threatLevel == "Low")      return 1;
        return 0; // Unknown level falls last
    }

    // Prints a single formatted row representing this record.
    void display() const {
        std::cout << std::left
                   << std::setw(6)  << id
                   << std::setw(20) << threatName
                   << std::setw(10) << threatLevel
                   << std::setw(16) << location
                   << std::setw(12) << status
                   << std::setw(18) << timestamp
                   << "\n";
    }

    // Prints the column header that matches display().
    static void displayHeader() {
        std::cout << std::left
                   << std::setw(6)  << "ID"
                   << std::setw(20) << "Threat Name"
                   << std::setw(10) << "Level"
                   << std::setw(16) << "Location"
                   << std::setw(12) << "Status"
                   << std::setw(18) << "Timestamp"
                   << "\n";
        std::cout << std::string(82, '-') << "\n";
    }
};

#endif // THREAT_H
