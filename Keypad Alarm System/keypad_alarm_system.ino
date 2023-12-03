#include <Keypad.h>
#include <LiquidCrystal.h>
#define GREEN_LED 12
#define RED_LED 13
#define RING 2

LiquidCrystal myLcd(A0, A1, A2, A3, A4, A5);

const byte ROWS = 4; 
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rows[ROWS] = {10,9,8,7};
byte columns[COLS] = {6,5,4,3};

Keypad keypad = Keypad(makeKeymap(keys), rows, columns, ROWS, COLS);

char pressed_key;
char correct_password[] = "5B2A";
int counter = 0;
  
String entered_password = "";

void setup()
{
  myLcd.begin(16, 2);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RING, OUTPUT);
}

void loop()
{
  pressed_key = keypad.getKey();
  
  if (pressed_key != NO_KEY)
  {
    counter ++;
    myLcd.print(pressed_key);
    entered_password += pressed_key;
  }
  
  if (counter == 4)
  {
    validate_password();
  }
}

void validate_password()
{
  if (entered_password.equals(correct_password))
  {
    digitalWrite(GREEN_LED, HIGH);
    tone(RING, 360);
    delay(100);
    noTone(RING);
    delay(5000);
    digitalWrite(GREEN_LED, LOW);
  }
  else
  {
    digitalWrite(RED_LED, HIGH);
    tone(RING, 233);
    delay(5000);
    noTone(RING);
    digitalWrite(RED_LED, LOW);
  }
  
  counter = 0;
  entered_password = "";
  myLcd.clear();
}