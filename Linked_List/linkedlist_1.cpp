// Implementation of singly linked list with head and tail pointers.

#include<iostream>
using namespace std;

// Node of singly linked list
class Node {
public:
    int data;      // Stores value
    Node* next;    // Pointer to next node

    // Constructor to initialize a node
    Node(int val){
        data = val;
        next = NULL;
    }
};


// Singly linked list with head and tail pointers
class List {
    Node* head;    // Points to first node
    Node* tail;    // Points to last node

public:
    // Constructor: initialize empty list
    List(){
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
            head = new_Node;
        }
    }

    //2. Insert at the end of the list
    void push_back(int val){
        Node* new_Node = new Node(val);

        // If list is empty, new node is both head and tail
        if(head == NULL){
            head = tail = new_Node;
            return;
        }else{
            // Attach new node after tail and move tail
            tail->next = new_Node;
            tail = new_Node;
        }
    }

    //3. Remove node from the beginning
    void pop_front(){
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        }else{
            // Move head to next and delete old head
            Node* temp = head;
            head = head->next;
            temp->next = NULL; // Detach node before deletion

            delete temp;

            // If list became empty, update tail as well
            if(head == NULL){
                tail = NULL;
            }
        }
    }

    //4. Remove node from the end
    void pop_back(){
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        }else if(head == tail){
            // Only one node in list
            delete head;
            head = tail = NULL;
        }else{
            // Traverse to node just before tail
            Node* temp = head;
            while (temp->next != tail){
                temp = temp->next;
            }

            // Delete tail and update it
            delete tail;
            tail = temp;
            tail->next = NULL;
        }
    }

    //5. Insert node at given 1-based position
    void insertAtPosition(int val, int pos){
        Node* new_Node = new Node(val);

        // Insertion at head (position 1)
        if(pos == 1){
            new_Node->next = head;
            head = new_Node;

            // If list was empty, tail also becomes new node
            if(tail == NULL){
                tail = new_Node;
            }
            return;
        }

        // Traverse to node at (pos - 1)
        Node* temp = head;
        for(int i = 1; i < pos - 1 && temp != NULL; i++){
            temp = temp->next;
        }

        // If position is beyond current length
        if(temp == NULL){
            cout << "Position out of bounds" << endl;
            delete new_Node;
            return;
        }

        // Insert new node in the middle or at the end
        new_Node->next = temp->next;
        temp->next = new_Node;

        // If inserted at the end, update tail
        if(new_Node->next == NULL){
            tail = new_Node;
        }
    }

    //6. Search for a value in the list
    int search(int key){
        Node* temp = head;
        int idx = 1;

        while(temp != NULL){
            if(temp->data == key){
                return idx;
            }
            temp = temp->next;
            idx++;
        }
        return -1; // Return -1 if not found
    }

    //7. Reverse the linked list in-place
    void reverseList(){
        Node* prev = NULL;
        Node* current = head;
        Node* next = NULL;

        // Standard iterative reversal
        while (current != NULL){
            next = current->next;   // Store next
            current->next = prev;   // Reverse current's link
            prev = current;         // Move prev ahead
            current = next;         // Move current ahead
        }

        // After reversal, prev is new head
        tail = head;
        head = prev;
    }

    //8. Middle of a linked list using slow and fast pointer approach
    void findMiddle(){
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        } 

        Node* slow = head;
        Node* fast = head;

        // Move fast pointer twice as fast as slow pointer
        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }

        cout << "Middle element is: " << slow->data << endl;
    }

    //9. Delete node at given 1-based position
    void deleteAtPosition(int pos){
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        }

        // If deleting first node
        if(pos == 1){
            Node* temp = head;
            head = head->next;
            delete temp;

            // If list becomes empty, update tail
            if(head == NULL){
                tail = NULL;
            }
            return;
        }

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

        // Delete the node at given position
        Node* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;

        // If deleting last node, update tail
        if(nodeToDelete == tail){
            tail = temp;
        }

        delete nodeToDelete;
    }

    //10. Delete all nodes in the list
    void clearList(){
        Node* temp = head;

        // Traverse and delete each node
        while (temp != NULL){
            Node* next = temp->next;
            delete temp;
            temp = next;
        }

        head = tail = NULL;
    }

    //11. Detect Cycle in linked list using Floyd’s Cycle Detection Algorithm
    bool hasCycle(){
        if(head == NULL) return false;

        Node* slow = head;
        Node* fast = head;

        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                return true; // Cycle detected
            }
        }
        return false; // No cycle
    }

    //12. Detect and remove cycle in linked list
    Node* detectAndRemoveCycle(){
        Node* slow = head;
        Node* fast = head;
        bool isCycle = false;

        // Detect cycle
        while (fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                isCycle = true;
                break;
            }
        }

        // If no cycle present
        if(!isCycle){
            return NULL;
        }

        // Move slow to head
        slow = head;
        Node* prev = NULL;

        // Find starting point of cycle
        while(slow != fast){
            slow = slow->next;
            prev = fast;
            fast = fast->next;
        }

        // Remove cycle
        prev->next = NULL;

        return slow; // Starting node of cycle
    }

    //13. Print list elements in order
    void printList(){
        Node* temp = head;
        while (temp != NULL){
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    //14. Destructor: ensure no memory leak
    ~List(){
        clearList();
    }
};

int main (){
    List ll;  // Create an empty list

    // Insert elements at the front: 3->2->1
    ll.push_front(1);
    ll.push_front(2);
    ll.push_front(3);

    // Insert elements at the back: 3->2->1->4->5
    ll.push_back(4);
    ll.push_back(5);

    ll.printList();  // Print current list

    // Detect cycle
    if(ll.hasCycle()){
        cout << "Cycle detected in the list." << endl;
    }else{
        cout << "No cycle in the list." << endl;
    }

    ll.pop_front();  // Delete first node
    ll.printList();

    ll.pop_back();   // Delete last node
    ll.printList();

    // Insert 10 at position 2
    ll.insertAtPosition(10, 2);
    ll.printList();

    // Search for value 10
    int pos = ll.search(10);
    if(pos != -1){
        cout << "Value 10 found at position: " << pos << endl;
    }else{
        cout << "Value 10 not found in the list." << endl;
    }

    // Find middle element
    ll.findMiddle();

    // Delete node at position 3
    ll.deleteAtPosition(3);
    ll.printList();

    // Reverse the list
    ll.reverseList();
    ll.printList();

    // Clear the list and print
    ll.clearList();
    ll.printList();

    return 0;
}
