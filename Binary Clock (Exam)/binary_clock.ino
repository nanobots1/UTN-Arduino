// Se trata de un reloj Binario.
// el reloj muestra la hora en numeros binarios
// el tiempo debe calcularse usando millis()
// el pulsador conectado a A0 aumenta la hora en 1 minuto
// el pulsador conectado a A1 disminuye la hora en 1 minuto
// cada vez que se cambia la hora con un pulsador, 
// debe mostrarse la hora nueva en el Monitor en Serie.
#define HOUR_DOZENS A5
#define HOUR_UNITS A4
#define MINUTES_DOZENS A3
#define MINUTES_UNITS A2
#define FIRST_LINE 4
#define SECOND_LINE 5
#define THIRD_LINE 6
#define FOURTH_LINE 7
#define INCREASE_MINUTES_BUTTON A0
#define DECREASE_MINUTES_BUTTON A1

//Variables de tiempo
unsigned long previous_millis = 0;
const long interval = 60000;
//Inicializo los contadores
int minutes_dozen_counter = 0;
int minutes_unit_counter = 0;
int hours_dozen_counter = 0;
int hours_unit_counter = 0;
//Variables de debouncing
static unsigned long debounce_time = 0;
const unsigned long debounce_delay = 200;

void setup() 
{
  	//Seteo las filas
    pinMode(FIRST_LINE, OUTPUT);
  	pinMode(SECOND_LINE, OUTPUT);
  	pinMode(THIRD_LINE, OUTPUT);
  	pinMode(FOURTH_LINE, OUTPUT);
    //Seteo las columnas
    pinMode(MINUTES_UNITS, OUTPUT);
    pinMode(MINUTES_DOZENS, OUTPUT);
    pinMode(HOUR_UNITS, OUTPUT);
    pinMode(HOUR_DOZENS, OUTPUT);
    //Seteo los pulsadores
    pinMode(INCREASE_MINUTES_BUTTON, INPUT_PULLUP);
    pinMode(DECREASE_MINUTES_BUTTON, INPUT_PULLUP);
    //Inicializo el Serial
    Serial.begin(9600);
}

void loop() 
{	
  //Leo el estado de los botones
  int increase_button_state = digitalRead(INCREASE_MINUTES_BUTTON);
  int decrease_button_state = digitalRead(DECREASE_MINUTES_BUTTON);
  //Guardo el tiempo actual
  unsigned long actual_millis = millis();
  
  //Compruebo si paso un minuto
  if(actual_millis - previous_millis >= interval)
  {
    //Establezco los contadores en modo 1 (Reloj-Incremento)
    establish_counters(1);	
    //Guardo los milis justo antes de salir del condicional
    previous_millis = millis();
  }
  
  //Comprobar si se presiono algun boton y si se cumplio el tiempo establecido de delay
  if (increase_button_state == LOW && (millis() - debounce_time) > debounce_delay) 
  {
    //Establezco los contadores en modo 2 (Boton-Incremento)
    establish_counters(2);
    //Se guarda el tiempo actual antes de salir del IF
    debounce_time = millis();
    
    //DEBOUNCING:
    //Hay X tiempo antes de salir, luego se ejecuta el loop y vuelve a comprobar la condicion del IF
    //Si el tiempo actual, menos el de debounce_time es mayor a 100 ms (debounce_delay),
    //entonces vuelve a entrar al IF y permite modificar los contadores nuevamente. Si no lo supera, todavia es
    //Muy temprano para poder volver a entrar al IF y puede interpretarse como que apretamos el boton muchas veces
  }
  if (decrease_button_state == LOW && (millis() - debounce_time) > debounce_delay) 
  {
    //Establezco los contadores en modo 3 (Boton-Decremento)
    establish_counters(3);
    //Se guarda el tiempo actual antes de salir del IF
    debounce_time = millis();
  }
  
  //Prender los leds que correspondan segun los contadores
  switch_leds_on_and_off();
}

