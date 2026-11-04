#include <iostream>
#include <string>
#include <utility>
#include <limits>

using namespace std;

struct SecurityNode {
    int targetPort;
    string statusText;
    SecurityNode* next;
};

class CircularSecurityScanner {
private:
    SecurityNode* head;
    int count;
    SecurityNode* activeTrackPointer;

    SecurityNode* GetNodeAt(int index) {
        if (head == nullptr) return nullptr;
        SecurityNode* current = head->next;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }

    void SwapData(SecurityNode* a, SecurityNode* b) {
        swap(a->targetPort, b->targetPort);
        swap(a->statusText, b->statusText);
    }

    int NormalizeIndex(int index) {
        if (count == 0) return 0;
        return ((index % count) + count) % count;
    }

public:
    CircularSecurityScanner() {
        head = nullptr;
        count = 0;
        activeTrackPointer = nullptr;
    }

    bool IsEmpty() { return count == 0; }
    bool IsNotEmpty() { return count > 0; }
    int GetCount() { return count; }

    void Insert(SecurityNode* target) {
        if (target == nullptr) return;
        if (head == nullptr) {
            head = target;
            target->next = target;
            activeTrackPointer = target;
        } else {
            target->next = head->next;
            head->next = target;
        }
        count++;
    }

    SecurityNode* Remove() {
        if (IsEmpty()) return nullptr;
        SecurityNode* first = head->next;
        if (first == head) {
            head = nullptr;
            activeTrackPointer = nullptr;
        } else {
            head->next = first->next;
            if (activeTrackPointer == first) {
                activeTrackPointer = head->next;
            }
        }
        first->next = nullptr;
        count--;
        return first;
    }

    void InsertAt(SecurityNode* target, int index) {
        if (target == nullptr) return;
        if (count == 0) {
            head = target;
            target->next = target;
            activeTrackPointer = target;
            count++;
            return;
        }
        if (index < 0) index = NormalizeIndex(index);
        if (index > count) index = count;

        if (index == 0) {
            Insert(target);
            return;
        }
        if (index == count) {
            target->next = head->next;
            head->next = target;
            head = target;
            count++;
            return;
        }
        SecurityNode* previous = GetNodeAt(index - 1);
        target->next = previous->next;
        previous->next = target;
        count++;
    }

    SecurityNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        index = NormalizeIndex(index);
        if (index == 0) return Remove();

        SecurityNode* previous = GetNodeAt(index - 1);
        SecurityNode* target = previous->next;
        previous->next = target->next;
        if (target == head) head = previous;
        if (activeTrackPointer == target) activeTrackPointer = previous->next;

        target->next = nullptr;
        count--;
        return target;
    }

    void Swap(int index1, int index2) {
        if (IsEmpty()) return;
        index1 = NormalizeIndex(index1);
        index2 = NormalizeIndex(index2);
        if (index1 == index2) return;
        SecurityNode* first = GetNodeAt(index1);
        SecurityNode* second = GetNodeAt(index2);
        SwapData(first, second);
    }

    void Sort() {
        if (count < 2) return;
        SecurityNode* current = head->next;
        for (int i = 0; i < count - 1; i++) {
            SecurityNode* nextNode = current->next;
            for (int j = i + 1; j < count; j++) {
                if (current->targetPort > nextNode->targetPort) {
                    SwapData(current, nextNode);
                }
                nextNode = nextNode->next;
            }
            current = current->next;
        }
    }

    void Reverse() {
        if (count < 2) return;
        SecurityNode* oldTail = head;
        SecurityNode* oldFirst = head->next;
        SecurityNode* previous = oldTail;
        SecurityNode* current = oldFirst;
        while (current != oldTail) {
            SecurityNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        oldTail->next = previous;
        head = oldFirst;
    }

    void ExecuteScanCycle(int passes) {
        if (IsEmpty()) {
            cout << "Scanner Queue Empty.\n";
            return;
        }
        if (activeTrackPointer == nullptr) activeTrackPointer = head->next;
        cout << "\n--- Starting Continuous Threat Scan Cycle ---\n";
        for (int i = 0; i < passes; i++) {
            cout << "Scanning Node Address [" << activeTrackPointer << "] -> Monitoring Target Port: " 
                 << activeTrackPointer->targetPort << " Status: [" << activeTrackPointer->statusText << "]\n";
            activeTrackPointer = activeTrackPointer->next;
        }
        cout << "--- Cycle Completed (Loop continues safely without hitting nullptr) ---\n";
    }

    void Print() {
        if (IsEmpty()) {
            cout << "No active nodes monitored.\n";
            return;
        }
        SecurityNode* current = head->next;
        cout << "\nIndex\tTarget Port\tSecurity Status\n";
        cout << "-------------------------------------------\n";
        for (int i = 0; i < count; i++) {
            cout << i << "\t" << current->targetPort << "\t\t" << current->statusText << endl;
            current = current->next;
        }
        cout << "Total Active Monitoring Items: " << count << endl;
    }

    ~CircularSecurityScanner() {
        while (IsNotEmpty()) {
            SecurityNode* temp = Remove();
            delete temp;
        }
    }
};

