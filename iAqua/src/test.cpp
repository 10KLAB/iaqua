#include "test.h"
#define button1 47 
#define button2 46
#define button3 45


/*
1.Separar las librerias por componentes, sensor de distancia, pantalla, botones
2.En la librería de la pantalla crear una función que reciba como parámetro posición y texto a mostrar
void printText(String text, int position)
3.Corregir los #define a Uppercase #define BUTTON_1
4. evitar números mágicos, ver función del sensor de distancia
*/

namespace iAqua {
namespace startTest {
//Cambiar nombre "u8g2" por uno que sea más legible"
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* EN=*/37, /* RW=*/35, /* RS=*/36,
                                 /* reset=*/34);

//Cambiar nombre "hcsr04" por uno que sea más legible"
HCSR04 hcsr04(/* TRI=*/30, /* ECH=*/31);

void setupScreen() { u8g2.begin(); }

void setupButtons() {
  for (int i = 45; i <= 47; i++)
    pinMode(i, INPUT); // button1:47-button2:46-button3:45
}

void helloWorld() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0, 24, "Hello World!");
  } while (u8g2.nextPage());
}
void buttonsTest() {
  if (digitalRead(button1)) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 35, "Button1");
    } while (u8g2.nextPage());
    delay(2000);
  } else if (digitalRead(button2)) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 35, "Button2");
    } while (u8g2.nextPage());
    delay(2000);
  } else if (digitalRead(button3)) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 35, "Button3");
    } while (u8g2.nextPage());
    delay(2000);
  }
}
void hcsrTest() {
/*
1. Nombrar adecuadamente la variable "d"
2. crear variable que remplace el valor "50" por una que exprese que significa ese valor
3. Nombrar de manera adecuada la función*/
  float d = hcsr04.dist();
  delay(70);
  while (d < 50) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 24, "sensor OK");
    } while (u8g2.nextPage());
    d = hcsr04.dist();
    delay(70);
  }
}
} // namespace startTest
} // namespace iAqua