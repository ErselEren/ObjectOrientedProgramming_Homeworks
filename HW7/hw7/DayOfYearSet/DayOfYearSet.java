package DayOfYearSet;

import java.util.ArrayList;
import java.lang.Object;
import java.io.File;
import java.io.IOException;

/**
*
* @author Ersel Celal Eren
*/

public class DayOfYearSet implements Cloneable{
    /**
    * This is a program for keeping days and months of dates.
    */
    
    
    //------------INNER CLASS---------------------
        /** Class for hold dates as day and month*/
        public static class DayOfYear{
            
            /** copy constructor*/
            public DayOfYear(){
                day = 0;
                month = 0;
                alive_counter++;
            }
            

            /** copy constructor*/
            public DayOfYear(DayOfYear other){
                day = other.day;
                month = other.month;
                alive_counter++;
            }
            

            /** constructor that takes day and month value as parameter*/
            public DayOfYear(int d,int m){
                try{
                    if(m<1&&m>12) throw new Exception("INVALID Month!");
                    if(d<1&&d>Days[m]) throw new Exception("INVALID Day");
                    day = d;
                    month = m;
                    alive_counter++;
                }catch(Exception e){
                    System.out.println(e.toString());
                }
            }
            

            /** returns true if given DayOfYear object is same with this object*/
            private boolean check_same(DayOfYear element){
                if(day == element.day && month == element.month)
                    return true;
                else return false;    
            }
            
            /** overriden toString method*/
            @Override
            public String toString(){
                return "|Day : "+day+", Month : "+month;
            }


            public void setDate(int d, int m){
                try{
                    if(m<1&&m>12) throw new Exception("INVALID Month!");
                    if(d<1&&d>Days[m]) throw new Exception("INVALID Day");
                    day = d;
                    month = m;
                }catch(Exception e){
                    System.out.println(e.toString());
                }
            }
            public int getDay(){return day;}
            public int getMonth(){return month;}
            private int day;
            private int month;
            
        }
    //------------INNER CLASS---------------------
    
    //----------------------------methods
    
    /** No parametere constructor*/
    public DayOfYearSet(){
        Arr = new DayOfYear[1];
        DayOfYear d1 = new DayOfYear();
        Arr[0] = d1;
        set_Days();
        alive_counter--;
    }
    

    /** Constructor that takes Arraylist as parameter
     *@param other DayOfYear object
    */
    public DayOfYearSet(ArrayList<DayOfYear> List){
        set_Days();
        Arr = new DayOfYear[List.size()+1];
        for(int i=0;i<List.size()+1;i++)
            Arr[i] = new DayOfYear();

        for(int i=0;i<List.size();i++){
            Arr[i+1].day = List.get(i).day;
            Arr[i+1].month = List.get(i).month;
        }
    }
    
    
    /** Returns true if two sets are equal without order
    * @param other DayOfYearSet object*/
    @Override
    public boolean equals(Object other){
        
        //if(other == null) return false;
        //if(other.getClass() != this.getClass()) return false;

        final DayOfYearSet newObj = (DayOfYearSet) other;
        //if(newObj.size()!= this.size()) return false;
        
        for(int i=1;i<newObj.Arr.length;i++)
            if(this.search_set(newObj.Arr[i])==false) return false;
        
        return true;
    }


    @Override
    public String toString(){
        for(int i=1;i<this.size();i++)
            System.out.println(Arr[i]);
        return "Set Printed\n";
    }
    
