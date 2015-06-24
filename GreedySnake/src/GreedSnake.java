 package com.sun.qdu;
 import java.awt.*;
 import java.awt.event.*;
 import javax.swing.*;
 import java.util.*;
 
public class GreedSnake extends KeyAdapter{
 
 JFrame mainFrame;
 Canvas paintCanvas;
 JLabel labelScore;   //counting score
 SnakeModel snakeModel=null;  // snake
 public static final int DEFAULT_WIDTH=640;
 public static final int DEFAULT_HEIGHT=480;
 public static final int nodeWidth=10;
 public static final int nodeHeight=10;
 
 
     public GreedSnake(){   //set element in window
       mainFrame=new JFrame("Snake Eater");
       Container cp=mainFrame.getContentPane();
       labelScore=new JLabel("Your score:",JLabel.CENTER);
       cp.add(labelScore,BorderLayout.NORTH);
       paintCanvas=new Canvas();
       paintCanvas.setSize(DEFAULT_WIDTH+1,DEFAULT_HEIGHT+1);
       paintCanvas.addKeyListener(this);
       
       cp.add(paintCanvas,BorderLayout.CENTER);
       JPanel panelButtom=new JPanel();
       panelButtom.setLayout(new BorderLayout());
       JLabel labelHelp;// intro message
       labelHelp=new JLabel("Author:  Rong LI  2013.4.30",JLabel.CENTER);
       panelButtom.add(labelHelp,BorderLayout.NORTH);
       
       labelHelp=new JLabel(" PageUP or PageDown: change speed",JLabel.CENTER);
       panelButtom.add(labelHelp,BorderLayout.EAST);
       
       labelHelp=new JLabel(" Enter: restart",JLabel.CENTER);
       panelButtom.add(labelHelp,BorderLayout.CENTER);
       labelHelp=new JLabel(" SPACE: pause",JLabel.CENTER);
       panelButtom.add(labelHelp,BorderLayout.WEST);
       cp.add(panelButtom,BorderLayout.SOUTH);
 
       mainFrame.addKeyListener(this);
       mainFrame.pack();
       mainFrame.setResizable(false);//windows size is not changed
       mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       mainFrame.setVisible(true);
       begin();
       }
 
      public void keyPressed(KeyEvent e){  //detect the key pressed
         int keyCode=e.getKeyCode();
         if(snakeModel.running)
         switch(keyCode){
          case KeyEvent.VK_UP:
          snakeModel.changeDirection(SnakeModel.UP);
          break;
          case KeyEvent.VK_DOWN:
          snakeModel.changeDirection(SnakeModel.DOWN);
          break;
          case KeyEvent.VK_LEFT:
          snakeModel.changeDirection(SnakeModel.LEFT);
          break;
          case KeyEvent.VK_RIGHT:
          snakeModel.changeDirection(SnakeModel.RIGHT);
          break;
          case KeyEvent.VK_PAGE_UP:
          snakeModel.speedUp();// speed up
          break;
          case KeyEvent.VK_PAGE_DOWN:
          snakeModel.speedDown();// speed down
          break;
          case KeyEvent.VK_SPACE:
          snakeModel.changePauseState();// pause
          break;
          default:
         }
        //restart
        if(keyCode==KeyEvent.VK_ENTER){
        snakeModel.running=false;
        begin();
       }
      }
 

      void repaint(){ // draw the item and window
       Graphics g=paintCanvas.getGraphics();
       //draw background
       g.setColor(Color.LIGHT_GRAY);
       g.fillRect(0,0,DEFAULT_WIDTH,DEFAULT_HEIGHT);
       //draw the snake
       g.setColor(Color.BLACK);
       LinkedList na=snakeModel.nodeArray;
       Iterator it=na.iterator();
       while(it.hasNext()){
         Node n=(Node)it.next();
         drawNode(g,n);
       }
       // draw the food
        g.setColor(Color.BLUE);
        Node n=snakeModel.food;
        drawNode(g,n);
        updateScore();
      }
 

       private void drawNode(Graphics g,Node n){  //draw function
         g.fillRect(n.x*nodeWidth,n.y*nodeHeight,nodeWidth-1,nodeHeight-1);
       }
 

       public void updateScore(){ //updateScore
         String s="your score: "+snakeModel.score;
         labelScore.setText(s);
       }
 
       void begin(){ // all is begin here
        if(snakeModel==null||!snakeModel.running){
         snakeModel=new SnakeModel(this,DEFAULT_WIDTH/nodeWidth, DEFAULT_HEIGHT/nodeHeight);
         new Thread(snakeModel).start();
        }
       }
 
       public static void main(String[] args){
         GreedSnake gs=new GreedSnake();
       }
 }


