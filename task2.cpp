#include <iostream>
#include <string>
using namespace std;

// ---------------- Node ----------------
class PhotoNode {
public:
    int    photoID;
    string name;
    string dateTaken;
    string location;
    PhotoNode* next;
    PhotoNode* prev;

    PhotoNode(int id, string n, string d, string loc) {
        photoID   = id;
        name      = n;
        dateTaken = d;
        location  = loc;
        next = prev = nullptr;
    }
};

// ---------------- Circular Doubly Linked List ----------------
class PhotoAlbum {
    PhotoNode* current;   // currently selected photo

public:
    PhotoAlbum() { current = nullptr; }
    ~PhotoAlbum() { clearAll(); }

    // 1. Add Photo at end
    void addPhoto(int id, string n, string d, string loc) {
        PhotoNode* newNode = new PhotoNode(id, n, d, loc);
        if (current == nullptr) {
            current       = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            PhotoNode* tail = current->prev;
            newNode->next = current;
            newNode->prev = tail;
            tail->next    = newNode;
            current->prev = newNode;
        }
        cout << "Photo \"" << n << "\" added.\n";
    }

    // 2. Insert Photo After Current
    void insertAfterCurrent(int id, string n, string d, string loc) {
        if (current == nullptr) {
            addPhoto(id, n, d, loc);
            return;
        }
        PhotoNode* newNode = new PhotoNode(id, n, d, loc);
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next       = newNode;
        cout << "Photo \"" << n << "\" inserted after current.\n";
    }

    // 3. Remove Photo by ID
    void removePhotoByID(int id) {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        PhotoNode* temp = current;
        do {
            if (temp->photoID == id) {
                if (temp->next == temp) {           // only node
                    delete temp;
                    current = nullptr;
                    cout << "Removed last photo.\n";
                    return;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == current) current = temp->next;
                cout << "Photo ID " << id << " removed.\n";
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Photo ID " << id << " not found.\n";
    }

    // 4. Remove Current Photo
    void removeCurrentPhoto() {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        if (current->next == current) {
            delete current;
            current = nullptr;
            cout << "Removed last photo.\n";
            return;
        }
        PhotoNode* toDelete = current;
        PhotoNode* nxt      = current->next;
        PhotoNode* prv      = current->prev;

        prv->next = nxt;
        nxt->prev = prv;
        current   = nxt;              // next becomes current
        cout << "Removed current photo: " << toDelete->name << "\n";
        delete toDelete;
    }

    // 5. Move Next
    void moveNext() {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        current = current->next;
        cout << "Moved to next photo.\n";
    }

    // 6. Move Previous
    void movePrevious() {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        current = current->prev;
        cout << "Moved to previous photo.\n";
    }

    // 7. Display Forward
    void displayForward() {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        cout << "Album (forward from current):\n";
        PhotoNode* temp = current;
        do {
            cout << "  ID: " << temp->photoID
                 << " | Name: "      << temp->name
                 << " | Date: "      << temp->dateTaken
                 << " | Location: "  << temp->location << "\n";
            temp = temp->next;
        } while (temp != current);
    }

    // 8. Display Backward
    void displayBackward() {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        cout << "Album (backward from current):\n";
        PhotoNode* temp = current;
        do {
            cout << "  ID: " << temp->photoID
                 << " | Name: "      << temp->name
                 << " | Date: "      << temp->dateTaken
                 << " | Location: "  << temp->location << "\n";
            temp = temp->prev;
        } while (temp != current);
    }

    // 9. Search Photo
    void searchPhoto(int id) {
        if (current == nullptr) { cout << "Album is empty.\n"; return; }
        PhotoNode* temp = current;
        do {
            if (temp->photoID == id) {
                cout << "Found -> ID: " << temp->photoID
                     << " | Name: "      << temp->name
                     << " | Date: "      << temp->dateTaken
                     << " | Location: "  << temp->location << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Photo ID " << id << " not found.\n";
    }

    // 10. Count Photos
    int countPhotos() {
        if (current == nullptr) return 0;
        int count = 0;
        PhotoNode* temp = current;
        do { count++; temp = temp->next; } while (temp != current);
        return count;
    }

    // Cleanup
    void clearAll() {
        if (current == nullptr) return;
        PhotoNode* tail = current->prev;
        tail->next = nullptr;
        PhotoNode* temp = current;
        while (temp) {
            PhotoNode* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        current = nullptr;
    }
};

// ---------------- Menu ----------------
int main() {
    PhotoAlbum album;

    // Initial input
    int n;
    cout << "Enter number of photos: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int id; string name, date, loc;
        cout << "\nPhoto " << i + 1 << ":\n";
        cout << "ID: ";        cin >> id; cin.ignore();
        cout << "Name: ";      getline(cin, name);
        cout << "Date: ";      getline(cin, date);
        cout << "Location: ";  getline(cin, loc);
        album.addPhoto(id, name, date, loc);
    }

    int choice;
    do {
        cout << "\n===== Photo Album =====\n";
        cout << "1. Add Photo\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Forward\n";
        cout << "8. Display Backward\n";
        cout << "9. Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int id; string name, date, loc;
            cout << "ID: ";        cin >> id; cin.ignore();
            cout << "Name: ";      getline(cin, name);
            cout << "Date: ";      getline(cin, date);
            cout << "Location: ";  getline(cin, loc);
            if (choice == 1) album.addPhoto(id, name, date, loc);
            else             album.insertAfterCurrent(id, name, date, loc);
        }
        else if (choice == 3) {
            int id; cout << "Enter ID: "; cin >> id;
            album.removePhotoByID(id);
        }
        else if (choice == 4) album.removeCurrentPhoto();
        else if (choice == 5) album.moveNext();
        else if (choice == 6) album.movePrevious();
        else if (choice == 7) album.displayForward();
        else if (choice == 8) album.displayBackward();
        else if (choice == 9) {
            int id; cout << "Enter ID: "; cin >> id;
            album.searchPhoto(id);
        }
        else if (choice == 10)
            cout << "Total photos: " << album.countPhotos() << "\n";
        else if (choice == 0) cout << "Exiting...\n";
        else cout << "Invalid choice.\n";

    } while (choice != 0);

    return 0;
}