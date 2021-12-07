// GxEPD2_HelloWorld.ino by Jean-Marc Zingg

// see GxEPD2_wiring_examples.h for wiring suggestions and examples
// if you use a different wiring, you need to adapt the constructor parameters!

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// select the display class and display driver class in the following file (new style):
#include "GxEPD2_display_selection_new_style.h"

// or select the display constructor line in one of the following files (old style):
#include "GxEPD2_display_selection.h"
#include "GxEPD2_display_selection_added.h"

// alternately you can copy the constructor from GxEPD2_display_selection.h or GxEPD2_display_selection_added.h to here
// e.g. for Wemos D1 mini:
GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)> display(GxEPD2_154_D67(/*CS=10*/ 8, /*DC=*/ 5, /*RST=*/ 6, /*BUSY=*/ 7)); // GDEH0154D67 200x200//
//GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)> display(GxEPD2_154_D67(/*CS=10*/ 10, /*DC=*/ 4, /*RST=*/ 5, /*BUSY=*/ 6)); // GDEH0154D67 200x200//
//

String select;
String reminder;

void ClearScreen()
{
  display.setFullWindow(); 
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
  }
  while (display.nextPage());
}

void Display(String s, int x, int y)
{
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.setPartialWindow(x, y,200, 20); // x,y,width,height
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x+3, y + 10);
    display.println(s);
    
  }
  while (display.nextPage());
}

void Selection() 
{
  while(Serial.available()>0)
{
   select=Serial.readString();
}
}


String I_Reminder() 
{
  while(Serial.available()>0)
{
  reminder=Serial.readString();
  return reminder;
}
}

void Call_Reminder(){
  
 Serial.println( "Which reminder do you want to add?  Enter c to clear screen");
 while(Serial.available() == 0);

  Selection();
  if ( select[0] == '1') 
  {
  delay(200);
  Serial.flush();
  
  Serial.println("Add reminder 1 ");
  while (Serial.available() == 0);
  String rem1 = I_Reminder();
  Display(rem1,1,1);
  Serial.flush();
  }
  
  else if (select[0] == '2')
  {
  delay(200);
  Serial.flush();
  
  Serial.println("Add reminder 2");
  while (Serial.available() == 0);
  String rem2 = I_Reminder();
  Display(rem2, 0,30);
  Serial.flush();
  }
  
 else if (select[0] == '3')
  {
  delay(200);
  Serial.flush();
  
  Serial.println("Add reminder 3");
  while (Serial.available() == 0);
  String rem2 = I_Reminder();
  Display(rem2, 0,50);
  Serial.flush();
  }

  else if (select[0] == '4')
  {
  delay(200);
  Serial.flush();
  
  Serial.println("Add reminder 4");
  while (Serial.available() == 0);
  String rem2 = I_Reminder();
  Display(rem2, 0,70);
  Serial.flush();
  }

  else if (select[0] == '5')
  {
  delay(200);
  Serial.flush();
  
  Serial.println("Add reminder 5");
  while (Serial.available() == 0);
  String rem2 = I_Reminder();
  Display(rem2, 0,90);
  Serial.flush();
  }

  else if (select[0] == 'c')
  ClearScreen();
  

  else
  Serial.println("Please input reminder number");
}


  
void setup()
{
  Serial.begin(9600);
  display.init();
  Serial.println("Do you want to add reminders: y or n?");
  
 
}









void loop()
{
 delay(500);


delay(1000);
 
Serial.println("Do you want to add reminders: y or n?");
while(Serial.available() == 0);
Selection();

if( select[0] == 'y') 
{
Serial.flush();
Call_Reminder();
}

else if (select[0] == 'n')
{
 delay(500);
Serial.print("END");
delay(500);
exit(0);
}

else
Serial.println("Please enter y or n");

}

  
