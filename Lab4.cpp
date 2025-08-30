#include<iostream>
using namespace std;

const int MAX = 100;

struct Node {
    int value; // total collected value
    int steps; // number of steps
    int x, y;  // position
};

// Manual heap implementation
Node heapArr[MAX*MAX];
int heapSize = 0;

bool isBetter(Node a, Node b) {
    // Higher value first, if tie then lower steps
    if (a.value == b.value) return a.steps < b.steps;
    return a.value > b.value;
}

void pushHeap(Node node) {
    heapArr[++heapSize] = node;
    int i = heapSize;
    while (i > 1 && isBetter(heapArr[i], heapArr[i/2])) {
        Node temp = heapArr[i];
        heapArr[i] = heapArr[i/2];
        heapArr[i/2] = temp;
        i /= 2;
    }
}

bool heapEmpty() {
    return heapSize == 0;
}

Node popHeap() {
    Node top = heapArr[1];
    heapArr[1] = heapArr[heapSize--];
    int i = 1;
    while (true) {
        int left = i*2, right = i*2+1, largest = i;
        if (left <= heapSize && isBetter(heapArr[left], heapArr[largest])) largest = left;
        if (right <= heapSize && isBetter(heapArr[right], heapArr[largest])) largest = right;
        if (largest != i) {
            Node temp = heapArr[i];
            heapArr[i] = heapArr[largest];
            heapArr[largest] = temp;
            i = largest;
        } else break;
    }
    return top;
}

int main(){
    int arr[MAX][MAX];
    int bestValue[MAX][MAX];
    int bestSteps[MAX][MAX];

    
    int n, m;
    cout<<"Enter the no. of rows : ";
    cin>>n;
    cout<<"Enter the no. of columns : ";
    cin>>m;
    
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            arr[i][j] = 0;
        }
    }
    
    while(true){
        int x, y, val;
        cout<<"Enter the x-value : ";
        cin>>x;
        if(x == -1) break;
        if(x < 0 || x >= n) continue;
        cout<<"Enter the y-value : ";
        cin>>y;
        if(y < 0 || y >= m) continue;
        cout<<"Enter either +ve value, -ve value, or -1 for blocked cell : ";
        cin>>val;

        arr[x][y] = val;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }

    // Initialize best arrays
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++) {
            bestValue[i][j] = -1;
            bestSteps[i][j] = -1;
        }

    // Directions: up, down, left, right
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    // Start at bottom-right
    if (arr[n-1][m-1] == -1) {
        cout<<"\nEntry point blocked!\n";
        return 0;
    }

    heapSize = 0;
    pushHeap({arr[n-1][m-1],0,n-1,m-1});
    bestValue[n-1][m-1] = arr[n-1][m-1];
    bestSteps[n-1][m-1] = 0;

     while (!heapEmpty()) {
        Node cur = popHeap();
        int x=cur.x, y=cur.y;

        if (x==0 && y==0) {
            cout<<"\nMaximum value collected: "<<cur.value<<"\n";
            cout<<"Minimum steps taken: "<<cur.steps<<"\n";
            return 0;
        }

        for (int k=0;k<4;k++) {
            int nx=x+dx[k], ny=y+dy[k];
            if(nx<0||ny<0||nx>=n||ny>=m) continue;
            if(arr[nx][ny]==-1) continue; // blocked

            int newValue = cur.value + arr[nx][ny];
            int newSteps = cur.steps + 1;

            if (newValue > bestValue[nx][ny] || 
                (newValue==bestValue[nx][ny] && newSteps<bestSteps[nx][ny])) {
                bestValue[nx][ny] = newValue;
                bestSteps[nx][ny] = newSteps;
                pushHeap({newValue,newSteps,nx,ny});
            }
        }
    }

    cout<<"\nNo valid path exists!\n";

    return 0;
}