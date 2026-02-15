#include <iostream>
using namespace std;



struct ClothingItem { // هيكل يمثل قطعة الملابس
    int id; // ID للقطعة
    string name; // اسم القطعة   
    int quantity; // الكمية
    ClothingItem* next; 
}*head = NULL; 


struct Node { // هيكل يمثل العناصر في الستاك
    ClothingItem Item; // بيانات العنصر من نوع ClothingItem
    Node* link; 
};


class Stack {
private:
    Node* top;  
    int size; 

public:
    Stack() {  
    top = NULL; 
    size = 0;  
    }

    
    void push(ClothingItem& element) { // دالة لإضافة عنصر إلى الستاك
    Node* n = new Node; 
    n->Item = element; 
    n->link = top; 
    top = n; 
    size++; 
    cout << "Item pushed to stack✅\n";
    }

    
    void pop() { // دالة لإزالة اخر عنصر من الستاك
    if (top == NULL) {  // إذا كان الستاك فاضي
    cout << "Stack is empty❌\n";
    return;
    }
    Node* temp = top; 
    top = top->link;  
    size--; 
    delete temp; 
    cout << "Item popped from stack✅\n";
    }

    
    int getSize() {
    return size;
    }

    
    Node* getTop() {
    return top;
    }

    
    void topelement() { // دالة لطباعة اخر عنصر في الستاك
    if (top == NULL) {
    cout << "Stack is empty❌\n";
    } 
    else {
    cout << "📌 Top element: ID: " << top->Item.id << ", Name: " << top->Item.name << ", Quantity: " << top->Item.quantity << endl;
    }
    }

    
    void stacksize() {
    cout << "Stack size: " << size << endl;
    }
};




Stack undoStack; // لاستخدامه في استدعاء دوال كلاس الستاك global object


void addItem(int id, string name, int quantity) { // دالة لإضافة قطعة ملابس إلى بداية القائمة
ClothingItem* newItem = new ClothingItem; 
newItem->id = id; 
newItem->name = name; 
newItem->quantity = quantity; 
    
newItem->next = head; 
head = newItem; 

cout << "Item added to inventory✅\n";
undoStack.push(*newItem); // إضافة القطعة إلى الستاك
}


void displayItems() { // دالة لعرض كل العناصر في المخزون
ClothingItem* temp = head; 
if (temp == NULL) { // إذا كانت القائمة فاضية
cout << "Sorry the inventory is empty right now\n";
return;
}

cout << "Current inventory📋:\n"; 
while (temp != NULL) { // عرض العناصر حتى الوصول إلى نهاية القائمة
cout << "ID: " << temp->id << ", Name: " << temp->name << ", Quantity: " << temp->quantity << endl;
temp = temp->next; 
}
}


void removeLastAdded() { // دالة لحذف آخر قطعة مضافة
if (undoStack.getSize() == 0 || head == NULL) { // إذا كان الستاك أو القائمة فاضية
cout << "Nothing to remove❌\n"; 
return;
}

ClothingItem* temp = head; 
head = head->next; 
delete temp; 
cout << "Last added item removed from inventory✅\n";
undoStack.pop(); // إزالة العنصر من الستاك بعد
}




int main() {
    int choice, id, quantity;
    string name;

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
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Name: "; cin >> name;
            cout << "Enter Quantity: "; cin >> quantity;
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
            cout << "Invalid choice see the menu⚠️\n"; // حالة اختيار غير صحيح
        }
    }
}
