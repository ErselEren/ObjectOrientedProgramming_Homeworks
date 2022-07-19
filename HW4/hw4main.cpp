#include "DayOfYearSet.h"
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace DateSpace;

int main(){
    srand(time(NULL)); //for random numbers

    vector<DayOfYearSet::DayOfYear> vectorSet; //vector of DayOfYear objects
    fill_vector(vectorSet);//filling vector randomly
    DayOfYearSet obj1(vectorSet); //constructor that takes vector as parameter
    obj1.add_element(3,6); //adding same element as we added to obj2 for testing no duplicates
    cout <<"\nTest 1 ||  testing add_element and constructor\n";
    cout <<"--------------------------------------------------";
    cout << obj1; //overloaded << operator test
    cout << "Size of obj1 is : "<<obj1.sizeOfSet();
    
    cout <<"\n\nTest 2 ||  removing element\n";
    //add arbitrary elements into it
    DayOfYearSet obj2; //no parameter constructor
    obj2.add_element(1,2); obj2.add_element(3,6); obj2.add_element(12,10); obj2.add_element(30,12); obj2.add_element(14,9); obj2.add_element(3,6);
    cout <<"--------------------------------------------------";
    cout <<"\nBefore remove" << obj2;
    obj2.remove_element(12,10); //valid removing
    obj2.remove_element(31,7);  //invalid
    cout <<"After remove" << obj2;
    cout <<"Size of obj2 : "<<obj2.sizeOfSet();
    
    
    cout <<"\n\n\nTest 3 ||  static counter function \n";
    cout <<"--------------------------------------------------";
    cout <<"\nAll alive DayOfYear objects : "<<DayOfYearSet::getCount(); //returns static int that counts alive DayOfYear objects


    cout <<"\n\n\nTest 4 ||  operator+ \n";
    cout <<"--------------------------------------------------";
    DayOfYearSet obj3;
    obj3 = obj1 + obj2; //union set is assigned to obj3
    cout << "\nUnion of obj1 and obj2 ---> obj3";
    cout << obj3; //printing obj3


    cout <<"\n\nTest 5 ||  operator^ \n";
    cout <<"--------------------------------------------------";
    obj3 = obj1^obj2; //intersection of two set 
    cout << obj3; //they both have Day-3, Month-6 


    cout <<"\n\nTest 6 ||  operator== \n"; //returns true if sets are equal
    cout <<"--------------------------------------------------";
    if(obj3==obj1) cout << "\nSets are equal.";
    else cout << "\nSets are not equal.";


    cout <<"\n\n\nTest 7 ||  operator!= \n"; //true if sets are not equal
    cout <<"--------------------------------------------------";
    if(obj3!=obj1) cout << "\nSets are not equal.";
    else cout << "\nSets are equal.";


    cout <<"\n\n\nTest 8 ||  operator- \n"; //difference of two set
    cout <<"--------------------------------------------------";
    DayOfYearSet obj5;
    obj5 = obj1-obj2; //Day-3 Month-6 wont exist in obj3 
    cout << obj5;


    cout <<"\n\n\nTest 9 ||  operator[] \n"; //returns DayOfYear object
    cout <<"--------------------------------------------------";
    cout <<"\nDay of obj2 at index 0 is "<< obj2[0].getDay() << " | Month of obj2 at index 0 is "<< obj2[0].getMonth();   
    cout <<"\nDay of obj1 at index 2 is "<< obj1[2].getDay() << " | Month of obj1 at index 2 is "<< obj1[2].getMonth()<<endl;


    cout <<"\n\n\nTest 10 ||  operator! \n"; //returns complement set
    cout <<"--------------------------------------------------";
    DayOfYearSet obj4;
    obj4 = !obj3;
    cout << obj4;


    return 0;
}