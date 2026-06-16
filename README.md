# 🛡️ Smart Defense Surveillance & Border Security Intelligence System

## Industry
Defense & National Security

## Course
**Data Structures & Algorithms with C++ (Semester II)**  
**B.Tech CSE (2025–2029)**  
**ITM Skills University**

---

# 📌 Problem Statement

Defense agencies require a centralized platform to monitor surveillance systems, analyze security threats, manage border operations, and support strategic decision-making for national security.

This project demonstrates the practical implementation of core Data Structures and Algorithms (DSA) concepts in a defense-intelligence environment through a menu-driven C++ application.

---

# 🎯 Project Objective

The **Smart Defense Surveillance & Border Security Intelligence System** provides a simulation of defense intelligence operations by integrating various DSA concepts such as:

- Binary Search Trees (BST)
- AVL Trees
- Sorting Algorithms
- Searching Algorithms
- Stack
- Queue
- Graph Algorithms (BFS, DFS, Dijkstra)
- Hashing using Unordered Maps

The system allows users to manage surveillance records, prioritize threats, process alerts, monitor patrol networks, and maintain asset information efficiently.

---

# 🏗️ Technical Implementation

| DSA Concept | Application |
|------------|-------------|
| BST & AVL Trees | Intelligence Database Management |
| Sorting Algorithms | Threat Prioritization |
| Searching Algorithms | Intelligence Record Retrieval |
| Stack | Mission Recovery & Operation History |
| Queue | Security Alert Processing |
| Graph (BFS, DFS, Dijkstra) | Border Patrol Network Analysis |
| Hashing (unordered_map) | Asset Identification & Tracking |

---

# 📂 Project Structure

```text
SmartDefenseSystem/
│
├── AlertQueue.h              # Queue-based security alert management
├── AssetManager.h            # Hash table (unordered_map) asset registry
├── AVLTree.h                 # Self-balancing AVL Tree implementation
├── BST.h                     # Binary Search Tree implementation
├── Graph.h                   # BFS, DFS and Dijkstra algorithms
├── MissionStack.h            # Stack-based mission recovery system
├── SearchAlgorithms.h        # Linear and Binary Search
├── SortingAlgorithms.h       # Bubble, Selection and Merge Sort
├── Threat.h                  # Threat record model
├── main.cpp                  # Main menu-driven application
├── Makefile                  # Build configuration
└── README.md                 # Project documentation
```

---

# ⚙️ Features & Modules

## 1️⃣ Surveillance Intelligence Database

Stores and manages threat intelligence records using:

- Binary Search Tree (BST)
- AVL Tree

### Operations
- Add Threat Records
- Search Threat Records
- Delete Threat Records
- Update Threat Records
- Display All Threats

### Stored Information
- Threat ID
- Threat Name
- Threat Level
- Location
- Description

---

## 2️⃣ Threat Prioritization System

Ranks threats according to severity levels:

**Critical > High > Medium > Low**

### Implemented Algorithms

- Bubble Sort
- Selection Sort
- Merge Sort

### Benefits
- Faster threat assessment
- Better resource allocation
- Improved response planning

---

## 3️⃣ Intelligence Search System

Efficient retrieval of surveillance records.

### Search Methods

#### Linear Search
- By Threat ID
- By Threat Name
- By Location

#### Binary Search
- By Threat ID

---

## 4️⃣ Mission Recovery System

Uses **STL Stack** to maintain operation history.

### Features

- Log Intelligence Operations
- View Mission History
- Undo Recent Operation
- Custom Mission Entries

### DSA Used

```cpp
std::stack
```

---

## 5️⃣ Security Alert Processing

Uses **STL Queue** to process alerts in FIFO order.

### Features

- Add Security Alerts
- Process Alerts
- View Pending Alerts

### DSA Used

```cpp
std::queue
```

---

## 6️⃣ Border Patrol Network

Represents surveillance and patrol routes as a weighted graph.

### Fixed Border Locations

- Base Camp
- Sector A
- Sector B
- Sector C
- Border Point 1
- Border Point 2
- Watch Tower

### Implemented Algorithms

#### Breadth First Search (BFS)
Used for area-wise surveillance traversal.

#### Depth First Search (DFS)
Used for route exploration.

#### Dijkstra’s Algorithm
Used for shortest patrol path calculation.

### Benefits

- Route Optimization
- Patrol Planning
- Resource Deployment

---

## 7️⃣ Asset Identification System

Maintains personnel and equipment records using hashing.

### Features

- Add Assets
- Search Assets
- Delete Assets
- Display Assets

### DSA Used

```cpp
std::unordered_map
```

### Example Assets

- Security Personnel
- Vehicles
- Drones
- Surveillance Equipment

---

## 8️⃣ Defense Intelligence Dashboard

Provides a summarized view of all system statistics.

### Dashboard Metrics

- Total Threats
- Critical Threat Count
- Pending Alerts
- Border Network Size
- Registered Assets

---

# 🚀 Building the Project

## Using Makefile

```bash
make
./sds
```

---

## Manual Compilation

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o sds
./sds
```

---

# 💻 Sample Menu

```text
====================================
SMART DEFENSE INTELLIGENCE SYSTEM
====================================

1. Surveillance Intelligence Database
2. Threat Prioritization
3. Intelligence Search System
4. Mission Recovery System
5. Security Alert Processing
6. Border Patrol Network
7. Asset Identification System
8. Dashboard
9. Exit

Enter Choice:
```

---

# 📊 Expected Outcomes

The system helps demonstrate:

- Efficient storage and retrieval of intelligence records
- Threat prioritization using sorting algorithms
- Fast searching mechanisms
- Mission recovery through stack operations
- Alert handling through queue operations
- Border route optimization using graph algorithms
- Asset tracking using hashing techniques

---

# 🔒 Defense Applications

- Border Security Monitoring
- Threat Intelligence Management
- Surveillance Data Organization
- Security Alert Handling
- Resource Deployment Planning
- Mission Recovery Tracking
- Asset Identification and Tracking

---

# 🛠 Technologies Used

- C++17
- STL (Stack, Queue, Vector, Unordered Map)
- Object-Oriented Programming
- Graph Algorithms
- Tree Data Structures
- Searching Algorithms
- Sorting Algorithms

---

# 📚 Learning Outcomes

Through this project, students gain practical experience with:

- Binary Search Trees
- AVL Trees
- Sorting Techniques
- Searching Techniques
- Stack Operations
- Queue Operations
- Graph Traversal Algorithms
- Shortest Path Algorithms
- Hash Tables
- Menu-Driven Software Design

---

# 👨‍🎓 Academic Project

**Smart Defense Surveillance & Border Security Intelligence System**

Developed as part of the **Data Structures & Algorithms with C++** course to demonstrate real-world applications of fundamental DSA concepts in the domain of **Defense & National Security**.

---

