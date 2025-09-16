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

    string maxColor;
    string minColor;

    bool firstInput = true;
    while(true){
        string col;
        cout<<"Enter the colour or 0 to stop : ";
        cin>>col;

        if(col == "0") break;

        if(firstInput) {
            minColor = col;
            maxColor = col;
            firstInput = false;
        } else {
            if(col < minColor) minColor = col;
            if(col > maxColor) maxColor = col;
        }

        mainStack.push(col);
    }


    cout<<"Minimum color: "<<minColor<<endl;
    cout<<"Maximum color: "<<maxColor<<endl;

    Stack<string> stack1;
    Stack<string> stack2;
    int totTransfer = 0;
    
    int totMinColCount = 0, totMaxColCount = 0;

    while(!mainStack.empty()){
        string topEl = mainStack.top();

        if(topEl == minColor) totMinColCount++;
        if(topEl == maxColor) totMaxColCount++;

        if(!stack1.empty()){
            if(topEl > stack1.top()){
                while(!stack1.empty() && topEl > stack1.top()){
                    string tempEl = stack1.top(); 
                    stack2.push(tempEl);
                    stack1.pop();
                    cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 1 to Stack 2"<<endl;
                    printStacks(totTransfer+1, mainStack, stack1, stack2);
                    totTransfer++;
                }
            } else if(topEl < stack1.top()){
                while(!stack2.empty() && stack2.top() > topEl){
                    string tempEl = stack2.top();
                    stack1.push(tempEl);
                    stack2.pop();
                    cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 2 to Stack 1"<<endl;
                    printStacks(totTransfer+1, mainStack, stack1, stack2);
                    totTransfer++;
                }   
            }
        }
        mainStack.pop();
        if(!mainStack.empty()){
            string nextEl = mainStack.top();

            if(topEl < nextEl){
                stack2.push(topEl);
                cout<<totTransfer+1<<". "<<topEl<<" is going from mainStack to Stack 2"<<endl;
                printStacks(totTransfer+1, mainStack, stack1, stack2);
                totTransfer++;
            } else{
                stack1.push(topEl);
                cout<<totTransfer+1<<". "<<topEl<<" is going from mainStack to Stack 1"<<endl;
                printStacks(totTransfer+1, mainStack, stack1, stack2);
                totTransfer++;
            }
        } else{
            stack1.push(topEl);
            cout<<totTransfer+1<<". "<<topEl<<" is going from mainStack to Stack 1"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
        }
    }

    int totElementStack1 = stack1.size();
    int totElementStack2 = stack2.size();

    if(totElementStack1 == 1 || totElementStack2 == 1){
        if(totElementStack1 == 1){
            string tempEl = stack1.top();
            mainStack.push(tempEl);
            stack1.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from mainStack to Stack 1"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
            
            while(!stack2.empty()){
                string tempEl = stack2.top();
                mainStack.push(tempEl);
                stack2.pop();
                cout<<totTransfer+1<<". "<<tempEl<<" is going from mainStack to Stack 2"<<endl;
                printStacks(totTransfer+1, mainStack, stack1, stack2);
                totTransfer++;
            }
        } else{
            string tempEl = stack2.top();
            mainStack.push(tempEl);
            stack2.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from mainStack to Stack 2"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
            
            while(!stack1.empty()){
                string tempEl = stack1.top();
                mainStack.push(tempEl);
                stack1.pop();
                cout<<totTransfer+1<<". "<<tempEl<<" is going from mainStack to Stack 1"<<endl;
                printStacks(totTransfer+1, mainStack, stack1, stack2);
                totTransfer++;
            }
        }
    }

    if((totElementStack1 - totMaxColCount) <= (totElementStack2 - totMinColCount)){
        while(stack1.size() > totMaxColCount){
            string tempEl = stack1.top();
            stack2.push(tempEl);
            stack1.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 1 to Stack 2"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
        }

        while(!stack1.empty()){
            string tempEl = stack1.top();
            mainStack.push(tempEl);
            stack1.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 1 to mainStack"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
        }

        while(!stack2.empty()){
            string tempEl = stack2.top();
            mainStack.push(tempEl);
            stack2.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 2 to mainStack"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
        }
    } else{
        while(stack2.size() > totMinColCount){
            string tempEl = stack2.top();
            stack1.push(tempEl);
            stack2.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 2 to Stack 1"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
        }

        while(!stack2.empty()){
            string tempEl = stack2.top();
            mainStack.push(tempEl);
            stack2.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 2 to mainStack"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
        }

        while(!stack1.empty()){
            string tempEl = stack1.top();
            mainStack.push(tempEl);
            stack1.pop();
            cout<<totTransfer+1<<". "<<tempEl<<" is going from Stack 1 to mainStack"<<endl;
            printStacks(totTransfer+1, mainStack, stack1, stack2);
            totTransfer++;
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