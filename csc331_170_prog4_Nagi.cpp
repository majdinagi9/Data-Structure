/* CSC 331 - 170L
   Majdi Nagi
   csc331_170_prog4_Nagi.cpp
   Assignment 4 due 11:59pm Saturday 4-25-2020.
   Purpose:The purpose of this program will be to check the priority each customer based on 
           the year of the order and to check if they have warranty or not. If they do have 
           warranty and they bought their bike in the last six years they will have more priority 
           than other customers. if not they will be placed in the second position of the heap if 
           they bought the bike in the last six years. If they don’t have warranty and they didn’t 
           want the bike in the last six years they would be placed in the last position of the heap. 
           Also, the word “service” will serve whoever in the front of the heap. And “end-of-file” will 
           be to quit using the program.
*/
#include <iostream>
#include <string>
using namespace std;

class EbikeOrder {
public:
    static int numOrder;
    int priorNum;
    int orderNum;
    string name;
    string order;

    EbikeOrder(){}
    EbikeOrder(string name, char warranty, string year) {

        this->name = name;
        numOrder++;
        orderNum = numOrder;
        priorNum = priorityNum(warranty, year);
        generateStr();
    }
    int priorityNum(char warranty, string y) {
        if (warranty == 'y')
            return 1;
        const int CURRENT_YEAR = 2020;

        int year = stoi(y);
        if (CURRENT_YEAR - year < 6)
            return 2;
        return 3;
    }

    void generateStr() {
        order += to_string(priorNum) += "-";

        if (orderNum < 9) {
            order += "00"; order += to_string(orderNum);
        }
        else if (orderNum < 99) {
            order += "0"; order += to_string(orderNum);
        }
        else {
            order += to_string(orderNum);
        }

        order += "-"; order += name;
    }
};
int EbikeOrder::numOrder = 0;
class BuildHeap {
private:
    int count = 0;
    int done = 0;
    EbikeOrder* heap[10];
public:
    void push(EbikeOrder* order) {

        if (count == 10) {
            cout << "Error: Queue is full" << endl;
            return;
        }

        heap[done] = order;
        int newNode = done;
        done++;
        count++;

        while (newNode) {
            int parentNode = (newNode - 1) / 2;
            if (heap[parentNode]->priorNum > order->priorNum) {
                EbikeOrder* temp = heap[parentNode];
                heap[parentNode] = order;
                heap[newNode] = temp;
            }
            else
                return;
            newNode = parentNode;
        }
    }
    void pop() {
        if (count == 0)
            cout << "Queue is empty" << endl;
        else if (count == 1) {
            cout << "(output: " << heap[0]->name << ")" << endl;
            count = 0;
            done = 0;
            heap[0] = 0;
        }
        else if (count == 2) {
            cout << "(output: " << heap[0]->name << ")" << endl;
            count--;
            done--;
            heap[0] = heap[1];
            heap[1] = 0;
        }
        else {
            cout << "(output: " << heap[0]->name << ")" << endl;
            count--;
            done--;
            heap[0] = heap[done];
            heap[done] = 0;

            int nodeIndex = 0;
            int leftChild = (2 * nodeIndex) + 1, rightChild = (2 * nodeIndex) + 2;

            do {

                if (heap[rightChild] != NULL) {

                    if ((heap[nodeIndex]->priorNum > heap[leftChild]->priorNum) ||
                        (heap[nodeIndex]->priorNum > heap[rightChild]->priorNum)) {

                        if (heap[leftChild]->priorNum < heap[rightChild]->priorNum) {
                            EbikeOrder* temp = heap[nodeIndex];
                            heap[nodeIndex] = heap[leftChild];
                            heap[leftChild] = temp;
                            nodeIndex = leftChild;
                        }
                        else if (heap[leftChild]->priorNum == heap[rightChild]->priorNum) {
                            if (heap[leftChild]->orderNum < heap[rightChild]->orderNum) {
                                EbikeOrder* temp = heap[nodeIndex];
                                heap[nodeIndex] = heap[leftChild];
                                heap[leftChild] = temp;
                                nodeIndex = leftChild;
                            }
                            else {
                                EbikeOrder* temp = heap[nodeIndex];
                                heap[nodeIndex] = heap[rightChild];
                                heap[rightChild] = temp;
                                nodeIndex = rightChild;
                            }
                        }
                        else {
                            EbikeOrder* temp = heap[nodeIndex];
                            heap[nodeIndex] = heap[rightChild];
                            heap[rightChild] = temp;
                            nodeIndex = rightChild;
                        }

                        leftChild = (2 * nodeIndex) + 1; rightChild = (2 * nodeIndex) + 2;
                    }
                }
                else {
                    if (heap[nodeIndex]->priorNum > heap[leftChild]->priorNum) {
                        EbikeOrder* temp = heap[nodeIndex];
                        heap[nodeIndex] = heap[leftChild];
                        heap[leftChild] = temp;
                        nodeIndex = leftChild;
                    }
                    leftChild = (2 * nodeIndex) + 1;
                    rightChild = (2 * nodeIndex) + 2;
                }


            } while (rightChild < done);
        }
    }
    int getCount() {
        return count;
    }

};

bool stringGenerator(string, char&, string&, string&);
bool validatingYear(string&);


int main() {
    string input;
    BuildHeap heap;
    cout << " Enter repair order in this form if you have warranty name-year-y,if not name-year-n and to Quit Enter: end-of-file" << endl;
    while (input != "end-of-file") {
        cout << "Enter: ";
        getline(cin, input);
        if (input == "end-of-file") {
            cout << "There are " << heap.getCount() << " remaining repair orders in the queue" << endl;
        }
        else if (input != "end-of-file") {
            if (input == "service") {
                heap.pop();
            }
            else {
                char warranty;
                string year;
                string name;

                if (stringGenerator(input, warranty, year, name)) {
                    EbikeOrder* order = new EbikeOrder(name, warranty, year);
                    heap.push(order);
                }
            }
        }
    } 
   
    
}
bool stringGenerator(string input, char& warranty, string& year, string& name) {
    warranty = *(input.end() - 1);
    if (!(warranty == 'y' || warranty == 'n')) {
        cout << "Invalid input" << endl;
        return false;
    }
    year = string(input.end() - 7, input.end() - 1);
    if (!validatingYear(year)) {
        cout << "Invalid input" << endl;
        return false;
    }
    name = string(input.begin(), input.end() - 7);
    return true;
}
bool validatingYear(string& year) {
    if (year.length() != 6)
        return false;
    else if (*(year.begin()) != '-' || *(year.end() - 1) != '-')
        return false;
    else {
        string yearToNum(year.begin() + 1, year.end() - 1);

        for (int i = 0; i < yearToNum.length(); i++) {
            char number = yearToNum[i];
            if (number < 48 || number > 57) {
                return false;
            }
        }
        year = yearToNum;
    }
    return true;
}

