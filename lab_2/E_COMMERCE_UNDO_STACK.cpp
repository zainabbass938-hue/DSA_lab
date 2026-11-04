#include <iostream>
using namespace std;

struct ActionNode
{
    int actionID;
    string actionType;
    string itemName;
    ActionNode* next;
};

class ActionStack
{
private:
    ActionNode* top;
    int count;

public:
    ActionStack()
    {
        top = nullptr;
        count = 0;
    }

    ActionStack(const ActionStack& other)
    {
        top = nullptr;
        count = 0;
        if (other.top == nullptr)
        {
            return;
        }

        ActionNode* temp = other.top;
        ActionNode* newHead = nullptr;
        ActionNode* newTail = nullptr;

        while (temp != nullptr)
        {
            ActionNode* newNode = new ActionNode();
            newNode->actionID = temp->actionID;
            newNode->actionType = temp->actionType;
            newNode->itemName = temp->itemName;
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

    ActionStack& operator=(const ActionStack& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (top != nullptr)
        {
            ActionNode* temp = top;
            top = top->next;
            delete temp;
        }
        count = 0;

        if (other.top == nullptr)
        {
            return *this;
        }

        ActionNode* temp = other.top;
        ActionNode* newHead = nullptr;
        ActionNode* newTail = nullptr;

        while (temp != nullptr)
        {
            ActionNode* newNode = new ActionNode();
            newNode->actionID = temp->actionID;
            newNode->actionType = temp->actionType;
            newNode->itemName = temp->itemName;
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

    ~ActionStack()
    {
        while (top != nullptr)
        {
            ActionNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void Push(ActionNode* action)
    {
        action->next = top;
        top = action;
        count++;
    }

    ActionNode* Pop()
    {
        if (IsEmpty())
        {
            return nullptr;
        }

        ActionNode* temp = top;
        top = top->next;
        temp->next = nullptr;
        count--;
        return temp;
    }

    ActionNode* GetTopValue()
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
            cout << "No actions to undo." << endl;
            return;
        }

        ActionNode* temp = top;
        cout << "TOP" << endl;
        while (temp != nullptr)
        {
            cout << temp->actionID << " | " << temp->actionType << " | " << temp->itemName << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    ActionStack cartActions;

    ActionNode* a1 = new ActionNode{1, "Add to Cart", "Wireless Mouse", nullptr};
    ActionNode* a2 = new ActionNode{2, "Add to Cart", "Keyboard", nullptr};
    ActionNode* a3 = new ActionNode{3, "Apply Discount", "SAVE10", nullptr};
    ActionNode* a4 = new ActionNode{4, "Remove from Cart", "Keyboard", nullptr};

    cartActions.Push(a1);
    cartActions.Push(a2);
    cartActions.Push(a3);
    cartActions.Push(a4);

    cout << "Action history so far:" << endl;
    cartActions.PrintStack();

    cout << endl << "IsEmpty: " << cartActions.IsEmpty() << endl;
    cout << "IsNotEmpty: " << cartActions.IsNotEmpty() << endl;

    ActionNode* lastAction = cartActions.GetTopValue();
    cout << endl << "Last action performed (GetTopValue): " << lastAction->actionType << " - " << lastAction->itemName << endl;

    cout << endl << "User performs a new action: Add to Cart - Headphones" << endl;
    ActionNode* a5 = new ActionNode{5, "Add to Cart", "Headphones", nullptr};
    cartActions.Push(a5);
    cartActions.PrintStack();

    cout << endl << "User clicks Undo..." << endl;
    ActionNode* undone = cartActions.Pop();
    cout << "Undone: " << undone->actionType << " - " << undone->itemName << endl;
    delete undone;

    cout << endl << "Action history after undo:" << endl;
    cartActions.PrintStack();

    cout << endl << "Testing Copy Constructor:" << endl;
    ActionStack copiedActions(cartActions);
    copiedActions.PrintStack();

    cout << endl << "Testing Assignment Operator:" << endl;
    ActionStack assignedActions;
    assignedActions = cartActions;
    assignedActions.PrintStack();

    cout << endl << "Undoing all remaining actions:" << endl;
    while (cartActions.IsNotEmpty())
    {
        ActionNode* removedAction = cartActions.Pop();
        cout << "Undone: " << removedAction->actionType << " - " << removedAction->itemName << endl;
        delete removedAction;
    }

    cout << endl << "IsEmpty after undoing all: " << cartActions.IsEmpty() << endl;

    cout << endl << "Confirming copiedActions is unaffected (deep copy check):" << endl;
    copiedActions.PrintStack();

    return 0;
}
