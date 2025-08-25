#include<iostream>
using namespace std;

const int MAX = 100;

template <typename T>
class Stack{
    T arr[MAX];
    int topIdx = -1;
public:
    void push(T el){
        topIdx++;
        arr[topIdx] = el;
    }

    void pop(){
        if(topIdx == -1) return;
        topIdx--;
    }

    bool empty(){
        return topIdx == -1;
    }

    T top(){
        if(topIdx == -1) return T();
        return arr[topIdx];
    }

    int size(){
        return topIdx + 1;
    }
};

template <typename T>
void printSingleStack(string name, Stack<T> st) {
    cout << name << ": ";
    if (st.empty()) {
        cout << "[ empty ]";
    } else {
        cout << "[ ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << "]";
    }
    cout << "\n";
};

template <typename T>
void printStacks(int stepNo, Stack<T> mainStack, Stack<T> stack1, Stack<T> stack2) {
    cout << "--- Step " << stepNo << " ---"<<endl;

    printSingleStack("mainStack", mainStack);
    printSingleStack("stack1   ", stack1);
    printSingleStack("stack2   ", stack2);
    cout << "-------------------\n";
}

int main(){
    Stack<string> mainStack;
    string colors[MAX];
    int totColors = 0;

    while(true){
        string col;
        cout<<"Enter the colour or 0 to stop : ";
        cin>>col;

        if(col == "0") break;

        mainStack.push(col);
        bool isColorPresent = false;
        for(string colour : colors){
            if(col == colour){
                isColorPresent = true;
                break;
            }
        }

        if(!isColorPresent){
            colors[totColors++] = col;
        }
    }

    for(int i=0; i<totColors-1; i++){
        for(int j=i+1; j<totColors; j++){
            if(colors[i] == colors[j]){
                swap(colors[j], colors[i+1]);
                i++;
            } else if(colors[i] > colors[j]){
                swap(colors[i], colors[j]);
            }
        }
    }

    for(string color : colors){
        cout<<color<<" ";
    }
    cout<<endl;

    Stack<string> stack1;
    Stack<string> stack2;
    int totTransfer = 0;

    while(mainStack.size() != 0){
        string topCol = mainStack.top();
        mainStack.pop();

        if(topCol == colors[totColors-1]){
            stack1.push(topCol);
            cout<<totTransfer+1<<". "<<topCol<<" is going from mainStack to Stack 1"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
        } else{
            stack2.push(topCol);
            cout<<totTransfer+1<<". "<<topCol<<" is going from mainStack to Stack 2"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
        }
        
        totTransfer++;
    }
    
    while(stack1.size() != 0){
        mainStack.push(stack1.top());
        stack1.pop();
        cout<<totTransfer+1<<". "<<stack1.top()<<" is going from Stack 1 to mainStack"<<endl;
        printStacks(totTransfer+1, mainStack, stack1, stack2);
        totTransfer++;
    }

    int stNum = 0;
    for(int i=totColors-2; i>=0; i--){
        if(stNum == 0){
            while(stack2.size() != 0){
                string topCol = stack2.top();
                stack2.pop();
                    
                if(topCol == colors[i]){
                    mainStack.push(topCol);
                    cout<<totTransfer+1<<". "<<topCol<<" is going from Stack 2 to mainStack"<<endl;
                    printStacks(totTransfer+1, mainStack, stack1, stack2);
                    totTransfer++;
                } else{
                    stack1.push(topCol);
                    cout<<totTransfer+1<<". "<<topCol<<" is going from Stack 2 to Stack 1"<<endl;
                    printStacks(totTransfer+1, mainStack, stack1, stack2);
                    totTransfer++;
                }        
            }
            stNum = 1-stNum;
        } else if(stNum == 1){
            while(stack1.size() != 0){
                string topCol = stack1.top();
                stack1.pop();

                if(topCol == colors[i]){
                    mainStack.push(topCol);
                    cout<<totTransfer+1<<". "<<topCol<<" is going from Stack 1 to mainStack"<<endl;
                    printStacks(totTransfer+1, mainStack, stack1, stack2);
                    totTransfer++;
                } else{
                    stack2.push(topCol);
                    cout<<totTransfer+1<<". "<<topCol<<" is going from Stack 1 to Stack 2"<<endl;
                    printStacks(totTransfer+1, mainStack, stack1, stack2);
                    totTransfer++;
                }        
            }
            stNum = 1-stNum;
        }            
    }

    cout<<"Total no. of steps to move the contents are : "<<totTransfer<<endl;

    cout << "Final Stack is :"<<endl;
    Stack<string> temp = mainStack;
    while (!temp.empty()) {
        cout << temp.top() << "\n";
        temp.pop();
    }

    return 0;
}