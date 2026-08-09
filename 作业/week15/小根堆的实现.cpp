#include <iostream>
#include <iomanip>
using namespace std;

/* UPLOAD START */

template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        T* heap;
        int length;
        int capacity;

        void doubleListSize()
        {
            T * oldheap = heap;
            heap = new T[2*capacity+1];
            capacity = 2 * capacity;
            for(int i=1;i<=length;i++)
            {
                heap[i] = oldheap[i];
            }
            delete [] oldheap;
        }
    public:
        AMinHeap(){
            capacity = 100;
            length = 0;
            heap = new T[capacity+1];
        }
        AMinHeap(T* arr, int n){
            capacity = 2*n;
            length = n;
            heap = new T[capacity+1];
            for(int i=0;i<n;i++)
            {
                heap[i+1] = arr[i];
            }
            for(int i=length/2;i>=1;i--)
            {
                int j = i;
                while(2*j<=length)
                {
                    int min = 2*j;
                    if(2*j+1<=length)
                    {
                        if(heap[2*j+1]<heap[2*j])min = 2*j+1;
                    }
                    if(heap[j]>heap[min])
                    {
                        T tmp = heap[min];
                        heap[min] = heap[j];
                        heap[j] = tmp;
                        j = min;
                    }
                    else break;
                }
            }
        }
        ~AMinHeap(){
            delete[] heap;
        }
        bool isEmpty(){
            return length==0;
        }
        T getMin(){
            if(length==0)throw "Heap Empty";
            return heap[1];
        }
        void push(T x){
            if(length+1>=capacity)doubleListSize();
            length += 1;
            heap[length] = x;
            int j = length;
            while(j>1&&heap[j]<heap[j/2])
            {
                T tmp = heap[j/2];
                heap[j/2] = heap[j];
                heap[j] = tmp;
                j = j/2;
            }
        }
        T delMin(){
            if(length==0)throw "Heap Empty";
            T tmpmin = heap[1];
            heap[1] = heap[length];
            length--;
            int j = 1;
            while(2*j<=length)
            {
                int min = 2*j;
                if(2*j+1<=length)
                {
                    if(heap[2*j+1]<heap[2*j])min = 2*j+1;
                }
                if(heap[j]>heap[min])
                {
                    T tmp = heap[min];
                    heap[min] = heap[j];
                    heap[j] = tmp;
                    j = min;
                }
                else break;
            }
            return tmpmin;
        }
        T* getLevelOrderArray(){
            T* tmp = new T[length+1];
            for(int i=1;i<=length;i++)
            {
                tmp[i] = heap[i];
            }
            return tmp;
        }
        int getNumData(){
            return length;
        }
};

/* UPLOAD END */

template <class T>
void printLevelOrder(T* data, int numItems){ //assumes class T has an overloaded ostream << operator.
    for(int i=1;i<=numItems;i++){
        cout << data[i] << " ";
    }
}

int test1(){ // normal test
    AMinHeap<int> amh;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    amh.push(10);
    amh.push(8);
    amh.push(6);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    amh.push(4);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    
    cout << "Top: " << amh.getMin() << endl;
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    
    cout << "Popping:" << endl;
    while(!amh.isEmpty()){
        cout << "Current Min: " << amh.delMin() << endl;
        cout << endl;
    }
    return 0;
}

int main(){
    //unit test for Heap.
    test1();
    return 0;
}
