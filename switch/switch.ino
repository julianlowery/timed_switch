#include <Time.h>
#include <TimeLib.h>

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
int HOUR_TIME_ON = 0;
int MINUTE_TIME_ON = 0;
int HOUR_TIME_OFF = 0;
int MINUTE_TIME_OFF = 0;

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


  current_state = ON;
}

void turn_off(){


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
