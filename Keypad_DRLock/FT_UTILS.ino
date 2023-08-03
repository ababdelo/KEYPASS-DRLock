
/**********************************************Get Code Function*************************************************/
void GetCode()
{
  //Getting code sequence
  i = 0;
  a = 0;
  j = 6;                    // You can change it value of j
  y = i;
  x = 4;
  while (keypressed != '#')
  {
    //The user press # to confirm the code otherwise he can keep typing
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY && keypressed != '#' ) {     //If the char typed isn't C and neither "nothing"
      bip();
      if (y < x)  // We do not want to print more than the size of the code[]
      {
        lcd.setCursor(j, 1);                            //This to write "*" on the LCD whenever a key is pressed
        lcd.print("*");                               //it's position is controlled by j
        j++;
        x--;
      }
      if (keypressed == code[i] && i < sizeof(code)) {  //if the char typed is correct a and i increments to verify the next caracter
        a++;                                //Now I think maybe I should have use only a or i ... too lazy to test it -_-'
        i++;
      }
      else
        a--;                            //if the character typed is wrong a decrements and cannot equal the size of code []
    }
  }
  keypressed = NO_KEY;
}
/**************************************************************************************************************/

/****************************************Change Code Function*************************************************/
void ChangeCode()
{
  //Change code sequence
  lcd.clear();
  lcd.print("  Changing Code ");
  delay(1000);
  lcd.clear();
  lcd.print(" Enter Old Code ");
  GetCode();                      //verify the old code first so you can change it
  if (a == sizeof(code))
  {
    //again verifying the a value
    lcd.clear();
    lcd.print("  Changing Code ");
    GetNewCode1();            //Get the new code
    GetNewCode2();            //Get the new code again to confirm it
    s = 0;
    for (i = 0 ; i < sizeof(code) ; i++)
    {
      //Compare codes in array 1 and array 2 from two previous functions
      if (code_buff1[i] == code_buff2[i])
        s++;                                //again this how we verifiy, increment s whenever codes are matching
    }
    if (s == sizeof(code))
    {
      //Correct is always the size of the array
      for (i = 0 ; i < sizeof(code) ; i++)
      {
        code[i] = code_buff2[i];       //the code array now receives the new code
        EEPROM.put(i, code[i]);        //And stores it in the EEPROM
      }
      lcd.clear();
      lcd.print("  Code Changed  ");
      delay(2000);
      e = 3;
    }
    else
    {
      //In case the new codes aren't matching
      lcd.clear();
      lcd.print("  Codes Are Not ");
      lcd.setCursor(0, 1);
      lcd.print("   Matching !!  ");
      denied();
      delay(2000);
    }
  }
  else
  { //In case the old code is wrong you can't change it
    lcd.clear();
    lcd.print("      Wrong     ");
    attempt();
    denied();
    delay(2000);
  }
}
/**************************************************************************************************************/

/****************************************Get New Code 1  Function**********************************************/
void GetNewCode1()
{
  i = 0;
  j = 6;
  x = 4;
  lcd.clear();
  lcd.print(" Enter New Code ");   //tell the user to enter the new code and press C
  lcd.setCursor(0, 1);
  lcd.print("   And Press C  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("   And Press C  ");     //Press C keep showing while the top row print ***
  while (keypressed != 'C') {          //C to confirm and quits the loop
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY && keypressed != 'C' ) {
      bip();
      if (y < x)  // We do not want to print more than the size of the code[]
      {
        lcd.setCursor(j, 0);                            //This to write "*" on the LCD whenever a key is pressed it's position is controlled by j
        lcd.print("*");
        x--;
      }          //On the new code you can show * as I did or change it to keypressed to show the keys
      code_buff1[i] = keypressed;   //Store caracters in the array
      i++;
      j++;
    }
  }
  keypressed = NO_KEY;
}
/**************************************************************************************************************/

/****************************************Get New Code 2  Function**********************************************/
void GetNewCode2()
{
  //This is exactly like the GetNewCode1 function but this time the code is stored in another array
  i = 0;
  j = 6;
  x = 4;

  lcd.clear();
  lcd.print("  Confirm Code  ");
  lcd.setCursor(0, 1);
  lcd.print("   And Press C  ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("   And Press C  ");
  while (keypressed != 'C')
  {
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY && keypressed != 'C' )
    {
      bip();
      if (y < x)  // We do not want to print more than the size of the code[]
      {
        lcd.setCursor(j, 0);                            //This to write "*" on the LCD whenever a key is pressed it's position is controlled by j
        lcd.print("*");
        x--;
      }
      code_buff2[i] = keypressed;
      i++;
      j++;
    }
  }
  keypressed = NO_KEY;
}
/**************************************************************************************************************/

/**************************Open Door Function******************************/
void OpenDoor()
{
  //Lock opening function open for 3s
  lcd.clear();
  lcd.print("     Welcome    ");       //With a message printed
  e = 5;
  digitalWrite(door, HIGH);
  access();
  delay(2600) ;
  digitalWrite(door, 0);
  lcd.clear();
  lcd.print("    Stand_By    ");
}
/**************************************************************************/

/***************Bip******************/
void bip()
{
  digitalWrite(buzzer, HIGH);
  delay(50) ;
  digitalWrite(buzzer, LOW);
}
/*************************************/

/***************access****************/
void access()
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(gnled, HIGH);
  delay(100) ;
  digitalWrite(buzzer, LOW);
  digitalWrite(gnled, LOW);
  delay(100) ;
  digitalWrite(buzzer, HIGH);
  digitalWrite(gnled, HIGH);
  delay(200) ;
  digitalWrite(buzzer, LOW);
  digitalWrite(gnled, LOW);
}
/*************************************/

/**************denied****************/
void denied()
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(rdled, HIGH);
  delay(700) ;
  digitalWrite(buzzer, LOW);
  digitalWrite(rdled, LOW);
}
/*************************************/

/*********************************************Timer**************************************************/
void Timer()
{
  for (int o = 0; o < 15; o++)
  {
    d--;
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Try again in ");
    lcd.setCursor(13, 0);
    lcd.print(d / 10);
    lcd.setCursor(14, 0);
    lcd.print(d % 10);
  }
  if (d == 0)
  {
    lcd.clear();
    lcd.print("    Stand_By    ");             //Return to standby mode it's the message do display when waiting
    e = 5;
  }
}
/**************************************************************************************************************/

/***********************************************Attempt*******************************************************/
void attempt()
{
  e--;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("attempt left");         //Message to print when the code is wrong to show the attempt left
  lcd.setCursor(1, 0);
  lcd.print(e);
}
/**************************************************************************************************************/
