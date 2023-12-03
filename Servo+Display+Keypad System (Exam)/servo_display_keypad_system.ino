// El preset de la izquierda pone la posición mínima
// El preset de la derecha pone la posición Máxima
// Si la posicion Maxima es menor a la mínima, entonces adopta el valor de la mínima
// La tecla A, Min y Max pasan a PMin y PMax
// La tecla B, lleva el Servo a PosMin;
// La tecla C, lleva el Servo a PosMax;
// La tecla D, pone a 0º PosMin;
// La tecla *, pone a 180º PosMax;
// La tecla 1 imprime por el Serial Min;
// La tecla 2 imprime por el Serial Max;
// La tecla 3 imprime por el Serial PosMin;
// La tecla 4 imprime por el Serial PosMax;
// La tecla 5 pone el servo a 90º (sin importar el cursor)
// La tecla # imprime la posición Actual;
// Las teclas no indicadas, no cumplen función alguna.

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define min_potentiometer A1
#define max_potentiometer A0

//SETTING UP SERVO AND LCD
Servo my_servo;
LiquidCrystal my_lcd(12, 2, A2, A3, A4, A5);

//SETTING UP KEYPAD
const byte ROWS = 4; 
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte row_pins[ROWS] = {10,9,8, 7};
byte column_pins[COLS] = {6,5, 4, 3};

Keypad keypad = Keypad(makeKeymap(keys), row_pins, column_pins, ROWS, COLS);

//GLOBAL VARIABLES
char pressed_key;
int min_potentiometer_level;
int max_potentiometer_level;
int min_potentiometer_mapped;
int max_potentiometer_mapped;
int min_position = 0;
int max_position = 180;
int servo_position;
unsigned long previous_millis = 0;

//SETUP
void setup()
{
  	my_lcd.begin(16,2);
    my_servo.attach(11,500,2500);
  	Serial.begin(9600);
}

//MAIN LOOP
void loop()
{
    //ANALOG-READING POTENTIOMETERS
  	min_potentiometer_level = analogRead(min_potentiometer);
    max_potentiometer_level = analogRead(max_potentiometer);
  
  	//MAPPING POTENTIOMETERS (0-180)
    min_potentiometer_mapped = map(min_potentiometer_level, 0, 1023, 0, 180);
    max_potentiometer_mapped = map(max_potentiometer_level, 0, 1023, 0, 180);
  	
  	//COMPARING POTENTIOMETERS
    if (max_potentiometer_mapped < min_potentiometer_mapped 
     || min_potentiometer_mapped > max_potentiometer_mapped)
    {
      max_potentiometer_mapped = min_potentiometer_mapped;
    }
	
  	//KEYPAD
  	pressed_key = keypad.getKey();
    perform_action_according_to_pressed_key(pressed_key);
  
  	//DISPLAY
  	display_info();
}

void perform_action_according_to_pressed_key(char pressed_key)
{
  	//SETTING UP SWITCH ACCORDING TO PRESSED KEY
  	switch (pressed_key)
    {
      case 'A':
        min_position = min_potentiometer_mapped;
	  	max_position = max_potentiometer_mapped;
      	break;
      case 'B':
        my_servo.write(min_position);
      	break;
      case 'C':
        my_servo.write(max_position);
      	break;
      case 'D':
        min_position = 0;
      	break;
      case '*':
        max_position = 180;
      	break;
      case '1':
        Serial.println("Min: " + String(min_potentiometer_mapped));
      	break;
      case '2':
        Serial.println("Max: " + String(max_potentiometer_mapped));
      	break;
      case '3':
        Serial.println("PosMin: " + String(min_position));
      	break;
      case '4':
        Serial.println("PosMax: " + String(max_position));
      	break;
      case '5':
        my_servo.write(90);
      	break;
      case '#':
        servo_position = my_servo.read();
        Serial.println("Current position: " + String(servo_position));
      	break;
    }
}

void display_info()
{
  	unsigned long actual_millis = millis();
  
  	//FIRST ROW Mn
  	my_lcd.setCursor(0, 0);
  	if (min_potentiometer_mapped > 99)
    {
      my_lcd.print("Mn: ");
    }
  	else if (min_potentiometer_mapped > 9)
    {
      my_lcd.print("Mn:  ");
    }
 	else
    {
      my_lcd.print("Mn:   ");
    }
  	my_lcd.print(min_potentiometer_mapped);
	
  	//FIRST ROW PMn
  	if (min_position > 99)
    {
      my_lcd.print(" PMn: ");
    }
  	else if (min_position > 9)
    {
      my_lcd.print(" PMn:  ");
    }
 	else
    {
      my_lcd.print(" PMn:   ");
    }
    my_lcd.print(min_position);
	
  	//SECOND ROW Mx
	my_lcd.setCursor(0, 1);  
  	if (max_potentiometer_mapped > 99)
    {
      my_lcd.print("Mx: ");
    }
  	else if (max_potentiometer_mapped > 9)
    {
      my_lcd.print("Mx:  ");
    }
 	else
    {
      my_lcd.print("Mx:   ");
    }
    my_lcd.print(max_potentiometer_mapped);
  	
  	//SECOND ROW PMx
  	if (max_position > 99)
    {
      my_lcd.print(" PMx: ");
    }
  	else if (max_position > 9)
    {
      my_lcd.print(" PMx:  ");
    }
 	else
    {
      my_lcd.print(" PMx:   ");
    }
    my_lcd.print(max_position);
	
  	//SHOW INFO AND CLEAR LCD
  	if(actual_millis - previous_millis >= 100)
  	{	
      previous_millis = millis();
      my_lcd.clear();
  	}
}