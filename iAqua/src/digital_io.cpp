#include "digital_io.h"
#include "screen_mananger.h"
#define BUTTON_1 43
#define BUTTON_2 44
#define SELECTION 45
#define CHANGE 46
#define BACK 47

#define VALVE_1 4
#define VALVE_2 5
#define VALVE_3 6
#define VALVE_4 7
#define VALVE_5 8
#define VALVE_6 9
#define VALVE_7 24
#define VALVE_8 25
#define UV_LIGTH 12
#define OZZONO 13
#define PUMP 14
#define AUXILIAR_RELAY 15

#define MOTOR_1A 41
#define MOTOR_1B 42
#define MOTOR_1SU 33
#define MOTOR_1SD 32

namespace iAqua {
namespace digitalIO {
void setupIO() {
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(SELECTION, INPUT);
  pinMode(CHANGE, INPUT);
  pinMode(BACK, INPUT);
  pinMode(VALVE_1, OUTPUT);
  pinMode(VALVE_2, OUTPUT);
  pinMode(VALVE_3, OUTPUT);
  pinMode(VALVE_4, OUTPUT);
  pinMode(VALVE_5, OUTPUT);
  pinMode(VALVE_6, OUTPUT);
  pinMode(VALVE_7, OUTPUT);
  pinMode(VALVE_8, OUTPUT);
  pinMode(UV_LIGTH, OUTPUT);
  pinMode(OZZONO, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(AUXILIAR_RELAY, OUTPUT);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(MOTOR_1SU, INPUT);
  pinMode(MOTOR_1SD, INPUT);
}

bool readButton(int button) {
  int verify_delay = 100;
  if (digitalRead(button)) {
    delay((verify_delay));
    if (digitalRead(button)) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}
void waitLeftButton(int button) {
  while(digitalRead(button)) {
    delay(1);
  }
}

void testButtons() {

  if (readButton(SELECTION)) {
    iAqua::screen::printScreen("Selection pressed", 35);
  } else if (readButton(CHANGE)) {
    iAqua::screen::printScreen("Change pressed", 35);
  } else if (readButton(BACK)) {
    iAqua::screen::printScreen("Back pressed", 35);
  }
}

void setValve(int valve, bool state) { digitalWrite(valve, state); }

void testValves() {
  int valves[8] = {VALVE_1, VALVE_2, VALVE_3, VALVE_4,
                   VALVE_5, VALVE_6, VALVE_7, VALVE_8};
  static int valve_selector = 0;
  bool exit_valves_menu = false;
  const int delay_time = 1;
  const int valve_on_time = 500;
  iAqua::screen::printScreen("valve#" + String(valve_selector + 1), 35);

  while (!exit_valves_menu) {
    if (readButton(CHANGE)) {
      valve_selector++;
      if (valve_selector >= 8) {
        valve_selector = 0;
      }
      iAqua::screen::printScreen("valve#" + String(valve_selector + 1), 35);
    }
    if (readButton(BACK)) {
      valve_selector--;
      if (valve_selector <= -1) {
        valve_selector = 7;
      }
      iAqua::screen::printScreen("valve#" + String(valve_selector + 1), 35);
    }
    if (readButton(SELECTION)) {
      if (readButton(SELECTION)) {
        setValve(valves[valve_selector], HIGH);
      }
      delay(valve_on_time);
      setValve(valves[valve_selector], LOW);
    }

    if (readButton(CHANGE) && readButton(BACK)) {
      exit_valves_menu = true;
      iAqua::screen::printScreen("exit valves", 35);
      while (readButton(CHANGE) || readButton(BACK)) {
        delay(delay_time);
      }
    }
  }
}

void testRelays() {
  int relays[4] = {UV_LIGTH, OZZONO, PUMP, AUXILIAR_RELAY};
  static int relay_selector = 0;
  bool exit_relays_menu = false;
  const int delay_time = 1;
  const int relay_time_on = 500;
  iAqua::screen::printScreen("relay#" + String(relay_selector + 1), 35);

  while (!exit_relays_menu) {
    if (readButton(CHANGE)) {
      relay_selector++;
      if (relay_selector >= 4) {
        relay_selector = 0;
      }
      iAqua::screen::printScreen("relay#" + String(relay_selector + 1), 35);
    }
    if (readButton(BACK)) {
      relay_selector--;
      if (relay_selector <= -1) {
        relay_selector = 4;
      }
      iAqua::screen::printScreen("relay#" + String(relay_selector + 1), 35);
    }
    if (readButton(SELECTION)) {
      if (readButton(SELECTION)) {
        setValve(relays[relay_selector], HIGH);
      }
      delay(relay_time_on);
      setValve(relays[relay_selector], LOW);
    }

    if (readButton(CHANGE) && readButton(BACK)) {
      exit_relays_menu = true;
      iAqua::screen::printScreen("exit relays", 35);
      while (readButton(CHANGE) || readButton(BACK)) {
        delay(delay_time);
      }
    }
  }
}

void stopDoor(){
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, LOW);
}

void doorUp(){
  digitalWrite(MOTOR_1A, HIGH);
  digitalWrite(MOTOR_1B, LOW);
  while(!digitalRead(MOTOR_1SU)){
    delay(1);
  }
  stopDoor();
}

void doorDown(){
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, HIGH);
  while(!digitalRead(MOTOR_1SD)){
    delay(1);
  }
  stopDoor();
}

void testDoor(){
  bool exit_door_menu = false;
  iAqua::screen::printScreen("Door menu", 35);

  while(!exit_door_menu){

    if(readButton(CHANGE)){
      iAqua::screen::printScreen("Door up", 35);
      doorUp();
    }
    if(readButton(BACK)){
      iAqua::screen::printScreen("Door down", 35);
      doorDown();
    }
    if(readButton(SELECTION)){
      exit_door_menu = true;
    }
  }
}

} // namespace digitalIO
} // namespace iAqua
