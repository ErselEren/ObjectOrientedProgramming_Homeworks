#include <iostream>
#include <memory>
#include <algorithm>
#include "GTUVector.cpp"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUArray.h"
#include "GTUArray.cpp"

using namespace std;
using namespace set_space;
using namespace vector_space;
using namespace array_space;

void print_test(const int &n){
    cout << "\nIn Print_Test ->"<< n;
}

int main(){
    
    cout <<"\n----------------------------------------------\n";
    cout <<"\n----------------------------------------------\n";
    cout <<"\n---------------------VECTOR----------------------\n";
    //--------------------------------------VECTOR-----------------------------------------
    GTUVector<int> vec1;
    vec1.add(1); //add function
    vec1.add(2);
    vec1.add(3);


    GTUVector<int> vec2(vec1); //copy constructor
    vec2.erase(vec2.begin()); //erasing first element


    cout <<"\nPrinting vec2 after erasing first element :";
    for(int i=0;i<vec2.size();i++)
        cout << " "<<vec2[i]; //[] operator
    

    if(vec2.empty()==1) cout <<"\nVec2 is empty"; //empty function
    else cout <<"\nVec2 is not empty";
    


    vec2.clear(); //clear function
    cout <<"\n\n---After clearing---";
    if(vec2.empty()==1) cout <<"\nVec2 is empty";
    else cout <<"\nVec2 is not empty";




    GTUVector<int> vec3;
    vec3.add(99);
    vec3.add(11);
    vec3.add(29);
    vec3.add(2);
    std::for_each(vec3.begin(),vec3.end(),print_test); //iterators and foreach
    std::sort(vec3.begin(),vec3.end()); //sort
    GTUIterator<int> it;
    for(it=vec3.begin();it!=vec3.end();it++)
        cout <<"\n Vec3 elements after sorted->"<<(*it);
    cout << endl << endl;



    it = find (vec3.begin(), vec3.end(), 29); //find function
    if (it != vec3.end())
        cout << "Element found in myvector: " << *it << '\n';
    else
        cout << "Element not found in myvector\n";


    GTUVector<int> vec4;
    for(int i=0;i<7;i++)
        vec4.add(i+3);
    vec4.erase(vec4.begin(),vec4.begin()+3);    
    cout <<"\nAfter erasing first 3 element of vec4 : ";
    for(int i=0;i<vec4.size();i++)
        cout <<" "<<vec4[i];


    //--------------------------------------SET-----------------------------------------
    cout <<"\n----------------------------------------------\n";
    cout <<"\n----------------------------------------------\n";
    cout <<"\n---------------------SET----------------------\n";
    

    GTUSet<int> set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);
    GTUSet<int> set2(set1);
    GTUIterator<int> it2;
    for(it2 = set2.begin();it2!=set2.end();it2++)
        cout << " "<<(*it2);

    
    GTUSet<int> set3;
    set3.add(1);
    set3.add(4);
    set3.add(5);
    set3.add(6);
    
    
    
    set2 = set1.union_of(set3);
    cout <<"\nAfter union of set1 and set3, set2 is-> ";
    for(it2 = set2.begin();it2!=set2.end();it2++)
        cout << " "<<(*it2);


    set2.erase(3);
    cout <<"\nAfter erasing element '3', set2 is-> ";
    for(it2 = set2.begin();it2!=set2.end();it2++)
        cout << " "<<(*it2);


    set2.erase(set2.begin());
    cout <<"\nAfter erasing first element, set2 is-> ";
    for(it2 = set2.begin();it2!=set2.end();it2++)
        cout << " "<<(*it2);


    it2 = set2.end();
    set2.erase(set2.begin(),it2-2);
    cout <<"\nAfter erasing from first element to 3rd element, set2 is-> ";
    for(it2 = set2.begin();it2!=set2.end();it2++)
        cout << " "<<(*it2);


    cout<<"\n\nFOR EACH : ";
    std::for_each(set2.begin(),set2.end(),print_test);
    cout << endl;


    set2.add(1);
    set2.add(27);
    std::sort(set2.begin(),set2.end()); //sort
    for(it=set2.begin();it!=set2.end();it++)
        cout <<"\n Set2 elements after sorted->"<<(*it);
    cout << endl << endl;
    

    it = find (set2.begin(), set2.end(), 13); //find function
    if (it != set2.end())
        cout << "Element found in set2: " << *it << '\n';
    else
        cout << "Element not found in set2\n";


    set2.clear();
    if(set2.empty()==1) cout <<"\nAfter clearing, Set2 is empty"; //empty function
    else cout <<"\nAfter clearing, Set2 is not empty";



    //--------------------------------------ARRAY-----------------------------------------
    cout <<"\n----------------------------------------------\n";
    cout <<"\n----------------------------------------------\n";
    cout <<"\n---------------------ARRAY----------------------\n";
    
    
    GTUArray<int,5> arr1;
    for(int i=0;i<arr1.size();i++)
        arr1[i] = i*2;
    
    for(int i=0;i<arr1.size();i++)
        cout <<" "<<arr1.at(i);


    cout <<"\nElement at 2th index : "<< arr1.at(2);    
    cout <<"\nElement at front : "<<arr1.front();
    cout <<"\nElement at back : "<<arr1.back();
    
    

    cout<<"\n\nFOR EACH : ";
    std::for_each(arr1.begin(),arr1.end(),print_test);
    cout << endl;


    arr1[0] = 10;
    arr1[2] = 15;
    std::sort(arr1.begin(),arr1.end()); //sort
    for(it=arr1.begin();it!=arr1.end();it++)
        cout <<"\n Arr1 elements after sorted->"<<(*it);
    cout << endl << endl;



    it = find (arr1.begin(), arr1.end(), 10); //find function
    if (it != arr1.end())
        cout << "Element found in arr1: " << *it << '\n';
    else
        cout << "Element not found in arr1\n";



    arr1.clear();
    if(arr1.empty()==1) cout <<"\nAfter clearing, Arr1 is empty"; //empty function
    else cout <<"\nAfter clearing, Arr1 is not empty";
    
    
    cout << endl;
    
    return 0;
}