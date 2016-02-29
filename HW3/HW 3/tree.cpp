//
//  main.cpp
//  HW3
//
//  Created by Jin on 5/2/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

//
//  mazestack.cpp
//  HW2
//
//  Created by Jin on 4/24/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//


#include <iostream>
using namespace std;


// the recursion start at the back of the array
// check if the last element in a2 is in the a1 at position k
// if find then check if the sequnce from 0 to k-1 does not contain sequence a2
// if it does then do the recursion again
// otherwise, decrement n2 and n1
// for exmaple:
// a1 = "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// a2 = "kyle" "cartman" "butters"
// since the last element in a2 is the same last element in a1
//then check if "stan" "kyle" "cartman" "kenny" "kyle" "cartman" contains the whole sequence a2
// otherwise decrement n1 and n2 and check.
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    //base case, if n2 is less than 1, return 1
    //if n1 is less than 1, then return 0
    if (n2<=0) {return 1;}
    if (n1<=0) {return 0;}
    
    //if element in a2 is in in a1
    if (a1[n1-1] == a2[n2-1]) {
        //if it does, then check the prior sequence contains a2, and add the result to the n1 and n2 both decrement by 1
        return countIncludes(a1, n1-1, a2, n2)+countIncludes(a1, n1-1, a2, n2-1);
    }
    else{
        //otherwise check if element a2 at n2 is in the a1 at n1-1
        return countIncludes(a1, n1-1, a2, n2);
    }
}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < divider come before all the other elements,
// and all the elements whose value is > divider come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= divider, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < divider
//   * for firstNotLess <= i < firstGreater, a[i] == divider
//   * for firstGreater <= i < n, a[i] > divider
// All the elements < divider end up in no particular order.
// All the elements > divider end up in no particular order.
void divide(string a[], int n, string divider,
            int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < divider
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == divider
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > divider
    
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > divider)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < divider)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    //base case, if n less then 2 then do nothing.
    if (n <= 1) {return;}
    int lessAndEqual,greater;
    
    //divide the sequence in to two
    //with all the elements that smaller than a[0] to be at left,
    //and all the elements that greater than a[0] to be at right.
    divide(a, n, a[0], lessAndEqual, greater);
    
    //then do the same thing to the left half and right half.
    order(a, lessAndEqual);
    order(a+greater, n-greater);
}


int main(int argc, const char * argv[]) {
    string a[] = {"stan", "kyle", "cartman", "kenny" ,"kyle", "cartman" ,"butters"};
    string b[] = {"kyle" ,"cartman" ,"butters" };
    cout<<countIncludes(a, 7, b, 3)<<endl;
    order(a, 7);
    for (int i = 0; i<7; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

