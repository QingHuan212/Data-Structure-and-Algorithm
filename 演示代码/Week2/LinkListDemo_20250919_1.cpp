#include <iostream>
using namespace std;

template <class T>
struct DNode{ // Data Node
    T data;
    DNode<T>* next;
};

template <class T>
class LinkList{ // vector list
    private:
        DNode<T>* head;
        int length;

        DNode<T>* findPrev(int i){ // find (i-1)-th node.
            DNode<T>* K = head;
            for(int j=0;j<i;j++){
                K = K->next;
            }
            return K;
        }
    public:
        LinkList(){
            length = 0;
            head = new DNode<T>;
            head->next = NULL;
        }
        LinkList(T* a, int n){
            length = 0;
            head = new DNode<T>;
            head->next = NULL;
            for(int i=n-1;i>=0;i--)
                insertEleAtPos(0,a[i]);
        }
        ~LinkList(){
            DNode<T>* K;
            while(head!=NULL){
                K = head;
                head = head->next;
                delete K;
            }
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
            DNode<T>* prevNode = findPrev(i);
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = prevNode->next;
            prevNode->next = newNode;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            DNode<T>* prevNode = findPrev(i);
            DNode<T>* delNode = prevNode->next;
            prevNode->next = delNode->next;
            T x = delNode->data;
            delete delNode;
            length--;
            return x;
        }
        void setEleAtPos(int i, T x){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            DNode<T>* prevNode = findPrev(i);
            DNode<T>* editNode = prevNode->next;
            editNode->data = x;
        }
        T getEleAtPos(int i){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            DNode<T>* prevNode = findPrev(i);
            DNode<T>* editNode = prevNode->next;
            return editNode->data;
        }
        int locateEle(T x){
            int i = 0;
            DNode<T>* K = head->next;
            while(K!=NULL){
                if(K->data==x) return i;
                K = K->next;
                i++;
            }
            return -1;
        }
        void printList(){
            DNode<T>* K = head->next;
            while(K!=NULL){
                cout << K->data << " ";
                K = K->next;
            }
        }
};

int main(){
    string SS[3] = {"AA","BB","CCC"};
    LinkList<string> ListS(SS,3);
    cout << (ListS.isEmpty() ? "Empty" : "Non-empty") << endl;
    cout << ListS.getLength() <<endl;
    ListS.printList();
    cout << endl;
    ListS.setEleAtPos(2,"CC");
    ListS.printList();
    cout << endl;
    cout << endl;

    LinkList<int> ListI;
    cout << (ListI.isEmpty() ? "Empty" : "Non-empty") << endl;
    for(int i=1;i<=31;i+=2){
        ListI.insertEleAtPos(0,i);
    }
    ListI.printList();
    cout << endl;

    for(int i=0;i<=500;i++){
        ListI.insertEleAtPos(ListI.getLength(),i);
    }
    ListI.printList();
    cout << endl;

    LinkList<int> ListJ;
    for(int j=0;j<5;j++){
        ListJ.insertEleAtPos(ListJ.getLength(),j);
    }
    ListJ.printList();
    cout << endl;

    try{
        ListJ.insertEleAtPos(0,500);
        ListJ.insertEleAtPos(10,7);
        ListJ.insertEleAtPos(0,100);
    }
    catch(const char* s){
        cout << s << endl;
    }
    ListJ.printList();
    cout << endl;

    cout << "Deleted element: " << ListJ.deleteEleAtPos(3) << endl;
    ListJ.printList();
    cout << endl;
    cout << ListJ.getLength() << endl;

    cout << ListJ.getEleAtPos(4) << endl;
    cout << "Position of 3: "<< ListJ.locateEle(3) << endl;
    cout << "Position of 500: "<< ListJ.locateEle(500) << endl;
    cout << "Position of 2: " << ListJ.locateEle(2) << endl;

    return 0;
}
