#include <iostream>
#include <string>
using namespace std;

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
            DNode<T>* helper;
            while(top!=NULL){
                helper = top;
                top = top->next;
                delete helper;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0; // return top==NULL;
        }
        void push(T x){
            length++;
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = top;
            top = newNode;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            length--;
            DNode<T>* delNode = top;
            T x = delNode->data;
            top = top->next;
            delete delNode;
            return x;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* helper = top;
            while(helper!=NULL){
                cout << helper->data << " ";
                helper = helper->next;
            }
            cout << ": stack bottom" << endl;
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

void test2(){
    // RPN evaluator, space separated between numbers and/or operators
    LinkStack<int> S;
    string input;

    do{
        cin >> input;
        if(input=="+"){
            if(S.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int pop1, pop2;
            pop2 = S.pop();
            pop1 = S.pop();
            int tmp = pop1 + pop2;
            S.push(tmp);
        }
        else if(input=="-"){
            if(S.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int pop1, pop2;
            pop2 = S.pop();
            pop1 = S.pop();
            int tmp = pop1 - pop2;
            S.push(tmp);
        }
        else if(input=="*"){
            if(S.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int pop1, pop2;
            pop2 = S.pop();
            pop1 = S.pop();
            int tmp = pop1 * pop2;
            S.push(tmp);
        }
        else if(input=="/"){
            if(S.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int pop1, pop2;
            pop2 = S.pop();
            pop1 = S.pop();
            int tmp = pop1 / pop2;
            S.push(tmp);
        }
        else if(input=="="){
            if(S.getLength()!=1){
                cout << "Invalid expression" << endl;
                return;
            }
            cout << S.pop() << endl;
        }
        else{
            int tmp = stoi(input);
            S.push(tmp);
        }
    }while(input!="=");
}

int main(){
    //test1();
    test2();
    return 0;
}
