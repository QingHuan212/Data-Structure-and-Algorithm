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
            left = NULL;
            right = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
        }
        ~BinTree(){

        }
        void addLChild(BinTree<T>* bt){
            left = bt;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
        }
        void addRChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addRChild(bt);
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
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        void printLevelOrder(){
            LinkQueue<BinTree<T> *> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmpN = q.deQueue();
                cout << tmpN->data << " ";
                if(tmpN->left!=NULL) q.enQueue(tmpN->left);
                if(tmpN->right!=NULL) q.enQueue(tmpN->right);
            }
        }


        bool isLeaf(){
            return left==NULL && right==NULL;
        }

};

struct HTNode{
    char c;
    int freq;
    bool isChar;
};

BinTree<HTNode*>* buildHuffmanTree(char* charSet, int* freqSet, int count){
    // STEP 1: create a node for each character
    BinTree<HTNode*>** forest = new BinTree<HTNode*>*[count];
    int treeCount = count;
    for(int i=0;i<count;i++){
        HTNode* ht = new HTNode;
        ht->c = charSet[i];
        ht->freq = freqSet[i];
        ht->isChar = true;
        forest[i] = new BinTree<HTNode*>(ht);
    }

    // arrange in descending order (bubble sort)
    for(int i=0;i<count;i++){
        for(int j=0;j<count-1;j++){
            if(forest[j]->getData()->freq < forest[j+1]->getData()->freq){
                BinTree<HTNode*>* bt = forest[j];
                forest[j] = forest[j+1];
                forest[j+1] = bt;
            }
        }
    }

    // combine until one tree left
    while(treeCount > 1){
        // merge forest[treeCount-2], forest[treeCount-1]
        HTNode* ht = new HTNode;
        ht->isChar = false;
        ht->freq = forest[treeCount-2]->getData()->freq + forest[treeCount-1]->getData()->freq;
        BinTree<HTNode*>* bt = new BinTree<HTNode*>(ht);
        bt->addLChild(forest[treeCount-2]);
        bt->addRChild(forest[treeCount-1]);

        // put the combined tree in the right location
        int j;
        for(j = treeCount-3;j>=0;j--){
            if(forest[j]->getData()->freq >= ht->freq){
                break;
            }
            forest[j+1] = forest[j];
        }
        forest[j+1] = bt;
        treeCount--;
    }

    return forest[0];

}

void printHT(BinTree<HTNode*>* bt, string s){
    if(bt->isLeaf()){
        cout << bt->getData()->c << ": " << s << endl;
        return;
    }
    printHT(bt->getLChild(),s+"0");
    printHT(bt->getRChild(),s+"1");
}

void printHT(BinTree<HTNode*>* bt){
    printHT(bt, "");
}

void testHT(){
    char testC1[4] = {'A','B','C','D'};
    int freqC1[4] = {24,6,5,17};
    BinTree<HTNode*>* bt = buildHuffmanTree(testC1,freqC1,4);
    printHT(bt);
    cout << endl;

    char testC2[7] = {'A','B','C','D','E','F','G'};
    int freqC2[7] = {9,11,5,7,8,2,3};
    BinTree<HTNode*>* bt2 = buildHuffmanTree(testC2,freqC2,7);
    printHT(bt2);
}

int main(){
    testHT();
    return 0;
}
