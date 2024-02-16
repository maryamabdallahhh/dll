 

#include <iostream>
#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void delete_all_nodes_with_key(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                Node* temp = current;
                if (current == head) {
                    head = current->next;
                    if (head)
                        head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                current = current->next;
                delete temp;
            }
            else {
                current = current->next;
            }
        }
    }

    void delete_even_positions() {
        Node* current = head;
        while (current && current->next) {
            Node* temp = current->next;
            current->next = temp->next;
            if (temp->next)
                temp->next->prev = current;
            delete temp;
            current = current->next;
        }
    }

    void delete_odd_positions() {
        Node* current = head;
        if (!current)
            return;
        while (current->next && current->next->next) {
            Node* temp = current->next;
            current->next = temp->next;
            if (temp->next)
                temp->next->prev = current;
            delete temp;
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            delete temp;
            current->next = nullptr;
        }
    }

    bool is_palindrome() {
        Node* start = head;
        Node* end = tail;
        while (start != end && end->next != start) {
            if (start->data != end->data)
                return false;
            start = start->next;
            end = end->prev;
        }
        return true;
    }

    int find_middle() {
        if (!head)
            return -1;
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }

    void swap_forward_backward(int k) {
        if (k <= 0)
            return;
        int count = 1;
        Node* forward = head;
        Node* backward = tail;
        while (count < k && forward != backward) {
            forward = forward->next;
            backward = backward->prev;
            count++;
        }
        if (forward == backward)
            return; // Same node, no need to swap
        swap_nodes(forward, backward);
    }

    void reverse() {
        if (!head || !head->next)
            return;
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            Node* nextNode = current->next;
            current->next = prev;
            current->prev = nextNode;
            prev = current;
            current = nextNode;
        }
        tail = head;
        head = prev;
    }

    void merge_2sorted_lists(DoublyLinkedList& other) {
        Node* current1 = head;
        Node* current2 = other.head;
        DoublyLinkedList mergedList;
        while (current1 && current2) {
            if (current1->data < current2->data) {
                mergedList.insert(current1->data);
                current1 = current1->next;
            }
            else {
                mergedList.insert(current2->data);
                current2 = current2->next;
            }
        }
        while (current1) {
            mergedList.insert(current1->data);
            current1 = current1->next;
        }
        while (current2) {
            mergedList.insert(current2->data);
            current2 = current2->next;
        }
        head = mergedList.head;
        tail = mergedList.tail;
    }

private:
    void swap_nodes(Node* node1, Node* node2) {
        if (!node1 || !node2)
            return;
        if (node1 == node2)
            return;
        if (node1->prev)
            node1->prev->next = node2;
        if (node2->next)
            node2->next->prev = node1;
        Node* temp = node1->prev;
        node1->prev = node2->prev;
        node2->prev = temp;
        temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
        if (node1->prev == nullptr)
            head = node1;
        if (node2->prev == nullptr)
            head = node2;
        if (node1->next == nullptr)
            tail = node1;
        if (node2->next == nullptr)
            tail = node2;
    }
};

int main() {
    DoublyLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(5);
    list.insert(5);
    list.insert(52);
    list.insert(50);
    list.insert(588);
    list.insert(5784);
    list.insert(2155);
    list.insert(5031);
    list.insert(577);



    cout << "Original list: ";
    list.display();

    list.delete_all_nodes_with_key(5);
    cout << "After deleting all nodes with key 5: ";
    list.display();

    list.delete_even_positions();
    cout << "After deleting even positions: ";
    list.display();

    list.delete_odd_positions();
    cout << "After deleting odd positions: ";
    list.display();

    cout << "Is Palindrome: " << boolalpha << list.is_palindrome() << endl;

    cout << "Middle value: " << list.find_middle() << endl;

    list.swap_forward_backward(2);
    cout << "After swapping forward with backward: ";
    list.display();

    list.reverse();
    cout << "After reversing: ";
    list.display();

    DoublyLinkedList list2;
    list2.insert(6);
    list2.insert(7);
    list2.insert(8);
    list2.insert(9);
    list2.insert(10);

    cout << "Second list: ";
    list2.display();

    list.merge_2sorted_lists(list2);
    cout << "Merged sorted lists: ";
    list.display();

    return 0;
}



 

 