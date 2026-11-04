#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    BookRequestNode* next;
};

class Queue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void EnQueue(BookRequestNode* request)
    {
        request->next = nullptr;
        if (rear == nullptr)
        {
            front = rear = request;
        }
        else
        {
            rear->next = request;
            rear = request;
        }
        count++;
        cout << "\n[SUCCESS] Book request added successfully!\n";
    }

    BookRequestNode* DeQueue()
    {
        if (front == nullptr)
            return nullptr;

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

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
        if (IsEmpty())
        {
            cout << "\nQueue is currently EMPTY!\n";
            return;
        }

        cout << "\n--- Pending Book Requests (FRONT -> REAR) ---\n";
        BookRequestNode* current = front;
        int position = 1;
        while (current != nullptr)
        {
            cout << position << ". Student ID: " << current->studentID
                 << " | Name: " << current->studentName
                 << " | Book ID: " << current->bookID
                 << " | Title: " << current->bookTitle << endl;
            current = current->next;
            position++;
        }
        cout << "----------------------------------------------\n";
    }

    ~Queue()
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

int main()
{
    Queue requestQueue;
    int choice;

    do
    {
        cout << "\n===== Library Book Request Management System =====\n";
        cout << "1. Add Book Request\n";
        cout << "2. Serve Next Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check if Queue is Empty\n";
        cout << "5. Check if Queue is Not Empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            BookRequestNode* newRequest = new BookRequestNode;

            cout << "\nEnter Student ID: ";
            cin >> newRequest->studentID;
            cin.ignore();

            cout << "Enter Student Name: ";
            getline(cin, newRequest->studentName);

            cout << "Enter Book ID: ";
            cin >> newRequest->bookID;
            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, newRequest->bookTitle);

            requestQueue.EnQueue(newRequest);
            break;
        }
        case 2:
        {
            BookRequestNode* served = requestQueue.DeQueue();
            if (served != nullptr)
            {
                cout << "\n--- Serving Request ---\n";
                cout << "Student ID   : " << served->studentID << endl;
                cout << "Student Name : " << served->studentName << endl;
                cout << "Book ID      : " << served->bookID << endl;
                cout << "Book Title   : " << served->bookTitle << endl;
                cout << "-----------------------\n";

                delete served;
            }
            else
            {
                cout << "\nNo pending requests to serve!\n";
            }
            break;
        }
        case 3:
            requestQueue.PrintQueue();
            break;

        case 4:
            if (requestQueue.IsEmpty())
                cout << "\nStatus: Queue is EMPTY.\n";
            else
                cout << "\nStatus: Queue is NOT empty.\n";
            break;

        case 5:
            if (requestQueue.IsNotEmpty())
                cout << "\nStatus: Queue is NOT empty (Requests pending).\n";
            else
                cout << "\nStatus: Queue is EMPTY.\n";
            break;

        case 6:
            cout << "\nExiting Program. Good Bye!\n";
            break;

        default:
            cout << "\nInvalid choice! Please enter a number between 1 and 6.\n";
        }

    } while (choice != 6);

    return 0;
}