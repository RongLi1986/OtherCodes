 package com.sun.qdu;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

import javax.swing.JOptionPane;


class SnakeModel implements Runnable{ //Model of Snake Eater
  GreedSnake gs;
  boolean[][] matrix;
  LinkedList nodeArray=new LinkedList();
  Node food;
  int maxX;//max x-axis
  int maxY;//max y-axis
  int direction=1; //initial direction  
  boolean running=false;
  int timeInterval=100;// speed(time for refresh the window)
  double speedChangeRate=0.5;// rate for change speed
  boolean paused=false;// state of game
  int score=0;
  int countMove=0;
  
  public static final int UP=2;
  public static final int DOWN=4;
  public static final int LEFT=1;
  public static final int RIGHT=3;

  public SnakeModel(GreedSnake gs,int maxX,int maxY){
     this.gs=gs;
     this.maxX=maxX;
     this.maxY=maxY;
     matrix=new boolean[maxX][];
     for(int i=0;i<maxX;++i){
       matrix[i]=new boolean[maxY];
       Arrays.fill(matrix[i],false);// no food and snake
     }
     
     int initArrayLength=7;
     for(int i=0;i<initArrayLength;++i){
       int x=maxX/2+i;
       int y=maxY/2;
       nodeArray.addLast(new Node(x,y));
       matrix[x][y]=true;// snake body
     }
     food=createFood();
     matrix[food.x][food.y]=true;// food
  }

   public void changeDirection(int newDirection){ //change direct
     if(Math.abs(newDirection-direction)!=2){// avoid the conflict (op direction)
     direction=newDirection;
     }
   }

   public boolean moveOn(){  //control the snake to move
     Node n=(Node)nodeArray.getFirst();
     int x=n.x;
     int y=n.y;
     switch(direction){
     case UP:
     y--; // just coordinate
     break;
     case DOWN:
     y++; //
     break;
     case LEFT:
     x--;
     break;
     case RIGHT:
     x++;
     break;
     }
     
    if((0<=x&&x<maxX)&&(0<=y&&y<maxY)){
      if(matrix[x][y]){// touch food or body
        if(x==food.x&&y==food.y){// food
        nodeArray.addFirst(food);// add food at first
        score+=1;
        countMove=0;
        food=createFood();
        matrix[food.x][food.y]=true;
        return true;
        }
        else 
        return false;// touch body
       }
       else{//no touch
       nodeArray.addFirst(new Node(x,y));//update snake
       matrix[x][y]=true;
       n=(Node)nodeArray.removeLast();//
       matrix[n.x][n.y]=false;
       countMove++;
       return true;
       }
      }
     return false;//touch border
     }


    public void run(){
      running=true;
     while(running){
      try{
        Thread.sleep(timeInterval);
      }
      catch(Exception e){
      break;
      }
      if(!paused){
        if(moveOn()){
        gs.repaint();
        }
        else{//game over
        JOptionPane.showMessageDialog(null,"GAME OVER","Game Over",JOptionPane.INFORMATION_MESSAGE);
        break;
        }
      }
     }
     running=false;
    }

  private Node createFood(){
   int x=0;
   int y=0;
   do{
    Random r=new Random();
    x=r.nextInt(maxX); //r%maxX
    y=r.nextInt(maxY);
   }while(matrix[x][y]);

   return new Node(x,y);
  }


   public void speedUp(){   //speedUp
      timeInterval*=speedChangeRate;
   }


    public void speedDown(){  //speedDown
      timeInterval/=speedChangeRate;
    }

    public void changePauseState(){ //change to pause
      paused=!paused;
    }
}



