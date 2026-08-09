#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T> *next;
};

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
        void insertLast(T x){
            insertEleAtPos(length,x);
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
struct Edge{
    T start;
    T end;
    int weight;
};

template <class T>
class AMGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer, numEdge;
        VecList<T> verList; // list of vertices
        int** adjMatrix;
        bool directed;

        void BFShelper(int st, bool* visited){
        	visited[st] = true;
        	cout << verList.getEleAtPos(st) << " ";
        	LinkQueue<int> q;
        	q.enQueue(st);
        	while(!q.isEmpty()){
        		int tmp = q.deQueue();
        		for(int k=0;k<numVer;k++){
        			// investigate adjMatrix[tmp][k]
        			if(adjMatrix[tmp][k]==0) continue;
        			if(visited[k]) continue;
        			visited[k] = true;
        			cout << verList.getEleAtPos(k) << " ";
        			q.enQueue(k);
				}
			}
		}

		void DFShelper(int st, bool* visited){
			visited[st] = true;
			cout << verList.getEleAtPos(st) << " ";
			for(int k=0;k<numVer;k++){
				if(adjMatrix[st][k]==0) continue;
				if(visited[k]) continue;
				DFShelper(k,visited);
			}
		}
    public:
        AMGraph(){ // we don't want this used.
        }
        AMGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.

            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;

			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;
			}
        }
        AMGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added now.

            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;

			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;
			}

			for(int i=0;i<e;i++){
				addEdge(eArr[i]->start,eArr[i]->end,eArr[i]->weight);
			}
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
            	delete [] adjMatrix[i];
			}
			delete [] adjMatrix;
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end,e.weight);
        }
        void addEdge(T st, T en, int w = 1){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]!=0) return;
            numEdge++;
            adjMatrix[sIndex][eIndex] = w;
            if(!directed) adjMatrix[eIndex][sIndex] = w;
        }
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);
        }
        void removeEdge(T st, T en){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==0) return;
            numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;
        }
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i) << " ";

            cout << endl << "Edges:" << endl;
            char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j] != 0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " << adjMatrix[i][j] <<endl;
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight<< ", weight = " << adjMatrix[i][j]  <<endl;
                }
            }
        }
        int** getMatrix(){
            return adjMatrix;
        }
        //BFS
        void printBFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
            	visited[i] = false;

            for(int i=0;i<numVer;i++)
            	if(!visited[i])
            		BFShelper(i,visited);
            cout << endl;
        }
        //DFS
        void printDFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
            	visited[i] = false;

            for(int i=0;i<numVer;i++)
            	if(!visited[i])
            		DFShelper(i,visited);
            cout << endl;
        }

        AMGraph<T>* PrimMST(){ // connected undirected graph
            T vers[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* res = new AMGraph<T>(vers,numVer,false);

            bool isInU[numVer];
            int minDist[numVer];
            int minIdx[numVer]; // (i, minIdx[i]) is an edge from V-U to U.
            isInU[0] = true;
            for(int i=1;i<numVer;i++){
                isInU[i] = false;
                minDist[i] = (adjMatrix[0][i]!=0 ? adjMatrix[0][i] : -1);
                minIdx[i] = (adjMatrix[0][i]!=0 ? 0 : -1);
            }

            int numInU = 1;
            while(numInU < numVer){
                int minD = -1;
                int minIndex = -1;
                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    if(minDist[i]==-1) continue;
                    if(minD==-1 || minDist[i] < minD){
                        minD = minDist[i];
                        minIndex = i;
                    }
                }

                isInU[minIndex] = true;
                numInU++;
                res->addEdge(verList.getEleAtPos(minIndex),verList.getEleAtPos(minIdx[minIndex]),minD);
                cout << "Adding Edge: (" << verList.getEleAtPos(minIndex);
                cout << "," << verList.getEleAtPos(minIdx[minIndex]) << "), cost = " << minD << endl;

                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    if(adjMatrix[minIndex][i]==0) continue;
                    if(minDist[i]==-1 || adjMatrix[minIndex][i] < minDist[i]){
                        minDist[i] = adjMatrix[minIndex][i];
                        minIdx[i] = minIndex;
                    }
                }
            }
            return res;
        }

        AMGraph<T>* KruskalMST(){
            T vers[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* res = new AMGraph<T>(vers,numVer,false);

            int eStart[numEdge];
            int eEnd[numEdge];
            int eWeight[numEdge];
            int idx = 0;

            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j]==0) continue;
                    eStart[idx] = i;
                    eEnd[idx] = j;
                    eWeight[idx] = adjMatrix[i][j];
                    idx++;
                }
            }

            for(int i=0;i<numEdge;i++){
                for(int j=0;j<numEdge-1;j++){
                    if(eWeight[j] > eWeight[j+1]){
                        int tmp = eStart[j];
                        eStart[j] = eStart[j+1];
                        eStart[j+1] = tmp;
                        tmp = eEnd[j];
                        eEnd[j] = eEnd[j+1];
                        eEnd[j+1] = tmp;
                        tmp = eWeight[j];
                        eWeight[j] = eWeight[j+1];
                        eWeight[j+1] = tmp;
                    }
                }
            }

            idx = 0;
            int compNum[numVer];
            int numComponents = numVer;
            for(int i=0;i<numVer;i++){
                compNum[i] = i;
            }

            while(numComponents > 1){
                // investigate (eStart[idx],eEnd[idx])
                int sComp = compNum[eStart[idx]];
                int eComp = compNum[eEnd[idx]];
                if(sComp==eComp){
                    cout << "Dropping Edge: (" << verList.getEleAtPos(eStart[idx]);
                    cout << "," << verList.getEleAtPos(eEnd[idx]) << "), cost = " << eWeight[idx] << endl;
                    idx++;
                    continue;
                }

                cout << "Adding Edge: (" << verList.getEleAtPos(eStart[idx]);
                cout << "," << verList.getEleAtPos(eEnd[idx]) << "), cost = " << eWeight[idx] << endl;
                res->addEdge(verList.getEleAtPos(eStart[idx]),verList.getEleAtPos(eEnd[idx]), eWeight[idx]);
                numComponents--;
                idx++;

                int minComp = (eComp < sComp ? eComp : sComp);
                for(int i=0;i<numVer;i++){
                    if(compNum[i]==eComp || compNum[i]==sComp){
                        compNum[i] = minComp;
                    }
                }
            }
            return res;

        }

        //Topo
        void printTopo(){ //directed graphs only
            if(!directed){
                cout << "Directed graphs only!" << endl;
                return;
            }

            bool isActive[numVer];
            int inDeg[numVer];

            for(int i=0;i<numVer;i++){
                isActive[i] = true;
                inDeg[i] = 0;
                for(int j=0;j<numVer;j++){
                    if(adjMatrix[j][i]==0) continue;
                    inDeg[i]++;
                }
            }

            LinkQueue<int> q;
            int numInQ = 0;

            bool changes = true;
            while(changes){
                changes = false;
                for(int i=0;i<numVer;i++){
                    if(!isActive[i]) continue;
                    if(inDeg[i]!=0) continue;
                    q.enQueue(i);
                    isActive[i] = false;
                    numInQ++;
                    changes = true;
                    for(int j=0;j<numVer;j++){
                        if(adjMatrix[i][j]==0) continue;
                        inDeg[j]--;
                    }
                }
            }

            if(numInQ < numVer){
                cout << "Loop detected." << endl;
                return;
            }

            cout << "Topo ordering: ";
            while(!q.isEmpty()){
                cout << verList.getEleAtPos(q.deQueue()) << " ";
            }
            cout << endl;
        }
};

