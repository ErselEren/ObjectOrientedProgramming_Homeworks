//use .txt format for load and save

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;
import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.*;
import java.awt.*;

/**
* PEG SOLITAIRE GAME
*/
public class PegSolitaire extends JFrame implements ActionListener, Boards, PegInterFace{

    private JFrame window;
    private JPanel panel1;
    private JPanel panel2;   
    private Container contents;
    private JButton[][] squares;
    private Color colorGray = Color.GRAY;
    private Color colorGreen = Color.GREEN;
    private Color colorCyan = Color.CYAN;
    private int row;
    private int col;
    private int board_type = 0;
    private int[][] table = new int[1][1];
    private JFrame f = new JFrame();
    private JFrame window1 = new JFrame("Choose direction");
    private JTextArea area=new JTextArea("Peg counter");  
    private int[] last_step = new int[3];
    private JFileChooser fc;
    private int status = 0;
    private static JTextField txt;
    private int StepCounter = 0;
    private int PegCounter = 0;
    
    /** Constructor with board choosing*/
    PegSolitaire(){
        RadioButtonHandler radioHandler = new RadioButtonHandler();
        ButtonGroup group = new ButtonGroup();

        //creating radio buttons
        JRadioButton j1 = new JRadioButton("Board type 1");
        JRadioButton j2 = new JRadioButton("Board type 2");
        JRadioButton j3 = new JRadioButton("Board type 3");
        JRadioButton j4 = new JRadioButton("Board type 4");
        JRadioButton j5 = new JRadioButton("Board type 5");
        
        //adding actionListener
        j1.addActionListener(radioHandler);
        j2.addActionListener(radioHandler);
        j3.addActionListener(radioHandler);
        j4.addActionListener(radioHandler);
        j5.addActionListener(radioHandler);
        
        //seting positions of buttons
        j1.setBounds(75,50,100,30);
        j2.setBounds(75,100,100,30);
        j3.setBounds(75,150,100,30);
        j4.setBounds(75,200,100,30);
        j5.setBounds(75,250,100,30);
        
        //adding buttons into group and Jframe
        group.add(j1);
        group.add(j2);
        group.add(j3);
        group.add(j4);
        group.add(j5);
        f.add(j1);
        f.add(j2);
        f.add(j3);
        f.add(j4);
        f.add(j5);
        f.setSize(300,400);
        f.setLayout(null);
        f.setVisible(true);   
    }

    /** Constructor with int array*/
    PegSolitaire(int other[][]){ //takes a int array and plays the game
        table = other;
        play_game();
    }

    /** checks if game is finished or not*/
    public boolean check_endgame(){ //returns true if it can't find valid move, else false
        for(int i=0;i<squares.length;i++){
            for(int j=0;j<squares.length;j++){
                if(squares[i][j].getBackground()==colorGreen){ //if index is peg
                    if(j>1)//check left
                        if(squares[i][j-1].getBackground()==colorGreen && squares[i][j-2].getBackground()==colorCyan)
                            return false;

                    if(j+2<squares.length)//check right
                        if(squares[i][j+1].getBackground() == colorGreen && squares[i][j+2].getBackground()==colorCyan)
                            return false;

                    if(i>1)//check up
                        if(squares[i-1][j].getBackground()==colorGreen && squares[i-2][j].getBackground()==colorCyan)
                            return false; 

                    if(i+2<squares.length)//check down
                        if(squares[i+1][j].getBackground() == colorGreen && squares[i+2][j].getBackground()==colorCyan)
                            return false;
                }
            }
        }
        return true;
    }

    /**controls buttons of board */
    private class ButtonHandler implements ActionListener{
        public void actionPerformed(ActionEvent e){
            Object source = e.getSource();
                for(int i=0;i<table.length;i++){
                  for(int j=0;j<table.length;j++){
                    if(source == squares[i][j]&&squares[i][j].getBackground()==colorGreen){ //if choosen button is peg
                        row = i;
                        col = j;
                        directionButtons(i, j); //manages direction process
                    }
                  }
                }
                area.setText("Counter : "+ getStepCounter());
        }
    }

    /**returns counter of steps that made*/
    public int getStepCounter(){
        return StepCounter;
    }

    /**returns number of peg that left*/
    public int getPegCounter(){
        return PegCounter;
    }
    
    /**controls buttons of board choosing */
    private class RadioButtonHandler implements ActionListener{
        public void actionPerformed(ActionEvent e){
                JRadioButton RadioButton = (JRadioButton)e.getSource();
                //sets board type according to chosen radioButton
                if(RadioButton.getText()=="Board type 1") board_type = 1;
                else if(RadioButton.getText()=="Board type 2") board_type = 2;  
                else if(RadioButton.getText()=="Board type 3") board_type = 3; 
                else if(RadioButton.getText()=="Board type 4") board_type = 4;
                else if(RadioButton.getText()=="Board type 5") board_type = 5;
                fill_board();
                play_game();
                f.setVisible(false);//close Jframe after choice
        }
    }

