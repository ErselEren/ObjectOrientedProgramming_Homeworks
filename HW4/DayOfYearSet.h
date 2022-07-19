#ifndef DAYOFYEARSET_H
#define DAYOFYEARSET_H
#include <iostream>
#include <vector>
#include <time.h>
#define SIZE 5 //it is used in first vector, which constructed obj1 in main. This is size of obj1 set. 

using namespace std;

namespace DateSpace //namespace definition
{
    enum dates{empty,jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};
    
    class DayOfYearSet{ //class definition
        public: 
            class DayOfYear{ //inner DayOfYear function
                public:
                    DayOfYear(){}
                    DayOfYear(int d, int m);
                    //setters getters
                    int getDay()const;
                    int getMonth()const;
                    void setDay(int d);
                    void setMonth(int m);
                private:
                    int day,month;
            };
            DayOfYearSet(vector<DayOfYearSet::DayOfYear> &newVector); //constructor that takes vector as parameter
            DayOfYearSet();
            const DayOfYearSet operator+(const DayOfYearSet& other);
            const DayOfYearSet operator-(const DayOfYearSet& other);
            const DayOfYearSet operator^(const DayOfYearSet& other);
            const bool operator==(const DayOfYearSet& other)const;
            const bool operator!=(const DayOfYearSet& other)const;
            const DayOfYearSet operator!()const;
            DayOfYear& operator[](int index);
            void remove_element(int day, int month);
            void add_element(int day,int month);
            int sizeOfSet() const;
            friend void fill_vector(vector<DayOfYearSet::DayOfYear> &vectorSet);
            friend bool check_same(vector<DayOfYearSet::DayOfYear> &vectorSet, int day, int month);
            friend ostream& operator<<(ostream& output, const DayOfYearSet& date);
            friend void print_obj(DayOfYearSet &obj1);
            int getDatesCount()const {return datesCount;}
            static int getCount();
            ~DayOfYearSet(){} //deconstructor
        private:
            static int staticDates;
            DayOfYear *dates = nullptr;
            int datesCount;
    };
}

#endif
