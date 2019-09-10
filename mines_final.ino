// testcolors demo for Adafruit RGBmatrixPanel library.
// Renders 512 colors on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420
// Library supports 4096 colors, but there aren't that many pixels!  :)

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.
#include <Arduino.h>
#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;




int GetNeighbours(int i, int j, int arr[][8]);

void PrintArray(int arr[][10]);

void PrintArraySmall(int arr[][8]);



void delay(int number_of_seconds);

struct boardValues{
  int rn_x;
  int rn_y;
};

struct zone{
    bool isReveal;
    bool isFlag;
    int number;
    bool isCurrent;

};

struct coordinate{
    int x;
    int y;
};

void PrintZoneArray(zone arr[][10]);

void PrintZoneRevealed(zone arr[][8]);

void PrintArrayZoneSmall(zone arr[][8]);

int * GetZones_X(zone arr[][8], int current_x, int current_y);

int * GetZones_Y(zone arr[][8], int current_x, int current_y);

coordinate * CombineArrays(int current_x, int current_y, zone arr[][8]);

void PrintCoordinate(coordinate *arr, zone arr2[][8]);

void openZone(int current_x, int current_y, zone arr[][8]);

void openNeighbours(int current_x, int current_y, zone arr[][8]);


RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  matrix.begin(); 
  drawBoard(8,8);
  setColorPixel(0, 7, "red");
  //delay(2000);
  setColorPixel(0, 4, "yellow");
  

  /*
  zone boardreal[10][10];

  for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {

          boardreal[i][j].number = 0;
          boardreal[i][j].isReveal = false;
          boardreal[i][j].isFlag= false;
          

      }
  }

  for (int i = 0; i < 6; i++) {

      //seed random number generator
      int x = rand()%(8)+1;
      //cout << x << endl;
      int y = rand()%(8)+1;
      //cout << y << endl;
      boardreal[x][y].number = 1;
  }


  PrintZoneArray(boardreal);
  zone numberBoard[8][8];
  boardValues thisBoard;
  thisBoard.rn_x= 0;
  thisBoard.rn_y= 0;

  for (int i = 1; i < 9; i++) {
      for (int j = 1; j < 9; j++) {
          
          if(i==1 && j==1){
            numberBoard[(i-1)][(j-1)].isCurrent==1;
          }
          else{
            numberBoard[(i-1)][(j-1)].isCurrent==0;
          }
          
          if (boardreal[i][j].number == 1) {
              //cout<< i << endl;
              //cout<<j << endl;
              numberBoard[(i - 1)][(j - 1)].number = 10;
              numberBoard[(i - 1)][(j - 1)].isReveal=false;
              numberBoard[(i - 1)][(j - 1)].isFlag= false;


          } else {

              //check index values
              int a = boardreal[(i - 1)][(j + 1)].number;
              int b = boardreal[(i - 1)][j].number;
              int c = boardreal[(i - 1)][(j - 1)].number;
              int d = boardreal[(i + 1)][(j + 1)].number;
              int e = boardreal[(i + 1)][(j)].number;
              int f = boardreal[(i + 1)][(j - 1)].number;
              int g = boardreal[i][(j + 1)].number;
              int h = boardreal[i][(j - 1)].number;

              //if (i==1 && j==8){
              //    cout << a + b + c + d + e + f + g + h << endl;
              //}
              numberBoard[(i - 1)][(j - 1)].number = a + b + c + d + e + f + g + h;
              numberBoard[(i - 1)][(j - 1)].isReveal= false;
              numberBoard[(i - 1)][(j - 1)].isFlag= false;


          }
      }
      
  }
  */
  // put your setup code here, to run once:
  
}

void loop() {
  for(int i=0; i<5; i++){
    setColorPixel(0, i, "yellow");
    //delay(3000);
  }
  
  // put your main code here, to run repeatedly:

}

void PrintZoneArray(zone arr[][10]){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if (j==8){
                
                //cout << " " << arr[i][j].number  << endl;
                if (i==8){
                    //cout <<  "`````````````````````" << endl;
                }
            }

            else{
                //cout << " " << arr[i][j].number;
            }

        }
    }

}

