#include <iostream>
using namespace std;

template <class T>
class VecList{ // vector list
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            capacity = 2*capacity;
            T* newArr = new T[capacity];
            for(int i=0;i<length;i++){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++)
                arr[i] = a[i];
        }
        ~VecList(){
            delete[] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(i<0 || i > length){
                throw "Illegal position";
            }
            if(length==capacity){
                doubleListSize();
            }
            for(int j=length-1;j>=i;j--){
                arr[j+1] = arr[j];
            }
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            T x = arr[i];
            for(int j=i+1;j<length;j++){
                arr[j-1] = arr[j];
            }
            length--;
            return x;
        }
        void setEleAtPos(int i, T x){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i] == x){
                    return i;
                }
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++){
                cout << arr[i] << " ";
            }
        }
};

template <class T>
class LinkStack{
    private:
        VecList<T> vL;
    public:
        LinkStack(){
        }
        ~LinkStack(){
        }
        int getLength(){
            return vL.getLength();
        }
        bool isEmpty(){
            return vL.isEmpty();
        }
        void push(T x){
            vL.insertEleAtPos(vL.getLength(),x);
        }
        T pop(){
            return vL.deleteEleAtPos(vL.getLength()-1);
        }
        T getTop(){
            return vL.getEleAtPos(vL.getLength()-1);
        }
        void printStack(){
            cout << "stack bottom: ";
            vL.printList();
            cout << ": stack top" << endl;
        }
};

void test1(){
    LinkStack<int> S;
    cout << (S.isEmpty()?"Empty Stack":"Non-empty Stack") << endl;
    S.printStack();
    cout << "Inserting things:" << endl;
    S.push(15);
    S.push(10);
    S.printStack();
    cout << "Peeking top of stack: it is " << S.getTop() << endl;
    cout << "Popping top of stack: it returns " << S.pop() << endl;
    cout << "Peeking top of stack again: it is " << S.getTop() << endl;
    S.printStack();
    S.pop();
    cout << "All things popped. " << (S.isEmpty()?"Empty Stack":"Non-empty Stack") << endl;
    cout << "Inserting things:" << endl;
    S.push(15);
    S.push(10);
    S.printStack();
    cout << "Peeking top of stack: it is " << S.getTop() << endl;
    cout << "Popping top of stack: it returns " << S.pop() << endl;
    cout << "Peeking top of stack again: it is " << S.getTop() << endl;
    S.printStack();
}

int main(){
    test1();
    return 0;
}

