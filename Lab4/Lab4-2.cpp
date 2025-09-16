#include<iostream>
using namespace std;

const int MAX = 100;
const int BLOCKED = -999;
const int INF = 1000000000;

struct Node {
    int value;
    int steps;
    int x, y;
    Node(int v = 0, int s = 0, int x_coord = 0, int y_coord = 0) {
        value = v;
        steps = s;
        x = x_coord;
        y = y_coord;
    }
};

// Custom heap implementation
Node heapArr[MAX * MAX];
int heapSize = 0;

bool isBetter(const Node& a, const Node& b) {
    // Prioritize lower steps first, then higher value
    if (a.steps == b.steps) return a.value > b.value;
    return a.steps < b.steps;
}

void pushHeap(Node node) {
    heapSize++;
    heapArr[heapSize] = node;
    int i = heapSize;
    while (i > 1 && isBetter(heapArr[i], heapArr[i/2])) {
        Node temp = heapArr[i];
        heapArr[i] = heapArr[i/2];
        heapArr[i/2] = temp;
        i /= 2;
    }
}

bool heapEmpty() { return heapSize == 0; }

Node popHeap() {
    if (heapSize == 0) return Node();
    Node top = heapArr[1];
    heapArr[1] = heapArr[heapSize];
    heapSize--;
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

int main() {
    int arr[MAX][MAX];
    int bestValue[MAX][MAX];
    int bestSteps[MAX][MAX];
    int parentX[MAX][MAX], parentY[MAX][MAX];

    int n, m;
    cout << "Enter the no. of rows : ";
    cin >> n;
    cout << "Enter the no. of columns : ";
    cin >> m;

    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            arr[i][j] = 0;

    cout << "\nEnter cells (x y val), val=-999 means blocked, end with x=-1:\n";
    while (true) {
        int x, y, val;
        cout << "Enter the x-value : ";
        cin >> x;
        if (x == -1) break;
        if (x < 0 || x >= n) continue;
        cout << "Enter the y-value : ";
        cin >> y;
        if (y < 0 || y >= m) continue;
        cout << "Enter +ve gift, -ve pothole, or -999 blocked: ";
        cin >> val;
        arr[x][y] = val;
    }

    cout << "\nGRID:\n";
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (arr[i][j] == BLOCKED) cout << "X ";
            else cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++) {
            bestValue[i][j] = -INF;
            bestSteps[i][j] = INF;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
        }

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    if (arr[n-1][m-1] == BLOCKED) {
        cout << "\nEntry point blocked!\n";
        return 0;
    }

    heapSize = 0;
    pushHeap(Node(arr[n-1][m-1], 0, n-1, m-1));
    bestValue[n-1][m-1] = arr[n-1][m-1];
    bestSteps[n-1][m-1] = 0;

    while (!heapEmpty()) {
        Node cur = popHeap();
        int x = cur.x, y = cur.y;
        if (x == 0 && y == 0) break; // Stop when exit is reached

        for (int k=0;k<4;k++) {
            int nx = x+dx[k], ny = y+dy[k];
            if(nx<0||ny<0||nx>=n||ny>=m) continue;
            if(arr[nx][ny]==BLOCKED) continue;

            int newValue = cur.value + arr[nx][ny];
            int newSteps = cur.steps + 1;

            // Prioritize lower steps, then higher value
            if (newSteps < bestSteps[nx][ny] ||
                (newSteps == bestSteps[nx][ny] && newValue > bestValue[nx][ny])) {
                bestValue[nx][ny] = newValue;
                bestSteps[nx][ny] = newSteps;
                parentX[nx][ny] = x;
                parentY[nx][ny] = y;
                pushHeap(Node(newValue,newSteps,nx,ny));
            }
        }
    }

    if (bestValue[0][0] == -INF) {
        cout<<"\nNo valid path exists!\n";
        return 0;
    }

    cout<<"Maximum value collected: "<<bestValue[0][0]<<"\n";
    cout<<"Minimum steps taken: "<<bestSteps[0][0]<<"\n";

    // Path reconstruction
    int pathX[MAX*MAX], pathY[MAX*MAX];
    int len=0;
    int cx=0, cy=0;
    while (true) {
        pathX[len]=cx;
        pathY[len]=cy;
        int px=parentX[cx][cy], py=parentY[cx][cy];
        len++;
        if (px == -1 && py == -1) break;
        cx=px; cy=py;
    }

    cout<<"Path from entry (bottom-right) to exit (top-left):\n";
    for (int i=len-1;i>=0;i--) {
        cout<<"("<<pathX[i]<<","<<pathY[i]<<") ";
        if (i>0) cout<<"-> ";
    }
    return 0;
}