#include "screen_mananger.h"
#define LINE_1 20
#define LINE_2 45

namespace iAqua {
namespace screen {
U8G2_ST7920_128X64_F_SW_SPI screen(U8G2_R0, /* EN=*/37, /* RW=*/35, /* RS=*/36,
                                   /* reset=*/34);
void setupScreen() { screen.begin(); }
void printScreen(String text, int line) {
  const char *myChar = text.c_str();
  screen.firstPage();
  do {
    screen.setFont(u8g2_font_ncenB14_tr);
    screen.drawStr(0, line, myChar);
  } while (screen.nextPage());
}

void printScreenTwoLines(String text1, int line1, String text2, int line2) {
  const char *myChar1 = text1.c_str();
  const char *myChar2 = text2.c_str();
  screen.firstPage();
  do {
    screen.setFont(u8g2_font_ncenB14_tr);
    screen.drawStr(0, line1, myChar1);
    screen.drawStr(0, line2, myChar2);
  } while (screen.nextPage());
}

void toggleText(String text1_a, String text1_b, String text2_a, String text2_b) {
  static unsigned long current_time = millis();
  const int refresh_time = 1500;
  static bool change_message = false;

  if(millis() - current_time >= refresh_time*2){
    change_message = false;
  }

  if (millis() >= current_time + refresh_time) {
    if (!change_message) {
      printScreenTwoLines(text1_a, LINE_1, text1_b, LINE_2);
    } else {
      printScreenTwoLines(text2_a, LINE_1, text2_b, LINE_2);
    }
    change_message = !change_message;
    current_time = millis();
  }
}

} // namespace screen

} // namespace iAqua