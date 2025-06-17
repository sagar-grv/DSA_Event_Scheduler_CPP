#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

// ANSI color codes for better readability in terminal
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// Event class to hold event details
class Event {
public:
    int priority;
    string name;
    string timing;
    int design_rating;
    int num_people;
    double cost;
    string description;

    Event(int p, string n, string t, int d, int np, double c, string desc)
        : priority(p), name(n), timing(t), design_rating(d), num_people(np), cost(c), description(desc) {}

    void display() const {
        cout << YELLOW << "Event: " << name << RESET
             << "\nPriority: " << priority
             << "\nTiming: " << timing
             << "\nDesign Rating: " << design_rating
             << "\nNumber of People: " << num_people
             << "\nCost: $" << cost
             << "\nDescription: " << description << "\n" << endl;
    }

    // Comparison operator to make lower priority values have higher priority
    bool operator<(const Event& other) const {
        return priority > other.priority;
    }
};

class EventScheduler {
private:
    priority_queue<Event> event_queue;

public:
    void add_event(const Event& event) {
        event_queue.push(event);
        cout << GREEN << "Added event: " << event.name << " with priority " << event.priority << RESET << endl;
    }

    void peek_next_event() const {
        if (event_queue.empty()) {
            cout << RED << "No events scheduled." << RESET << endl;
        } else {
            cout << CYAN << "Next event: " << RESET;
            event_queue.top().display();
        }
    }

    void remove_next_event() {
        if (event_queue.empty()) {
            cout << RED << "No events to remove." << RESET << endl;
        } else {
            cout << RED << "Removing event: " << RESET;
            event_queue.top().display();
            event_queue.pop();
        }
    }

    void display_all_events() const {
        if (event_queue.empty()) {
            cout << RED << "No events scheduled." << RESET << endl;
        } else {
            priority_queue<Event> copy = event_queue;
            cout << CYAN << "All scheduled events (sorted by priority):" << RESET << endl;
            while (!copy.empty()) {
                copy.top().display();
                copy.pop();
            }
        }
    }
};

class UserManager {
private:
    unordered_map<string, string> users;
    const string file_name = "users.txt";

    void load_users_from_file() {
        ifstream file(file_name);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t delimiter_pos = line.find(',');
                if (delimiter_pos != string::npos) {
                    string username = line.substr(0, delimiter_pos);
                    string password = line.substr(delimiter_pos + 1);
                    users[username] = password;
                }
            }
            file.close();
        }
    }

    void save_user_to_file(const string& username, const string& password) {
        ofstream file(file_name, ios::app);
        if (file.is_open()) {
            file << username << "," << password << endl;
            file.close();
        } else {
            cout << RED << "Error: Could not open user file for writing." << RESET << endl;
        }
    }

public:
    UserManager() {
        load_users_from_file();
    }

    void register_user(const string& username, const string& password) {
        if (username.empty() || password.empty()) {
            cout << RED << "Error: Username and password cannot be empty." << RESET << endl;
            return;
        }

        if (users.find(username) != users.end()) {
            cout << RED << "Error: Username already exists. Please choose a different username." << RESET << endl;
        } else {
            users[username] = password;
            save_user_to_file(username, password);
            cout << GREEN << "User registered successfully!" << RESET << endl;
        }
    }

    bool login(const string& username, const string& password) {
        if (users.find(username) != users.end() && users[username] == password) {
            cout << GREEN << "Login successful! Welcome, " << username << "!" << RESET << endl;
            return true;
        } else {
            cout << RED << "Login failed. Invalid username or password." << RESET << endl;
            return false;
        }
    }
};

int get_int_input(const string& prompt) {
    int input;
    cout << prompt;
    while (!(cin >> input) || input <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. " << prompt << RESET;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

double get_double_input(const string& prompt) {
    double input;
    cout << prompt;
    while (!(cin >> input) || input < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. " << prompt << RESET;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

void add_event_interactive(EventScheduler& scheduler) {
    cout << "\n--- Add New Event ---" << endl;

    string name;
    cout << "Enter event name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << RED << "Event name cannot be empty." << RESET << endl;
        return;
    }

    string timing;
    cout << "Enter event timing (e.g., '12:00 PM'): ";
    getline(cin, timing);

    int priority = get_int_input("Enter event priority (lower is higher priority): ");
    int design_rating = get_int_input("Enter event design rating (1-10): ");
    int num_people = get_int_input("Enter expected number of people: ");
    double cost = get_double_input("Enter event cost: $");

    string description;
    cout << "Enter event description: ";
    getline(cin, description);
    if (description.empty()) {
        description = "No description provided.";
    }

    Event new_event(priority, name, timing, design_rating, num_people, cost, description);
    scheduler.add_event(new_event);
}

int main() {
    EventScheduler scheduler;
    UserManager user_manager;

    int choice;
    bool exit_program = false;

    while (!exit_program) {
        bool logged_in = false;
        string username, password;

        while (!logged_in && !exit_program) {
            cout << "\n--- User Login Interface ---" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            choice = get_int_input("Enter your choice: ");

            switch (choice) {
                case 1:
                    cout << "Enter new username: ";
                    getline(cin, username);
                    cout << "Enter new password: ";
                    getline(cin, password);
                    user_manager.register_user(username, password);
                    break;
                case 2:
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    logged_in = user_manager.login(username, password);
                    break;
                case 3:
                    cout << RED << "Exiting program." << RESET << endl;
                    exit_program = true;
                    break;
                default:
                    cout << RED << "Invalid choice. Please try again." << RESET << endl;
            }
        }

        if (logged_in) {
            do {
                cout << "\n--- Event Scheduler Menu ---" << endl;
                cout << "1. Add New Event" << endl;
                cout << "2. Peek Next Event" << endl;
                cout << "3. Remove Next Event" << endl;
                cout << "4. Display All Events" << endl;
                cout << "5. Logout" << endl;
                choice = get_int_input("Enter your choice: ");

                switch (choice) {
                    case 1:
                        add_event_interactive(scheduler);
                        break;
                    case 2:
                        scheduler.peek_next_event();
                        break;
                    case 3:
                        scheduler.remove_next_event();
                        break;
                    case 4:
                        scheduler.display_all_events();
                        break;
                    case 5:
                        cout << RED << "Logging out." << RESET << endl;
                        logged_in = false;
                        break;
                    default:
                        cout << RED << "Invalid choice. Please try again." << RESET << endl;
                }
            } while (logged_in);
        }
    }

    return 0;
}
