// C++ code
#define red 3
#define green 4
#define blue 5
#define temperature_sensor A0
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int sensor_state;
  int temperature; 
  sensor_state = analogRead(temperature_sensor);
  temperature = map(sensor_state, 20, 358, -40, 125);
  
  if (temperature < 0)
  {
    turnOnLED(LOW, HIGH, LOW);
  }
  else if (temperature > -1 && temperature < 31)
  {
    turnOnLED(LOW, LOW, HIGH);
  }
  else
  {
    turnOnLED(HIGH, LOW, LOW);
  }
  
  Serial.println(temperature);
}

void turnOnLED(int red_state, int blue_state, int green_state)
{
  digitalWrite(red, red_state);
  digitalWrite(green, green_state);
  digitalWrite(blue, blue_state);
}