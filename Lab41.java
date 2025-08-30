import javax.swing.*;
import java.awt.*;
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

public class Lab41 extends JPanel {
    static final int MAX = 100;
    static final int BLOCKED = -999;
    static final int INF = 1000000000;
    static int[][] arr = new int[MAX][MAX];
    static int n, m;
    static int[] pathX = new int[MAX*MAX];
    static int[] pathY = new int[MAX*MAX];
    static int pathLen = 0;

    // Heap
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

    // Visualization
    int robotStep = 0;
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        int cellSize = Math.min(500/n, 500/m);
        // Draw grid background
        g.setColor(new Color(230, 230, 250)); // Light lavender
        g.fillRect(50, 50, m*cellSize, n*cellSize);
        // Draw cells
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                int x = 50 + j*cellSize;
                int y = 50 + i*cellSize;
                if (arr[i][j] == BLOCKED) {
                    g.setColor(new Color(80, 80, 80)); // Dark gray
                    g.fillRect(x, y, cellSize, cellSize);
                } else {
                    g.setColor(Color.WHITE);
                    g.fillRect(x, y, cellSize, cellSize);
                    g.setColor(new Color(120, 120, 120));
                    g.drawRect(x, y, cellSize, cellSize);
                    if (arr[i][j] > 0) {
                        g.setColor(new Color(34, 139, 34)); // Green for gifts
                    } else if (arr[i][j] < 0) {
                        g.setColor(new Color(220, 20, 60)); // Red for potholes
                    } else {
                        g.setColor(new Color(120, 120, 120)); // Neutral
                    }
                    g.setFont(new Font("Arial", Font.BOLD, cellSize/3));
                    g.drawString(String.valueOf(arr[i][j]), x+cellSize/4, y+cellSize/2);
                }
            }
        }
        // Draw path so far
        g.setColor(new Color(30, 144, 255)); // Dodger blue
        for (int s = 0; s <= robotStep && s < pathLen; s++) {
            int px = pathY[pathLen-1-s];
            int py = pathX[pathLen-1-s];
            int x = 50 + px*cellSize;
            int y = 50 + py*cellSize;
            g.fillOval(x+cellSize/3, y+cellSize/3, cellSize/3, cellSize/3);
        }
        // Draw robot
        if (robotStep < pathLen) {
            int rx = pathY[pathLen-1-robotStep];
            int ry = pathX[pathLen-1-robotStep];
            int x = 50 + rx*cellSize;
            int y = 50 + ry*cellSize;
            g.setColor(new Color(255, 140, 0)); // Orange for robot
            g.fillOval(x+cellSize/6, y+cellSize/6, cellSize*2/3, cellSize*2/3);
            g.setColor(Color.BLACK);
            g.setFont(new Font("Arial", Font.BOLD, cellSize/2));
            g.drawString("R", x+cellSize/3, y+cellSize*2/3);
        }
    }

    public void animate() throws InterruptedException {
        JFrame frame = new JFrame("Robot Path Visualizer");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(700, 700);
        frame.add(this);
        frame.setVisible(true);
        for (robotStep = 0; robotStep < pathLen; robotStep++) {
            repaint();
            Thread.sleep(900); // Slower animation for visibility
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        int[][] bestValue = new int[MAX][MAX];
        int[][] bestSteps = new int[MAX][MAX];
        int[][] parentX = new int[MAX][MAX];
        int[][] parentY = new int[MAX][MAX];

        System.out.print("Enter the no. of rows : ");
        n = sc.nextInt();
        System.out.print("Enter the no. of columns : ");
        m = sc.nextInt();

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
        int cx=0, cy=0;
        while (true) {
            pathX[pathLen]=cx;
            pathY[pathLen]=cy;
            int px=parentX[cx][cy], py=parentY[cx][cy];
            pathLen++;
            if (px == -1 && py == -1) break;
            cx=px; cy=py;
        }

        System.out.print("Path from entry (bottom-right) to exit (top-left):\n");
        for (int i=pathLen-1;i>=0;i--) {
            System.out.print("("+pathX[i]+","+pathY[i]+") ");
            if (i>0) System.out.print("-> ");
        }
        System.out.println();

        // Visualize
        Lab41 panel = new Lab41();
        panel.animate();
    }
}
