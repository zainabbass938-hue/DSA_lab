#include <iostream>
#include <string>

using namespace std;

struct PacketNode
{
    int packetID;
    string protocol;
    string sourceIP;
    PacketNode* left;
    PacketNode* right;

    PacketNode(int id, string proto, string src)
    {
        packetID = id;
        protocol = proto;
        sourceIP = src;
        left = nullptr;
        right = nullptr;
    }
};

class PacketHistory
{
private:
    PacketNode* head;
    PacketNode* tail;
    PacketNode* current;

public:
    PacketHistory()
    {
        head = tail = current = nullptr;
    }

    void CapturePacket(PacketNode* node)
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

    void MoveForward()
    {
        if (current != nullptr && current->right != nullptr)
            current = current->right;
        else
            cout << "End of history logs.\n";
    }

    void MoveBackward()
    {
        if (current != nullptr && current->left != nullptr)
            current = current->left;
        else
            cout << "Beginning of history logs.\n";
    }

    void DisplayCurrentPacket()
    {
        if (current == nullptr)
        {
            cout << "No packets captured yet.\n";
            return;
        }
        cout << "Current Packet: [" << current->packetID << "] " << current->protocol << " from " << current->sourceIP << endl;
    }

    void DeleteCurrentLog()
    {
        if (current == nullptr) return;
        PacketNode* removed = current;
        PacketNode* previous = current->left;
        PacketNode* next = current->right;
        if (previous != nullptr)
            previous->right = next;
        else
            head = next;
        if (next != nullptr)
            next->left = previous;
        else
            tail = previous;
        current = (next != nullptr) ? next : previous;
        delete removed;
    }

    void ViewAllForward()
    {
        cout << "\n--- Network Packet Logs (Oldest to Newest) ---\n";
        for (PacketNode* node = head; node != nullptr; node = node->right)
        {
            cout << "ID: " << node->packetID << " | Proto: " << node->protocol << " | Src: " << node->sourceIP;
            if (node == current)
                cout << " [ACTIVE]";
            cout << endl;
        }
    }

    ~PacketHistory()
    {
        PacketNode* node = head;
        while (node != nullptr)
        {
            PacketNode* next = node->right;
            delete node;
            node = next;
        }
    }
};

int main()
{
    PacketHistory history;
    int choice;
    int id;
    string proto, src;

    history.CapturePacket(new PacketNode(1, "TCP", "192.168.1.5"));
    history.CapturePacket(new PacketNode(2, "UDP", "10.0.0.1"));
    history.CapturePacket(new PacketNode(3, "HTTP", "172.16.254.1"));

    do
    {
        cout << "\n1. View Active Packet\n";
        cout << "2. Move to Next Log\n";
        cout << "3. Move to Previous Log\n";
        cout << "4. Capture New Packet\n";
        cout << "5. Clear Active Packet Log\n";
        cout << "6. Print All Logs\n";
        cout << "7. Close Analyzer\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                history.DisplayCurrentPacket();
                break;
            case 2:
                history.MoveForward();
                break;
            case 3:
                history.MoveBackward();
                break;
            case 4:
                cout << "Packet ID: ";
                cin >> id;
                cin.ignore();
                cout << "Protocol: ";
                getline(cin, proto);
                cout << "Source IP: ";
                getline(cin, src);
                history.CapturePacket(new PacketNode(id, proto, src));
                break;
            case 5:
                history.DeleteCurrentLog();
                break;
            case 6:
                history.ViewAllForward();
                break;
            case 7:
                break;
        }
    } while (choice != 7);

    return 0;
}
