#include<iostream>
using namespace std;

const int BLOCKED = -999;
const int MAX_SIZE = 20;
const int MAX_STATES = 1000;

void stringCopy(char* dest, const char* src){
    int i = 0;
    while (src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int stringCompare(const char* str1, const char* str2){
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0'){
        if (str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

struct Coordinate{
    int x, y;
};

struct Path{
    Coordinate points[MAX_SIZE];
    int length = 0;
    
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
    
    void copyFrom(const Path& other){
        length = other.length;
        for (int i = 0; i < length; i++){
            points[i] = other.points[i];
        }
    }
};

struct GiftSet{
    char gifts[MAX_SIZE][10]; // "x,y" format
    int count = 0;
    
    void addGift(int x, int y){
        if (count < MAX_SIZE){
            sprintf(gifts[count], "%d,%d", x, y);
            count++;
        }
    }
    
    bool hasGift(int x, int y){
        char key[20];
        sprintf(key, "%d,%d", x, y);
        for (int i = 0; i < count; i++){
            if (stringCompare(gifts[i], key) == 0){
                return true;
            }
        }
        return false;
    }
    
    void copyFrom(const GiftSet& other){
        count = other.count;
        for (int i = 0; i < count; i++){
            stringCopy(gifts[i], other.gifts[i]);
        }
    }
};

struct State{
    int x, y, value, steps;
    Path path;
    GiftSet collected;
    
    void copyFrom(const State& other){
        x = other.x;
        y = other.y;
        value = other.value;
        steps = other.steps;
        path.copyFrom(other.path);
        collected.copyFrom(other.collected);
    }
};

struct StateQueue{
    State states[MAX_STATES];
    int size = 0;
    
    bool isEmpty(){
        return size == 0;
    }
    
    void push(const State& state){
        if (size < MAX_STATES){
            states[size] = state;
            size++;
        }
    }
};

void printGrid(int grid[MAX_SIZE][MAX_SIZE], int rows, int cols, int exitX, int exitY, const Path& path, const GiftSet& collected){
    cout<<"Final Grid with Path:"<<endl;    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            bool isOnPath = false;
            for (int k = 0; k < path.length; k++){
                if (path.points[k].x == i && path.points[k].y == j){
                    isOnPath = true;
                    break;
                }
            }
            
            if (i == exitX && j == exitY){
                cout<<"E ";
            } else if (isOnPath){
                cout<<"* ";
            } else if (grid[i][j] == BLOCKED){
                cout<<"X ";
            } else{
                cout<<grid[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

int main(){
    int rows, cols;    
    cout<<"Enter the no. of rows : ";
    cin >> rows;
    cout<<"Enter the no. of columns : ";
    cin >> cols;
    
    int grid[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = 0;
    
    while (true){
        int x, y, val;
        cout<<"Enter the x-value : ";
        cin >> x;
        if (x == -1) break;
        if (x < 0 || x >= rows) continue;
        cout<<"Enter the y-value : ";
        cin >> y;
        if (y < 0 || y >= cols) continue;
        cout<<"Enter +ve for gift, -ve for pothole, or -999 for blocked: ";
        cin >> val;
        grid[x][y] = val;
    }
    
    cout<<"Initial Matrix is : "<<endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (grid[i][j] == BLOCKED) cout<<"X ";
            else cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }

    int startX = rows - 1, startY = cols - 1;
    
    StateQueue queue;
    
    State initialState;
    initialState.x = rows-1;
    initialState.y = cols-1;
    initialState.value = grid[startX][startY];
    initialState.steps = 0;
    initialState.path.addPoint(startX, startY);
    if (grid[startX][startY] > 0){
        initialState.collected.addGift(startX, startY);
    }
    
    queue.push(initialState);
    
    State bestState;
    bestState.steps = -1;
    double bestRatio = -999999.0;
    
    int dx[] ={-1, 1, 0, 0};
    int dy[] ={0, 0, -1, 1};
    
    int maxSteps = rows * cols;
    
    while (!queue.isEmpty()){
        State current = queue.states[0];

        for (int i = 0; i < queue.size - 1; i++){
            queue.states[i] = queue.states[i + 1];
        }
        queue.size--;

        if (current.steps > maxSteps) continue;

        if (current.x == 0 && current.y == 0){
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

                State newState;
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
        cout<<"No valid path exists!"<<endl;
        return 0;
    }
    
    cout<<"Steps = "<<bestState.steps<<", Value = "<<bestState.value<<endl;
    
    cout<<"Path from entry (bottom-right) to exit (top-left):\n";
    for (int i = 0; i < bestState.path.length; i++){
        cout<<"("<<bestState.path.points[i].x<<","<<bestState.path.points[i].y<<")";
        if (i < bestState.path.length - 1) cout<<" -> ";
    }
    cout<<endl;
    
    printGrid(grid, rows, cols, 0, 0, bestState.path, bestState.collected);    
    cout<<"Robot has reached the exit!"<<endl;    
    return 0;
}