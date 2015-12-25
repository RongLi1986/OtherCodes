//
//  main.cpp
//  cppBase
//
//  base example for operator overlording
//
//  Created by Rong LI on 12/25/15.
//  Copyright (c) 2015 Rong LI. All rights reserved.
//

#include <iostream>
using namespace std;

class Integer{
    int i;
public:
    Integer(int ii):i(ii){
    
    }
    
    const Integer operator+(const Integer& rv){
        return Integer(i+rv.i);   /* i is private? ===> but it in same class */
    }
    
    Integer operator+=(const Integer& rv){  //diff between return Integer and Integer& ????
        i+=rv.i;
        return *this;
    }
    
    void printValue(){
        cout<<i<<endl;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    
    Integer ii(5);
    Integer kk(8);
    
    Integer xx(0);
    
    xx+=ii+kk;
    
    xx.printValue();
    return 0;
}
