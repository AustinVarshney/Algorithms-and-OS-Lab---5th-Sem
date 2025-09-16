import java.util.*;

public class Lab2 {
    static final int MAX = 100;
    static final int INF = 100000;

    static int primsAlgo(int[][] graph, int n, int stIdx, char[] verticeProp) {
        char currChar = verticeProp[stIdx];
        boolean[] visited = new boolean[n];
        int minLength = 0;

        int[] distanceTV = new int[n];
        int[] nbrTV = new int[n];
        Arrays.fill(distanceTV, INF);
        Arrays.fill(nbrTV, -1);

        List<Integer> TE = new ArrayList<>();

        for (int j = 0; j < n; j++) {
            if (verticeProp[j] == currChar && graph[stIdx][j] != INF && j != stIdx) {
                nbrTV[j] = stIdx;
                distanceTV[j] = graph[stIdx][j];
            }
        }

        distanceTV[stIdx] = 0;
        nbrTV[stIdx] = -1;
        visited[stIdx] = true;

        for (int i = 1; i < n; i++) {
            int idx = -1;
            for (int j = 0; j < n; j++) {
                if (verticeProp[j] == currChar && !visited[j] &&
                        (idx == -1 || distanceTV[j] < distanceTV[idx])) {
                    idx = j;
                }
            }
            if (idx == -1) break;

            visited[idx] = true;

            TE.add(graph[idx][nbrTV[idx]]);
            minLength += graph[idx][nbrTV[idx]];
            System.out.println(idx + " - " + nbrTV[idx] + " -> " + graph[idx][nbrTV[idx]]);

            for (int j = 0; j < n; j++) {
                if (verticeProp[j] == currChar && (distanceTV[j] > graph[idx][j]) && !visited[j]) {
                    distanceTV[j] = graph[idx][j];
                    nbrTV[j] = idx;
                }
            }
        }

        return minLength;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[][] graph = new int[MAX][MAX];

        System.out.print("Enter the no. of vertices : ");
        int n = sc.nextInt();

        char[] verticeProp = new char[n];
        for (int i = 0; i < n; i++) {
            verticeProp[i] = 'D'; // 'D' = no valid property yet
            Arrays.fill(graph[i], INF);
        }

        int totalG = 0, totalN = 0, totalL = 0;
        int firstG = -1, firstN = -1, firstL = -1;

        while (true) {
            System.out.print("Enter 1st Node : ");
            int u = sc.nextInt();
            if (u == -1) break;

            if (verticeProp[u] == 'D') {
                System.out.print("Enter the Property1 : ");
                char prop1 = sc.next().charAt(0);
                verticeProp[u] = prop1;
                if (prop1 == 'G') {
                    totalG++;
                    if (totalG == 1) firstG = u;
                } else if (prop1 == 'N') {
                    totalN++;
                    if (totalN == 1) firstN = u;
                } else if (prop1 == 'L') {
                    totalL++;
                    if (totalL == 1) firstL = u;
                }
            }

            System.out.print("Enter 2nd Node : ");
            int v = sc.nextInt();
            if (verticeProp[v] == 'D') {
                System.out.print("Enter the Property2 : ");
                char prop2 = sc.next().charAt(0);
                verticeProp[v] = prop2;
                if (prop2 == 'G') {
                    totalG++;
                    if (totalG == 1) firstG = v;
                } else if (prop2 == 'N') {
                    totalN++;
                    if (totalN == 1) firstN = v;
                } else if (prop2 == 'L') {
                    totalL++;
                    if (totalL == 1) firstL = v;
                }
            }

            System.out.print("Enter Weight : ");
            int weight = sc.nextInt();

            graph[u][v] = weight;
            graph[v][u] = weight;
        }

        int minG = primsAlgo(graph, n, firstG, verticeProp);
        System.out.println("Value of answer1 is : " + minG);
        int minN = primsAlgo(graph, n, firstN, verticeProp);
        System.out.println("Value of answer2 is : " + minN);
        int minL = primsAlgo(graph, n, firstL, verticeProp);
        System.out.println("Value of answer3 is : " + minL);

        sc.close();
    }
}