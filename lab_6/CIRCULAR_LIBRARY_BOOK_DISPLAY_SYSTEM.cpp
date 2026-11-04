#include <iostream>
#include <string>
#include <utility>
#include <limits>

using namespace std;

struct BookNode {
    int bookID;
    string title;
    BookNode* next;
};

class CircularLinkedList {
private:
    BookNode* head;
    int count;
    BookNode* currentDisplayNode;

    BookNode* GetNodeAt(int index) {
        if (head == nullptr) return nullptr;
        BookNode* current = head->next;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }

    void SwapData(BookNode* a, BookNode* b) {
        swap(a->bookID, b->bookID);
        swap(a->title, b->title);
    }

    int NormalizeIndex(int index) {
        if (count == 0) return 0;
        return ((index % count) + count) % count;
    }

public:
    CircularLinkedList() {
        head = nullptr;
        count = 0;
        currentDisplayNode = nullptr;
    }

    bool IsEmpty() { return count == 0; }
    bool IsNotEmpty() { return count > 0; }
    int GetCount() { return count; }

    void Insert(BookNode* book) {
        if (book == nullptr) return;
        if (head == nullptr) {
            head = book;
            book->next = book;
            currentDisplayNode = book;
        } else {
            book->next = head->next;
            head->next = book;
        }
        count++;
    }

    BookNode* Remove() {
        if (IsEmpty()) return nullptr;
        BookNode* first = head->next;
        if (first == head) {
            head = nullptr;
            currentDisplayNode = nullptr;
        } else {
            head->next = first->next;
            if (currentDisplayNode == first) {
                currentDisplayNode = head->next;
            }
        }
        first->next = nullptr;
        count--;
        return first;
    }

    void InsertAt(BookNode* book, int index) {
        if (book == nullptr) return;
        if (count == 0) {
            head = book;
            book->next = book;
            currentDisplayNode = book;
            count++;
            return;
        }
        if (index < 0) index = NormalizeIndex(index);
        if (index > count) index = count;

        if (index == 0) {
            Insert(book);
            return;
        }
        if (index == count) {
            book->next = head->next;
            head->next = book;
            head = book;
            count++;
            return;
        }
        BookNode* previous = GetNodeAt(index - 1);
        book->next = previous->next;
        previous->next = book;
        count++;
    }

    BookNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        index = NormalizeIndex(index);
        if (index == 0) return Remove();

        BookNode* previous = GetNodeAt(index - 1);
        BookNode* target = previous->next;
        previous->next = target->next;
        if (target == head) head = previous;
        if (currentDisplayNode == target) currentDisplayNode = previous->next;
        
        target->next = nullptr;
        count--;
        return target;
    }

    void Swap(int index1, int index2) {
        if (IsEmpty()) return;
        index1 = NormalizeIndex(index1);
        index2 = NormalizeIndex(index2);
        if (index1 == index2) return;
        BookNode* first = GetNodeAt(index1);
        BookNode* second = GetNodeAt(index2);
        SwapData(first, second);
    }

    void Sort() {
        if (count < 2) return;
        BookNode* current = head->next;
        for (int i = 0; i < count - 1; i++) {
            BookNode* nextNode = current->next;
            for (int j = i + 1; j < count; j++) {
                if (current->bookID > nextNode->bookID) {
                    SwapData(current, nextNode);
                }
                nextNode = nextNode->next;
            }
            current = current->next;
        }
    }

    void Reverse() {
        if (count < 2) return;
        BookNode* oldTail = head;
        BookNode* oldFirst = head->next;
        BookNode* previous = oldTail;
        BookNode* current = oldFirst;
        while (current != oldTail) {
            BookNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        oldTail->next = previous;
        head = oldFirst;
    }

    void MoveToNext() {
        if (IsEmpty()) {
            cout << "Screen Empty: No books to rotate.\n";
            return;
        }
        if (currentDisplayNode == nullptr) currentDisplayNode = head->next;
        else currentDisplayNode = currentDisplayNode->next;
        cout << "Now Displaying on Screen -> [ID: " << currentDisplayNode->bookID << "] " << currentDisplayNode->title << "\n";
    }

    void Print() {
        if (IsEmpty()) {
            cout << "No books in the collection.\n";
            return;
        }
        BookNode* current = head->next;
        cout << "\nIndex\tBook ID\tTitle\n";
        cout << "-----------------------------------\n";
        for (int i = 0; i < count; i++) {
            cout << i << "\t" << current->bookID << "\t" << current->title << endl;
            current = current->next;
        }
        cout << "Total books: " << count << endl;
    }

    ~CircularLinkedList() {
        while (IsNotEmpty()) {
            BookNode* temp = Remove();
            delete temp;
        }
    }
};

BookNode* CreateBookFromInput() {
    int id;
    string title;
    cout << "Enter Book ID: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter numbers only: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);
    BookNode* book = new BookNode;
    book->bookID = id;
    book->title = title;
    book->next = nullptr;
    return book;
}

int main() {
    CircularLinkedList library;
    int choice = 0;

    do {
        cout << "\n========================================";
        cout << "\n  CIRCULAR LIBRARY BOOK DISPLAY SYSTEM  ";
        cout << "\n========================================";
        cout << "\n1. Display All Books";
        cout << "\n2. Insert Book at Head";
        cout << "\n3. Remove Book from Head";
        cout << "\n4. Insert Book at Index";
        cout << "\n5. Remove Book at Index";
        cout << "\n6. Swap Books";
        cout << "\n7. Sort Books by ID";
        cout << "\n8. Reverse Book Collection";
        cout << "\n9. Move to Next Book (Circular Rotation)";
        cout << "\n10. Check Collection Status";
        cout << "\n11. Exit";
        cout << "\n\nEnter your choice: ";

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
            case 2:
                cout << "\n[Insert at Head's Next Node]\n";
                library.Insert(CreateBookFromInput());
                break;
            case 3: {
                BookNode* rem = library.Remove();
                if (rem != nullptr) {
                    cout << "Removed: " << rem->title << endl;
                    delete rem;
                } else cout << "List is empty.\n";
                break;
            }
            case 4: {
                int idx;
                cout << "Enter insertion index: ";
                cin >> idx;
                library.InsertAt(CreateBookFromInput(), idx);
                break;
            }
            case 5: {
                if (library.IsEmpty()) {
                    cout << "List is empty.\n";
                    break;
                }
                int idx;
                cout << "Enter removal index: ";
                cin >> idx;
                BookNode* rem = library.RemoveAt(idx);
                if (rem != nullptr) {
                    cout << "Removed: " << rem->title << endl;
                    delete rem;
                }
                break;
            }
            case 6: {
                int idx1, idx2;
                cout << "Enter first index: ";
                cin >> idx1;
                cout << "Enter second index: ";
                cin >> idx2;
                library.Swap(idx1, idx2);
                break;
            }
            case 7:
                library.Sort();
                cout << "Books sorted by ID successfully.\n";
                break;
            case 8:
                library.Reverse();
                cout << "Collection order reversed.\n";
                break;
            case 9:
                library.MoveToNext();
                break;
            case 10:
                if (library.IsNotEmpty()) cout << "Collection status: Active (" << library.GetCount() << " books)\n";
                else cout << "Collection status: Empty\n";
                break;
            case 11:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Range is 1-11.\n";
        }
    } while (choice != 11);

    return 0;
}
