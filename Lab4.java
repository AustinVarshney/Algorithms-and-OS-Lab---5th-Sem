import java.util.Scanner;

class Node {
    int value, steps, x, y;
    Node(int v, int s, int x_coord, int y_coord) {
        value = v;
        steps = s;
        x = x_coord;
        y = y_coord;
    }
}

public class Lab4 {
    static final int MAX = 100;
    static final int BLOCKED = -999;
    static final int INF = 1000000000;

    static Node[] heapArr = new Node[MAX * MAX];
    static int heapSize = 0;

    static boolean isBetter(Node a, Node b) {
        if (a.steps == b.steps) return a.value > b.value;
        return a.steps < b.steps;
    }

    static void pushHeap(Node node) {
        heapArr[++heapSize] = node;
        int i = heapSize;
        while (i > 1 && isBetter(heapArr[i], heapArr[i/2])) {
            Node temp = heapArr[i];
            heapArr[i] = heapArr[i/2];
            heapArr[i/2] = temp;
            i /= 2;
        }
    }

    static boolean heapEmpty() { return heapSize == 0; }

    static Node popHeap() {
        if (heapSize == 0) return new Node(0,0,0,0);
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

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[][] arr = new int[MAX][MAX];
        int[][] bestValue = new int[MAX][MAX];
        int[][] bestSteps = new int[MAX][MAX];
        int[][] parentX = new int[MAX][MAX];
        int[][] parentY = new int[MAX][MAX];

        System.out.print("Enter the no. of rows : ");
        int n = sc.nextInt();
        System.out.print("Enter the no. of columns : ");
        int m = sc.nextInt();

        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                arr[i][j] = 0;

        System.out.println("\nEnter cells (x y val), val=-999 means blocked, end with x=-1:");
        while (true) {
            System.out.print("Enter the x-value : ");
            int x = sc.nextInt();
            if (x == -1) break;
            if (x < 0 || x >= n) continue;
            System.out.print("Enter the y-value : ");
            int y = sc.nextInt();
            if (y < 0 || y >= m) continue;
            System.out.print("Enter +ve gift, -ve pothole, or -999 blocked: ");
            int val = sc.nextInt();
            arr[x][y] = val;
        }

        System.out.println("\nGRID:");
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (arr[i][j] == BLOCKED) System.out.print("X ");
                else System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }

        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++) {
                bestValue[i][j] = -INF;
                bestSteps[i][j] = INF;
                parentX[i][j] = -1;
                parentY[i][j] = -1;
            }

        int[] dx = {-1,1,0,0};
        int[] dy = {0,0,-1,1};

        if (arr[n-1][m-1] == BLOCKED) {
            System.out.println("\nEntry point blocked!");
            return;
        }

        heapSize = 0;
        pushHeap(new Node(arr[n-1][m-1], 0, n-1, m-1));
        bestValue[n-1][m-1] = arr[n-1][m-1];
        bestSteps[n-1][m-1] = 0;

        while (!heapEmpty()) {
            Node cur = popHeap();
            int x = cur.x, y = cur.y;
            if (x == 0 && y == 0) break;

            for (int k=0;k<4;k++) {
                int nx = x+dx[k], ny = y+dy[k];
                if(nx<0||ny<0||nx>=n||ny>=m) continue;
                if(arr[nx][ny]==BLOCKED) continue;

                int newValue = cur.value + arr[nx][ny];
                int newSteps = cur.steps + 1;

                if (newSteps < bestSteps[nx][ny] ||
                    (newSteps == bestSteps[nx][ny] && newValue > bestValue[nx][ny])) {
                    bestValue[nx][ny] = newValue;
                    bestSteps[nx][ny] = newSteps;
                    parentX[nx][ny] = x;
                    parentY[nx][ny] = y;
                    pushHeap(new Node(newValue,newSteps,nx,ny));
                }
            }
        }

        if (bestValue[0][0] == -INF) {
            System.out.println("\nNo valid path exists!");
            return;
        }

        System.out.println("\nMaximum value collected: " + bestValue[0][0]);
        System.out.println("Minimum steps taken: " + bestSteps[0][0]);

        // Path reconstruction
        int[] pathX = new int[MAX*MAX];
        int[] pathY = new int[MAX*MAX];
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

        System.out.print("Path from entry (bottom-right) to exit (top-left):\n");
        for (int i=len-1;i>=0;i--) {
            System.out.print("("+pathX[i]+","+pathY[i]+") ");
            if (i>0) System.out.print("-> ");
        }
    }
}
