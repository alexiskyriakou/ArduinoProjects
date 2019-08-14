#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544( 5, 4, 3);

#define MAX5387_addr  0x50   //address of MAX5387
#define Wiper_01      0x11   //Wiper 01 Command Byte
#define Wiper_02      0x12   //Wiper 02 Command Byte
#define Wiper_01_02   0X13   //Wiper 01 & 02 Command Byte

//boolean backlight = true;
int Volume = 50;
int Balance = 0;

int menupos = 1;
int page = 1; // Volume page = 1, Balance page 2

volatile int up = 0;
volatile int down = 0;
volatile int  select = 0;

//--- INPUTS
const int OnOff = 7; //
const int UpBtn = 6;
const int DownBtn = 5;
const int MuteBtn = 3;
const int SelectBtn = 4;

//--- OUTPUTS
const int Relay = 17;
const int SDZ = 10;
const int Faultz = 9;
const int Mute = 8;

int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int muteButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;
int lastMuteButtonState = 0;


void setup() {
  Serial.begin(9600);
  //  pinMode(2, INPUT_PULLUP);
  //  pinMode(1, INPUT_PULLUP);
  //  pinMode(0, INPUT_PULLUP);
  //  pinMode(7,OUTPUT);

  //input setup
  pinMode(OnOff, INPUT);// maybe will be output
  pinMode(UpBtn, INPUT);
  pinMode(DownBtn, INPUT);
  pinMode(MuteBtn, INPUT);
  pinMode(SelectBtn, INPUT);

  //output declare
  pinMode(Mute, OUTPUT);

  //display declare
  display.begin();
  display.setContrast(50); //Set contrast to 50
  display.clearDisplay();
  display.display();

}

void loop() {

  Serial.print("Volume: ");
  Serial.print(Volume);
  Serial.print("   Balance: ");
  Serial.println(Balance);
  Serial.print("MenuPos: ");
  Serial.print(menupos);
  Serial.print("Page: ");
  Serial.println(page);

  drawMenu();

  downButtonState = digitalRead(DownBtn);
  selectButtonState = digitalRead(SelectBtn);
  upButtonState =   digitalRead(UpBtn);
  muteButtonState = digitalRead(MuteBtn);

  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();
  checkIfMuteButtonIsPressed();

  if (up && page == 1 ) {
    up = 0;
    menupos--;
    if (menupos == 0)
    {
      menupos = 2;
    }
  } else if (up && page == 2 ) {
    up = 0;
    Volume--;
  } else if ( up && page == 3) {
    up = 0;
    Balance--;
  }


  if (down && page == 1) {
    down = 0;
    menupos++;
    if (menupos == 3)
    {
      menupos = 1;
    }
  } else if (down && page == 2 ) {
    down = 0;
    Volume++;
  } else if ( up && page == 3) {
    up = 0;
    Balance--;
  }


  if (select) {
    select = 0;

    if (page == 1 && menupos == 1)
    {
      page = 2;

    } else if (page == 1 && menupos == 2) {
      page = 3;
    }
    else if (page == 2 || page == 3) {
      page = 1;
    }
  }

}

void checkIfDownButtonIsPressed()
{
  if (downButtonState != lastDownButtonState)
  {
    if (downButtonState == 0)
    {
      down = true;
    }
    delay(50);
  }
  lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState)
  {
    if (upButtonState == 0) {
      up = true;
    }
    delay(50);
  }
  lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
  if (selectButtonState != lastSelectButtonState)
  {
    if (selectButtonState == 0) {
      select = true;
    }
    delay(50);
  }
  lastSelectButtonState = selectButtonState;
}

void checkIfMuteButtonIsPressed()
{
  if (muteButtonState != lastMuteButtonState)
  {
    if (muteButtonState == 0) {
      //add code to send mute function to the digital pot
    }
    delay(50);
  }
  lastMuteButtonState = muteButtonState;
}


void drawMenu()
{

  if (page == 1)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);

    if (menupos == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Contrast");
    display.setCursor(0, 25);

    if (menupos == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Light: ");

    if (menupos == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 35);
    display.print(">Reset");
    display.display();
  }


  else if (page == 2)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("CONTRAST");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.setTextSize(2);
    display.display();
  }

}
