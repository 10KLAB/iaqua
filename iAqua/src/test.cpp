#include "test.h"

namespace iAqua{
    namespace startTest{
        U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* EN=*/37, /* RW=*/35, /* RS=*/36, /* reset=*/34);
        
        void setUpScreen(){
            u8g2.begin();
        }
        void helloWorld(){
            u8g2.firstPage();
            do {
                u8g2.setFont(u8g2_font_ncenB14_tr);
                u8g2.drawStr(0,24,"Hello World!");
            } while ( u8g2.nextPage() );
        }
    }
}