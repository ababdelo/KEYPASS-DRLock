
#include "KEYPASS_DRLOCK.h"

/***************************************************Void Setup Function**************************************************/
void setup()  // the setup function runs once when you press reset or power the board
{
  // initialize digital pin.
  pinMode(Btn_L, INPUT_PULLUP);
  pinMode(Btn_D, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(door, OUTPUT);

  pinMode(rdled, OUTPUT);
  pinMode(gnled, OUTPUT);

  lcd.init();// initialize lcd.
  lcd.begin (16, 2);
  lcd.backlight();
  lcd.print("    Stand_By    ");      //What's written on the LCD you can change

  digitalWrite(lamp, HIGH);
  lampval = 1;

  /**************************************************************************************************************/
  // (It's done only once  ! ! ! )

  //  for (i = 0 ; i < sizeof(code); i++) //When you upload the code the first time keep it commented
  //  {
  //    EEPROM.get(i, code[i]);             //Upload the code and change it to store it in the EEPROM
  //  }                                  //Then uncomment this for loop and reupload the code

  /**************************************************************************************************************/

}
/**************************************************************************************************************/


/**************************************************Void Loop Function*********************************************/
void loop()  // the loop function runs over and over again forever
{
  if (e == 0) // first thing to do is to check if there's no more attempt ,so it may block the system for a while
  {
    Timer(); // call timer function
  }
  else // else , if the user still have attempts enter the scope
  {
    d = 15; // re - initialize the value of the timer counter to 15 sc
    keypressed = myKeypad.getKey();               //Constantly waiting for a key to be pressed
    if (keypressed == '*')
    {
      // * to start entering the code
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Enter Code   ");            //Message to show
      GetCode();           //Getting code function
      if (a == sizeof(code))        //The GetCode function assign a value to a (it's correct when it has the size of the code array)
        OpenDoor();                   //Open lock function if code is correct
      else {
        lcd.clear();
        lcd.print("      Wrong     ");          //Message to print when the code is wrong
        denied();
        attempt();
      }
      delay(1000);
      lcd.clear();
      lcd.print("    Stand_By    ");             //Return to standby mode it's the message do display when waiting
    }
  }
  if (keypressed == 'C') {                //To change the code it calls the changecode function
    ChangeCode();
    lcd.clear();
    lcd.print("    Stand_By    ");                 //When done it returns to main mode
  }

  /********************************************************/
  if (digitalRead(Btn_L) == LOW) // check if the lamp button inside the room is clicked
  {
    while (digitalRead(Btn_L) == LOW) { // the while just to make sure the button don't get clicked more than one time so the system won't go crazy
      delay(50);
    }
    lampval = ! lampval; // value of lampval will be it's opposite to know what was the value of the lamp before , if it was turned ON, the system will next turn it OFF
    digitalWrite(lamp, lampval);
  }
  /********************************************************/

  /********************************************************/
  if (digitalRead(Btn_D) == LOW) { // check if the door button inside the rrom is clicked to let the user go out from the room without entering password
    OpenDoor();
  }
  /********************************************************/
}
/**************************************************************************************************************/
