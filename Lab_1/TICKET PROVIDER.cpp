#include <iostream>
#include <string>
using namespace std;

struct TicketNode
{
    int ticketID;
    string passengerName;
    string destination;
    TicketNode* next;
};

class Queue
{
private:
    TicketNode* front;
    TicketNode* rear;
    int count;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void EnQueue(TicketNode* request)
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
        cout << "\n[SUCCESS] Ticket request added successfully!\n";
    }

    TicketNode* DeQueue()
    {
        if (front == nullptr)
            return nullptr;

        TicketNode* request = front;
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

        cout << "\n--- Current Ticket Counter Queue (FRONT -> REAR) ---\n";
        TicketNode* current = front;
        int position = 1;
        while (current != nullptr)
        {
            cout << position << ". Ticket ID: " << current->ticketID
                 << " | Name: " << current->passengerName
                 << " | Destination: " << current->destination << endl;
            current = current->next;
            position++;
        }
        cout << "---------------------------------------------------\n";
    }

    ~Queue()
    {
        while (front != nullptr)
        {
            TicketNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

int main()
{
    Queue ticketQueue;
    int choice;

    do
    {
        cout << "\n===== Online Ticket Counter System =====\n";
        cout << "1. Add Passenger Request\n";
        cout << "2. Serve Next Passenger\n";
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
            TicketNode* newPassenger = new TicketNode;

            cout << "\nEnter Ticket ID: ";
            cin >> newPassenger->ticketID;
            cin.ignore();

            cout << "Enter Passenger Name: ";
            getline(cin, newPassenger->passengerName);

            cout << "Enter Destination: ";
            getline(cin, newPassenger->destination);

            ticketQueue.EnQueue(newPassenger);
            break;
        }
        case 2:
        {
            TicketNode* served = ticketQueue.DeQueue();
            if (served != nullptr)
            {
                cout << "\n--- Serving Passenger ---\n";
                cout << "Ticket ID   : " << served->ticketID << endl;
                cout << "Name        : " << served->passengerName << endl;
                cout << "Destination : " << served->destination << endl;
                cout << "-------------------------\n";

                delete served;
            }
            else
            {
                cout << "\nNo pending passengers to serve!\n";
            }
            break;
        }
        case 3:
            ticketQueue.PrintQueue();
            break;

        case 4:
            if (ticketQueue.IsEmpty())
                cout << "\nStatus: Queue is EMPTY.\n";
            else
                cout << "\nStatus: Queue is NOT empty.\n";
            break;

        case 5:
            if (ticketQueue.IsNotEmpty())
                cout << "\nStatus: Queue is NOT empty (Passengers waiting).\n";
            else
                cout << "\nStatus: Queue is EMPTY.\n";
            break;

        case 6:
            cout << "\nExiting System. Good Bye!\n";
            break;

        default:
            cout << "\nInvalid choice! Please enter between 1 and 6.\n";
        }

    } while (choice != 6);

    return 0;
}