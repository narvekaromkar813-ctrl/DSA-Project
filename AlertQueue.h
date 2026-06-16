#ifndef ALERT_QUEUE_H
#define ALERT_QUEUE_H

#include <queue>
#include <string>
#include <iostream>
#include <iomanip>

// A single security alert raised by the surveillance network.
struct Alert {
    int alertId;
    std::string threatType;
    std::string priority;
    std::string location;
};

// Security Alert Processing (Module 5).
// Implements a strict FIFO queue (using STL std::queue) of pending alerts.
class AlertQueue {
private:
    std::queue<Alert> alerts;
    int nextId = 1;

public:
    // Add Alert: enqueues a new alert at the back of the queue.
    void addAlert(const std::string& type, const std::string& priority, const std::string& location) {
        Alert a{nextId++, type, priority, location};
        alerts.push(a);
        std::cout << "[Alert] Added Alert #" << a.alertId << " (" << type << " @ " << location << ")\n";
    }

    // Process Alert: dequeues and "handles" the oldest pending alert (FIFO).
    bool processAlert() {
        if (alerts.empty()) {
            std::cout << "[Alert] No pending alerts to process.\n";
            return false;
        }
        Alert a = alerts.front();
        alerts.pop();
        std::cout << "[Alert] Processed Alert #" << a.alertId
                   << " | Type: " << a.threatType
                   << " | Priority: " << a.priority
                   << " | Location: " << a.location << "\n";
        return true;
    }

    // Display Pending Alerts: shows the queue contents without removing them.
    void display() const {
        if (alerts.empty()) {
            std::cout << "[Alert] No pending alerts.\n";
            return;
        }
        std::queue<Alert> temp = alerts; // copy preserves original FIFO order
        std::cout << std::left << std::setw(10) << "AlertID" << std::setw(18) << "Threat Type"
                   << std::setw(12) << "Priority" << std::setw(15) << "Location" << "\n";
        std::cout << std::string(55, '-') << "\n";
        while (!temp.empty()) {
            Alert a = temp.front();
            temp.pop();
            std::cout << std::left << std::setw(10) << a.alertId << std::setw(18) << a.threatType
                       << std::setw(12) << a.priority << std::setw(15) << a.location << "\n";
        }
    }

    bool isEmpty() const { return alerts.empty(); }
    int size() const { return static_cast<int>(alerts.size()); }
};

#endif // ALERT_QUEUE_H
