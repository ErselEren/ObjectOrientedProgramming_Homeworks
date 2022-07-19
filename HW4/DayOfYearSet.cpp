#include "DayOfYearSet.h"
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

namespace DateSpace {

int DayOfYearSet::staticDates = 0; //static variable initalize

//CONSTRUCTORS----------------------------------------------------------------------------
DayOfYearSet::DayOfYearSet(){
   datesCount = 0;
}

DayOfYearSet::DayOfYear::DayOfYear(int d, int m){ //dayofyear constructor that takes day and month variable
    day=d;
    month=m;
}

DayOfYearSet::DayOfYearSet(vector<DayOfYearSet::DayOfYear> &newVector){
    //allocate size for *dates
    //then fill it in loop from vector
    int size;
    size = newVector.size();
    datesCount = size;
    staticDates += size;
    dates = new DayOfYear[size];
    for(int i=0;i<size;i++){
        dates[i].setDay(newVector[i].getDay());
        dates[i].setMonth(newVector[i].getMonth());
    }
    
}

//MEMBER FUNCTINOS------------------------------------------------------------------------

//setter for DayOfYear object variables
void DayOfYearSet::DayOfYear::setDay(int d){ day = d;}
void DayOfYearSet::DayOfYear::setMonth(int m){month = m;}

//getter for DayOfYear object variables
int DayOfYearSet::DayOfYear::getDay()const{return day;}
int DayOfYearSet::DayOfYear::getMonth()const{return month;}
int DayOfYearSet::sizeOfSet()const{ return datesCount;}

void DayOfYearSet::add_element(int day,int month){ //checks duplicates
    int flag = 1;
    for(int i=0;i<getDatesCount();i++){ //checks if this element is exist in set
        if(dates[i].getDay()==day&&dates[i].getMonth()==month){
            flag = 0;
        }
    }
    
    if(flag==1){ //if not exist
        if(datesCount!=0){
            DayOfYear *temp;
            int i;
            temp = new DayOfYear[datesCount+1];
            for(i=0;i<datesCount;i++){ //copying elements
                temp[i].setDay(dates[i].getDay());
                temp[i].setMonth(dates[i].getMonth());
            }
            //adding elements into last index
            temp[i].setDay(day);
            temp[i].setMonth(month);
            dates = temp;
        }
        else{ //if set is empty 
            dates = new DayOfYear[1];
            dates->setDay(day);
            dates->setMonth(month);
        }
        //increasing counters
        datesCount++;
        staticDates++;
    }
    else{
        cerr << "\nDay "<< day<<" Month "<< month << " is exist in set\n";
    }
}

void DayOfYearSet::remove_element(int day, int month){
    vector<DayOfYearSet::DayOfYear> vectorSet; //temp vector of DayOfYear
    for(int i=0;i<getDatesCount();i++){ //if given element is not in the set, push it back to vector
        if(dates[i].getDay()!=day||dates[i].getMonth()!=month){
            vectorSet.push_back(dates[i]);
        }
        else staticDates--;
    }
         
    int size; //then copying into *dates
    size = vectorSet.size();
    datesCount = size;
    dates = new DayOfYear[size];
    for(int i=0;i<size;i++){
        dates[i].setDay(vectorSet[i].getDay());
        dates[i].setMonth(vectorSet[i].getMonth());
    }
}

DayOfYearSet::DayOfYear& DayOfYearSet::operator[](int index){ 
    //returns element at given index
    if(index>datesCount) cerr << "Limit Exceeded!";
    else if(index<0) cerr << "Index must be nonnegative integer";
    else return dates[index];
    exit(0);
}

const DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet& other){
    int flag;
    vector<DayOfYearSet::DayOfYear> tempSet; //temporary vector
    for(int i=0;i<getDatesCount();i++){ //pushing first set back to vector
        DayOfYearSet::DayOfYear date(dates[i].getDay(),dates[i].getMonth());
        tempSet.push_back(date);
    }

    //then checks every element of two sets, if not exist in first set, then add is   
    for(int i=0;i<other.getDatesCount();i++){
        flag = 1;    
        for(int j=0;j<getDatesCount();j++){
            if(tempSet[j].getDay()==other.dates[i].getDay()&&tempSet[j].getMonth()==other.dates[i].getMonth()){
                flag = 0;
                break;
            }  
        }
        if(flag==1){
            DayOfYearSet::DayOfYear date(other.dates[i].getDay(),other.dates[i].getMonth());
            tempSet.push_back(date);
        }        
    }
    staticDates += tempSet.size();
    return DayOfYearSet(tempSet); //returning DayOfYearSet object            
}

const DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet& other){
    vector<DayOfYearSet::DayOfYear> vectorSet; //temporary vector
    auto flag = 0;
    
    for(decltype(flag)i=0;i<getDatesCount();i++){ //checks every element of both set
        for(int j=0;j<other.getDatesCount();j++){
            if(dates[i].getDay()==other.dates[j].getDay()&&dates[i].getMonth()==other.dates[j].getMonth()){
                flag = 1;
                break;
            }
        }
        if(flag==0){//if not exist, add it to vector
            DayOfYearSet::DayOfYear date(dates[i].getDay(),dates[i].getMonth());
            vectorSet.push_back(date);
        }
    }
    staticDates+=vectorSet.size();
    return DayOfYearSet(vectorSet); //returning DayOfYearSet object
}

const bool DayOfYearSet::operator==(const DayOfYearSet& other) const{
    int flag;
    
    //first checks size of sets
    if(getDatesCount()!=other.getDatesCount()) return false;

    //if it can't finds an element from first set in second set, returns false
    for(int i=0;i<getDatesCount();i++){
        flag = 0;
        for(int j=0;j<other.getDatesCount();j++){
           if(dates[i].getDay()==other.dates[j].getDay()&&dates[i].getMonth()==other.dates[j].getMonth()){
               flag = 1;
               break;
           }
        }
        if(flag==0) return false;
    }
    return true;
}

const bool DayOfYearSet::operator!=(const DayOfYearSet& other) const{
    //opposite of operator== function
    if(*this==other) return false;
    else return true;
}

const DayOfYearSet DayOfYearSet::operator^(const DayOfYearSet& other){
    
    vector<DayOfYearSet::DayOfYear> vectorSet; //temporary set

    for(int i=0;i<getDatesCount();i++){//if it finds same date in both set, add it to vector
        for(int j=0;j<other.getDatesCount();j++){
            if(dates[i].getDay()==other.dates[j].getDay()&&dates[i].getMonth()==other.dates[j].getMonth()){
                DayOfYearSet::DayOfYear date(dates[i].getDay(),dates[i].getMonth());
                vectorSet.push_back(date);
                break;
            }
        }
    }

    staticDates += vectorSet.size();
    return DayOfYearSet(vectorSet); //return object of DayOfYearSet
}

const DayOfYearSet DayOfYearSet::operator!()const{
    vector<int> daysOfMonths{0,31,28,31,30,31,30,31,31,30,31,30,31}; //to calculate days of months
    vector<DayOfYearSet::DayOfYear> vectorSet; 
    int flag;
    //it starts from 1 January to 31 December, if it doesn't find same date, add it to vector
    for(int i=1;i<daysOfMonths.size();i++){ //from 1 to 12 months
        for(int j=1;j<daysOfMonths[i];j++){ 
            flag = 1;
            for(int k=0;k<getDatesCount();k++){ 
                if(dates[k].getDay()==j&&dates[k].getMonth()==i){
                    flag = 0;
                    break;
                }
            }
            if(flag==1){
                DayOfYearSet::DayOfYear date(j,i);
                vectorSet.push_back(date);
            }
        }
    }
    staticDates += vectorSet.size();
    return DayOfYearSet(vectorSet);
}

int DayOfYearSet::getCount(){
    return staticDates;
}

//FRIEND FUNCTIONS-----------------------------------------------------------------------
bool check_same( vector<DayOfYearSet::DayOfYear> &vectorSet, int day, int month){
    for(int i=0;i<vectorSet.size();i++)
        if(vectorSet[i].getMonth()==month&&vectorSet[i].getDay()==day) return false;

    return true;
}

void fill_vector(vector<DayOfYearSet::DayOfYear> &vectorSet){
    //it fills vector by randomly also it checks duplicates
    int day,month;
    for(int i=0;i<SIZE;i++){ 
        month = rand()%12+1;
        if(month==dates::jan||month==dates::mar||month==dates::may||month==dates::jul||month==dates::aug||month==dates::oct||month==dates::dec) day = rand()%31+1;
        else if(month==dates::apr||month==dates::jun||month==dates::sep||month==dates::nov) day = rand()%30+1;
        else day = rand()%28+1;
        if(check_same(vectorSet,day,month)==1){
            DayOfYearSet::DayOfYear date(day,month);
            vectorSet.push_back(date);
        }
    }

}

ostream& operator<<(ostream& output, const DayOfYearSet& date){
    //printing all dates of set
    for(int i=0;i<date.getDatesCount();i++)
        output << "\nDay : "<<date.dates[i].getDay() << "  -  Month : " << date.dates[i].getMonth();
    output <<endl;
    return output;    
}

}