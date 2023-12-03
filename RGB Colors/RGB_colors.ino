// C++ code
#define red 6
#define blue 5
#define green 3
#define red_potentiometer A0
#define green_potentiometer A1
#define blue_potentiometer A2

void setup()
{
}

void loop()
{  
  int red_potentiometer_state = analogRead(red_potentiometer);
  int set_range_red = set_range(red_potentiometer_state);
  set_color(red, set_range_red);
  
  int green_potentiometer_state = analogRead(green_potentiometer);
  int set_range_green = set_range(green_potentiometer_state);
  set_color(green, set_range_green);
    
  int blue_potentiometer_state = analogRead(blue_potentiometer);
  int set_range_blue = set_range(blue_potentiometer_state);
  set_color(blue, set_range_blue);
}

int set_range(int potentiometer_state)
{
  int allowed_range =  map(potentiometer_state, 0, 1023, 0, 100);
  return allowed_range;
}

void set_color(int color, int allowed_range)
{
  analogWrite(color, allowed_range);
}