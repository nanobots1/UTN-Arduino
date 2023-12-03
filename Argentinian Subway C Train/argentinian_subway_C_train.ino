// C++ code
//
#define LED_CONSTITUCION 5
#define LED_SAN_JUAN 6
#define LED_INDEPENDENCIA 7
#define LED_MORENO 8
#define LED_G 10
#define LED_F 2
#define LED_A 3
#define LED_B 4
#define LED_E A5
#define LED_D A4
#define LED_C A3
#define RING A2
#define BUTTON 9
int counter = 0;

void setup()
{
  pinMode(LED_CONSTITUCION, OUTPUT);
  pinMode(LED_SAN_JUAN, OUTPUT);
  pinMode(LED_INDEPENDENCIA, OUTPUT);
  pinMode(LED_MORENO, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(RING, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RING, OUTPUT);
  Serial.begin(9600);
}

void show_digit(int digit_to_show)
{ 
  switch (digit_to_show)
  {
	case 0:
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_C, HIGH);
    digitalWrite(LED_D, HIGH);
    digitalWrite(LED_E, HIGH);
    digitalWrite(LED_F, HIGH);
    digitalWrite(LED_G, LOW);
    break;
    case 1:
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_C, HIGH);
    digitalWrite(LED_D, LOW);
    digitalWrite(LED_E, LOW);
    digitalWrite(LED_F, LOW);
    digitalWrite(LED_G, LOW);
    break;
    case 2:
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_C, LOW);
    digitalWrite(LED_D, HIGH);
    digitalWrite(LED_E, HIGH);
    digitalWrite(LED_F, LOW);
    digitalWrite(LED_G, HIGH);
    break;
    case 3:
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_C, HIGH);
    digitalWrite(LED_D, HIGH);
    digitalWrite(LED_E, LOW);
    digitalWrite(LED_F, LOW);
    digitalWrite(LED_G, HIGH);
    break;
    case -50:
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, LOW);
    digitalWrite(LED_D, LOW);
    digitalWrite(LED_E, LOW);
    digitalWrite(LED_F, LOW);
    digitalWrite(LED_G, LOW);
    break;
  }
  return;
}

void loop()
{
  int button_state = digitalRead(BUTTON);
  
  if (button_state == 1)
  {
    Serial.println("Counter de entrada:");
    Serial.println(counter);
    switch (counter)
  	{
      case 0:
      show_digit(3);
      digitalWrite(LED_MORENO, LOW);
      digitalWrite(LED_CONSTITUCION, HIGH);
      tone(RING, 392);
      delay(1000);
      counter++;
      Serial.println("Counter case 0:");
      Serial.println(counter);
      break;
      case 1:
      show_digit(2);
      digitalWrite(LED_CONSTITUCION, LOW);
      digitalWrite(LED_SAN_JUAN, HIGH);
      tone(RING, 329.63);
      delay(1000);
      counter++;
      Serial.println("Counter case 1:");
      Serial.println(counter);
      break;
      case 2:
      show_digit(1);
      digitalWrite(LED_SAN_JUAN, LOW);
      digitalWrite(LED_INDEPENDENCIA, HIGH);
      tone(RING, 277.18);
      delay(1000);
      counter++;
      Serial.println("Counter case 2:");
      Serial.println(counter);
      break;
      case 3:
      show_digit(0);
      digitalWrite(LED_INDEPENDENCIA, LOW);
      digitalWrite(LED_MORENO, HIGH);
      tone(RING, 233.08);
      delay(1000);
      counter++;
      Serial.println("Counter case 3:");
      Serial.println(counter);
      break;
      default:
      counter = 0;
      Serial.println("Counter case >3:");
      Serial.println(counter);
      break;
  	}
  }
  else
  {
    noTone(RING);
    digitalWrite(LED_MORENO, LOW);
    digitalWrite(LED_CONSTITUCION, LOW);
    digitalWrite(LED_SAN_JUAN, LOW);
    digitalWrite(LED_INDEPENDENCIA, LOW);
    show_digit(-50);
    counter = 0;
  }
}