#include <iostream>
using namespace std;

// Structure representing a clothing item node in a singly linked list
struct ClothingItem {
    int id;            // Unique item ID
    string name;       // Item name
    int quantity;      // Available quantity
    ClothingItem* next; // Pointer to the next item in the list
} *head = NULL;


// Structure representing a node in the stack
struct Node {
    ClothingItem Item; // Stored clothing item data
    Node* link;        // Pointer to the next stack node
};


// Stack class used to support undo functionality
class Stack {
private:
    Node* top;  // Pointer to the top element of the stack
    int size;   // Current stack size

public:
    // Constructor initializes an empty stack
    Stack() {
        top = NULL;
        size = 0;
    }

    // Push a new element onto the stack
    void push(ClothingItem& element) {
        Node* n = new Node;
        n->Item = element;
        n->link = top;
        top = n;
        size++;
        cout << "Item pushed to stack✅\n";
    }

    // Remove the top element from the stack
    void pop() {
        if (top == NULL) {
            cout << "Stack is empty❌\n";
            return;
        }
        Node* temp = top;
        top = top->link;
        size--;
        delete temp;
        cout << "Item popped from stack✅\n";
    }

    // Return the current stack size
    int getSize() {
        return size;
    }

    // Return a pointer to the top stack node
    Node* getTop() {
        return top;
    }

    // Display the top element of the stack
    void topelement() {
        if (top == NULL) {
            cout << "Stack is empty❌\n";
        }
        else {
            cout << "📌 Top element: ID: " << top->Item.id
                 << ", Name: " << top->Item.name
                 << ", Quantity: " << top->Item.quantity << endl;
        }
    }

    // Print the current stack size
    void stacksize() {
        cout << "Stack size: " << size << endl;
    }
};


// Global stack object used for undo operations
Stack undoStack;


// Add a new clothing item to the beginning of the linked list
void addItem(int id, string name, int quantity) {
    ClothingItem* newItem = new ClothingItem;
    newItem->id = id;
    newItem->name = name;
    newItem->quantity = quantity;

    newItem->next = head;
    head = newItem;

    cout << "Item added to inventory✅\n";
    undoStack.push(*newItem); // Save item for undo support
}


// Display all items currently stored in the inventory
void displayItems() {
    ClothingItem* temp = head;

    if (temp == NULL) {
        cout << "Sorry the inventory is empty right now\n";
        return;
    }

    cout << "Current inventory📋:\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << ", Name: " << temp->name
             << ", Quantity: " << temp->quantity << endl;
        temp = temp->next;
    }
}


// Remove the most recently added item from the inventory
void removeLastAdded() {
    if (undoStack.getSize() == 0 || head == NULL) {
        cout << "Nothing to remove❌\n";
        return;
    }

    ClothingItem* temp = head;
    head = head->next;
    delete temp;

    cout << "Last added item removed from inventory✅\n";
    undoStack.pop(); // Update undo stack
}


int main() {
    int choice, id, quantity;
    string name;

    // Main menu loop
    while (true) {
        cout << "\n📌 Clothing Inventory Menu:\n";
        cout << "1. ➕ Add Item\n";
        cout << "2. 📦 Display Inventory\n";
        cout << "3. 🔙 Remove Last Added Item\n";
        cout << "4. 🚪 Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Quantity: ";
                cin >> quantity;
                addItem(id, name, quantity);
                break;

            case 2:
                displayItems();
                break;

            case 3:
                removeLastAdded();
                break;

            case 4:
                cout << "Exiting program👋\n";
                return 0;

            default:
                cout << "Invalid choice see the menu⚠️\n";
        }
    }
}
