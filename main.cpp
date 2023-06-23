#include <iostream>
#include "termProject.h"

using namespace std;

int main(){
    PersonLL database;

    database.loadFile("input.txt");
    
    cout << "After loadFile"<< endl;
    
    database.printByAge();
    database.printByName();

    database.add("person1",21);
    database.add("person2",30);

    cout << "After add(person1,21) , add(person2,30)"<< endl;

    database.printByAge();
    database.printByName();

    database.update("person2",32);
    database.update("person1",27);

    cout << "After update(person1,27) , update(person2,32)"<< endl;
    
    database.printByAge();
    database.printByName();


    database.remove("person2");
    database.remove("person1");

    cout << "After remove(person1) , remove(person2)"<< endl;

    database.printByAge();
    database.printByName();


    database.saveToFileByAge("age.txt");
    database.saveToFileByName("name.txt");

    return 0;
}