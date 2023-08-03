
#ifndef KEYPASS_DRLOCK_H
#define KEYPASS_DRLOCK_H

//Make sure to get the right libraries  !
/***************** Include the library used in th code****************/
#include <Keypad.h> // Library for the Keypad
#include <EEPROM.h> // Library for the EEPROM
#include <LiquidCrystal_I2C.h> // library for LCD_I2c Module
#include <Wire.h>
/********************************************************************/

/********************** Define the pins ****************************/

#define Btn_L  A1
#define Btn_D  A0

#define lamp  A2
#define door  A3

#define buzzer  12
#define rdled  11
#define gnled  10

/*******************************************************************/

/**************************** Declare used Variables *******************************/

bool lampval /* ,settime*/;

const byte ROWS = 4;         //number of rows on the keypad
const byte COLS = 4;         //number of columns on the keypad

//define the cymbols on the buttons of the keypads
char keymap[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char keypressed;                 //Where the keys are stored it changes very often
char code[4] = {'1', '9', '7', '3'}; //The default code.

char code_buff1[sizeof(code)];  //Where the new key is stored
char code_buff2[sizeof(code)];  //Where the new key is stored again so it's compared to the previous one

unsigned int a = 0, i = 0, s = 0, j = 0, e = 5, d = 15, x = 0, y = 0;
//    j: refaire to the index of column in LCD_I2C
//    a: to store variables of function GetCode
//    e: attempt rev-counnter
//    d: timer

//                  R1, R2, R3, R4
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
//                  C1, C2, C3, C4
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

/************************************************************************************/

//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2); // To know ur I2c address Device just use code example "I2c_scanner" of the library 'Wire' :)

/*********** Used Functions *****************/

void GetCode();
void ChangeCode();
void GetNewCode1();
void GetNewCode2();
void OpenDoor();
void bip();
void access();
void denied();
void Timer();
void attempt();

/********************************************/


/********************************** Features ****************************************/

//byte StandBy[] = {B00111, B01110, B11100, B11000, B11000, B11100, B01110, B00111};
//
//byte O_Lock[] = {B01110, B10001, B10001, B00001, B11111, B11011, B11011, B11111};
//
//byte C_Lock[] = {B01110, B10001, B10001, B10001, B11111, B11011, B11011, B11111};

/************************************************************************************/

#endif