SecurityNode* GetNodeInput() {
    int port;
    string status;
    cout << "Enter Security Port/ID: ";
    while (!(cin >> port)) {
        cout << "Invalid entry. Enter numeric port details: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter Port Security Assessment Status: ";
    cin >> status;
    SecurityNode* node = new SecurityNode;
    node->targetPort = port;
    node->statusText = status;
    node->next = nullptr;
    return node;
}

int main() {
    CircularSecurityScanner scanner;
    int choice = 0;

    do {
        cout << "\n=========================================";
        cout << "\n   CYBERSECURITY CYCLIC MONITORING APP   ";
        cout << "\n=========================================";
        cout << "\n1. View All Monitored System Points";
        cout << "\n2. Insert Security Point at Front Queue";
        cout << "\n3. Remove Front Security Target Node";
        cout << "\n4. Insert Security Target Point at Index";
        cout << "\n5. Remove Security Target Point at Index";
        cout << "\n6. Swap Nodes";
        cout << "\n7. Sort Log Points by Target ID";
        cout << "\n8. Reverse Scanner Processing Sequence";
        cout << "\n9. Run Simulated Continuous Inspection Loop";
        cout << "\n10. Check Track Vector Activity Status";
        cout << "\n11. Terminate Terminal Monitor";
        cout << "\n\nEnter Selection: ";

        if (!(cin >> choice)) {
            cout << "Invalid entry. Select options between 1 and 11.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: scanner.Print(); break;
            case 2: scanner.Insert(GetNodeInput()); break;
            case 3: {
                SecurityNode* rem = scanner.Remove();
                if (rem != nullptr) { delete rem; cout << "Front node cleared.\n"; }
                break;
            }
            case 4: {
                int idx; cout << "Enter index: "; cin >> idx;
                scanner.InsertAt(GetNodeInput(), idx);
                break;
            }
            case 5: {
                if (scanner.IsEmpty()) break;
                int idx; cout << "Enter index to purge: "; cin >> idx;
                SecurityNode* rem = scanner.RemoveAt(idx);
                if (rem != nullptr) delete rem;
                break;
            }
            case 6: {
                int i1, i2; cout << "Index 1: "; cin >> i1; cout << "Index 2: "; cin >> i2;
                scanner.Swap(i1, i2);
                break;
            }
            case 7: scanner.Sort(); break;
            case 8: scanner.Reverse(); break;
            case 9: {
                int passes;
                cout << "Enter simulation trace counts (e.g. 10 to demonstrate circular wrap): ";
                cin >> passes;
                scanner.ExecuteScanCycle(passes);
                break;
            }
            case 10:
                if (scanner.IsNotEmpty()) cout << "Active Node Count: " << scanner.GetCount() << endl;
                else cout << "Queue Inactive.\n";
                break;
            case 11: break;
        }
    } while (choice != 11);

    return 0;
}
