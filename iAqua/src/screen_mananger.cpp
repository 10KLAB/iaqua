#include "screen_mananger.h"

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

} // namespace screen

} // namespace iAqua