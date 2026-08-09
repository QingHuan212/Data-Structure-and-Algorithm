#include <iostream>
#include <string>
using namespace std;

template <class T>
struct DNode {
    T data;
    DNode<T>* next;
};

template <class T>
class LinkQueue {
private:
    DNode<T>* front;
    DNode<T>* back;
    int length;
public:
    LinkQueue() {
        front = new DNode<T>;
        front->next = NULL;
        back = front;
        length = 0;
    }
    ~LinkQueue() {
        while (front != NULL) {
            back = front;
            front = front->next;
            delete back;
        }
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void enQueue(T x) {
        DNode<T>* tmpN = new DNode<T>;
        tmpN->data = x;
        tmpN->next = NULL;
        back->next = tmpN;
        back = tmpN;
        length++;
    }
    T deQueue() {
        if (length == 0) throw "Queue Empty!";
        DNode<T>* tmpN = front->next;
        front->next = tmpN->next;
        T tmpD = tmpN->data;
        delete tmpN;
        length--;
        if (length == 0) back = front;
        return tmpD;
    }
    T peekQueue() {
        if (length == 0) throw "Queue Empty!";
        return front->next->data;
    }
    void printQueue() {
        cout << "Front of queue: ";
        DNode<T>* tmp = front->next;
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << ": back of queue" << endl;
    }
};

void Josephus(int n, int m)
{
    int c = 0;
    LinkQueue<int>* j = new LinkQueue<int>();
    for (int i = 1; i <= n; i++)
    {
        j->enQueue(i);
    }
    while (j->getLength() != 0)
    {
        if (m > j->getLength()) c = m % j->getLength();
        else c = m;
        for (int i = 0; i < c - 1; i++)
        {
            j->enQueue(j->deQueue());
        }
        cout << j->deQueue() << " ";
    }
    delete j;
};

int main()
{
    int n, m;
    cin >> n >> m;
    Josephus(n, m);
    return 0;
}