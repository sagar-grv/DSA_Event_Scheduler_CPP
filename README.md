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
```

## 📁 Files
- Finallization.cpp — Main source file
- users.txt — Stores registered usernames and passwords (plain text)

## 📷 Sample Output

```bash
--- User Login Interface ---
1. Register
2. Login
3. Exit
Enter your choice: 1
Enter new username: admin
Enter new password: 123
User registered successfully!

```

## 📚 Concepts Covered
- Priority Queue
- File Handling
- Classes and Objects
- STL (queue, map)
- Input validation

## 📌 Note
- Users are stored in users.txt.
- Priorities: Lower numbers mean higher priority.

## 🙋‍♂️ Author
- Sagar Gurav
 📫 work.sagargurav1812@gmail.com
- 🌐 GitHub Profile

