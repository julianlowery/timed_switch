#include <Time.h>
#include <TimeLib.h>

#define MOTOR_PIN_1 9
#define MOTOR_PIN_2 10
#define MOTOR_PIN_3 11
#define MOTOR_PIN_4 12

typedef enum {
  WAIT,
  TURN_ON,
  TURN_OFF
} status_t;

typedef enum {
  ON,
  OFF
} state_t;

enum {
  backward,
  forward
};

// time settings
int hour_time_on = 23;
int minute_time_on = 0;
int hour_time_off = 5;
int minute_time_off = 1;

// Function prototypes
void turn_on();
void turn_off();
status_t get_status();

void step_once(bool dir);
void power_save();

void setup() {
  // Set this when power on to callibrate
  int _hr = 23;
  int _min = 0;
  int _sec = 0;
  int _day = 0;
  int _month = 1;
  int _year = 2019;
  setTime(_hr, _min, _sec, _day, _month, _year);

  // setup motor output pins
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_3, OUTPUT);
  pinMode(MOTOR_PIN_4, OUTPUT);
}

// globals
state_t current_state = OFF;


// main loop
void loop() {
  if (get_status() == TURN_ON && current_state == OFF)
    turn_on();
  else if (get_status() == TURN_OFF && current_state == ON)
    turn_off();
  else
    delay(5);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTION DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void turn_on() {
  for (int i = 0; i < 300; i++) {
    step_once(forward);
    delay(10);
  }
  power_save();
  current_state = ON;
}

void turn_off() {
  for (int i = 0; i < 300; i++) {
    step_once(backward);
    delay(10);
  }
  power_save();
  current_state = OFF;
}

status_t get_status() {
  int current_hour = hour();
  int current_minute = minute();

  if (current_hour == hour_time_on && current_minute == minute_time_on)
    return TURN_ON;
  else if (current_hour == hour_time_off && current_minute == minute_time_off)
    return TURN_OFF;
  else
    return WAIT;
}

void step_once(bool dir) {
  static uint8_t step_number = 0;
  if (dir) {
    switch (step_number) {
      case 0:
        digitalWrite(MOTOR_PIN_1, HIGH);
        digitalWrite(MOTOR_PIN_2, LOW);
        digitalWrite(MOTOR_PIN_3, LOW);
        digitalWrite(MOTOR_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(MOTOR_PIN_1, HIGH);
        digitalWrite(MOTOR_PIN_2, HIGH);
        digitalWrite(MOTOR_PIN_3, LOW);
        digitalWrite(MOTOR_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(MOTOR_PIN_1, LOW);
        digitalWrite(MOTOR_PIN_2, HIGH);
        digitalWrite(MOTOR_PIN_3, HIGH);
        digitalWrite(MOTOR_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(MOTOR_PIN_1, LOW);
        digitalWrite(MOTOR_PIN_2, LOW);
        digitalWrite(MOTOR_PIN_3, HIGH);
        digitalWrite(MOTOR_PIN_4, HIGH);
        break;
    }
  } else {
    switch (step_number) {
      case 0:
        digitalWrite(MOTOR_PIN_1, LOW);
        digitalWrite(MOTOR_PIN_2, LOW);
        digitalWrite(MOTOR_PIN_3, HIGH);
        digitalWrite(MOTOR_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(MOTOR_PIN_1, LOW);
        digitalWrite(MOTOR_PIN_2, HIGH);
        digitalWrite(MOTOR_PIN_3, HIGH);
        digitalWrite(MOTOR_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(MOTOR_PIN_1, HIGH);
        digitalWrite(MOTOR_PIN_2, HIGH);
        digitalWrite(MOTOR_PIN_3, LOW);
        digitalWrite(MOTOR_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(MOTOR_PIN_1, HIGH);
        digitalWrite(MOTOR_PIN_2, LOW);
        digitalWrite(MOTOR_PIN_3, LOW);
        digitalWrite(MOTOR_PIN_4, HIGH);
    }
  }
  step_number++;
  step_number = step_number % 4;
}

void power_save(){
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, LOW);
  digitalWrite(MOTOR_PIN_3, LOW);
  digitalWrite(MOTOR_PIN_4, LOW);
}
