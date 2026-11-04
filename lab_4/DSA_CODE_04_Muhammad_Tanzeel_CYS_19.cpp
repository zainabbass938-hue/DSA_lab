#include <iostream>
#include <string>

using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void Add(BookRequestNode* request)
    {
        request->next = nullptr;
        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;
            while (current->next != nullptr && current->next->priority <= request->priority)
            {
                current = current->next;
            }
            request->next = current->next;
            current->next = request;
            if (request->next == nullptr)
            {
                rear = request;
            }
        }
        count++;
    }

    BookRequestNode* Remove()
    {
        if (front == nullptr)
        {
            return nullptr;
        }
        BookRequestNode* request = front;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        request->next = nullptr;
        count--;
        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        BookRequestNode* current = front;
        while (current != nullptr)
        {
            cout << "Student ID: " << current->studentID << endl;
            cout << "Student Name: " << current->studentName << endl;
            cout << "Book ID: " << current->bookID << endl;
            cout << "Book Title: " << current->bookTitle << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "-----------------------------" << endl;
            current = current->next;
        }
    }

    PriorityQueue(const PriorityQueue& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
        BookRequestNode* current = other.front;
        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;
            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;
            Add(newNode);
            current = current->next;
        }
    }

    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
        {
            return *this;
        }
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
        BookRequestNode* current = other.front;
        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;
            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;
            Add(newNode);
            current = current->next;
        }
        return *this;
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

BookRequestNode* CreateRequest(int studentID, string studentName, int bookID, string bookTitle, int priority)
{
    BookRequestNode* request = new BookRequestNode;
    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = nullptr;
    return request;
}

int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====" << endl;
        cout << "1. Add Book Request" << endl;
        cout << "2. Process Highest Priority Request" << endl;
        cout << "3. Display All Requests" << endl;
        cout << "4. Check Queue Status" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 1)
        {
            int sID, bID, prio;
            string sName, bTitle;

            cout << "Enter Student ID: ";
            cin >> sID;
            cin.ignore();
            cout << "Enter Student Name: ";
            getline(cin, sName);
            cout << "Enter Book ID: ";
            cin >> bID;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, bTitle);
            cout << "Enter Priority (1 = Urgent, 2 = Project, 3 = Normal): ";
            cin >> prio;

            BookRequestNode* newRequest = CreateRequest(sID, sName, bID, bTitle, prio);
            requests.Add(newRequest);
            cout << "Request added successfully!" << endl;
        }
        else if (choice == 2)
        {
            if (requests.IsEmpty())
            {
                cout << "No pending requests to process." << endl;
            }
            else
            {
                BookRequestNode* processed = requests.Remove();
                cout << "\n--- Processing Request ---" << endl;
                cout << "Student: " << processed->studentName << " (ID: " << processed->studentID << ")" << endl;
                cout << "Book: " << processed->bookTitle << " (ID: " << processed->bookID << ")" << endl;
                cout << "Priority: " << processed->priority << endl;
                delete processed;
            }
        }
        else if (choice == 3)
        {
            if (requests.IsEmpty())
            {
                cout << "The queue is empty." << endl;
            }
            else
            {
                cout << "\n--- Current Pending Requests ---" << endl;
                requests.PrintQueue();
            }
        }
        else if (choice == 4)
        {
            if (requests.IsEmpty())
            {
                cout << "Queue Status: Empty" << endl;
            }
            else
            {
                cout << "Queue Status: Not Empty (Requests are pending)" << endl;
            }
        }
        else if (choice == 5)
        {
            cout << "Exiting program. Thank you!" << endl;
        }
        else
        {
            cout << "Invalid choice! Please select between 1 and 5." << endl;
        }

    } while (choice != 5);

    return 0;
}