    /** Adds new DayOfYear object into set
     * @param element DayOfYear object */
    public void add(DayOfYear element){
        for(int i=0;i<Arr.length;i++)
            if(Arr[i].check_same(element)==true)
                return;
        
        DayOfYear[] newArr = new DayOfYear[Arr.length+1];
        for(int i=0;i<Arr.length;i++)
            newArr[i] = Arr[i];

        newArr[Arr.length] = element;
        Arr = newArr;
    }

    
    /** Gets DayOfYear object as parameter and removes that element from set*/
    public void remove(DayOfYear element){

        //allocate memory for new array set
        DayOfYear[] newArr = new DayOfYear[Arr.length-1];
        for(int i=0;i<newArr.length;i++) 
            newArr[i] = new DayOfYear(); 
        

        int k = 0;
            for(int i=0;i<Arr.length;i++){//if date is different, adds it to new array of set
                if(element.day != Arr[i].day || element.month != Arr[i].month){
                    newArr[k].day = Arr[i].day;
                    newArr[k].month = Arr[i].month;
                    k++;
                }
        
            }
        alive_counter-= Arr.length;     
        Arr = newArr;     
    }

    
    /** Returns size of DayOfYear array of set*/
    public int size(){return Arr.length;}

    
    /** Operator+ 
     * @param other DayOfYear object
    */
    public DayOfYearSet find_union(DayOfYearSet other){ //operator+
        int flag;
        DayOfYearSet temp = new DayOfYearSet();

        for(int i=0;i<Arr.length;i++) //pass this set to temp
            temp.add(Arr[i]);
            
            //then check elements and fill with other set
        for(int i=0;i<other.Arr.length;i++){ 
            flag = 0;
            for(int j=0;j<temp.Arr.length;j++)
                if(other.Arr[i].check_same(temp.Arr[j])==true) flag = 1;
                
            if(flag==0) temp.add(other.Arr[i]);
        }
        return temp;
    }

    
    /** Operator-
     * @param other DayOfYear object
    */
    public DayOfYearSet find_difference(DayOfYearSet other){ //operator-
        DayOfYearSet temp = new DayOfYearSet();
        int flag = 0;
        for(int i=0;i<Arr.length;i++){
            flag = 0;
            for(int j=0;j<other.Arr.length;j++)
                if(Arr[i].check_same(other.Arr[j])==true)
                    flag = 1;
                    
            if(flag==0)temp.add(Arr[i]);
        }
        return temp;
    }

    
    /** Opeartor^
     * @param other DayOfYear object
    */
    public DayOfYearSet find_intersection(DayOfYearSet other){ //operator^
        DayOfYearSet temp = new DayOfYearSet();
        for(int i=0;i<Arr.length;i++)
            for(int j=0;j<other.Arr.length;j++)
                if(Arr[i].check_same(other.Arr[j])==true) //if it finds same, adds it to temp
                    temp.add(Arr[i]);
                     
        return temp;
    }

    
    /** Operator! 
     * @param other DayOfYear object
    */
    public DayOfYearSet find_complement(){ //operator!
        DayOfYearSet tempSet = new DayOfYearSet(); //creates new set
        for(int i=1;i<13;i++){
            for(int j=1;j<=Days[i];j++){ 
                //creates new element and search it in set
                DayOfYear temp = new DayOfYear(j,i); 
                if(search_set(temp)==false)
                    tempSet.add(temp);
            }
        }
        return tempSet;       
    }

    
    /** returns alive DayOfYear objects number*/
    public static int get_alive_counter(){ return alive_counter;}

    
    /** fills Days array with number of day of each month*/
    private void set_Days(){
        Days[0] = 0; 
        Days[1] = 31;   Days[2] = 28;   Days[3] = 31;
        Days[4] = 30;   Days[5] = 31;   Days[6] = 30; 
        Days[7] = 31;   Days[8] = 31;   Days[9] = 30; 
        Days[10] = 31;  Days[11] = 30;  Days[12] = 31;
    }

    
    /** Returns object of given index*/
    public DayOfYear get(int index){return Arr[index];}

    
    /** gets index and DayOfYear object as parameter and changes date of given index
    * @param index Index that will be changed 
    * @param element is DayOfYear objects that wanted to be changed
    */
    public void set(int index, DayOfYear element){
        if(index>=0&&index<=Arr.length)//sets the given index's date from given element
            Arr[index].setDate(element.getDay(), element.getMonth());     
    }

    
    /** searchs DayOfYear elements in set
    *@param element is DayOfYear objects that wanted to be searched */
    public boolean search_set(DayOfYear element){
        for(int i=1;i<Arr.length;i++) //search this set, returns true if it finds
            if(element.day == Arr[i].day && element.month == Arr[i].month)
                return true;
            
        return false;
    }
    
    
    /** clones one set to another with deep copy*/
    @Override
    public Object clone()throws CloneNotSupportedException{
        var temp = new DayOfYearSet(); //creates new set
        temp.Arr = new DayOfYear[Arr.length]; //allocate memory for array
        
        for(int i=0;i<temp.Arr.length;i++) //allocate memory for every object
            temp.Arr[i] = new DayOfYear();
    
        for(int i=0;i<temp.Arr.length;i++){ //deep copy 
            temp.Arr[i].month = Arr[i].month;
            temp.Arr[i].day = Arr[i].day;
        }
        alive_counter--;
        return temp;   
    }
    

    
    //----------------------------variables
    /** It keeps dates.*/
    private DayOfYear[] Arr;
    
    /** Counts alive DayOfYear objects.*/
    private static int alive_counter = 0;
    
    /** All days of a year for complement.*/
    private static int[] Days = new int[13];
}
