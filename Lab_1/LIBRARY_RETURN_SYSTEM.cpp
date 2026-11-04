#include <iostream>
using namespace std;

struct BookNode
{
    int bookID;
    string title;
    string author;
    BookNode* next;
};

class Stack
{
private:
    BookNode* top;
    int count;

public:
    Stack()
    {
        top = nullptr;
        count = 0;
    }

    Stack(const Stack& other)
    {
        top = nullptr;
        count = 0;
        if (other.top == nullptr)
        {
            return;
        }

        BookNode* temp = other.top;
        BookNode* newHead = nullptr;
        BookNode* newTail = nullptr;

        while (temp != nullptr)
        {
            BookNode* newNode = new BookNode();
            newNode->bookID = temp->bookID;
            newNode->title = temp->title;
            newNode->author = temp->author;
            newNode->next = nullptr;

            if (newHead == nullptr)
            {
                newHead = newNode;
                newTail = newNode;
            }
            else
            {
                newTail->next = newNode;
                newTail = newNode;
            }

            temp = temp->next;
        }

        top = newHead;
        count = other.count;
    }

    Stack& operator=(const Stack& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (top != nullptr)
        {
            BookNode* temp = top;
            top = top->next;
            delete temp;
        }
        count = 0;

        if (other.top == nullptr)
        {
            return *this;
        }

        BookNode* temp = other.top;
        BookNode* newHead = nullptr;
        BookNode* newTail = nullptr;

        while (temp != nullptr)
        {
            BookNode* newNode = new BookNode();
            newNode->bookID = temp->bookID;
            newNode->title = temp->title;
            newNode->author = temp->author;
            newNode->next = nullptr;

            if (newHead == nullptr)
            {
                newHead = newNode;
                newTail = newNode;
            }
            else
            {
                newTail->next = newNode;
                newTail = newNode;
            }

            temp = temp->next;
        }

        top = newHead;
        count = other.count;
        return *this;
    }

    ~Stack()
    {
        while (top != nullptr)
        {
            BookNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void Push(BookNode* book)
    {
        book->next = top;
        top = book;
        count++;
    }

    BookNode* Pop()
    {
        if (IsEmpty())
        {
            return nullptr;
        }

        BookNode* temp = top;
        top = top->next;
        temp->next = nullptr;
        count--;
        return temp;
    }

    BookNode* GetTopValue()
    {
        if (IsEmpty())
        {
            return nullptr;
        }
        return top;
    }

    bool IsEmpty()
    {
        return top == nullptr;
    }

    bool IsNotEmpty()
    {
        return top != nullptr;
    }

    void PrintStack()
    {
        if (IsEmpty())
        {
            cout << "The pile is empty." << endl;
            return;
        }

        BookNode* temp = top;
        cout << "TOP" << endl;
        while (temp != nullptr)
        {
            cout << temp->bookID << " | " << temp->title << " | " << temp->author << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    Stack libraryPile;

    BookNode* b1 = new BookNode{101, "PF", "Author1", nullptr};
    BookNode* b2 = new BookNode{102, "OOP", "Author2", nullptr};
    BookNode* b3 = new BookNode{103, "DBMS", "Author3", nullptr};
    BookNode* b4 = new BookNode{104, "DSA", "Author4", nullptr};

    libraryPile.Push(b1);
    libraryPile.Push(b2);
    libraryPile.Push(b3);
    libraryPile.Push(b4);

    cout << "Initial Pile:" << endl;
    libraryPile.PrintStack();

    cout << endl << "IsEmpty: " << libraryPile.IsEmpty() << endl;
    cout << "IsNotEmpty: " << libraryPile.IsNotEmpty() << endl;

    BookNode* topBook = libraryPile.GetTopValue();
    cout << endl << "Top book (GetTopValue): " << topBook->title << endl;

    cout << endl << "Returning a new book: Artificial Intelligence" << endl;
    BookNode* b5 = new BookNode{105, "Artificial Intelligence", "Author5", nullptr};
    libraryPile.Push(b5);
    libraryPile.PrintStack();

    cout << endl << "Processing (Pop) the top book..." << endl;
    BookNode* processed = libraryPile.Pop();
    cout << "Processed: " << processed->title << endl;
    delete processed;

    cout << endl << "Pile after processing:" << endl;
    libraryPile.PrintStack();

    cout << endl << "Testing Copy Constructor:" << endl;
    Stack copiedPile(libraryPile);
    copiedPile.PrintStack();

    cout << endl << "Testing Assignment Operator:" << endl;
    Stack assignedPile;
    assignedPile = libraryPile;
    assignedPile.PrintStack();

    cout << endl << "Popping all books from original pile:" << endl;
    while (libraryPile.IsNotEmpty())
    {
        BookNode* removed = libraryPile.Pop();
        cout << "Removed: " << removed->title << endl;
        delete removed;
    }

    cout << endl << "IsEmpty after popping all: " << libraryPile.IsEmpty() << endl;

    cout << endl << "Confirming copiedPile is unaffected (deep copy check):" << endl;
    copiedPile.PrintStack();

    return 0;
}