void establish_counters(int mode)
{
  if (mode == 1 || mode == 2) //Modo 1: Incrementar por reloj | Modo 2: Incrementar por boton
  {
      minutes_unit_counter++; //Aumento el contador de unid min
      if (minutes_unit_counter == 10) //Si al aumentar el cont de unid min, este es 10
      {
        minutes_unit_counter = 0; //Entonces lo reseteamos a 0
        minutes_dozen_counter++; //Corresponde aumentar la decena de min
        if (minutes_dozen_counter == 6) //Si al aumentar la decena de min, esta es 6
        {
          minutes_dozen_counter = 0;//Entonces lo reseteamos a 0
          hours_unit_counter++; //Corresponde aumentar la unidad de hora
          if (hours_dozen_counter < 2 && hours_unit_counter == 10) //Si al aumentar la unidad de hora, esta es 10
          {
            hours_unit_counter = 0; //Entonces lo reseteamos a 0
            hours_dozen_counter++; //Corresponde aumentar la docena de hora
          }
          if (hours_dozen_counter == 2 && hours_unit_counter == 4) // Si se llega a las 24hs
          { //Reseteamos todo a 0.
      		minutes_unit_counter = 0;
      		minutes_dozen_counter = 0;
      		hours_dozen_counter = 0;
      		hours_unit_counter = 0;
          }
        }
      }
    }
   if (mode == 3) //Modo 3: Decrementar por boton
   {
      minutes_unit_counter--; //Decremento la unidad de minutos
      if (minutes_unit_counter == -1) //Si al decrementar la unid minutos llega a -1
      {
        minutes_unit_counter = 9; //Entonces lo reseteamos a 9
        minutes_dozen_counter--; //Corresponde decrementar la docena de minutos
        if (minutes_dozen_counter == -1) //Si al decrementar la doc minut esta es -1
        {
          minutes_dozen_counter = 5; //Entonces la reseteamos a 5
          hours_unit_counter--; //Corresponde decrementar la unidad de hora
          if (hours_unit_counter == -1) // Si al decrementar la unid hora esta es -1
          {
            hours_unit_counter = 9; //Entonces la reseteamos a 9
            hours_dozen_counter--; //Corresponde decrementar la docena de hora
          	if (hours_dozen_counter == -1) //Si al decrementar la docena de hora esta es -1
          	{   // Reseteamos todo a las 23.59 hs
      			minutes_unit_counter = 9;
      			minutes_dozen_counter = 5;
      			hours_dozen_counter = 2;
      			hours_unit_counter = 3;
          	}
          }
         }
       }
    }
  //Imprimir la hora correspondiente SOLO al utilizar los pulsadores
  if (mode == 2 || mode == 3)
  {
    Serial.println(String(hours_dozen_counter) + String(hours_unit_counter) +  ":" + String(minutes_dozen_counter) + String(minutes_unit_counter));
  }
  return;
}

void switch_leds_on_and_off()
{
  //Deshabilito todas las columnas
  digitalWrite(MINUTES_DOZENS, HIGH);
  digitalWrite(HOUR_UNITS, HIGH);
  digitalWrite(HOUR_DOZENS, HIGH);
  digitalWrite(MINUTES_UNITS, HIGH);

  //Defino los pines de fila y columna correspondientes a cada dígito. Uso una MATRIZ
  int row_and_columns_matrix[4][2] = {
    {MINUTES_UNITS, minutes_unit_counter},
    {MINUTES_DOZENS, minutes_dozen_counter},
    {HOUR_UNITS, hours_unit_counter},
    {HOUR_DOZENS, hours_dozen_counter}
  };

  //Variables de tiempo para controlar la duración de cada columna
  unsigned long column_time = 0;
  const unsigned long column_duration = 1;

  //Itero sobre cada fila de la matriz
  for (int matrix_row = 0; matrix_row < 4; matrix_row++) 
  {
    int selected_column = row_and_columns_matrix[matrix_row][0]; //Elijo la columna de LEDS
    int selected_counter = row_and_columns_matrix[matrix_row][1]; //Elijo el contador correspondiente

    //Habilito la fila deseada segun el contador, llamando a la funcion 'show_digit'
    show_digit(selected_counter);

    //Habilito la columna deseada
    digitalWrite(selected_column, LOW);

    //Guardo el tiempo actual
    column_time = millis();

    //Espero hasta que haya transcurrido la duración deseada
    while (millis() - column_time < column_duration) 
    {
    //La idea es darle un tiempo prudente al LED para que prenda de manera notoria en la simulacion
    //Solo se saldara del bucle while, cuando el tiempo actual menos el tiempo guardado en la variable
    //'column time', sea mayor o igual a 1 ms (guardado en column duration)
    }
    
    //Deshabilito la columna que prendi
    digitalWrite(selected_column, HIGH);
  }
  return;
}

void show_digit(int digit_to_show)
{
   	//Comienzo apagando todas las filas
    digitalWrite(FIRST_LINE, LOW);
    digitalWrite(SECOND_LINE, LOW);
    digitalWrite(THIRD_LINE, LOW);
    digitalWrite(FOURTH_LINE, LOW);
    
    //Segun el numero del parametro, se habilitan determinadas filas para que prendan los LEDs
    switch(digit_to_show)
  	{
    case 0:
    break; //Quiero que este apagado.
    case 1:
    digitalWrite(FIRST_LINE, HIGH); //Quiero que prenda solo la primera fila, etc.
    break;
    case 2:
    digitalWrite(SECOND_LINE, HIGH);
    break;
    case 3:
    digitalWrite(FIRST_LINE, HIGH);
    digitalWrite(SECOND_LINE, HIGH);
    break;
    case 4:
    digitalWrite(THIRD_LINE, HIGH);
    break;
    case 5:
    digitalWrite(FIRST_LINE, HIGH);
    digitalWrite(THIRD_LINE, HIGH);
    break;
    case 6:
    digitalWrite(SECOND_LINE, HIGH);
    digitalWrite(THIRD_LINE, HIGH);
    break;
    case 7:
    digitalWrite(FIRST_LINE, HIGH);
    digitalWrite(SECOND_LINE, HIGH);
    digitalWrite(THIRD_LINE, HIGH);
    break;
    case 8:
    digitalWrite(FOURTH_LINE, HIGH);
    break;
    case 9:
    digitalWrite(FIRST_LINE, HIGH);
    digitalWrite(FOURTH_LINE, HIGH);
    break;
  	}
  return;
}