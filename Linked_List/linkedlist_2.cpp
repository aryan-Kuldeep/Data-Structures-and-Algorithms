// Implementation of doubly linked list with head and tail pointers

#include<iostream>
using namespace std;

class Node {
    Node* prev;    // Pointer to previous node
    int data;      // Stores value
    Node* next;    // Pointer to next node

public:
    // Constructor to initialize a node
    Node(int val){  
        data = val;
        prev = next = NULL;
    }   
};

class List {
    Node* head;    // Points to first node
    Node* tail;    // Points to last node
public:
    // Constructor: initialize empty list
    DoublyList(){
        head = tail = NULL;
    }

    //1. Insert at the beginning of the list
    void push_front(int val){
        Node* new_Node = new Node(val); 
        // If list is empty, new node is both head and tail
        if(head == NULL){
            head = tail = new_Node;
            return;
        }else{
            // Link new node before current head
            new_Node->next = head;
            head->prev = new_Node;
            head = new_Node;
        }
    }

    //2. Insert at the end of the list
    void push_back(int val){
        Node* new_Node = new Node(val);
        // If list is empty, new node is both head and tail 
        if(tail == NULL){
            head = tail = new_Node;
            return;
        }else{
            // Link new node after current tail
            tail->next = new_Node;
            new_Node->prev = tail;
            tail = new_Node;
        }
    }

    //3. Remove node from the beginning
    void pop_front(){
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        }else if(head == tail){
            // Only one node in list
            delete head;
            head = tail = NULL;
        }else{
            // Move head to next node and delete old head
            Node* temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
        }
    }

    //4. Remove node from the end
    void pop_back(){
        if(tail == NULL){
            cout << "List is empty" << endl;        
            return;
        }else if(head == tail){
            // Only one node in list
            delete head;
            head = tail = NULL;
        }else{
            // Move tail to previous node and delete old tail
            Node* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
        }
    }

    //5. Insert node at given 1-based position
    void insertAtPosition(int val, int pos){
        Node* new_Node = new Node(val); 
        // If inserting at the beginning
        if(pos == 1){
            push_front(val);
            return;
        } else{
            // Traverse to node just before the position
            Node* temp = head;
            for(int i = 1; i < pos - 1 && temp != NULL; i++){
                temp = temp->next;
            }

            // If position is beyond current length, insert at end
            if(temp == NULL){
                push_back(val);
                return;
            }

            // Link new node in its position
            new_Node->next = temp->next;
            new_Node->prev = temp;

            if(temp->next != NULL){
                temp->next->prev = new_Node;
            } else {
                // If inserting at the end, update tail
                tail = new_Node;
            }
            
            temp->next = new_Node;
        }
    }

    //6. Delete node at given 1-based position
    void deleteAtPosition(int pos){
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        }
        // If deleting first node
        if(pos == 1){   
            pop_front();
            return;
        } else{
            // Traverse to node just before the one to be deleted
            Node* temp = head;
            for(int i = 1; i < pos - 1 && temp != NULL; i++){
                temp = temp->next;
            }

            // If position is beyond current length
            if(temp == NULL || temp->next == NULL){
                cout << "Position out of bounds" << endl;
                return;
            }

            // Node to be deleted
            Node* nodeToDelete = temp->next;

            // Link previous node to next node
            temp->next = nodeToDelete->next;

            if(nodeToDelete->next != NULL){
                nodeToDelete->next->prev = temp;
            } else {
                // If deleting last node, update tail
                tail = temp;
            }

            delete nodeToDelete;
        }
    }

    //7. Search for a value and return its position (1-based), or -1 if not found
    int search(int val){
        Node* temp = head;
        int pos = 1;
        while (temp != NULL){
            if(temp->data == val){
                return pos;
            }
            temp = temp->next;
            pos++;
        }
        return -1; // Not found
    }

    //8. Detect if there is a cycle in the list
    bool hasCycle(){
        Node* slow = head;  
        Node* fast = head;  
        while(fast != NULL && fast->next != NULL){
            slow = slow->next;          
            fast = fast->next->next;    
            if(slow == fast){            
                return true;             
            }
        }
        return false; // No cycle
    }

    //9. If there is a cycle, find the starting node of the cycle
    Node* findCycleStart(){
        Node* slow = head;
        Node* fast = head;
        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                break; // Cycle detected
            }
        }
        // If no cycle, return NULL
        if(fast == NULL || fast->next == NULL){
            return NULL;
        }   
        // Move one pointer to head and keep the other at meeting point
        slow = head;
        while(slow != fast){
            slow = slow->next;  
            fast = fast->next;
        }
        return slow; // Return the starting node of the cycle
    }

    //10. Clear the list and free memory
    void clearList(){
        Node* temp = head;
        while (temp != NULL){
            Node* next = temp->next;
            delete temp;    
            temp = next;
        }
        head = tail = NULL;
    }   

    //11. Detect and remove cycle in the list, return starting node of cycle or NULL if no cycle
    Node* detectAndRemoveCycle(){
        Node* slow = head;
        Node* fast = head;
        bool isCycle = false;
        while (fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                isCycle = true;
                break;
            }
        }
        if(!isCycle){
            return NULL; // No cycle
        }
        slow = head;
        Node* prev = NULL;
        while(slow != fast){
            slow = slow->next;  
            prev = fast;
            fast = fast->next;
        }
        // Remove cycle by setting the next pointer of the previous node to NULL
        prev->next = NULL;
        return slow; // Return the starting node of the cycle   
    }

    //12. Detect and remove cycle in linked list
    Node* detectAndRemoveCycle(){
        Node* slow = head;
        Node* fast = head;
        bool isCycle = false;
        while (fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                isCycle = true;
                break;
            }
        }
        if(!isCycle){
            return NULL; // No cycle
        }
        slow = head;
        Node* prev = NULL;
        while(slow != fast){
            slow = slow->next;  
            prev = fast;
            fast = fast->next;
        }
        // Remove cycle by setting the next pointer of the previous node to NULL
        prev->next = NULL;
        return slow; // Return the starting node of the cycle   
    }

    //13. Print the list elements in order
    void printList(){
        Node* temp = head;
        while (temp != NULL){
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }   

    // Destructor to free memory
    ~List(){
        clearList();
    }
};

int main() {
    List myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    myList.push_front(5);
    myList.insertAtPosition(15, 3); // Insert 15 at position 3
    cout << "List after insertions: ";
    myList.printList();

    cout << "Position of 20: " << myList.search(20) << endl;

    myList.pop_front();
    cout << "List after popping front: ";
    myList.printList();

    myList.pop_back();
    cout << "List after popping back: ";
    myList.printList();

    myList.deleteAtPosition(2); // Delete node at position 2
    cout << "List after deleting position 2: ";
    myList.printList();

    return 0;
}