void PrintArrayZoneSmall(zone arr[][8]){
    for(int k=0; k<8; k++){
        for(int l=0; l<8; l++){
            if (l==7){
                //cout << " " << k << endl;
                //cout << " " << l  << endl;
                //cout << " " << arr[k][l].number  << endl;
                if (k==7){
                    //cout <<  "`````````````````````" << endl;
                }
            }
            else{
                //cout << " " << arr[k][l].number;
            }

        }
    }
}

void PrintZoneRevealed(zone arr[][8]){
    for (int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if (arr[i][j].isReveal== 1){
                if (j==7){
                    //cout << " " << k << endl;
                    //cout << " " << l  << endl;
                    //cout << " " << arr[i][j].number  <<  endl;
                    if (i==7){
                        //cout <<  "`````````````````````" << endl;
                    }
                }
                else{
                    //cout << " " << arr[i][j].number;
                }
            }
            else{
                if (j==7){
                    //cout << " " << k << endl;
                    //cout << " " << l  << endl;
                    //cout << " x"  << endl;
                    if (i==7){
                        //cout <<  "`````````````````````" << endl;
                    }
                }
                else{
                    //cout << " x";
                }


            }
        }
    }
}


int * GetZones_X(zone arr[][8], int current_x, int current_y){

    static int r[8];

    if (current_x==0){
        if (current_y==0){
            r[0]= 100;
            r[1]= 100;
            r[2]= 100;
            r[3]= current_x;
            r[4]= current_x+1;
            r[5]= current_x+1;
            r[6]= 100;
            r[7]= 100;


        }
        else if (current_y==7){
            r[0]= 100;
            r[1]= 100;
            r[2]= 100;
            r[3]= 100;
            r[4]= 100;
            r[5]= current_x+1;
            r[6]= current_x+1;
            r[7]= current_x;



        }
        else{
            r[0]= 100;
            r[1]= 100;
            r[2]= 100;
            r[3]= current_x;
            r[4]= current_x+1;
            r[5]= current_x+1;
            r[6]= current_x+1;
            r[7]= current_x;



        }
    }

    else if (current_x==7){
        if (current_y==0){
            r[0]= 100;
            r[1]= current_x-1;
            r[2]= current_x-1;
            r[3]= current_x;
            r[4]= 100;
            r[5]= 100;
            r[6]= 100;
            r[7]= 100;


        }
        else if (current_y==7){
            r[0]= current_x-1;
            r[1]= current_x-1;
            r[2]= 100;
            r[3]= 100;
            r[4]= 100;
            r[5]= 100;
            r[6]= 100;
            r[7]= current_x;


        }
        else{
            r[0]= current_x-1;
            r[1]= current_x-1;
            r[2]= current_x-1;
            r[3]= current_x;
            r[4]= 100;
            r[5]= 100;
            r[6]= 100;
            r[7]= current_x;


        }
    }
    else{
        if (current_y==0){
            r[0]= 100;
            r[1]= current_x-1;
            r[2]= current_x-1;
            r[3]= current_x;
            r[4]= current_x+1;
            r[5]= current_x+1;
            r[6]= 100;
            r[7]= 100;
        }

        else if(current_y==7){
            r[0]= current_x-1;
            r[1]= current_x-1;
            r[2]= 100;
            r[3]= 100;
            r[4]= 100;
            r[5]= current_x+1;
            r[6]= current_x+1;
            r[7]= current_x;
        }

        else{
            r[0]= current_x-1;
            r[1]= current_x-1;
            r[2]= current_x-1;
            r[3]= current_x;
            r[4]= current_x+1;
            r[5]= current_x+1;
            r[6]= current_x+1;
            r[7]= current_x;
        }



    }

    return r;
}

