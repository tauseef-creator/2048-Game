/*Tauseef Razaq
i211236
About 2048:Randomly 2 and 4 appear at random places in a board with every right/left/up/down move
and get double if there's same number in the adjacent place
*/
#ifdef _WIN32
#include <conio.h>
#define downKey 80    // keys
#define upKey 72      //defined
#define rightKey 77   //to
#define leftKey 75    //control
#else
#include <unistd.h>
#include <termios.h>
// #include <ncurses/curses.h>          
// #define downKey 66    // keys
// #define upKey 65      //defined
// #define rightKey 67   //to
// #define leftKey 68    //control
#endif


#define escKey 27     //game
#include <iostream>
#include <time.h>     //generate random numbers + starter
using namespace std;

#ifdef __linux__
//pleathora of code just to use getch() in linux////////////////////////////////
//void set_raw_mode(int fd) {
//  // Save the current terminal attributes
//  termios term;
//  tcgetattr(fd, &term);
//
//  // Set the terminal to raw mode
//  termios raw = term;
//  raw.c_lflag &= ~(ICANON | ECHO);
//  tcsetattr(fd, TCSANOW, &raw);
//}
//
//void restore_mode(int fd, termios& term) {
//  // Restore the original terminal attributes
//  tcsetattr(fd, TCSANOW, &term);
//}
//
//char get_input(int fd) {
//  fflush(stdout);
//
//  // Read a single character from the terminal
//  char c;
//  read(fd, &c, 1);
//
//  return c;
//}
/////////////////////////////////////////////////////////////////
#endif
  //function to move integers downward
    //same logic, wit minor differneces, is used for all moves i.e., up ,down, right, left
void downAll(int downMode[][4], int &score)
{
    int row, column, changeRow=3, mltValidColumnDn[4];     //1D array is used to add only two numbers at single index in a column
      for(row=0; row<4; row++)                             //in single move
      {
          mltValidColumnDn[row]=-1;
      }
      for(row=0; row<4; row++)
      {
          for(column=0; column<4; column++)
          {
              if(downMode[row][column]!=0)          //chooses the upcoming nonzero number
              {
                  for(int downRow=changeRow; downRow>=0; downRow--) //checks last number of same column
                  {
                      int flag=1;
                          if(downMode[downRow][column]==0)          //for placing number with zero
                           {
                                 for(int allUp=downRow-1; allUp>=0 && flag; allUp--)  //flag is used
                                 {                                                    //to break loop
                                     if(downMode[allUp][column]!=0)                   //after replacing one number
                                      {
                                          downMode[downRow][column]=downMode[allUp][column];
                                          downMode[allUp][column]=0;
                                              flag=0;

                                       }
                                  }
                          }

                          else    //for multiplying if appears the same number
                          {
                               for(int allUp2=downRow-1; allUp2>=0 && flag; allUp2--)
                                 {
                                     if(downMode[allUp2][column]!=0 && downMode[allUp2][column]==downMode[downRow][column])
                                      {
                                                                                           //columns gets noted and

                                                 if(!(column==mltValidColumnDn[column] ))        //stores information
                                                  {                                           //loops not works for same column

                                                     downMode[downRow][column]*=2;            //again
                                                     score+=downMode[downRow][column];
                                                     downMode[allUp2][column]=0;
                                                     mltValidColumnDn[column]=column;

                                                     flag=0;
                                                  }

                                       }
                                       else
                                       {
                                           flag=0;    //only adds two same numbers near to each other
                                       }
                                  }
                          }
                  }
              }
          }

      }

}
  //Function to move integers upward
