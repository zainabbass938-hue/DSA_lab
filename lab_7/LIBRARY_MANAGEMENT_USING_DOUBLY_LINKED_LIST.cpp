#include <iostream>
#include <string>

using namespace std;

struct dNode
{
    int bookID;
    string title;
    dNode* left;
    dNode* right;

    dNode(int id, string name)
    {
        bookID = id;
        title = name;
        left = nullptr;
        right = nullptr;
    }
};

class DoublyLinkedList
{
private:
    dNode* head;
    dNode* tail;
    dNode* current;

public:
    DoublyLinkedList()
    {
        head = tail = current = nullptr;
    }

    void InsertRight(dNode* node)
    {
        if (node == nullptr) return;
        node->left = tail;
        node->right = nullptr;
        if (tail != nullptr)
            tail->right = node;
        else
            head = node;
        tail = node;
        if (current == nullptr)
            current = node;
    }

    void Next()
    {
        if (current != nullptr && current->right != nullptr)
            current = current->right;
        else
            cout << "No next book.\n";
    }

    void Previous()
    {
        if (current != nullptr && current->left != nullptr)
            current = current->left;
        else
            cout << "No previous book.\n";
    }

    void PrintCurrent()
    {
        if (current == nullptr)
        {
            cout << "The borrowing session is empty.\n";
            return;
        }
        cout << "Current Book: " << current->bookID << " - " << current->title << endl;
    }

    void InsertAfterCurrent(dNode* node)
    {
        if (node == nullptr) return;
        if (current == nullptr)
        {
            InsertRight(node);
            return;
        }
        node->left = current;
        node->right = current->right;
        if (current->right != nullptr)
            current->right->left = node;
        else
            tail = node;
        current->right = node;
    }

    dNode* RemoveCurrent()
    {
        if (current == nullptr) return nullptr;
        dNode* removed = current;
        dNode* previous = current->left;
        dNode* next = current->right;
        if (previous != nullptr)
            previous->right = next;
        else
            head = next;
        if (next != nullptr)
            next->left = previous;
        else
            tail = previous;
        current = (next != nullptr) ? next : previous;
        removed->left = nullptr;
        removed->right = nullptr;
        return removed;
    }

    void PrintForward()
    {
        cout << "\nBorrowing Session (Forward):\n";
        for (dNode* node = head; node != nullptr; node = node->right)
        {
            cout << node->bookID << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << endl;
        }
    }

    void PrintBackward()
    {
        cout << "\nBorrowing Session (Backward):\n";
        for (dNode* node = tail; node != nullptr; node = node->left)
        {
            cout << node->bookID << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << endl;
        }
    }

    ~DoublyLinkedList()
    {
        dNode* node = head;
        while (node != nullptr)
        {
            dNode* next = node->right;
            delete node;
            node = next;
        }
    }
};

int main()
{
    DoublyLinkedList session;
    int choice;
    int id;
    string title;

    session.InsertRight(new dNode(101, "Data Structures"));
    session.InsertRight(new dNode(102, "Database Systems"));
    session.InsertRight(new dNode(103, "Operating Systems"));

    do
    {
        cout << "\n1. Display Current Book\n";
        cout << "2. Move to Next Book\n";
        cout << "3. Move to Previous Book\n";
        cout << "4. Insert Book at the End\n";
        cout << "5. Insert Book After Current Book\n";
        cout << "6. Remove Current Book\n";
        cout << "7. Display Session from First to Last\n";
        cout << "8. Display Session from Last to First\n";
        cout << "9. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                session.PrintCurrent();
                break;
            case 2:
                session.Next();
                break;
            case 3:
                session.Previous();
                break;
            case 4:
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                session.InsertRight(new dNode(id, title));
                break;
            case 5:
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                session.InsertAfterCurrent(new dNode(id, title));
                break;
            case 6:
                {
                    dNode* removed = session.RemoveCurrent();
                    if (removed != nullptr)
                        delete removed;
                }
                break;
            case 7:
                session.PrintForward();
                break;
            case 8:
                session.PrintBackward();
                break;
            case 9:
                break;
        }
    } while (choice != 9);

    return 0;
}
