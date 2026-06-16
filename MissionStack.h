#ifndef MISSION_STACK_H
#define MISSION_STACK_H

#include <stack>
#include <string>
#include <iostream>

// Mission Recovery System (Module 4).
// Tracks every significant operation (Added/Deleted/Updated Threat, etc.)
// using an STL stack so the most recent action can always be undone.
class MissionStack {
private:
    std::stack<std::string> history;

public:
    // Push operation: records a new action onto the stack.
    void push(const std::string& operation) {
        history.push(operation);
        std::cout << "[Mission Log] Recorded: " << operation << "\n";
    }

    // Undo operation: removes (undoes) the most recently logged action.
    bool undo() {
        if (history.empty()) {
            std::cout << "[Mission Log] No operations to undo.\n";
            return false;
        }
        std::cout << "[Mission Log] Undo -> " << history.top() << "\n";
        history.pop();
        return true;
    }

    // Display stack history without mutating the underlying stack
    // (a temporary copy is used since std::stack offers no iteration).
    void display() const {
        if (history.empty()) {
            std::cout << "[Mission Log] No history recorded.\n";
            return;
        }
        std::stack<std::string> temp = history;
        std::cout << "---- Mission History (most recent first) ----\n";
        int idx = static_cast<int>(temp.size());
        while (!temp.empty()) {
            std::cout << idx-- << ". " << temp.top() << "\n";
            temp.pop();
        }
    }

    bool isEmpty() const { return history.empty(); }
    int size() const { return static_cast<int>(history.size()); }
};

#endif // MISSION_STACK_H