void upAll(int upMode[][4], int &score)
  {
      int row, column,firstRow=0, mltValidColumnUp[4];
      for(row=0; row<4; row++)
      {
          mltValidColumnUp[row]=-1;     // just to differ the value during multiplication
      }
      for(row=0; row<4; row++)
      {
          for(column=0; column<4; column++)
          {
              if(upMode[row][column]!=0)
              {
                  for(int fromUp=firstRow; fromUp<4;fromUp++)
                  {
                      int flag=1;
                      if(upMode[fromUp][column]==0)
                      {
                          for(int lower=fromUp+1; lower<4 && flag;lower++)
                          {
                              if(upMode[lower][column]!=0)
                              {
                                  upMode[fromUp][column]=upMode[lower][column];
                                  upMode[lower][column]=0;
                                   flag=0;
                              }
                          }
                      }
                      else    //for multiplying if appears the same number
                          {
                               for(int lower2=fromUp+1; lower2<4 && flag; lower2++)
                                 {
                                     if(upMode[lower2][column]!=0 && upMode[lower2][column]==upMode[fromUp][column])
                                      {
                                                                                           //columns gets noted and

                                              if(!(column==mltValidColumnUp[column]))        //stores information
                                               {                                           //loops not works for same column

                                                  upMode[fromUp][column]*=2;            //again
                                                  score+=upMode[fromUp][column];
                                                  upMode[lower2][column]=0;
                                                  mltValidColumnUp[column]=column;

                                                  flag=0;
                                               }

                                       }
                                      else if(upMode[lower2][column]!=0 && upMode[lower2][column]!=upMode[fromUp][column])
                                       {
                                          flag=0;    //only adds two same numbers near to each other
                                       }
                                  }
                          }
                  }
              }
          }
      }
  }

 //Function to move all number rightward
 void rightAll(int rightMode[][4], int &score)
 {
     int row, column, lastCol=3, mltValidrowRt[4];
        for(row=0; row<4; row++)
        {
             mltValidrowRt[row]=-1;
        }
        for(row=0; row<4; row++)
        {
            for(column=0; column<4; column++)
            {
                if(rightMode[row][column]!=0)
                {
                    for(int fromRight=lastCol; fromRight>=0; fromRight--)
                    {
                       int flag=1;

                          if(rightMode[row][fromRight]==0)          //for placing number with zero
                           {
                                 for(int left1=fromRight-1; left1>=0 && flag; left1--)
                                 {
                                     if(rightMode[row][left1]!=0)
                                      {
                                          rightMode[row][fromRight]=rightMode[row][left1];
                                          rightMode[row][left1]=0;
                                              flag=0;

                                       }
                                  }
                          }

                          else    //for multiplying if appears the same number
                          {
                               for(int left2=fromRight-1; left2>=0 && flag; left2--)
                                 {
                                     if(rightMode[row][left2]!=0 && rightMode[row][left2]==rightMode[row][fromRight])
                                      {
                                                                                           //columns gets noted and

                                                 if(!(row==mltValidrowRt[row] ))        //stores information
                                                  {                                           //loops not works for same column

                                                     rightMode[row][fromRight]*=2;            //again
                                                     score+=rightMode[row][fromRight];
                                                     rightMode[row][left2]=0;
                                                     mltValidrowRt[row]=row;

                                                     flag=0;
                                                  }
                                            //}

                                       }
                                       else
                                       {
                                           flag=0;    //only adds two same numbers near to each other
                                       }
                                  }

                       }
                }
            }
        }
 }
 }
 //function to move all number leftward

 void leftAll(int leftMode[][4], int &score)
 {

     int row, column, lastCol=0, mltValidrowlft[4];
        for(row=0; row<4; row++)
        {
             mltValidrowlft[row]=-1;
        }
        for(row=0; row<4; row++)
        {
            for(column=0; column<4; column++)
            {
                if(leftMode[row][column]!=0)
                {
                    for(int fromRight=lastCol; fromRight<4; fromRight++)
                    {
                       int flag=1;

                          if(leftMode[row][fromRight]==0)          //for placing number with zero
                           {
                                 for(int left1=fromRight+1; left1<4 && flag; left1++)
                                 {
                                     if(leftMode[row][left1]!=0)
                                      {
                                          leftMode[row][fromRight]= leftMode[row][left1];
                                          leftMode[row][left1]=0;
                                              flag=0;

                                       }
                                  }
                          }

                          else    //for multiplying if appears the same number
                          {
                               for(int left2=fromRight+1; left2<4 && flag; left2++)
                                 {
                                     if(leftMode[row][left2]!=0 && leftMode[row][left2]==leftMode[row][fromRight])
                                      {
                                                                                           //columns gets noted and

                                                 if(!(row==mltValidrowlft[row] ))        //stores information
                                                  {                                           //loops not works for same column

                                                     leftMode[row][fromRight]*=2;            //again
                                                     score+=leftMode[row][fromRight];
                                                     leftMode[row][left2]=0;
                                                     mltValidrowlft[row]=row;

                                                     flag=0;
                                                  }
                                            //}

                                       }
                                       else
                                       {
                                           flag=0;    //only adds two same numbers near to each other
                                       }
                                  }

                       }
                }
            }
        }
 }
 }
   //Function to generate 2/4 at random index in array
void storeInRandom(int randArray[][4])
{
    srand(time(NULL));         //srand is used to avoid rand to generate the same number every time we run program
    int randomIndexR=rand()%4;  //row
    int randomIndexC=rand()%4;  //col
    int twoFour;
        if(time(NULL)%2==0)     //to generate
           {                    //2 and 4
              twoFour=2;        //after
           }
         else                  //every move
            {
              twoFour=4;
            }

        if(randArray[randomIndexR][randomIndexC]==0)
        {
               randArray[randomIndexR][randomIndexC]=twoFour;
        }
        else
        {
            while(randArray[randomIndexR][randomIndexC]!=0)    //looks for empty index to store number
            {
                randomIndexR=rand()%4;
                randomIndexC=rand()%4;
            }
            randArray[randomIndexR][randomIndexC]=twoFour;
        }


}
void print2048() {
    cout << endl <<"    2222       0000          4444      8888  " << endl;
    cout << "  22    22   00    00       44 44    88    88  "<< endl;
    cout << "        22   00    00      44  44    88    88     "<< endl;
    cout << "      22     00    00     44   44      8888        "<< endl;
    cout << "    22       00    00    44    44    88    88            "<< endl;
    cout << "  22         00    00    4444444444  88    88" << endl;
    cout << "  22222222     0000            44      8888  " << endl;
    cout << endl;
}

    //print array after every  move
