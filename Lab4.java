import java.util.Scanner;

public class Lab4{
    static final int BLOCKED = -999;
    static final int MAX_SIZE = 20;
    static final int MAX_STATES = 1000;

    static void stringCopy(char[] dest, char[] src){
        int i = 0;
        while (i < src.length && src[i] != '\0'){
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    static int stringCompare(char[] str1, char[] str2){
        int i = 0;
        while (i < str1.length && i < str2.length && str1[i] != '\0' && str2[i] != '\0'){
            if (str1[i] != str2[i]){
                return str1[i] - str2[i];
            }
            i++;
        }
        if (i < str1.length && str1[i] != '\0') return 1;
        if (i < str2.length && str2[i] != '\0') return -1;
        return 0;
    }

    static class Coordinate{
        int x, y;
        
        Coordinate(){
            x = 0;
            y = 0;
        }
    }

    static class Path{
        Coordinate[] points;
        int length = 0;
        
        Path(){
            points = new Coordinate[MAX_SIZE];
            for (int i = 0; i < MAX_SIZE; i++){
                points[i] = new Coordinate();
            }
        }
        
        void addPoint(int x, int y){
            if (length < MAX_SIZE){
                points[length].x = x;
                points[length].y = y;
                length++;
            }
        }
        
        int countPoint(int x, int y){
            int count = 0;
            for (int i = 0; i < length; i++){
                if (points[i].x == x && points[i].y == y){
                    count++;
                }
            }
            return count;
        }
        
        void copyFrom(Path other){
            length = other.length;
            for (int i = 0; i < length; i++){
                points[i].x = other.points[i].x;
                points[i].y = other.points[i].y;
            }
        }
    }

    static class GiftSet{
        char[][] gifts; // "x,y" format
        int count = 0;
        
        GiftSet(){
            gifts = new char[MAX_SIZE][10];
        }
        
        // Helper: convert int to string
        void intToStr(int num, char[] buf){
            int i = 0, j;
            if (num < 0){ 
                buf[i++] = '-'; 
                num = -num; 
            }
            int start = i;
            int n = num, len = 0;
            if (n == 0){ 
                buf[i++] = '0'; 
                buf[i] = '\0'; 
                return; 
            }
            while (n > 0){ 
                buf[i++] = (char)((n % 10) + '0'); 
                n /= 10; 
                len++; 
            }
            buf[i] = '\0';
            // Reverse digits
            for (j = 0; j < len / 2; j++){
                char t = buf[start + j];
                buf[start + j] = buf[start + len - 1 - j];
                buf[start + len - 1 - j] = t;
            }
        }
        
        void addGift(int x, int y){
            if (count < MAX_SIZE){
                char[] xstr = new char[10];
                char[] ystr = new char[10];
                intToStr(x, xstr);
                intToStr(y, ystr);
                int k = 0, i = 0;
                while (i < xstr.length && xstr[i] != '\0') gifts[count][k++] = xstr[i++];
                gifts[count][k++] = ',';
                i = 0;
                while (i < ystr.length && ystr[i] != '\0') gifts[count][k++] = ystr[i++];
                gifts[count][k] = '\0';
                count++;
            }
        }
        
        boolean hasGift(int x, int y){
            char[] key = new char[20];
            char[] xstr = new char[10];
            char[] ystr = new char[10];
            intToStr(x, xstr);
            intToStr(y, ystr);
            int k = 0, i = 0;
            while (i < xstr.length && xstr[i] != '\0') key[k++] = xstr[i++];
            key[k++] = ',';
            i = 0;
            while (i < ystr.length && ystr[i] != '\0') key[k++] = ystr[i++];
            key[k] = '\0';
            for (int j = 0; j < count; j++){
                if (stringCompare(gifts[j], key) == 0){
                    return true;
                }
            }
            return false;
        }
        
        void copyFrom(GiftSet other){
            count = other.count;
            for (int i = 0; i < count; i++){
                stringCopy(gifts[i], other.gifts[i]);
            }
        }
    }

    static class State{
        int x, y;
        int value;
        int steps;
        Path path;
        GiftSet collected;
        
        State(){
            path = new Path();
            collected = new GiftSet();
        }
        
        void copyFrom(State other){
            x = other.x;
            y = other.y;
            value = other.value;
            steps = other.steps;
            path.copyFrom(other.path);
            collected.copyFrom(other.collected);
        }
    }

    static class StateQueue{
        State[] states;
        int size;
        
        StateQueue(){
            states = new State[MAX_STATES];
            for (int i = 0; i < MAX_STATES; i++){
                states[i] = new State();
            }
            size = 0;
        }
        
        boolean isEmpty(){
            return size == 0;
        }
        
        void push(State state){
            if (size < MAX_STATES){
                states[size].copyFrom(state);
                size++;
            }
        }
    }

    static void printGrid(int[][] grid, int rows, int cols, int robotX, int robotY, Path path, int currentStep){
        System.out.print("\033[H\033[2J"); // Clear screen
        System.out.flush();
        System.out.println("Grid:");
        String horizontal = "\033[45m+"; // Magenta background for grid lines
        for (int j = 0; j < cols; j++) horizontal += "------+";
        
        for (int i = 0; i < rows; i++){
            System.out.println(horizontal + "\033[0m");
            for (int j = 0; j < cols; j++){
                boolean isRobot = (i == robotX && j == robotY);
                boolean isPath = false;
                
                // Check if current cell is on the path up to current step
                for (int k = 0; k <= currentStep && k < path.length; k++){
                    if (i == path.points[k].x && j == path.points[k].y){
                        isPath = true;
                        break;
                    }
                }
                
                String cell = "      ";
                String color = "\033[47m"; // Default: white background
                
                if (isRobot){
                    color = "\033[43m\033[30m"; // Yellow bg, black text
                    cell = "  R   ";
                } else if (grid[i][j] == BLOCKED){
                    color = "\033[41m\033[97m"; // Red bg, white text
                    cell = "  X   ";
                } else if (isPath){
                    color = "\033[44m\033[97m"; // Blue bg, white text
                    cell = "  .   ";
                } else if (grid[i][j] < 0){
                    color = "\033[101m\033[30m"; // Bright red bg, black text
                    cell = String.format("%5d ", grid[i][j]);
                } else if (grid[i][j] > 0){
                    color = "\033[102m\033[30m"; // Bright green bg, black text
                    cell = String.format("%5d ", grid[i][j]);
                } else{
                    color = "\033[47m\033[30m"; // White bg, black text
                    cell = "  0   ";
                }
                System.out.print(color + "|" + cell + "\033[0m");
            }
            System.out.println("|\033[0m");
        }
        System.out.println(horizontal + "\033[0m");
    }

    static void printFinalGrid(int[][] grid, int rows, int cols, int exitX, int exitY, 
                              Path path, GiftSet collected){
        System.out.println("Final Grid with Path:");
        
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                boolean isOnPath = false;
                for (int k = 0; k < path.length; k++){
                    if (path.points[k].x == i && path.points[k].y == j){
                        isOnPath = true;
                        break;
                    }
                }
                
                if (i == exitX && j == exitY){
                    System.out.print("E ");
                } else if (isOnPath){
                    System.out.print("* ");
                } else if (grid[i][j] == BLOCKED){
                    System.out.print("X ");
                } else{
                    System.out.print(grid[i][j] + " ");
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the no. of rows : ");
        int rows = scanner.nextInt();
        System.out.print("Enter the no. of columns : ");
        int cols = scanner.nextInt();
        
        int[][] grid = new int[MAX_SIZE][MAX_SIZE];
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                grid[i][j] = 0;
            }
        }
        
        System.out.println("Enter cells (x y val), val=-999 means blocked, end with x=-1:");
        while (true){
            System.out.print("Enter the x-value : ");
            int x = scanner.nextInt();
            if (x == -1) break;
            if (x < 0 || x >= rows) continue;
            System.out.print("Enter the y-value : ");
            int y = scanner.nextInt();
            if (y < 0 || y >= cols) continue;
            System.out.print("Enter +ve for gift, -ve for pothole, or -999 for blocked: ");
            int val = scanner.nextInt();
            grid[x][y] = val;
        }
        
        System.out.println("GRID:");
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (grid[i][j] == BLOCKED) System.out.print("X ");
                else System.out.print(grid[i][j] + " ");
            }
            System.out.println();
        }
        