    /**controls direction buttons */
    private class DirectionButtonHandler implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e) {
            JButton directionButton = (JButton)e.getSource();
            //calls make_move method with direction parameter
            if(directionButton.getText()=="LEFT") make_move(1);
            else if(directionButton.getText()=="RIGHT") make_move(2);
            else if(directionButton.getText()=="UP") make_move(3);
            else if(directionButton.getText()=="DOWN") make_move(4);
            

            window1.setVisible(false);
            if(check_endgame()==true) System.exit(1);
        }
        
    }

    /** makes move and changes board*/
    public boolean make_move(int direction){//returns true if movement is valid, else false
        if(direction==1){//left
            if(col>1){
                if(squares[row][col-1].getBackground()==colorGreen && squares[row][col-2].getBackground()==colorCyan){
                    squares[row][col].setBackground(colorCyan);
                    squares[row][col].setText("");
                    squares[row][col-1].setBackground(colorCyan);
                    squares[row][col-1].setText("");
                    squares[row][col-2].setBackground(colorGreen);
                    squares[row][col-2].setText("P");
                    last_step[0] = 1;
                    last_step[1] = row;
                    last_step[2] = col;
                    StepCounter++;
                    return true; 
                }
                return false;
            }
            return false;
        }
        else if(direction==2){//right
            if(col+2<squares.length){
                if(squares[row][col+1].getBackground() == colorGreen && squares[row][col+2].getBackground()==colorCyan){
                    squares[row][col].setBackground(colorCyan);
                    squares[row][col].setText("");
                    squares[row][col+1].setBackground(colorCyan);
                    squares[row][col+1].setText("");
                    squares[row][col+2].setBackground(colorGreen);
                    squares[row][col+2].setText("P");
                    last_step[0] = 2;
                    last_step[1] = row;
                    last_step[2] = col;
                    StepCounter++;
                    return true;   
                }
                return false;
            }
            return false;
        }
        else if(direction==3){//up
            if(row>1){
                if(squares[row-1][col].getBackground()==colorGreen && squares[row-2][col].getBackground()==colorCyan){
                    squares[row][col].setBackground(colorCyan);
                    squares[row][col].setText("");
                    squares[row-1][col].setBackground(colorCyan);
                    squares[row-1][col].setText("");
                    squares[row-2][col].setBackground(colorGreen);
                    squares[row-2][col].setText("P");
                    last_step[0] = 3;
                    last_step[1] = row;
                    last_step[2] = col;
                    StepCounter++;
                    return true;    
                }
                return false;
            }
            return false;
        }
        else if(direction==4){//down   
            if(row+2<squares.length){
                if(squares[row+1][col].getBackground() == colorGreen && squares[row+2][col].getBackground()==colorCyan){
                    squares[row][col].setBackground(colorCyan);
                    squares[row][col].setText("");
                    squares[row+1][col].setBackground(colorCyan);
                    squares[row+1][col].setText("");
                    squares[row+2][col].setBackground(colorGreen);
                    squares[row+2][col].setText("P");
                    last_step[0] = 4;
                    last_step[1] = row;
                    last_step[2] = col;
                    StepCounter++;
                    return true;   
                }
                return false;
            }
            return false;
        }
        return false;
    }

    /**creates window for direction buttons*/
    public void directionButtons(int i, int j){
        window1.setLocationRelativeTo(squares[i][j]);//opens direction windows in front of pressed button
        window1.setVisible(true); 
        
        DirectionButtonHandler directionHandler = new DirectionButtonHandler();
        JPanel panel1 = new JPanel();
        
        //creating direction buttons
        JButton j1 = new JButton("LEFT");
        JButton j2 = new JButton("RIGHT");
        JButton j3 = new JButton("UP");
        JButton j4 = new JButton("DOWN");
        
        //adding actionlistener
        j1.addActionListener(directionHandler);
        j2.addActionListener(directionHandler);
        j3.addActionListener(directionHandler);
        j4.addActionListener(directionHandler);
        
        //adding buttons to panel
        panel1.add(j1);
        panel1.add(j2);
        panel1.add(j3);
        panel1.add(j4);

        panel1.setVisible(true);
        window1.add(panel1);
        window1.pack(); 
    }

    /**fills board with buttons */
    private void setButtons(ActionListener buttonHandler){
        squares = new JButton[table.length][table.length];//allocating memory for board
        for(int i=0;i<table.length;i++){
            for(int j=0;j<table.length;j++){
                
                JButton b = new JButton(" ");
                b.setPreferredSize(new Dimension(50,50));//size of buttons

                if(table[i][j]==1){//peg
                    b.setText("P");
                    squares[i][j] = b;
                    squares[i][j].setBackground(colorGreen);
                }
                else if(table[i][j]==2){//empty
                    b.setText("");
                    squares[i][j] = b;
                    squares[i][j].setBackground(colorCyan);
                }
                else{//wall
                    squares[i][j] = b;
                    squares[i][j].setBackground(colorGray);
                }

                contents.add(squares[i][j]);
                squares[i][j].addActionListener(buttonHandler); //adding actionListener for every button
            }
        }
    }
    
    public void reset_board(){
        for(int i=0;i<squares.length;i++){
            for(int j=0;j<squares.length;j++){
                if(squares[i][j].getBackground()==colorCyan){
                    squares[i][j].setBackground(colorGreen);
                    squares[i][j].setText("P");
                }
            }
        }
        squares[squares.length/2][squares.length/2].setBackground(colorCyan);
        squares[squares.length/2][squares.length/2].setText("");
        PegCounter = 0;
        StepCounter = 0;
    }

    /**creates window and panels and calls necessary functions*/
    public void play_game(){//sets panels, calls fill_board and setButtonsv
        ButtonHandler buttonHandler = new ButtonHandler();
        window = new JFrame("PegSolitaire");
        panel1 = new JPanel();
        panel2 = new JPanel(); 
        panel1.setBackground(Color.CYAN);
        panel2.setBackground(Color.DARK_GRAY);
        
        //creating buttons and adding them into panel2
        JButton undoButton = new JButton("Undo");
        JButton saveButton = new JButton("Save");
        JButton loadButton = new JButton("Load");
        JButton autoButton = new JButton("Auto Single Step");
        JButton resetButton = new JButton("Reset");
        panel2.add(saveButton);
        panel2.add(loadButton);
        panel2.add(undoButton);
        panel2.add(autoButton);
        panel2.add(resetButton);
        
        
        panel2.add(area);
        area.setBounds(10,30, 200,200);  
        setLayout(new GridLayout(table.length,table.length));//gridlayout for board
        setSize(new Dimension(500,500));
        contents = getContentPane();
        fill_board();
        setButtons(buttonHandler);
        panel1.add(contents);
        window.setResizable(false);
        window.add(panel1); //adding panel1 into window
        window.add(panel2,BorderLayout.SOUTH); //adding panel2 into window
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.pack();
        window.setVisible(true);

        //undo button listener calls undo method
        resetButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                reset_board();
            }
        });

        //undo button listener calls undo method
        undoButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                undo();
            }
        });
        
        //gets chosen text file and writes board into it
        saveButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                fc = new JFileChooser();
                fc.setDialogTitle("Save file");
                int result = fc.showSaveDialog(null);
                if(result == JFileChooser.APPROVE_OPTION){
                    save_game();
                }
            }
        });
        
        //gets chosen text file and reads board from it
        loadButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                fc = new JFileChooser();
                fc.setDialogTitle("Load File");
                int result = fc.showSaveDialog(null);
                if(result == JFileChooser.APPROVE_OPTION){
                    load_game();
                }
            }
        });

        //plays one single step randomly
        autoButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //random hamle ve direction üret
                Random rand= new Random();
                int randRow;
                int randCol;
                int randDirection;
                while(true){
                    randRow = rand.nextInt(table.length);
                    randCol = rand.nextInt(table.length);
                    randDirection = rand.nextInt(4)+1;
                    if(squares[randRow][randCol].getBackground()==colorGreen){
                        row = randRow;
                        col = randCol;
                        if(make_move(randDirection)==true){break;}
                    }
                }
                area.setText("Counter : "+ getStepCounter());
                if(check_endgame()==true) end_of_game();
            }
        });
        
    }

    /**manages end of the game screen*/
    public void end_of_game(){
        for(int i=0;i<squares.length;i++)
            for(int j=0;j<squares.length;j++)
                if(squares[i][j].getBackground()==colorGreen) PegCounter++;
            
        window.setVisible(false);
        JFrame endFrame = new JFrame("GAME IS OVER");
        JPanel endPanel = new JPanel();
        JTextArea endText=new JTextArea("Your score is : " + getPegCounter()); 
        endFrame.setBounds(300,300,500,500);
        endPanel.setSize(new Dimension(300,300));
        endText.setBounds(100,100, 500,500); 
        endPanel.add(endText);
        endFrame.add(endPanel); 
        endFrame.setVisible(true);
        endFrame.pack();
        endFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    /**fills int table array from interface*/
    public void fill_board(){//fills int table array from interface
        if(status!=0) return;
        
        if(board_type==1){
            int[][] temp = new int[squares1.length][squares1.length];
            for(int i=0;i<squares1.length;i++)
                for(int j=0;j<squares1.length;j++)
                    temp[i][j] = squares1[i][j];
            table = temp;                    
        }
        else if(board_type==2){
            int[][] temp = new int[squares2.length][squares2.length];
            for(int i=0;i<squares2.length;i++)
                for(int j=0;j<squares2[i].length;j++)
                    temp[i][j] = squares2[i][j];
            table = temp;
        }
        else if(board_type==3){
            int[][] temp = new int[squares3.length][squares3.length];
            for(int i=0;i<squares3.length;i++)
                for(int j=0;j<squares3[i].length;j++)
                    temp[i][j] = squares3[i][j];
            table = temp;        
        }
        else if(board_type==4){
            int[][] temp = new int[squares4.length][squares4.length];
            for(int i=0;i<squares4.length;i++)
                for(int j=0;j<squares4[i].length;j++)
                    temp[i][j] = squares4[i][j];
            table = temp;        
        }
        else if(board_type==5){
            int[][] temp = new int[squares5.length][squares5.length];
            for(int i=0;i<squares5.length;i++)
                for(int j=0;j<squares5[i].length;j++)
                    temp[i][j] = squares5[i][j];
            table = temp;        
        }
    }

    /**loads game from text files */
    public void load_game(){
        try{
            int counter = 0;
            int length=0;
            int[][] temp;
            String line;
            //opens file and gets size information of board
            File file = fc.getSelectedFile();
            Scanner filereader = new Scanner(file);
            while(filereader.hasNextLine()){ 
                counter++;
                length = filereader.nextLine().length();
            }
            temp = new int[counter][length];
            filereader.close();
            
            //opens file, reads line by line and holds them in temp 2D int array
            counter = 0;
            filereader = new Scanner(file);
            while(filereader.hasNextLine()){
                line = new String(filereader.nextLine());
                for(int i=0;i<line.length();i++){
                    temp[counter][i] = Character.getNumericValue(line.charAt(i));
                }
                counter++;
            }
            filereader.close();
            window.setVisible(false);
            new PegSolitaire(temp);
        }
        catch(IOException xe)
        {
            System.exit(0);
        }
    }

    /**writes board into txt file */
    public void save_game(){//writes every cell of board into file
        try
        {
            File file=fc.getSelectedFile();
            FileWriter fw = new FileWriter(file);
            for(int i=0;i<squares.length;i++)
            {
                String line = new String(); //line is string that holds every line row of board
                for(int j=0;j<squares.length;j++)//modifying line according to type of cells
                {
                    if(squares[i][j].getBackground()==colorGray) line +="0";
                    else if(squares[i][j].getBackground()==colorGreen) line +="1";
                    else if(squares[i][j].getBackground()==colorCyan) line += "2";
                }
                line +="\n";
                fw.write(line); //writing line into file
            }
            fw.close();
        }
        catch(IOException xe)
        {
            System.out.println(xe);
        }
    }

    /**undo single step*/
    public void undo(){//last_step hold data of previous movement
        if(last_step[0]==1){//if previous movement is left
            squares[last_step[1]][last_step[2]].setBackground(colorGreen);
            squares[last_step[1]][last_step[2]].setText("P");
            squares[last_step[1]][last_step[2]-1].setBackground(colorGreen);
            squares[last_step[1]][last_step[2]-1].setText("P");
            squares[last_step[1]][last_step[2]-2].setBackground(colorCyan);
            squares[last_step[1]][last_step[2]-2].setText("");
        }
        else if(last_step[0]==2){//if previous movement is right
            squares[last_step[1]][last_step[2]].setBackground(colorGreen);
            squares[last_step[1]][last_step[2]].setText("P");
            squares[last_step[1]][last_step[2]+1].setBackground(colorGreen);
            squares[last_step[1]][last_step[2]+1].setText("P");
            squares[last_step[1]][last_step[2]+2].setBackground(colorCyan);
            squares[last_step[1]][last_step[2]+2].setText("");
        }
        else if(last_step[0]==3){//if previous movement is up
            squares[last_step[1]][last_step[2]].setBackground(colorGreen);
            squares[last_step[1]][last_step[2]].setText("P");
            squares[last_step[1]-1][last_step[2]].setBackground(colorGreen);
            squares[last_step[1]-1][last_step[2]].setText("P");
            squares[last_step[1]-2][last_step[2]].setBackground(colorCyan);
            squares[last_step[1]-2][last_step[2]].setText("");
        }
        else if(last_step[0]==4){//if previous movement is down
            squares[last_step[1]][last_step[2]].setBackground(colorGreen);
            squares[last_step[1]][last_step[2]].setText("P");
            squares[last_step[1]+1][last_step[2]].setBackground(colorGreen);
            squares[last_step[1]+1][last_step[2]].setText("P");
            squares[last_step[1]+2][last_step[2]].setBackground(colorCyan);
            squares[last_step[1]+2][last_step[2]].setText("");
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        //empty
    }
}
