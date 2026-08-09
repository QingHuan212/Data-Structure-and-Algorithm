#include <iostream>
using namespace std;

template <class T>
class VecList{ // vector list
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){

            cout << "Doubling..." << endl;

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
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
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
            if(i<0 || i > length)
                throw "Illegal position";
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
            if(i<0 || i >= length)
                throw "Illegal position";
            T x = arr[i];
            for(int j=i+1;j<length;j++){
                arr[j-1] = arr[j];
            }
            length--;
            return x;
        }
        void setEleAtPos(int i, T x){
            if(i<0 || i >= length)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i<0 || i >= length)
                throw "Illegal position";
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

int main(){
    string ST[4] = {"AA","BB","CC","DDD"};
    VecList<string> LS(ST,4);
    cout << (LS.isEmpty() ? "Empty" : "Non-empty") << endl;
    cout << LS.getLength() << endl;
    LS.printList();
    cout << endl;
    LS.setEleAtPos(3,"DD");
    LS.printList();
    cout << endl;
    cout << endl;

    VecList<int> LI;
    cout << (LI.isEmpty() ? "Empty" : "Non-empty") << endl;
    cout << LI.getLength() << endl;
    LI.printList();
    cout << endl;
    for(int i=0;i<16;i+=2){
        LI.insertEleAtPos(0,i);
    }
    LI.printList();
    cout << endl;

    for(int i=1;i<=500;i++){
        LI.insertEleAtPos(LI.getLength(),i);
    }
    LI.printList();
    cout << endl;
    cout << endl;

    VecList<int> L2;
    for(int i=0;i<5;i++){
        L2.insertEleAtPos(L2.getLength(),i);
    }
    L2.printList();
    cout << endl;

    try{
        L2.insertEleAtPos(0,200);
        L2.insertEleAtPos(10,-300);
        L2.insertEleAtPos(0,500);
        L2.printList();
        cout << endl;
    }
    catch(const char* s){
        cout << s << endl;
    }
    L2.printList();
    cout << endl;

    cout << "search for element 3: " << L2.locateEle(3) << endl;
    L2.deleteEleAtPos(L2.locateEle(3));
    L2.printList();
    cout << endl;


    return 0;
}
