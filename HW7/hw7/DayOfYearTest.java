import java.io.FileWriter;
import java.util.ArrayList;
import java.io.File;
import java.io.IOException;
import DayOfYearSet.*;


//All functions are tested twice or more and De Morgan rules are tested for 6 different set.
//output of this program is written in output.txt
//To run the program, write "make" 
//Document files are included in javadoc folder
//There are javadoc comments in DayOfYearSet.java file which has class implementation.

public class DayOfYearTest {
    
    public static void write_to_file(DayOfYearSet set, String Name)
    {
        try 
        {
            FileWriter _writer = new FileWriter( Name + ".txt");
            for(int i=1;i<set.size();i++)
                _writer.write(set.get(i).getDay()+"  "+set.get(i).getMonth()+"\n");
            
            _writer.close();
        } catch (IOException e) 
        {
            System.out.println("Error in file writing!");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws CloneNotSupportedException{
        
        //----------set1 created and filled with 5 element-------------------
        DayOfYearSet set1 =  new DayOfYearSet(); //new set1
        DayOfYearSet.DayOfYear element1 = new DayOfYearSet.DayOfYear(31,1);
        DayOfYearSet.DayOfYear element2 = new DayOfYearSet.DayOfYear(14,9);
        DayOfYearSet.DayOfYear element3 = new DayOfYearSet.DayOfYear(8,11);
        DayOfYearSet.DayOfYear element4 = new DayOfYearSet.DayOfYear(14,4);
        DayOfYearSet.DayOfYear element5 = new DayOfYearSet.DayOfYear(25,7);
        set1.add(element1); //add function
        set1.add(element2);
        set1.add(element3);
        set1.add(element4);
        set1.add(element5);
        System.out.println("---------------set1-----------------");
        System.out.println(set1); //printing set1
        System.out.println("1-ALIVE DAYOFYEAR OBJECTS : "+DayOfYearSet.get_alive_counter());
        

        //----------set2 created and set1 is copied to set2-------------------
        DayOfYearSet set2 =  new DayOfYearSet(); // new set2
        set2 = (DayOfYearSet)set1.clone(); //copying set1 into set2
        System.out.println("---------------set2-----------------");
        System.out.println(set2); //printing set2
        System.out.println("2-ALIVE DAYOFYEAR OBJECTS : "+DayOfYearSet.get_alive_counter());


        //----------element3(Day 8, Month 11) removed from set2---------------
        set2.remove(element3);
        System.out.println("---------------set2-after-remove----");
        System.out.println(set2); //printing set2
        System.out.println("3-ALIVE DAYOFYEAR OBJECTS : "+DayOfYearSet.get_alive_counter());


        //----------set3 created and filled with 3 element-------------------
        DayOfYearSet set3 =  new DayOfYearSet();
        DayOfYearSet.DayOfYear element6 = new DayOfYearSet.DayOfYear(29,5);
        DayOfYearSet.DayOfYear element7 = new DayOfYearSet.DayOfYear(13,12);
        DayOfYearSet.DayOfYear element8 = new DayOfYearSet.DayOfYear(25,7);
        set3.add(element6);
        set3.add(element7);
        set3.add(element8); //here, Day 25, Month 7 is already exist, therefore duplicate won't exist in set2
        
        
        //----------union of set1 and set3 is assigned to set2
        set2 = set3.find_union(set1);
        System.out.println("---------------set2-after-union-----");
        System.out.println(set2); //printing set2


        
        //----------set4 is created and element6 and element1 are added 
        //----------then difference of set2 and set4 is assigned to set4
        DayOfYearSet set4 =  new DayOfYearSet();
        set4.add(element6);
        set4.add(element1);
        set4 = set2.find_difference(set4);
        System.out.println("---------------set4-after-difference-");
        System.out.println(set4); //printing set4


        //-----------set5 is created and intersection of set1 and set4 is assigned to set5
        DayOfYearSet set5 =  new DayOfYearSet();
        set5 = set1.find_intersection(set4);
        System.out.println("---------------set5-after-intersection-");
        System.out.println(set5); //printing set5
        

        //------------creating element with the same value of element4 and remove from set5
        DayOfYearSet.DayOfYear element9 = new DayOfYearSet.DayOfYear(14,4);
        set5.remove(element9);
        System.out.println("---------------set5-after-remove----");
        System.out.println(set5); //printing set5

        //-------------set6 is created and complement of set5 is assigned to set6
        DayOfYearSet set6 =  new DayOfYearSet();
        set6 = set5.find_complement();


        // de morgan rules. Since, there is no operator overloading in Java,
        // + ! == ^ operators are in the name of, complement, union, intersection and equals
        // these if statement is --> !(set1+set2) == !set1 ^ !set2
        if(((set1.find_union(set2)).find_complement()).equals((set1.find_complement()).find_intersection(set2.find_complement())))
            System.out.println("De Morgan rule is working!");
        else 
            System.out.println("De Morgan rule is not working!");
        
        //_________________________________________________________________________________________________________________________

        if(((set3.find_union(set4)).find_complement()).equals((set3.find_complement()).find_intersection(set4.find_complement())))
            System.out.println("De Morgan rule is working!");
        else 
            System.out.println("De Morgan rule is not working!");
        //_________________________________________________________________________________________________________________________
        
        if(((set5.find_union(set6)).find_complement()).equals((set5.find_complement()).find_intersection(set6.find_complement())))
            System.out.println("De Morgan rule is working!");
        else 
            System.out.println("De Morgan rule is not working!");



        //---------------testing constructor that takes ArrayList as parameter
        ArrayList<DayOfYearSet.DayOfYear> setList = new ArrayList<DayOfYearSet.DayOfYear>(3);
        DayOfYearSet.DayOfYear element10 = new DayOfYearSet.DayOfYear(21,2);
        DayOfYearSet.DayOfYear element11 = new DayOfYearSet.DayOfYear(17,6);
        DayOfYearSet.DayOfYear element12 = new DayOfYearSet.DayOfYear(5,5);
        setList.add(element10);
        setList.add(element11);
        setList.add(element12);
        DayOfYearSet set7 =  new DayOfYearSet(setList);
        System.out.println("\n\n---------------set7-------------");
        System.out.println(set7); //printing set7
        


        write_to_file(set1,"set1");
        write_to_file(set2,"set2");
        write_to_file(set3,"set3");
        write_to_file(set4,"set4");
        write_to_file(set5,"set5");
        write_to_file(set6,"set6");

        //set6 is complement of set5. Remove the comment to print all dates of set
            //System.out.println("\n\n---------------set6-------------");
            //System.out.println(set6); //printing set6
    }

}