void PrintArray(int printIt[][4], int score)
{
    int row, column;
    print2048();
     cout << "\nPlay with arrow keys | ";
     cout << "Press ESC to exit\n";
      cout << "\nYour score:" << score;
      cout << "\n\n\n";
    for(row=0; row<4; row++)
    {
        cout << "       "<< "\t";
        for(column=0; column<4; column++)
        {
            if(printIt[row][column]==0)
            {
                cout << "." << "\t";
            }
            else
                cout << printIt[row][column] << "\t";
        }
          cout << endl;
    }

}
bool validity(int checkIt[][4])                    //this function checks when
{                                                  //all indexes all fill
    int    row, column;                            //and if there is possible move,
	for(row=0; row<4; row++)                       //by looking for any zero or
    	{
    	    for(column=0 ; column<4 ; column++)        //adjacent same number
    		{
    		    if(checkIt[row][column]==0)             //and return accordingly
    	    	{
    			return false;
			    }
    		}
    	}

	for(row=0; row<3; row++)
    {

    	for(column=0; column<3; column++)
    	{

    		if(checkIt[row+1][column]==checkIt[row][column] || checkIt[row][column+1]==checkIt[row][column])
    		{
    			return false;
			}
    	}
    }
    for(row=3; row>0; row--)
    {
        for(column=3; column>0; column--)
        {
            if(checkIt[row-1][column]==checkIt[row][column] || checkIt[row][column-1]==checkIt[row][column])
            {
                return false;
            }
        }
    }
  return true;
}
bool validForRdm(int board2048[][4], int toCheck[][4])
{
    int row, column;                                      //this function checks all numbers
       for(row=0; row<4; row++)                         //in temporary array, stored in previous move
       {                                               //and check if current particular move
           cout << "\t";                                 //is possible or not
           for(column=0; column<4; column++)
           {
               if(board2048[row][column]!=toCheck[row][column])
               {
                   return true;
               }
           }
       }
    return false;
}

int main()
{

//     termios term;
//   tcgetattr(0, &term);

//   set_raw_mode(0);

  int Two048[4][4], row, column;
  int shouldMove[4][4];
  int option, score=0;
  for(int row=0; row<4; row++)             //initializing array
  {                                        //with 0
      for(int column=0; column<4; column++)
      {
          shouldMove[row][column]=0;
          Two048[row][column]=0;
      }
  }
  print2048();
  cout << "\nPress some button to continue...";
    #ifdef _WIN32
    getch();
    system("CLS");
    #else
    system("stty raw");
     getchar();
     system("stty cooked");
    #endif
  int starter=6, timer=clock();
  cout << endl;
    cout << "\nGame starting in ";
    while(starter>0)
       {
             if(clock()>timer+1000)              //to print a number of loader after one second
             {
                timer=clock();
                if (starter==3 || starter==2 || starter==1)
                {
                       cout << ".";
                }
                else
                {
                       cout << starter-3<< " ";
                }
                 starter--;
             }
       }
       #ifdef _WIN32
      system("CLS");
      #else
      system("clear");
      #endif

   ////initial number//
    int numR, numC;
    srand(time(NULL));
    numR=rand()%4;
    numC=rand()%4;
    Two048[numR][numC]=2;
    PrintArray(Two048, score);
  ///////////////////
   int flag=1;
      while(flag)
         {
             for(row=0; row<4; row++)                         //loop saves board after each iteration
             {
                 for(column=0; column<4; column++)            //to check validity later after move
                 {
                     shouldMove[row][column]=Two048[row][column];
                 }
             }
             #ifdef _WIN32
            option = getch();
              system("CLS");
            #else
            system("stty raw");
             option = getchar();
            //  cout << "you enterd" << static_cast<char>(option);
             system("stty cooked");
            system("clear");
            #endif
                switch(option)
                {

                  case 's':{downAll(Two048, score);}break;    //ASCII of
                  case 'w':{upAll(Two048, score);}break;      //entered buttons e.g., "80" for "down arrow key"
                  case 'd':{rightAll(Two048, score);}break;   //because we're using
                  case 'a':{leftAll(Two048, score);}break;    //getch() function
                  case escKey:  {
                              cout << "\n\n****Game Terminated****\n\n";
                              return 0;
                            }break;
                }


         if(validForRdm(Two048, shouldMove))
			{
			      storeInRandom(Two048);
			}
		        PrintArray(Two048, score);

		if(validity(Two048))
		{
			cout<<"\n\n\t\t\"GAME OVER\"" << endl;
			cout << "\n\tPress any key to continue\n";
			#ifdef _WIN32
            getch();
            #else
            system("stty raw");
            getchar();
            system("stty cooked");
            #endif
			break;
		}
      }
// restore_mode(0, term);

return 0;

}
