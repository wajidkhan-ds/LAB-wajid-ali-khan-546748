#include <iostream>
#include <string>
using namespace std;

// ---------------- Node ----------------
class CoachNode {
public:
    int    coachNumber;
    string coachType;
    int    capacity;
    int    passengers;
    CoachNode* next;
    CoachNode* prev;

    CoachNode(int num, string type, int cap, int pass) {
        coachNumber = num;
        coachType   = type;
        capacity    = cap;
        passengers  = pass;
        next = prev = nullptr;
    }

    int available() const { return capacity - passengers; }
};

// ---------------- Circular Doubly Linked List ----------------
class Train {
    CoachNode* current;

public:
    Train() { current = nullptr; }
    ~Train() { clearAll(); }

    // 1. Add Coach at end
    void addCoach(int num, string type, int cap, int pass) {
        CoachNode* newNode = new CoachNode(num, type, cap, pass);
        if (current == nullptr) {
            current       = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            CoachNode* tail = current->prev;
            newNode->next = current;
            newNode->prev = tail;
            tail->next    = newNode;
            current->prev = newNode;
        }
        cout << "Coach " << num << " added.\n";
    }

    // 2. Insert Coach after a specified coach number
    void insertAfter(int targetNum, int num, string type, int cap, int pass) {
        if (current == nullptr) {
            cout << "Train is empty. Adding as first coach.\n";
            addCoach(num, type, cap, pass);
            return;
        }
        CoachNode* temp = current;
        do {
            if (temp->coachNumber == targetNum) {
                CoachNode* newNode = new CoachNode(num, type, cap, pass);
                newNode->next = temp->next;
                newNode->prev = temp;
                temp->next->prev = newNode;
                temp->next       = newNode;
                cout << "Coach " << num << " inserted after "
                     << targetNum << ".\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Coach " << targetNum << " not found.\n";
    }

    // 3. Remove Coach by number
    void removeCoach(int num) {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        CoachNode* temp = current;
        do {
            if (temp->coachNumber == num) {
                if (temp->next == temp) {
                    delete temp;
                    current = nullptr;
                    cout << "Removed last coach.\n";
                    return;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == current) current = temp->next;
                cout << "Coach " << num << " removed.\n";
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Coach " << num << " not found.\n";
    }

    // 4. Move Forward
    void moveForward() {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        current = current->next;
        cout << "Moved forward.\n";
    }

    // 5. Move Backward
    void moveBackward() {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        current = current->prev;
        cout << "Moved backward.\n";
    }

    // 6. Display Clockwise (forward)
    void displayClockwise() {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        cout << "Train (clockwise):\n";
        CoachNode* temp = current;
        do {
            cout << "  Coach " << temp->coachNumber
                 << " | Type: " << temp->coachType
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->passengers
                 << " | Empty seats: " << temp->available() << "\n";
            temp = temp->next;
        } while (temp != current);
    }

    // 7. Display Anti-clockwise (backward)
    void displayAntiClockwise() {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        cout << "Train (anti-clockwise):\n";
        CoachNode* temp = current;
        do {
            cout << "  Coach " << temp->coachNumber
                 << " | Type: " << temp->coachType
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->passengers
                 << " | Empty seats: " << temp->available() << "\n";
            temp = temp->prev;
        } while (temp != current);
    }

    // 8. Search Coach
    void searchCoach(int num) {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        CoachNode* temp = current;
        do {
            if (temp->coachNumber == num) {
                cout << "Found -> Coach " << temp->coachNumber
                     << " | Type: " << temp->coachType
                     << " | Capacity: " << temp->capacity
                     << " | Passengers: " << temp->passengers << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Coach " << num << " not found.\n";
    }

    // 9. Find Maximum Available Capacity
    void findMaxAvailable() {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        CoachNode* best = current;
        CoachNode* temp = current->next;
        while (temp != current) {
            if (temp->available() > best->available()) best = temp;
            temp = temp->next;
        }
        cout << "Coach with most empty seats -> "
             << best->coachNumber
             << " (" << best->coachType << ") - "
             << best->available() << " empty seats.\n";
    }

    // 10. Display Current Coach
    void displayCurrent() {
        if (current == nullptr) { cout << "Train is empty.\n"; return; }
        cout << "Current Coach -> " << current->coachNumber
             << " | Type: " << current->coachType
             << " | Capacity: " << current->capacity
             << " | Passengers: " << current->passengers
             << " | Empty seats: " << current->available() << "\n";
    }

    // 11. Reverse Train Direction (pointer manipulation only)
    void reverseTrain() {
        if (current == nullptr || current->next == current) return;

        CoachNode* temp = current;
        do {
            CoachNode* nxt = temp->next;
            temp->next = temp->prev;
            temp->prev = nxt;
            temp = nxt;
        } while (temp != current);

        current = current->next;   // old tail becomes new head
        cout << "Train direction reversed.\n";
    }

    // Cleanup
    void clearAll() {
        if (current == nullptr) return;
        CoachNode* tail = current->prev;
        tail->next = nullptr;
        CoachNode* temp = current;
        while (temp) {
            CoachNode* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        current = nullptr;
    }
};

// ---------------- Menu ----------------
int main() {
    Train train;

    int n;
    cout << "Enter number of coaches: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int num, cap, pass; string type;
        cout << "\nCoach " << i + 1 << ":\n";
        cout << "Coach Number: ";    cin >> num; cin.ignore();
        cout << "Coach Type: ";      getline(cin, type);
        cout << "Passenger Capacity: "; cin >> cap;
        cout << "Current Passengers: "; cin >> pass;
        train.addCoach(num, type, cap, pass);
    }

    int choice;
    do {
        cout << "\n===== Train Coach Navigation =====\n";
        cout << "1. Add Coach\n";
        cout << "2. Insert Coach After Specified Coach\n";
        cout << "3. Remove Coach by Number\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Clockwise\n";
        cout << "7. Display Anti-clockwise\n";
        cout << "8. Search Coach\n";
        cout << "9. Find Max Available Capacity\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train Direction\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int num, cap, pass; string type;
            cout << "Coach Number: ";    cin >> num; cin.ignore();
            cout << "Coach Type: ";      getline(cin, type);
            cout << "Capacity: ";        cin >> cap;
            cout << "Passengers: ";      cin >> pass;
            train.addCoach(num, type, cap, pass);
        }
        else if (choice == 2) {
            int target, num, cap, pass; string type;
            cout << "Insert after Coach Number: "; cin >> target;
            cout << "New Coach Number: "; cin >> num; cin.ignore();
            cout << "Coach Type: ";       getline(cin, type);
            cout << "Capacity: ";         cin >> cap;
            cout << "Passengers: ";       cin >> pass;
            train.insertAfter(target, num, type, cap, pass);
        }
        else if (choice == 3) {
            int num; cout << "Coach Number to remove: "; cin >> num;
            train.removeCoach(num);
        }
        else if (choice == 4)  train.moveForward();
        else if (choice == 5)  train.moveBackward();
        else if (choice == 6)  train.displayClockwise();
        else if (choice == 7)  train.displayAntiClockwise();
        else if (choice == 8) {
            int num; cout << "Coach Number to search: "; cin >> num;
            train.searchCoach(num);
        }
        else if (choice == 9)  train.findMaxAvailable();
        else if (choice == 10) train.displayCurrent();
        else if (choice == 11) train.reverseTrain();
        else if (choice == 0)  cout << "Exiting...\n";
        else cout << "Invalid choice.\n";

    } while (choice != 0);

    return 0;
}