int * GetZones_Y(zone arr[][8], int current_x, int current_y){
    static int r[8];

    if (current_x==0){
        if (current_y==0){
            r[0]= 100;
            r[1]= 100;
            r[2]= 100;
            r[3]= current_y+1;
            r[4]= current_y+1;
            r[5]= current_y;
            r[6]= 100;
            r[7]= 100;



        }
        else if (current_y==7){
            r[0]= 100;
            r[1]= 100;
            r[2]= 100;
            r[3]= 100;
            r[4]= 100;
            r[5]= current_y;
            r[6]= current_y-1;
            r[7]= current_y-1;



        }
        else{
            r[0]= 100;
            r[1]= 100;
            r[2]= 100;
            r[3]= current_y+1;
            r[4]= current_y+1;
            r[5]= current_y;
            r[6]= current_y-1;
            r[7]= current_y-1;



        }
    }

    else if (current_x==7){
        if (current_y==0){
            r[0]= 100;
            r[1]= current_y;
            r[2]= current_y+1;
            r[3]= current_y+1;
            r[4]= 100;
            r[5]= 100;
            r[6]= 100;
            r[7]= 100;

        }
        else if (current_y==7){
            r[0]= current_y-1;
            r[1]= current_y;
            r[2]= 100;
            r[3]= 100;
            r[4]= 100;
            r[5]= 100;
            r[6]= 100;
            r[7]= current_y-1;


        }
        else{
            r[0]= current_y-1;
            r[1]= current_y;
            r[2]= current_y+1;
            r[3]= current_y+1;
            r[4]= 100;
            r[5]= 100;
            r[6]= 100;
            r[7]= current_y-1;


        }
    }
    else{
        if(current_y==0){
            r[0]= 100;
            r[1]= current_y;
            r[2]= current_y+1;
            r[3]= current_y+1;
            r[4]= current_y+1;
            r[5]= current_y;
            r[6]= 100;
            r[7]= 100;

        }
        else if(current_y==7){
            r[0]= current_y-1;
            r[1]= current_y;
            r[2]= 100;
            r[3]= 100;
            r[4]= 100;
            r[5]= current_y;
            r[6]= current_y-1;
            r[7]= current_y-1;

        }
        else{
            r[0]= current_y-1;
            r[1]= current_y;
            r[2]= current_y+1;
            r[3]= current_y+1;
            r[4]= current_y+1;
            r[5]= current_y;
            r[6]= current_y-1;
            r[7]= current_y-1;

        }

    }

    return r;
}

coordinate * CombineArrays(int current_x, int current_y, zone arr[][8]){
    int *x;
    int *y;

    static coordinate final[8];


    x= GetZones_X(arr, current_x, current_y);
    y= GetZones_Y(arr, current_x, current_y);

    for ( int i = 0; i < 8; i++ ) {
        int final_x= *(x+i);
        int final_y= *(y+i);
        final[i].x= final_x;
        final[i].y= final_y;
    }

    return final;
}

void PrintCoordinate(coordinate *arr, zone arr2[][8]){
    for (int i=0; i<8; i++){
        coordinate temp= *(arr+i);

        if (temp.x==100 && temp.y==100){
            //cout<< "there is no such node" << endl;
        }
        else{
            //cout<< "( " << temp.x << ", " << temp.y << "), and the value at this node is " << arr2[temp.x][temp.y].number << endl;
        }


    }
}

void openZone(int current_x, int current_y, zone arr[][8]){

    if (arr[current_x][current_y].isReveal==0 && arr[current_x][current_y].isFlag==0){
        arr[current_x][current_y].isReveal= true;

        //cout<< current_x<< ", ";
        //cout<<current_y<<endl;
        if (arr[current_x][current_y].number==0){



            for (int i=0; i<8; i++){
                coordinate *final= CombineArrays(current_x, current_y, arr);
                coordinate temp= *(final+i);
                int temp_x= temp.x;
                //cout<< temp_x<< ", ";

                int temp_y= temp.y;
                //cout<<temp_y<< endl;


                if (temp_x==100 && temp_y==100){
                    continue;
                }
                else{
                    if ((arr[temp_x][temp_y].isReveal==0)){
                        //arr[temp_x][temp_y].isReveal;
                        openZone(temp_x, temp_y, arr);
                    }
                }
            }
        }

    }

}

