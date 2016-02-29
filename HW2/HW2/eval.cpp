//
//  main.cpp
//  HW2
//
//  Created by Jin on 4/24/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
#include <cassert>
using namespace std;


int precedence(char op){
    switch (op) {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;;
    }
}

int comparePrecedence(char l,char r){
    return precedence(l)-precedence(r);
}

bool convertCharToBool(char c){
    return (c=='T')? true:false;
}

char convertBoolToChar(bool b){
    return b? 'T':'F';
}

char evaluateOprator(char op,char operand1, char operand2){
    if (op == '&') {
        return convertBoolToChar(convertCharToBool(operand1) && convertCharToBool(operand2));
    }
    else if (op == '|'){
        return convertBoolToChar(convertCharToBool(operand1) || convertCharToBool(operand2));
    }
    return 0;
}

bool checkPrand(string s){
    int parandCount = 0;
    char ch;
    for (int i = 0; i<s.length(); i++) {
        ch = s[i];
        if (ch=='(') {
            parandCount++;
        }
        else if (ch==')'){
            parandCount--;
            if (parandCount<0) {
                return false;
            }
        }
    }
    return parandCount==0;
}


bool performOperator(char op,stack<char> &operands){
    if (op == '!') {
        if (operands.empty()) {
            return false;
        }
        char operand = operands.top();
        operands.pop();
        operands.push((operand=='F')? 'T':'F');
        return true;
    }
    if (operands.empty()) {
        return false;
    }
    char operand2 = operands.top();
    operands.pop();
    if (operands.empty()) {
        return false;
    }
    char operand1 = operands.top();
    operands.pop();
    operands.push(evaluateOprator(op, operand1, operand2));
    return true;
}

bool checkString(string &s){
    char ch,lastCh = 0;
    for (int i = 0; i<s.length(); i++) {
        ch = s[i];
        switch (ch) {
            case '&':
            case '|':
                if (lastCh == '&' || lastCh == '|') {
                    return false;
                }
                lastCh = ch;
                break;
            case '!':
            case ' ':
            case '(':
            case ')':
                lastCh = ch;
                break;
            case 'T':
            case 'F':
                if (lastCh == 'T' || lastCh=='F') {
                    return false;
                }
                lastCh = ch;
                break;
            case 't':
                s[i] = 'T';
                break;
            case 'f':
                s[i] = 'F';
                break;
            default:
                return false;
        }
    }
    return true;
}

int evaluate(string infix, string& postfix, bool& result){
    if (infix.length()==0 || !checkPrand(infix) || !checkString(infix)) {
        return 1;
    }
    stack<char> operatorStack;
    postfix = "";
    char ch,top,lastCh = '\0';
    
    for (int i = 0,len = (int)infix.length(); i < len; i++) {
        ch = infix[i];
        switch (ch) {
            case 'T':
            case 'F':
                postfix.push_back(ch);
                lastCh = ch;
                break;
            case '(':
                operatorStack.push(ch);
                lastCh = ch;
                break;
            case ')':
                while ((top = operatorStack.top()) != '(') {
                    postfix.push_back(top);
                    operatorStack.pop();
                }
                operatorStack.pop();
                lastCh = ch;
                break;
            case '|':
            case '!':
            case '&':
                if (lastCh == '(' && ch != '!') {
                    return 1;
                }
                while (!operatorStack.empty() && (top = operatorStack.top()) != '(' && comparePrecedence(ch, top)<=0) {
                    postfix.push_back(top);
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                lastCh = ch;
                break;
            default:
                break;
        }
    }
    while (!operatorStack.empty()) {
        top = operatorStack.top();
        postfix.push_back(top);
        operatorStack.pop();
    }
    
    stack<char> operandStack;
    for (int i = 0,len=(int)postfix.size(); i<len; i++) {
        ch = postfix[i];
        if (ch == 'T' || ch == 'F') {
            operandStack.push(ch);
        }
        else{
            if(!performOperator(ch,operandStack))return 1;
        }
    }
    if (operandStack.size()!=1) {
        return 1;
    }
    result = convertCharToBool(operandStack.top());
    return 0;
}

int main(int argc, const char * argv[]) {
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cout << "Passed all tests" << endl;
    return 0;
}
