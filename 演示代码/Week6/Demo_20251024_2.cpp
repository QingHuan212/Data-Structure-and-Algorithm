#include <iostream>
using namespace std;

template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
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
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            front->next = NULL;
            back = front;
            length = 0;
        }
        ~LinkQueue(){
            while(front!=NULL){
                back = front;
                front = front->next;
                delete back;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void enQueue(T x){
            DNode<T>* tmpN = new DNode<T>;
            tmpN->data = x;
            tmpN->next = NULL;
            back->next = tmpN;
            back = tmpN;
            length++;
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            DNode<T>* tmpN = front->next;
            front->next = tmpN->next;
            T tmpD = tmpN->data;
            delete tmpN;
            length--;
            if(length==0) back = front;
            return tmpD;
        }
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void printQueue(){
            cout << "Front of queue: ";
            DNode<T>* tmp = front->next;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ": back of queue" << endl;
        }
};

template <class T>
class BinTree{
    private:
        T data;
        BinTree<T>* left;
        BinTree<T>* right;
    public:
        BinTree(){
            left = nullptr;
            right = nullptr;
        }
        BinTree(T x){
            data = x;
            left = nullptr;
            right = nullptr;
        }
        ~BinTree(){

        }
        void addLChild(BinTree<T>* bt){
            left = bt;
        }
        void addLChild(T x){
            BinTree<T>* newTree = new BinTree<T>(x);
            addLChild(newTree);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
        }
        void addRChild(T x){
            BinTree<T>* newTree = new BinTree<T>(x);
            addRChild(newTree);
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        BinTree<T>* getLChild(){
            return left;
        }
        BinTree<T>* getRChild(){
            return right;
        }
        void printPreOrderR(){
            cout << data << " ";
            if(left!=nullptr) left->printPreOrderR();
            if(right!=nullptr) right->printPreOrderR();
        }
        void printPostOrderR(){
            if(left!=nullptr) left->printPostOrderR();
            if(right!=nullptr) right->printPostOrderR();
            cout << data << " ";
        }
        void printInOrderR(){
            if(left!=nullptr) left->printInOrderR();
            cout << data << " ";
            if(right!=nullptr) right->printInOrderR();
        }
        void printLevelOrder(){
            LinkQueue<BinTree<T>*> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmp = q.deQueue();
                cout << tmp->data << " ";
                if(tmp->left!=nullptr) q.enQueue(tmp->left);
                if(tmp->right!=nullptr) q.enQueue(tmp->right);
            }
        }

        void printPreOrderNR(){
            LinkStack<BinTree<T>*> S;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !S.isEmpty()){
                if(tmp!=NULL){
                    cout << tmp->data << " ";
                    if(tmp->right!=NULL) S.push(tmp->right);
                    tmp = tmp->left;
                }
                else{
                    tmp = S.pop();
                }
            }
        }

        void printInOrderNR(){
            LinkStack<BinTree<T>*> S;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !S.isEmpty()){
                if(tmp!=NULL){
                    S.push(tmp);
                    tmp = tmp->left;
                }
                else{
                    tmp = S.pop();
                    cout << tmp->data << " ";
                    tmp = tmp->right;
                }
            }
        }

        void printPostOrderNR(){
            LinkStack<BinTree<T>*> Stree;
            //LinkStack<int> Snum;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !Stree.isEmpty()){
                if(tmp!=NULL){
                    Stree.push(tmp);
                    //Snum.push(1);
                    tmp = tmp->left;
                }
                else{
                    tmp = Stree.pop();
                    if(Stree.isEmpty() || Stree.getTop()!=tmp){
                        Stree.push(tmp);
                        Stree.push(tmp);
                        tmp = tmp->right;
                    }
                    else{
                        Stree.pop();
                        cout << tmp->data << " ";
                        tmp = NULL;
                    }

                    /*int num = Snum.pop();
                    if(num==1){
                        Stree.push(tmp);
                        Snum.push(2);
                        tmp = tmp->right;
                    }
                    else{
                        cout << tmp->data << " ";
                        tmp = NULL;
                    }*/
                }
            }
        }
};

void test0(){
    BinTree<char> bt('A');
    bt.addLChild('B');
    bt.getLChild()->addRChild('C');
    bt.addRChild('D');
    BinTree<char>* btDp = bt.getRChild();
    btDp->addLChild('E');
    btDp->addRChild('F');
    btDp->getRChild()->addLChild('G');
    btDp->getRChild()->getLChild()->addRChild('H');
    btDp->getRChild()->addRChild('I');

    cout << "Preorder: ";
    bt.printPreOrderR();
    cout << endl;
    cout << "In order: ";
    bt.printInOrderR();
    cout << endl;
    cout << "Post order: ";
    bt.printPostOrderR();
    cout << endl;
    cout << "Level order: ";
    bt.printLevelOrder();
    cout << endl;

    cout << "Preorder: ";
    bt.printPreOrderNR();
    cout << endl;
    cout << "In order: ";
    bt.printInOrderNR();
    cout << endl;
    cout << "Post order: ";
    bt.printPostOrderNR();
    cout << endl;
}

int main(){
    test0();
    return 0;
}
