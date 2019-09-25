#include <Time.h>
#include <TimeLib.h>

//TEST
int led_pin = 4;

typedef enum{
  WAIT,
  TURN_ON,
  TURN_OFF
}status_t;

typedef enum{
  ON,
  OFF
}state_t;

// constants
int HOUR_TIME_ON = 18;
int MINUTE_TIME_ON = 1;
int HOUR_TIME_OFF = 18;
int MINUTE_TIME_OFF = 2;

// Functions
void turn_on();
void turn_off();
status_t get_status();

void setup() {
// Set this when power on to callibrate
int _hr = 18;
int _min = 0;
int _sec = 0;
int _day = 0;
int _month = 1;
int _year = 2019;
setTime(_hr, _min, _sec, _day, _month, _year);

// TEST
pinMode(led_pin, OUTPUT);
}

// globals
state_t current_state = OFF;

// main loop
void loop() {
  if(get_status() == TURN_ON && current_state == OFF)
    turn_on();
  else if(get_status() == TURN_OFF && current_state == ON)
    turn_off();
  else
    delay(10);
}

void turn_on(){

  digitalWrite(led_pin, HIGH);
  current_state = ON;
}

void turn_off(){

  digitalWrite(led_pin, LOW);
  current_state = OFF;
}

status_t get_status(){
  int current_hour = hour();
  int current_minute = minute();

  if(current_hour == HOUR_TIME_ON && current_minute == MINUTE_TIME_ON)
    return TURN_ON;
  else if(current_hour == HOUR_TIME_OFF && current_minute == MINUTE_TIME_OFF)
    return TURN_OFF;
  else
    return WAIT;
}