        int startX = rows - 1, startY = cols - 1;
        int endX = 0, endY = 0;
        
        StateQueue queue = new StateQueue();
        
        State initialState = new State();
        initialState.x = startX;
        initialState.y = startY;
        initialState.value = grid[startX][startY];
        initialState.steps = 0;
        initialState.path.addPoint(startX, startY);
        if (grid[startX][startY] > 0){
            initialState.collected.addGift(startX, startY);
        }
        
        queue.push(initialState);
        
        State bestState = new State();
        bestState.steps = -1;
        double bestRatio = -999999.0;
        
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};
        
        int maxSteps = rows * cols;
        
        while (!queue.isEmpty()){
            State current = new State();
            current.copyFrom(queue.states[0]);
            for (int i = 0; i < queue.size - 1; i++){
                queue.states[i].copyFrom(queue.states[i + 1]);
            }
            queue.size--;

            if (current.steps > maxSteps) continue;

            if (current.x == endX && current.y == endY){
                double currentRatio = current.steps > 0 ? (double)current.value / current.steps : current.value;
                if (bestState.steps == -1 || currentRatio > bestRatio){
                    bestState.copyFrom(current);
                    bestRatio = currentRatio;
                }
                continue;
            }

            for (int i = 0; i < 4; i++){
                int newX = current.x + dx[i];
                int newY = current.y + dy[i];

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] != BLOCKED){
                    if (current.path.countPoint(newX, newY) > 0) continue;

                    State newState = new State();
                    newState.x = newX;
                    newState.y = newY;
                    newState.steps = current.steps + 1;
                    newState.value = current.value;
                    newState.path.copyFrom(current.path);
                    newState.path.addPoint(newX, newY);
                    newState.collected.copyFrom(current.collected);

                    int cellValue = grid[newX][newY];
                    if (cellValue > 0){
                        if (!current.collected.hasGift(newX, newY)){
                            newState.value += cellValue;
                            newState.collected.addGift(newX, newY);
                        }
                    } else if (cellValue < 0){
                        newState.value += cellValue;
                    }
                    queue.push(newState);
                }
            }
        }
        
        if (bestState.steps == -1){
            System.out.println("No valid path exists!");
            scanner.close();
            return;
        }
        
        System.out.println("Steps = " + bestState.steps + ", Value = " + bestState.value);

        System.out.println("Path from entry (bottom-right) to exit (top-left):");
        for (int i = 0; i < bestState.path.length; i++){
            System.out.print("(" + bestState.path.points[i].x + "," + bestState.path.points[i].y + ")");
            if (i < bestState.path.length - 1) System.out.print(" -> ");
        }
        System.out.println();
        
        System.out.println("Animating robot movement...");
        try{
            for (int step = 0; step < bestState.path.length; step++){
                printGrid(grid, rows, cols, 
                         bestState.path.points[step].x, 
                         bestState.path.points[step].y, 
                         bestState.path, step);
                Thread.sleep(1600);
            }
        } catch (InterruptedException e){
            System.out.println("Animation interrupted.");
        }
        
        // Show final grid
        printFinalGrid(grid, rows, cols, endX, endY, bestState.path, bestState.collected);
        
        System.out.println("Robot has reached the exit!");
        
        scanner.close();
    }
}