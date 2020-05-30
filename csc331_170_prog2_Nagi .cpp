/*
CSC 331 - 170L
Majdi Nagi
csc331_170_prog2_Nagi.cpp
Assignment 2 due 11:59pm Saturday 3-15-2020.
Purpose: the purpose of this program is to create a linked list for name and age and the list should be sorted based on who is younger. You have to enter transaction. For example, "A" to add someone to the list, "L" to print what's inside the list,"D" is to delete some one from the list. Also we can't have two.
*/
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;


struct listNode {
    int age;
    string name;
    listNode* link;
};


listNode* buildListForward();
bool insertName(listNode**, int, string);
void showList(listNode*);
bool nameInList(listNode**, string);
bool deleteNode(struct listNode**, string);

int main() {
    listNode* head;
    head = buildListForward();
}


listNode* buildListForward() {
    listNode* first, * last;
    string name, t;
    int age, namelen, pos1, pos2;
    char cmd = ' ';

    first = NULL;
    last = NULL;

    while (cmd != 'Q') {
        cout << "enter transaction: ";
        getline(cin, t);
        t.erase(std::remove_if(t.begin(), t.end(), ::isspace), t.end());
        cmd = t[0];
        pos1 = 1;
        for (int i = 1; i < t.length(); i++) {
            if (!isdigit(t[i])) {
                pos2 = i;
            }
        }
        cmd = toupper(cmd);
        cout << "cmd = " << cmd << endl;
        if (cmd == 'A') {
            pos1 = 1;
            name = t.substr(pos1, pos2);
            istringstream(t.substr(pos2 + 1)) >> age;
            if (nameInList(&first, name) == 0) {
                if (insertName(&first, age, name)) {
                    cout << "name added" << endl;
                }
            }
            else {
                cout << "Name not added." << endl;
            }

        }
        else if (cmd == 'L') {
            showList(first);
        }
        else if (cmd == 'D') {
            pos1 = 1;
            name = t.substr(pos1, pos2);
            if (deleteNode(&first, name) == 1) {
                cout << "Name deleted" << endl;
            }
            else {
                cout << "Name not found.";
            }
        }
    }
    return first;
}

bool insertName(listNode** first, int userAge, string userName) {
    listNode* current, * head, * newNode, * prior{};
    head = *first;
    int done;
    if (head == NULL) {
        head = new listNode;
        head->age = userAge;
        head->name = userName;
        head->link = NULL;
        done = 1;
    }
    else {
        if (head->age > userAge) {
            newNode = new listNode;
            newNode->age = userAge;
            newNode->name = userName;
            newNode->link = head;
            head = newNode;
            done = 1;
        }
        else {
            done = 0;
            current = head;
            while ((current != NULL) && (!done)) {
                if (current->age > userAge) {
                    newNode = new listNode;
                    newNode->age = userAge;
                    newNode->name = userName;
                    newNode->link = current;
                    prior->link = newNode;
                    done = 1;
                }
                else {
                    prior = current;
                    current = current->link;
                }
            }
            if (!done) {
                newNode = new listNode;
                newNode->age = userAge;
                newNode->name = userName;
                newNode->link = current;
                prior->link = newNode;
                done = 1;
            }
        }
    }
    *first = head;
    return done;
}

void showList(listNode* head) {
    listNode* current;
    current = head;
    string userName;

    while (current != NULL) {
        cout << current->name << " " << current->age << endl;
        current = current->link;

    }
    cout << endl;
}

bool nameInList(listNode** head, string userName) {
    listNode* current;
    current = *head;
    int found;
    found = 0;
    while ((current != NULL) && (!found)) {
        found = (userName == current->name);
        current = current->link;
    }
    return found;
}

bool deleteNode(listNode** head, string userName) {

    listNode* temp = *head, * prev{};

    if (temp != NULL && temp->name == userName) {
        *head = temp->link;
        delete temp;
        return true;
    }
    while ((temp != NULL && temp->name != userName)) {
        prev = temp;
        temp = temp->link;
    }
    if (temp == NULL) {
        return false;
    }

    prev->link = temp->link;

    delete temp;
    return true;
}
