#include <iostream>
#include <string>
using namespace std;

// ---------------- Node ----------------
class TabNode {
public:
    int    tabID;
    string title;
    string url;
    TabNode* next;
    TabNode* prev;

    TabNode(int id, string t, string u) {
        tabID = id;
        title = t;
        url   = u;
        next  = prev = nullptr;
    }
};

// ---------------- Circular Doubly Linked List ----------------
class BrowserTabManager {
    TabNode* current;   // active tab (also serves as entry point)

public:
    BrowserTabManager() { current = nullptr; }

    ~BrowserTabManager() { clearAll(); }

    // 1. Open New Tab – insert after current
    void openNewTab(int id, string title, string url) {
        TabNode* newNode = new TabNode(id, title, url);

        if (current == nullptr) {                 // empty list
            current       = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            TabNode* tail = current->prev;        // last node
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next       = newNode;
            // new tab does NOT become current unless we choose so;
            // spec says "insert after current", so current stays.
        }
        cout << "Tab \"" << title << "\" opened.\n";
    }

    // 2. Close Current Tab
    void closeCurrentTab() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }
        if (current->next == current) {           // only tab
            cout << "Closing last tab: " << current->title << "\n";
            delete current;
            current = nullptr;
            return;
        }
        TabNode* toDelete = current;
        TabNode* nextTab  = current->next;
        TabNode* prevTab  = current->prev;

        prevTab->next = nextTab;
        nextTab->prev = prevTab;
        current = nextTab;                        // next becomes current
        cout << "Closed tab: " << toDelete->title << "\n";
        delete toDelete;
    }

    // 3. Move Next
    void moveNext() {
        if (current == nullptr) { cout << "No tabs.\n"; return; }
        current = current->next;
        cout << "Moved to next tab.\n";
    }

    // 4. Move Previous
    void movePrevious() {
        if (current == nullptr) { cout << "No tabs.\n"; return; }
        current = current->prev;
        cout << "Moved to previous tab.\n";
    }

    // 5. Display Current Tab
    void displayCurrent() {
        if (current == nullptr) { cout << "No active tab.\n"; return; }
        cout << "Current Tab -> ID: " << current->tabID
             << " | Title: "       << current->title
             << " | URL: "         << current->url << "\n";
    }

    // 6. Display All Tabs Forward
    void displayForward() {
        if (current == nullptr) { cout << "No tabs open.\n"; return; }
        cout << "Tabs (forward):\n";
        TabNode* temp = current;
        do {
            cout << "  [ID " << temp->tabID << "] "
                 << temp->title << " - " << temp->url << "\n";
            temp = temp->next;
        } while (temp != current);
    }

    // 7. Display All Tabs Backward
    void displayBackward() {
        if (current == nullptr) { cout << "No tabs open.\n"; return; }
        cout << "Tabs (backward):\n";
        TabNode* temp = current;
        do {
            cout << "  [ID " << temp->tabID << "] "
                 << temp->title << " - " << temp->url << "\n";
            temp = temp->prev;
        } while (temp != current);
    }

    // 8. Search Tab by ID
    void searchTab(int id) {
        if (current == nullptr) { cout << "No tabs open.\n"; return; }
        TabNode* temp = current;
        do {
            if (temp->tabID == id) {
                cout << "Found -> ID: " << temp->tabID
                     << " | Title: "    << temp->title
                     << " | URL: "      << temp->url << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Tab with ID " << id << " not found.\n";
    }

    // Cleanup
    void clearAll() {
        if (current == nullptr) return;
        TabNode* tail = current->prev;
        tail->next = nullptr;               // break circle
        TabNode* temp = current;
        while (temp != nullptr) {
            TabNode* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        current = nullptr;
    }
};

// ---------------- Menu ----------------
int main() {
    BrowserTabManager bm;
    int choice;

    do {
        cout << "\n===== Browser Tab Manager =====\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab by ID\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id; string t, u;
            cout << "Enter Tab ID: ";        cin >> id;
            cin.ignore();
            cout << "Enter Title: ";         getline(cin, t);
            cout << "Enter URL: ";           getline(cin, u);
            bm.openNewTab(id, t, u);
        }
        else if (choice == 2) bm.closeCurrentTab();
        else if (choice == 3) bm.moveNext();
        else if (choice == 4) bm.movePrevious();
        else if (choice == 5) bm.displayCurrent();
        else if (choice == 6) bm.displayForward();
        else if (choice == 7) bm.displayBackward();
        else if (choice == 8) {
            int id; cout << "Enter Tab ID to search: "; cin >> id;
            bm.searchTab(id);
        }
        else if (choice == 0) cout << "Exiting...\n";
        else cout << "Invalid choice.\n";

    } while (choice != 0);

    return 0;
}