// put something that multiplies matrix, just for demonstrating meaning of A^k
// another that multiplies matrix.
template <class T>
void printMatrix(T** mat, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << setw(7) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// multiply 2 square matrices
int** mulMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = 0;
            for(int k=0;k<n;k++){
                tmp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return tmp;
}

int** addMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = mat1[i][j]+mat2[i][j];
        }
    }
    return tmp;
}

void test0(){
    int ver[9] = {1,2,3,4,5,6,7,8,9};
    Edge<int>* edges[10];
    edges[0] = new Edge<int>{1,2};
    edges[1] = new Edge<int>{1,3};
    edges[2] = new Edge<int>{1,4};
    edges[3] = new Edge<int>{2,3};
    edges[4] = new Edge<int>{2,4};
    edges[5] = new Edge<int>{3,4};
    edges[6] = new Edge<int>{5,8};
    edges[7] = new Edge<int>{5,9};
    edges[8] = new Edge<int>{6,8};
    edges[9] = new Edge<int>{9,6};

    AMGraph<int> amg1(ver,9,edges,10);
    AMGraph<int> amg2(ver,9,edges,10,true);

    //amg1.addEdge(7,3);
    //amg1.addEdge(7,4);

    //amg2.addEdge(3,7);
    //amg2.addEdge(7,9);
    //amg2.removeEdge(6,8);

    cout << "Graph 1: " << endl;
    amg1.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg1.getMatrix(),9);
    cout << "BFS:" << endl;
    amg1.printBFS();
    cout << "DFS:" << endl;
    amg1.printDFS();

    cout << "Graph 2: " << endl;
    amg2.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg2.getMatrix(),9);
    cout << "BFS:" << endl;
    amg2.printBFS();
    cout << "DFS:" << endl;
    amg2.printDFS();

    cout << "Below is demonstration for powers of Adjacency matrix (for graph 1)" << endl;
    int** amg1_m1 = amg1.getMatrix();
    int** amg1_m2 = mulMatrix(amg1_m1,amg1_m1,9);
    int** amg1_m3 = mulMatrix(amg1_m1,amg1_m2,9);
    int** amg1_m4 = mulMatrix(amg1_m1,amg1_m3,9);
    int** amg1_m5 = mulMatrix(amg1_m1,amg1_m4,9);
    int** amg1_m6 = mulMatrix(amg1_m1,amg1_m5,9);
    int** amg1_m7 = mulMatrix(amg1_m1,amg1_m6,9);
    int** amg1_m8 = mulMatrix(amg1_m1,amg1_m7,9);
    int** amg1_m9 = mulMatrix(amg1_m1,amg1_m8,9);
    int** result = addMatrix(amg1_m1,amg1_m2,9);
    result = addMatrix(amg1_m3,result,9);
    result = addMatrix(amg1_m4,result,9);
    result = addMatrix(amg1_m5,result,9);
    result = addMatrix(amg1_m6,result,9);
    result = addMatrix(amg1_m7,result,9);
    result = addMatrix(amg1_m8,result,9);
    result = addMatrix(amg1_m9,result,9);
    printMatrix(result,9);
}

