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
            DNode<T>* temp;
            while(top!=NULL){
                temp = top;
                top = top->next;
                delete temp;
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
            if(length==0) throw "Stack empty!";
            length--;
            DNode<T>* del = top;
            top = top->next;
            T x = del->data;
            delete del;
            return x;
        }
        T getTop(){
            if(length==0) throw "Stack empty!";
            return top->data;
        }
        void printStack(){
            cout << "stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
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
    LinkStack<int> Sint;
    string input;
    do{
        cin >> input;
        if(input=="+"){
            if(Sint.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int first, second;
            second = Sint.pop();
            first = Sint.pop();
            int result = first + second;
            Sint.push(result);
        }
        else if(input=="-"){
            if(Sint.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int first, second;
            second = Sint.pop();
            first = Sint.pop();
            int result = first - second;
            Sint.push(result);
        }
        else if(input=="*"){
            if(Sint.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int first, second;
            second = Sint.pop();
            first = Sint.pop();
            int result = first * second;
            Sint.push(result);
        }
        else if(input=="/"){
            if(Sint.getLength()<2){
                cout << "Invalid expression" << endl;
                return;
            }
            int first, second;
            second = Sint.pop();
            first = Sint.pop();
            int result = first / second;
            Sint.push(result);
        }
        else if(input=="="){
            if(Sint.getLength()!=1){
                cout << "Invalid expression" << endl;
                return;
            }
            cout << Sint.pop() << endl;
        }
        else{
            int toput = stoi(input);
            Sint.push(toput);
        }
    }while(input!="=");
}

int main(){
    //test1();
    test2();
    return 0;
}