void setColorPixel(int x, int y, String color) {
  //sets a pixel at (x, y) to a specific color
  //color is limited to white, black, red, orange, yellow, green, blue, purple, and pink

  x = x+1;
  y = y+1;
  
  if (color.equalsIgnoreCase("white")) {
    matrix.drawPixel(x, y, matrix.Color333(7, 7, 7));
  }

  if (color.equalsIgnoreCase("black")) {
    matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
  }

  if (color.equalsIgnoreCase("red")) {
    matrix.drawPixel(x, y, matrix.Color333(7, 0, 0));
  }

  if (color.equalsIgnoreCase("orange")) {
    matrix.drawPixel(x, y, matrix.Color333(7, 4, 0));
  }

  if (color.equalsIgnoreCase("yellow")) {
    matrix.drawPixel(x, y, matrix.Color333(7, 7, 0));
  }

  if (color.equalsIgnoreCase("green")) {
    matrix.drawPixel(x, y, matrix.Color333(0, 7, 0));
  }

  if (color.equalsIgnoreCase("blue")) {
    matrix.drawPixel(x, y, matrix.Color333(0, 0, 7));
  }

  if (color.equalsIgnoreCase("purple")) {
    matrix.drawPixel(x, y, matrix.Color333(4, 0, 7));
  }

  if (color.equalsIgnoreCase("pink")) {
    matrix.drawPixel(x, y, matrix.Color333(7, 0, 4));
  }

}

void drawBoard(int width, int height) {
  //draws a white rectangle of size width x height on the led matrix, positioned two spaces from the left, with height centered

  int heightHalf = height/2;

  matrix.fillRect(1, 1, 1 + width, 1 + height, matrix.Color333(2, 2, 2));
}

void displayNumber(int x) {
  //displays the number on the right side in red, centered on the y-axis

  String num = String(x);
  if (num.length() == 1) {
    num = String("0" + num);
  }
  
  matrix.setCursor(20, 4);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.setTextSize(1);

  matrix.print(num);
}

void gameOver() {
  //displays game over across the screen
  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 0));
  
  matrix.setCursor(6, 0);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(3, 3, 3));

  matrix.print("GAME");

  matrix.setCursor(2, 8);
  matrix.print("OVER");
}

void matchStrategy(zone arr[][8], int current_x, int current_y, boardValues imp){

  if(current_x==imp.rn_x && current_y==imp.rn_y){
    setColorPixel(current_x, current_y, "black");
    
  }
  else{
      if(arr[current_x][current_y].isFlag==1){
        setColorPixel(current_x, current_y, "red");
      }
      else{
          if (arr[current_x][current_y].isReveal==1){
            if (arr[current_x][current_y].number==0){
              setColorPixel(current_x, current_y, "yellow");
              
            }
            else if(arr[current_x][current_y].number==1){
              setColorPixel(current_x, current_y, "blue");
              
            }
            else if(arr[current_x][current_y].number==2){
              setColorPixel(current_x, current_y, "green");
              
            }
            else if(arr[current_x][current_y].number==3){
              setColorPixel(current_x, current_y, "purple");
              
            }
            else if(arr[current_x][current_y].number==4){
              setColorPixel(current_x, current_y, "pink");
            }
      
            else if(arr[current_x][current_y].number==10){
              setColorPixel(current_x, current_y, "red");
            }
        }
     }
    
  }
  
}

void resetOriginalCurrent(boardValues imp, zone arr[][8]){
  
    
    imp.rn_y=0;
    takeXStep(imp, arr);
    takeYStep(imp, arr);
}

int takeXStep(boardValues imp, zone arr[][8]){
  imp.rn_x= imp.rn_x+1;
  int counter;
  while (arr[imp.rn_x][imp.rn_y].isReveal==1){
    imp.rn_x= imp.rn_x+1;
    if (imp.rn_x==7){
      //go to the next value fo y and repeat 
      break;
    }
  }
  return imp.rn_x;
  
}

int takeYStep(boardValues imp, zone arr[][8]){
  imp.rn_y= imp.rn_y+1;
  while (arr[imp.rn_x][imp.rn_y].isReveal==1){
    imp.rn_y= imp.rn_y+1;
    if (imp.rn_y==7){
      //go to the next value of x and repeat
      break;
    }
  }
  return imp.rn_y;
}

void makeFlag(zone zoneToFlag){
  zoneToFlag.isFlag= 1;
}

void letsReveal(boardValues imp, zone arr[][8]){
  openZone(imp.rn_x, imp.rn_y, arr);
}