void test2(){
    int ver[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(ver,6);
    amg1.addEdge(0,1,34);
    amg1.addEdge(0,5,19);
    amg1.addEdge(0,2,46);
    amg1.addEdge(5,2,25);
    amg1.addEdge(5,3,25);
    amg1.addEdge(5,4,26);
    amg1.addEdge(2,3,17);
    amg1.addEdge(3,4,38);
    amg1.addEdge(1,4,12);

    cout << "Prim: " << endl;
    amg1.PrimMST()->printGraph();
    cout << endl << "Kruskal: " << endl;
    amg1.KruskalMST()->printGraph();
}

void testTopo(){
    int ver[7] = {1,2,3,4,5,6,7};
    AMGraph<int> amg(ver,7,true);
    amg.addEdge(1,3);
    amg.addEdge(1,4);
    amg.addEdge(3,5);
    amg.addEdge(5,7);
    amg.addEdge(4,5);
    amg.addEdge(4,7);
    amg.addEdge(4,6);
    amg.addEdge(2,4);
    amg.addEdge(2,6);
    amg.addEdge(6,7);
    amg.printTopo();

    cout << "Adding a new edge: <7,4>:" << endl;
    amg.addEdge(7,4);
    amg.printTopo();

    cout << "Removing that edge <7,4> and reversing the edge <6,7> -> <7,6>:" << endl;
    amg.removeEdge(7,4);
    amg.removeEdge(6,7);
    amg.addEdge(7,6);
    amg.printTopo();
}

int main(){
    test2();
    testTopo();
    return 0;
}
