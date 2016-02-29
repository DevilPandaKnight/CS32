//
//  main.cpp
//  HW3
//
//  Created by Jin on 5/2/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//animal class, a pure absctrct class.
class Animal {
public:
    //initialize the name, and all its subclass will call this to setup its name.
    Animal(string AnimalName):_name(AnimalName){};
    
    //pure virtual desctrctor
    virtual ~Animal(){}
    
    //name getter, all the animal will use this getter to get its name.
    string name() const{return _name;}
    
    //pure virtual method
    virtual string moveAction() const = 0;
    virtual void speak() const = 0;
private:
    string _name;
};

class Cat:public Animal{
public:
    //cat constructor, calls its super to init name.
    Cat(string catName):Animal(catName){}
    
    //cat destructor, print out the destrucing message.
    virtual ~Cat(){cout<<"Destroying "<< name()<<" the cat"<<endl;}
    
    //cat can only walk
    virtual string moveAction() const{return "walk";}
    
    //cat speak Meow
    virtual void speak() const{cout<<"Meow";}
};

class Pig:public Animal{
public:
    //pig constructor, calls its super to init name. and it also init own pounds data member.
    Pig(string pigName,int pound):Animal(pigName),pounds(pound){}
    
    //pig destructor, print out the destrucing message.
    virtual ~Pig(){cout<<"Destroying "<< name()<<" the pig"<<endl;}
    
    //pig can only walk
    virtual string moveAction() const{return "walk";}
    
    //if the pig is less than 180 pounds, then it speak Oink, otherwise its speak Grunt 
    virtual void speak() const{(pounds<180)? cout<<"Oink":cout<<"Grunt"; }
private:
    int pounds;
};

class Duck:public Animal{
public:
    //duck constructor, calls its super to init name.
    Duck(string duckName):Animal(duckName){}
    
    //duck destructor, print out the destrucing message.
    virtual ~Duck(){cout<<"Destroying "<< name()<<" the duck"<<endl;}
    
    //duck can swim
    virtual string moveAction() const{return "swim";}
    
    //duck speak quack
    virtual void speak() const{cout<<"Quack";}
};


void animate(const Animal* a)
{
    a->speak();
    cout << "!  My name is " << a->name()
    << ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
    
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
    // Pigs have a name and a weight in pounds.  Pigs under 180
    // pounds oink; pigs weighing at least 180 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");
    
    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);
    
    // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}