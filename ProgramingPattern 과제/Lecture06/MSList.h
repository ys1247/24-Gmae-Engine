#ifndef MSLIST_H
#define MSLIST_H

template <typename T>
class MSList {
private:
    struct Node {
        T* data;
        Node* next;
        Node(T* item) : data(item), next(nullptr) {}
    };

    Node* head;

public:
    MSList() : head(nullptr) {}

    ~MSList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp->data;
            delete temp;
        }
    }

    void push_back(T* item) {
        if (head == nullptr) {
            head = new Node(item);
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(item);
        }
    }

    T* operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            if (current == nullptr) {
                return nullptr;
            }
            current = current->next;
        }
        return current->data;
    }

    int size() const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }
};

#endif // MSLIST_H
