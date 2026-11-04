#include <iostream>
#include <string>
#include <utility>
#include <limits>

using namespace std;

// ========================================
// Book Node
// ========================================
struct BookNode {
    int bookID;
    string title;
    BookNode* next;
};

// ========================================
// Linked List Class
// ========================================
class LinkedList {
private:
    BookNode* head;
    int count;

    // Return the node at a valid index
    BookNode* GetNodeAt(int index) {
        BookNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++)
            current = current->next;
        return current;
    }

    // Copy book data between nodes
    void CopyBookData(BookNode* a, BookNode* b) {
        swap(a->bookID, b->bookID);
        swap(a->title, b->title);
    }

public:
    // Constructor
    LinkedList() {
        head = nullptr;
        count = 0;
    }

    // Insert a book at the head
    void Insert(BookNode* book) {
        if (book == nullptr) return;
        book->next = head;
        head = book;
        count++;
    }

    // Remove a book from the head
    BookNode* Remove() {
        if (IsEmpty()) return nullptr;
        BookNode* book = head;
        head = head->next;
        book->next = nullptr;
        count--;
        return book;
    }

    // Check whether the list is empty
    bool IsEmpty() { return head == nullptr; }
    bool IsNotEmpty() { return head != nullptr; }
    int GetCount() { return count; }

    // Insert at a specified index
    void InsertAt(BookNode* book, int index) {
        if (book == nullptr) return;

        // Correct the insertion index
        if (index < 0) index = 0;
        if (index > count) index = count;

        if (index == 0) {
            Insert(book);
            return;
        }

        BookNode* previous = GetNodeAt(index - 1);
        book->next = previous->next;
        previous->next = book;
        count++;
    }

    // Remove at a specified index
    BookNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;

        // Correct the removal index
        if (index < 0) index = 0;
        if (index >= count) index = count - 1;

        if (index == 0) return Remove();

        BookNode* previous = GetNodeAt(index - 1);
        BookNode* book = previous->next;
        previous->next = book->next;
        book->next = nullptr;
        count--;
        return book;
    }

    // Swap book data at two indexes
    void Swap(int index1, int index2) {
        if (index1 < 0 || index1 >= count || index2 < 0 || index2 >= count) return;
        if (index1 == index2) return;

        BookNode* first = GetNodeAt(index1);
        BookNode* second = GetNodeAt(index2);
        CopyBookData(first, second);
    }

    // Sort books by book ID in ascending order
    void Sort() {
        for (BookNode* i = head; i != nullptr; i = i->next) {
            for (BookNode* j = i->next; j != nullptr; j = j->next) {
                if (i->bookID > j->bookID) CopyBookData(i, j);
            }
        }
    }

    // Reverse the linked list
    void Reverse() {
        BookNode* previous = nullptr;
        BookNode* current = head;
        BookNode* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }

    // Display all books
    void Print() {
        BookNode* current = head;
        int index = 0;
        cout << "\nIndex\tBook ID\tTitle\n";
        cout << "-----------------------------------\n";
        while (current != nullptr) {
            cout << index << "\t" << current->bookID << "\t" << current->title << endl;
            current = current->next;
            index++;
        }
        cout << "Total books: " << count << endl;
    }

    // Copy constructor
    LinkedList(const LinkedList& other) {
        head = nullptr;
        count = 0;
        BookNode* current = other.head;
        while (current != nullptr) {
            BookNode* copy = new BookNode{ current->bookID, current->title, nullptr };
            InsertAt(copy, count);
            current = current->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;
        while (!IsEmpty()) delete Remove();
        BookNode* current = other.head;
        while (current != nullptr) {
            BookNode* copy = new BookNode{ current->bookID, current->title, nullptr };
            InsertAt(copy, count);
            current = current->next;
        }
        return *this;
    }

    // Destructor
    ~LinkedList() {
        while (!IsEmpty()) delete Remove();
    }
};

// ========================================
// Helper functions for user input validation
// ========================================
BookNode* CreateBookFromInput() {
    int id;
    string title;

    cout << "Enter Book ID (Integer): ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a numerical ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.ignore(); // Clear the newline character left in the stream
    cout << "Enter Book Title: ";
    getline(cin, title);

    BookNode* book = new BookNode;
    book->bookID = id;
    book->title = title;
    book->next = nullptr;
    return book;
}

// ========================================
// Main: Dynamic User-Driven System
// ========================================
int main() {
    LinkedList library;
    int choice = 0;

    do {
        cout << "\n=================================";
        cout << "\n     LIBRARY MANAGEMENT SYSTEM   ";
        cout << "\n=================================";
        cout << "\n1. Display Library Collection";
        cout << "\n2. Insert Book at Head";
        cout << "\n3. Insert Book at Specific Index";
        cout << "\n4. Remove Book from Head";
        cout << "\n5. Remove Book from Specific Index";
        cout << "\n6. Swap Two Books by Index";
        cout << "\n7. Sort Library by Book ID";
        cout << "\n8. Reverse Library List Order";
        cout << "\n9. Exit Program";
        cout << "\n\nEnter your choice (1-9): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid selection. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                library.Print();
                break;

            case 2: {
                cout << "\n[Inserting Book at Head]\n";
                BookNode* newBook = CreateBookFromInput();
                library.Insert(newBook);
                cout << "Book successfully added to the head.\n";
                break;
            }

            case 3: {
                cout << "\n[Inserting Book at Specific Index]\n";
                int idx;
                cout << "Enter index (Current total books: " << library.GetCount() << "): ";
                cin >> idx;
                BookNode* newBook = CreateBookFromInput();
                library.InsertAt(newBook, idx);
                cout << "Book successfully added at index " << idx << ".\n";
                break;
            }

            case 4: {
                BookNode* removed = library.Remove();
                if (removed != nullptr) {
                    cout << "\nSuccessfully removed from head: " << removed->title << " (ID: " << removed->bookID << ")\n";
                    delete removed;
                } else {
                    cout << "\nThe library is empty. Nothing to remove.\n";
                }
                break;
            }

            case 5: {
                if (library.IsEmpty()) {
                    cout << "\nThe library is empty. Nothing to remove.\n";
                    break;
                }
                int idx;
                cout << "\nEnter index to remove (0 to " << library.GetCount() - 1 << "): ";
                cin >> idx;
                BookNode* removed = library.RemoveAt(idx);
                if (removed != nullptr) {
                    cout << "Successfully removed from index " << idx << ": " << removed->title << "\n";
                    delete removed;
                }
                break;
            }

            case 6: {
                if (library.GetCount() < 2) {
                    cout << "\nYou need at least 2 books to perform a swap operation.\n";
                    break;
                }
                int idx1, idx2;
                cout << "\nEnter first index to swap: ";
                cin >> idx1;
                cout << "Enter second index to swap: ";
                cin >> idx2;
                library.Swap(idx1, idx2);
                cout << "Books at index " << idx1 << " and index " << idx2 << " swapped successfully.\n";
                break;
            }

            case 7:
                library.Sort();
                cout << "\nLibrary sorted by Book ID in ascending order.\n";
                break;

            case 8:
                library.Reverse();
                cout << "\nLibrary sequence reversed successfully.\n";
                break;

            case 9:
                cout << "\nExiting Library Management System. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice. Please select an option between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
