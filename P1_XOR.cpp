#include <cstdint>
#include <iostream>

struct Node {
    int data;
    
    Node* both;
};

class XORLinkedList {
private:
    Node* head;
    Node* tail;
    
    Node* XOR(Node* a, Node* b);

public:
    
    
    XORLinkedList();
  
    
    void insert_at_head(int data);
  
    
    void insert_at_tail(int data);
  
    void delete_from_head();
  
    void delete_from_tail();
  
    void print_list();
};

XORLinkedList::XORLinkedList()
{
    head = tail = nullptr; 
                           
}

Node* XORLinkedList::XOR(Node* a, Node* b)
{
    return (
      
        
        Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

void XORLinkedList::insert_at_head(int data)
{
    Node* new_node = new Node();
    new_node->data = data;
    new_node->both = XOR(nullptr, head);

    if (head) {
        head->both
            = XOR(new_node, XOR(head->both, nullptr));
    }
    else {
        tail = new_node;
    }
    
    head = new_node;
}

void XORLinkedList::insert_at_tail(int data)
{
    Node* new_node = new Node();
    new_node->data = data;
    new_node->both = XOR(tail, nullptr);

    if (tail) {
        tail->both
            = XOR(XOR(tail->both, nullptr), new_node);
    }
    else {
        head = new_node;
    }

    tail = new_node;
}

void XORLinkedList::delete_from_head()
{
    if (head) {
        Node* next = XOR(head->both, nullptr);
        delete head;
        head = next;

        if (next) {
            next->both = XOR(next->both, head);
        }
        else {

            tail = nullptr;
        }
    }
}

void XORLinkedList::delete_from_tail()
{
    if (tail) {
        Node* prev = XOR(tail->both, nullptr);
        delete tail;
        tail = prev;

        if (prev) {
            prev->both = XOR(prev->both, tail);
        }
        else {

            head = nullptr;
        }
    }
}

void XORLinkedList::print_list()
{
    Node* current = head;
    Node* prev = nullptr;
    while (current) {
        std::cout << current->data << " ";
        Node* next = XOR(prev, current->both);
        prev = current;
        current = next;
    }
    std::cout << std::endl;
}

int main()
{
    XORLinkedList list;
    list.insert_at_head(10);
    list.insert_at_head(20);
    list.insert_at_tail(30);
    list.insert_at_tail(40);
    list.print_list();
    return 0;
}
