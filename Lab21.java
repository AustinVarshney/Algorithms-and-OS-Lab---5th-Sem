import java.util.*;

public class Lab21 {
    static final int MAX = 100;
    static final int INF = 100000;

    static int PrimsAlgo(int[][] graph, int n, int stIdx, int[] verticeProp, boolean filterByGround) {
        boolean[] visited = new boolean[n];
        int minLength = 0;

        int[] Distance_TV = new int[n];
        int[] Nbr_TV = new int[n];
        Arrays.fill(Distance_TV, INF);
        Arrays.fill(Nbr_TV, -1);

        List<Integer> TE = new ArrayList<>();

        for (int j = 0; j < n; j++) {
            boolean includeNode = filterByGround ? (verticeProp[j] == 1) : true;
            if (includeNode && graph[stIdx][j] != INF && j != stIdx) {
                Nbr_TV[j] = stIdx;
                Distance_TV[j] = graph[stIdx][j];
            }
        }

        Distance_TV[stIdx] = 0;
        Nbr_TV[stIdx] = -1;
        visited[stIdx] = true;

        for (int i = 1; i < n; i++) {
            int idx = -1;
            for (int j = 0; j < n; j++) {
                boolean includeNode = filterByGround ? (verticeProp[j] == 1) : true;
                if (includeNode && !visited[j] && (idx == -1 || Distance_TV[j] < Distance_TV[idx])) {
                    idx = j;
                }
            }
            if (idx == -1) break;

            visited[idx] = true;

            TE.add(graph[idx][Nbr_TV[idx]]);
            minLength += graph[idx][Nbr_TV[idx]];
            System.out.println(Nbr_TV[idx] + " - " + idx + " -> (" + graph[idx][Nbr_TV[idx]] + ")");

            for (int j = 0; j < n; j++) {
                boolean includeNode = filterByGround ? (verticeProp[j] == 1) : true;
                if (includeNode && (Distance_TV[j] > graph[idx][j]) && !visited[j]) {
                    Distance_TV[j] = graph[idx][j];
                    Nbr_TV[j] = idx;
                }
            }
        }

        return minLength;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the no. of vertices : ");
        int n = sc.nextInt();
        int[][] graph = new int[MAX][MAX];
        int[] verticeProp = new int[n];

        for (int i = 0; i < n; i++) {
            verticeProp[i] = -1;
            Arrays.fill(graph[i], INF);
        }

        int totalG = 0;
        int firstG = 0;

        while (true) {
            System.out.print("Enter 1st Node : ");
            int u = sc.nextInt();
            if (u == -1) break;
            if (verticeProp[u] == -1) {
                System.out.print("Enter 1 if grounded or 0 : ");
                int isHavingGround = sc.nextInt();
                verticeProp[u] = isHavingGround;
                if (isHavingGround == 1) {
                    totalG++;
                    if (totalG == 1) {
                        firstG = u;
                    }
                }
            }

            System.out.print("Enter 2nd Node : ");
            int v = sc.nextInt();
            if (verticeProp[v] == -1) {
                System.out.print("Enter 1 if grounded or 0 : ");
                int isHavingGround = sc.nextInt();
                verticeProp[v] = isHavingGround;
                if (isHavingGround == 1) {
                    totalG++;
                    if (totalG == 1) {
                        firstG = v;
                    }
                }
            }

            System.out.print("Enter Weight : ");
            int weight = sc.nextInt();

            graph[u][v] = weight;
            graph[v][u] = weight;

            System.out.println("<--------------Edge is added-------------->");
        }

        int minG = PrimsAlgo(graph, n, firstG, verticeProp, true);
        System.out.println("Value of answer1 is : " + minG);
        int minN = PrimsAlgo(graph, n, 0, verticeProp, false);
        System.out.println("Value of answer2 is : " + minN);
        int minL = PrimsAlgo(graph, n, 0, verticeProp, false);
        System.out.println("Value of answer3 is : " + minL);

        System.out.println("Total Length of the wire required : " + (minL + minG + minN));

        sc.close();
    }
}
