template <class T>
struct DNode {
    T data;
    DNode<T>* next;
};
template <class T>
class LinkList {
private:
    int length;
    DNode<T>* head;
public:
    LinkList() {
        head = new DNode<T>;
        head->next = NULL;
        length = 0;
    }
    LinkList(T* a, int n) {
        head = new DNode<T>;
        head->next = NULL;
        for (int i = n - 1; i >= 0; i--) {
            DNode<T>* tmpNode = new DNode<T>;
            tmpNode->next = head->next;
            tmpNode->data = a[i];
            head->next = tmpNode;
        }
        length = n;
    }
    ~LinkList() {
        while (head != NULL) {
            DNode<T>* tmpNode = head;
            head = head->next;
            delete tmpNode;
        }
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void insertEleAtPos(int i, T x) {
        if (i < 0 || i > length)
            throw "Bad position";
        DNode<T>* tmpNode = head;
        for (int j = 0; j < i; j++) {
            tmpNode = tmpNode->next;
        }
        DNode<T>* newNode = new DNode<T>;
        newNode->data = x;
        newNode->next = tmpNode->next;
        tmpNode->next = newNode;
        length++;
    }
    T deleteEleAtPos(int i) {
        if (i < 0 || i >= length)
            throw "Bad position";
        DNode<T>* tmpNode = head;
        for (int j = 0; j < i; j++) {
            tmpNode = tmpNode->next;
        }
        DNode<T>* delNode = tmpNode->next;
        tmpNode->next = delNode->next;
        T tmp = delNode->data;
        delete delNode;
        length--;
        return tmp;
    }
    void setEleAtPos(int i, T x) {
        if (i < 0 || i >= length)
            throw "Bad position";
        DNode<T>* tmpNode = head;
        for (int j = 0; j <= i; j++) {
            tmpNode = tmpNode->next;
        }
        tmpNode->data = x;
    }
    T getEleAtPos(int i) {
        if (i < 0 || i >= length)
            throw "Bad position";
        DNode<T>* tmpNode = head;
        for (int j = 0; j <= i; j++) {
            tmpNode = tmpNode->next;
        }
        return tmpNode->data;
    }
    int locateEle(T x) {
        DNode<T>* tmpNode = head->next;
        int count = 0;
        while (tmpNode != NULL) {
            if (tmpNode->data == x) return count;
            tmpNode = tmpNode->next;
            count++;
        }
        return -1;
    }
    void printList() {
        DNode<T>* tmpNode = head->next;
        while (tmpNode != NULL) {
            cout << tmpNode->data << " ";
            tmpNode = tmpNode->next;
        }
    }

    LinkList<T>* unionWithAnotherSortedList(LinkList<T>* L) {
        LinkList<T>* NL = new LinkList<T>;
        DNode<T>* tmp = head->next;
        int i = 0, j;
        T a;
        if (tmp == NULL)return L;
        while (tmp != NULL)
        {
            NL->insertEleAtPos(i, tmp->data);
            tmp = tmp->next;
            i++;
        }
        if (L->isEmpty())return NL;
        for (i = 0; i < L->getLength(); i++)
        {
            a = L->getEleAtPos(i);
            if (NL->locateEle(a) != (-1))continue;
            if (a > NL->getEleAtPos(NL->getLength() - 1))
            {
                NL->insertEleAtPos(NL->getLength(), a);
                continue;
            }
            for (j = 0; j < NL->getLength(); j++)
            {
                if (a < NL->getEleAtPos(j))
                {
                    if (j == 0)NL->insertEleAtPos(0, a);
                    else NL->insertEleAtPos(j, a);
                    break;
                }
            }
        }
        return NL;
    }
};