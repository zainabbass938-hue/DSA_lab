#include <iostream>
#include <string>
#include <utility>
#include <limits>

using namespace std;

struct RuleNode {
    int ruleID;
    string ipAddress;
    int priority;
    RuleNode* next;
};

class FirewallManager {
private:
    RuleNode* head;
    int count;

    RuleNode* GetNodeAt(int index) {
        RuleNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++)
            current = current->next;
        return current;
    }

    void CopyRuleData(RuleNode* a, RuleNode* b) {
        swap(a->ruleID, b->ruleID);
        swap(a->ipAddress, b->ipAddress);
        swap(a->priority, b->priority);
    }

public:
    FirewallManager() {
        head = nullptr;
        count = 0;
    }

    void Insert(RuleNode* rule) {
        if (rule == nullptr) return;
        rule->next = head;
        head = rule;
        count++;
    }

    RuleNode* Remove() {
        if (IsEmpty()) return nullptr;
        RuleNode* rule = head;
        head = head->next;
        rule->next = nullptr;
        count--;
        return rule;
    }

    bool IsEmpty() { return head == nullptr; }
    int GetCount() { return count; }

    void InsertAt(RuleNode* rule, int index) {
        if (rule == nullptr) return;
        if (index < 0) index = 0;
        if (index > count) index = count;

        if (index == 0) {
            Insert(rule);
            return;
        }

        RuleNode* previous = GetNodeAt(index - 1);
        rule->next = previous->next;
        previous->next = rule;
        count++;
    }

    RuleNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        if (index < 0) index = 0;
        if (index >= count) index = count - 1;

        if (index == 0) return Remove();

        RuleNode* previous = GetNodeAt(index - 1);
        RuleNode* rule = previous->next;
        previous->next = rule->next;
        rule->next = nullptr;
        count--;
        return rule;
    }

    void Swap(int index1, int index2) {
        if (index1 < 0 || index1 >= count || index2 < 0 || index2 >= count) return;
        if (index1 == index2) return;

        RuleNode* first = GetNodeAt(index1);
        RuleNode* second = GetNodeAt(index2);
        CopyRuleData(first, second);
    }

    void Sort() {
        for (RuleNode* i = head; i != nullptr; i = i->next) {
            for (RuleNode* j = i->next; j != nullptr; j = j->next) {
                if (i->priority > j->priority) {
                    CopyRuleData(i, j);
                }
            }
        }
    }

    void Reverse() {
        RuleNode* previous = nullptr;
        RuleNode* current = head;
        RuleNode* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }

    void Print() {
        RuleNode* current = head;
        int index = 0;
        cout << "\nIndex\tRule ID\tIP Address\tPriority\n";
        cout << "-------------------------------------------\n";
        while (current != nullptr) {
            cout << index << "\t" << current->ruleID << "\t" << current->ipAddress << "\t" << current->priority << endl;
            current = current->next;
            index++;
        }
        cout << "Total Active Rules: " << count << endl;
    }

    ~FirewallManager() {
        while (!IsEmpty()) {
            RuleNode* temp = Remove();
            delete temp;
        }
    }
};

RuleNode* CreateRuleFromInput() {
    int id;
    string ip;
    int priority;

    cout << "Enter Rule ID (Integer): ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter Target IP Address: ";
    cin >> ip;

    cout << "Enter Priority Level (1=Highest, 5=Lowest): ";
    while (!(cin >> priority)) {
        cout << "Invalid input. Enter a number (1-5): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    RuleNode* rule = new RuleNode;
    rule->ruleID = id;
    rule->ipAddress = ip;
    rule->priority = priority;
    rule->next = nullptr;
    return rule;
}

int main() {
    FirewallManager firewall;
    int choice = 0;

    do {
        cout << "\n=================================";
        cout << "\n    FIREWALL RULE MANAGER (ACL)  ";
        cout << "\n=================================";
        cout << "\n1. Display Active Rules";
        cout << "\n2. Insert Rule at Head";
        cout << "\n3. Insert Rule at Specific Priority Index";
        cout << "\n4. Remove Rule from Head";
        cout << "\n5. Remove Rule from Specific Index";
        cout << "\n6. Swap Two Rules by Index";
        cout << "\n7. Sort Rules by Priority Level";
        cout << "\n8. Reverse Rule Execution Order";
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
                firewall.Print();
                break;

            case 2: {
                cout << "\n[Inserting Rule at Head]\n";
                RuleNode* newRule = CreateRuleFromInput();
                firewall.Insert(newRule);
                cout << "Rule successfully activated at the top.\n";
                break;
            }

            case 3: {
                cout << "\n[Inserting Rule at Specific Index]\n";
                int idx;
                cout << "Enter index (Current rules: " << firewall.GetCount() << "): ";
                cin >> idx;
                RuleNode* newRule = CreateRuleFromInput();
                firewall.InsertAt(newRule, idx);
                cout << "Rule successfully inserted at index " << idx << ".\n";
                break;
            }

            case 4: {
                RuleNode* removed = firewall.Remove();
                if (removed != nullptr) {
                    cout << "\nSuccessfully deactivated rule: " << removed->ipAddress << " (ID: " << removed->ruleID << ")\n";
                    delete removed;
                } else {
                    cout << "\nNo active rules to remove.\n";
                }
                break;
            }

            case 5: {
                if (firewall.IsEmpty()) {
                    cout << "\nNo active rules to remove.\n";
                    break;
                }
                int idx;
                cout << "\nEnter index to remove (0 to " << firewall.GetCount() - 1 << "): ";
                cin >> idx;
                RuleNode* removed = firewall.RemoveAt(idx);
                if (removed != nullptr) {
                    cout << "Successfully deactivated rule at index " << idx << ": " << removed->ipAddress << "\n";
                    delete removed;
                }
                break;
            }

            case 6: {
                if (firewall.GetCount() < 2) {
                    cout << "\nYou need at least 2 rules to perform a swap operation.\n";
                    break;
                }
                int idx1, idx2;
                cout << "\nEnter first index to swap: ";
                cin >> idx1;
                cout << "Enter second index to swap: ";
                cin >> idx2;
                firewall.Swap(idx1, idx2);
                cout << "Rules at index " << idx1 << " and index " << idx2 << " swapped successfully.\n";
                break;
            }

            case 7:
                firewall.Sort();
                cout << "\nRules sorted by priority level (Highest Priority First).\n";
                break;

            case 8:
                firewall.Reverse();
                cout << "\nRule matching sequence reversed successfully.\n";
                break;

            case 9:
                cout << "\nExiting Firewall Manager. Systems Secured!\n";
                break;

            default:
                cout << "\nInvalid choice. Please select between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
