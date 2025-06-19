#include "LinkedQueue.h"

template <typename T>
class ExtendedQueue : public LinkedQueue<T> {
public:
    // Function to remove a node with a specific PID
    bool cancel(int pid) {
        Node<T>* prev = nullptr;
        Node<T>* curr = this->frontPtr;

        // Traverse the linked list
        while (curr != nullptr) {
            Patient* p = curr->getItem();

            // Check if the current node matches the PID
            if (p->get_PID() == pid) {
                // If the node is the first node
                if (prev == nullptr) {
                    this->frontPtr = curr->getNext();
                } else {
                    prev->setNext(curr->getNext());
                }

                // If the node is the last node
                if (curr == this->backPtr) {
                    this->backPtr = prev;
                }

                // Delete the current node
                delete curr;
                this->count--;
                return true; // Successfully removed
            }

            // Move to the next node
            prev = curr;
            curr = curr->getNext();
        }

        return false; // Node with given PID not found
    }
};