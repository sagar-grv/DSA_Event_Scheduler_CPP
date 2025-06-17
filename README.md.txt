# 🎯 Priority-based Event Scheduler with Login System

A C++ project implementing a priority-based event scheduler with user login and registration features using DSA concepts like `priority_queue` and `unordered_map`.

## 💡 Features
- 🔐 User Registration and Login
- 📅 Add, Peek, Remove, and Display Events
- 🧠 Events managed using Priority Queue (min-heap logic)
- 🎨 Colored CLI using ANSI escape codes

## 🛠 Data Structures Used
- `priority_queue<Event>` — for managing event priority
- `unordered_map<string, string>` — for user credential storage

## 🖥️ Usage
```bash
g++ Finallization.cpp -o scheduler
./scheduler
