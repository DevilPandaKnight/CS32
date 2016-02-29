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



// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    //base case, if n is less than 1, then return true.
    if (n<=0) {return true;}
    
    //if the predicate return false, then return false.
    if (!somePredicate(a[n-1])) {return false;}
    
    //if the predicate at n-1 return true then it true.
    //otherwise it return false.
    return allTrue(a, n-1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    //base case, if n is less than 1, then return 0.
    if (n <= 0) {return 0;}
    
    //get counting result from n-1 then add 1 since the predicate is false.
    if (!somePredicate(a[n-1])) {return 1+countFalse(a, n-1);}
    
    //get counting result from n-1 then add 0 since the predicate is true.
    return 0+countFalse(a, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    //base case, if n is less than 1, then return 0.
    if (n<=0) {return -1;}
    
    //if predicate return false
    if (!somePredicate(a[n-1])) {
        //then check if all the case that prior to this index is true.
        int index = firstFalse(a, n-1);
        
        //if the prior case were all true, then return this index.
        if (index == -1) {
            return n-1;
        }
        //if the prior case were not all true return the index that is false.
        return index;
    }
    return firstFalse(a, n-1);
}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int indexOfLeast(const string a[], int n)
{
    //base case, if n is 0, return -1
    //if n is 1 return 0
    if (n < 1) {return -1;}
    if (n < 2) {return 0;}
    
    //get the index that refers to the current smallest one
    int index = indexOfLeast(a, n-1);
    
    //if it less then the value at index n-1, then return the smallest index
    if (a[index] <= a[n-1]) {return index;}
    
    //otherwise return the index n-1
    return n-1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    //base case if n2 is less than 1, return true
    //if n1 less than n2 then there is no posible to be true, so return false.
    if (n2 <= 0) {return true;}
    if (n1 < n2) {return false;}
    
    //check the elements in a2 to see if it in a1 in a backward manner
    if (a2[n2-1] == a1[n1-1]) {
        //if find the element in a2 that is in a1, then decrement both index
        return includes(a1, n1-1, a2, n2-1);
    }//otherwise only decrement the n1
    else{
        return includes(a1, n1-1, a2, n2);
    }
    
}
