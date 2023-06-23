#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Person_Node{
public:
    string name;
    int age;
    Person_Node *nameNext, *ageNext;
    Person_Node(string Name, int Age);
};

class PersonLL{
private:
    Person_Node *head_name, *head_age;
    void addToNameList(Person_Node *node);
    void addToAgeList(Person_Node *node);

public:    
    PersonLL(): head_name(NULL), head_age(NULL){};
    void add(string name,int age);
    bool remove(string name);
    void update(string name, int age);
    void printByAge();
    void printByName();
    void loadFile(string filename);
    void saveToFileByAge(string filename);
    void saveToFileByName(string filename);
};

Person_Node::Person_Node(string Name, int Age){
    name = Name;
    age = Age;
    nameNext = ageNext = NULL;
}

void PersonLL::add(string name, int age){
    Person_Node *newNode = new Person_Node(name, age);

    addToAgeList(newNode);
    addToNameList(newNode);
}

bool PersonLL::remove(string name){
    Person_Node *prevName = NULL, *prevAge = NULL;
    Person_Node *curName = head_name, *curAge = head_age;

    bool ageStatus, nameStatus;

    while(curAge != NULL){
        if(curAge->name == name){
            if(prevAge == NULL){
                head_age = curAge->ageNext;
                prevAge = curAge;
                curAge = curAge->ageNext;
                prevAge->ageNext = NULL;

                ageStatus = true;
                break;
            }
            else if(curAge->ageNext == NULL){ 
                curAge = prevAge;
                prevAge = prevAge->ageNext;
                curAge->ageNext = NULL;

                ageStatus = true;
                break;
            }
            else{
                Person_Node *temp;
                temp = curAge;
                curAge = curAge->ageNext;
                temp->ageNext = NULL;
                prevAge->ageNext = curAge;
                prevAge = temp;

                ageStatus = true;
                break;
            }
        }
        prevAge = curAge;
        curAge = curAge->ageNext;
    }

    while(curName != NULL){
        if(curName->name == name){
            if(prevName == NULL){ 
                head_name = curName->nameNext;
                prevName = curName;
                curName = curName->nameNext;
                prevName->nameNext = NULL;

                nameStatus = true;
                break;
            }
            else if(curName->nameNext == NULL){ 
                curName = prevName;
                prevName = prevName->nameNext;
                curName->nameNext = NULL;

                nameStatus = true;
                break;
            }
            else{
                Person_Node *temp;
                temp = curName;
                curName = curName->nameNext;
                temp->nameNext = NULL;
                prevName->nameNext = curName;
                prevName = temp;

                nameStatus = true;
                break;
            }
        }
        prevName = curName;
        curName = curName->nameNext;
    }

    if(ageStatus == true && nameStatus == true){
        delete prevAge; //or delete prevName;
        return true;
    }
    else{
        return false;
    }
}

void PersonLL::update(string name, int age){
    remove(name);
    add(name,age);
}

void PersonLL::printByAge(){
    Person_Node *curAge = head_age;

    cout << "printByAge function is running.." << endl;

    while(curAge != NULL){
        cout << curAge->name << " " << curAge->age << endl;
        curAge = curAge->ageNext;
    }

    cout << endl;
}

void PersonLL::printByName(){
    Person_Node *curName = head_name;

    cout << "printByName function is running.." << endl;

    while(curName != NULL){
        cout << curName->name << " " << curName->age << endl;
        curName = curName->nameNext;
    }

    cout << endl;
}

void PersonLL::loadFile(string filename){
    ifstream file;
    file.open(filename,ios::in);

    string name;
    int age;

    while(file >> name){
        file >> age;
        add(name,age);
    }

    file.close();
}

void PersonLL::saveToFileByAge(string filename){
    ofstream file;
    file.open(filename,ios::out);
    Person_Node *temp = head_age;

    while(temp != NULL){
        file << temp->name << " " << temp->age << endl;
        temp = temp->ageNext;
    }

    file.close();
}

void PersonLL::saveToFileByName(string filename){
    ofstream file;
    file.open(filename,ios::out);
    Person_Node *temp = head_name;

    while(temp != NULL){
        file << temp->name << " " << temp->age << endl;
        temp = temp->nameNext;
    }

    file.close();
}

void PersonLL::addToAgeList(Person_Node *node){
    if(head_age == NULL){
        head_age = node;
        return;
    }

    if(head_age->age >= node->age){
        node->ageNext = head_age;
        head_age = node;
        return;
    }

    Person_Node *temp = head_age;
    Person_Node *tail = head_age;

    while(tail->ageNext != NULL){
        tail = tail->ageNext;
    }

    while(temp->ageNext != NULL){
        if(temp->ageNext->age >= node->age){
            node->ageNext = temp ->ageNext;
            temp->ageNext = node;
            return;
        }
        temp = temp ->ageNext;
    }

    if(tail->age <= node->age){
        tail->ageNext = node;
        tail = node;
    }
}

void PersonLL::addToNameList(Person_Node *node){
    if(head_name == NULL){
        head_name = node;
        return;
    }

    if(node->name.compare(head_name->name) == -1){ // node->name < head_name->name
        node->nameNext = head_name;
        head_name = node;
        return;
    }

    Person_Node *temp = head_name;
    Person_Node *tail = head_name;

    while(tail->nameNext != NULL){
        tail = tail->nameNext;
    }

    while(temp->nameNext != NULL){
        if(temp->nameNext->name.compare(node->name) == 1 || temp->nameNext->name.compare(node->name) == 0){ //temp->nameNext->name >= node->name
            node->nameNext = temp ->nameNext;
            temp->nameNext = node;
            return;
        }
        temp = temp ->nameNext;
    }

    if(tail->name.compare(node->name) == -1 || tail->name.compare(node->name) == 0){ //tail->name <= node->name
        tail->nameNext = node;
        tail = node;
    }
}