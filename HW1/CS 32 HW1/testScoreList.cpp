//
//  testScoreList.cpp
//  HW1
//
//  Created by Jin on 4/12/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include <iostream>
#include <assert.h>
using namespace std;
#include "ScoreList.h"


void foo(ScoreList s){
	cout<<endl;
    s.print();
    s.remove(5);
    s.add(100);
    cout<<endl;
    s.print();
    ScoreList a;
    a = s;
    a.remove(9);
    cout<<"\na:";
    a.print();
    
    cout<<"-------------"<<endl;
    s.print();
}


int main()
{
    ScoreList s;
    s.add(5);
    s.add(9);
    s.print();
    foo(s);
    ScoreList a = s;
    a.remove(5);
    a.add(9);
    cout<<endl;
    a.print();
    cout<<endl;
    a = s;
    s.remove(5);
    a.print();
    cout<<endl;
    s.print();

}