#include "test.h"
#define button1 47
#define button2 46
#define button3 45

namespace iAqua{
    namespace startTest{
        U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* EN=*/37, /* RW=*/35, /* RS=*/36, /* reset=*/34);
        
        void setupScreen(){
            u8g2.begin();
        }
        void setupButtons(){
            for (int i=45; i<=47;i++) pinMode(i,INPUT);//button1:47-button2:46-button3:45
        }
        void helloWorld(){
            u8g2.firstPage();
            do {
                u8g2.setFont(u8g2_font_ncenB14_tr);
                u8g2.drawStr(0,24,"Hello World!");
            } while ( u8g2.nextPage() );
        }
        void buttonsTest(){
            if(digitalRead(button1)){
                u8g2.firstPage();
                do {
                    u8g2.setFont(u8g2_font_ncenB14_tr);
                    u8g2.drawStr(0,35,"Button1");
                } while ( u8g2.nextPage() );
                delay(2000);
            }
            else if(digitalRead(button2)){
                u8g2.firstPage();
                do {
                    u8g2.setFont(u8g2_font_ncenB14_tr);
                    u8g2.drawStr(0,35,"Button2");
                } while ( u8g2.nextPage() );
                delay(2000);
            }
            else if(digitalRead(button3)){
                u8g2.firstPage();
                do {
                    u8g2.setFont(u8g2_font_ncenB14_tr);
                    u8g2.drawStr(0,35,"Button3");
                } while ( u8g2.nextPage() );
                delay(2000);
            }
        }
    }
}