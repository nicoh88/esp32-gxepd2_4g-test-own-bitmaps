#include <Arduino.h>
#include <Wire.h>

#define ENABLE_GxEPD2_GFX 1

const uint8_t PIN_EPD_BUSY  = 14;
const uint8_t PIN_EPD_CS    = 13;
const uint8_t PIN_EPD_RST   = 21;
const uint8_t PIN_EPD_DC    = 22;

const uint8_t PIN_EPD_PWR   = 26; 

#define MAX_DISPLAY_BUFFER_SIZE 65536ul // e.g.

////
//// Testing with GxEPD2 without Grayscale 
////
//#include <GxEPD2_BW.h>
//#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
//#define GxEPD2_DRIVER_CLASS GxEPD2_750_T7
//#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
////

////
//// GxEPD2_4G
////
#include <GxEPD2_4G_4G.h>
#define GxEPD2_DISPLAY_CLASS GxEPD2_4G_4G
#define GxEPD2_DRIVER_CLASS GxEPD2_750_T7
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 4) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 4))
////

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, 
    MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display
        (GxEPD2_DRIVER_CLASS(PIN_EPD_CS,
            PIN_EPD_DC,
            PIN_EPD_RST,
            PIN_EPD_BUSY));

#undef MAX_DISPLAY_BUFFER_SIZE
#undef MAX_HEIGHT

#include "Bitmaps4g800x480.h"
#include "Bitmaps4g800x480_nh.h"
#include "Bitmaps800x480_nh.h"
#include "bmp1.h"

// Setup function
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);

  Serial.println("Display init...");
  display.init(115200);
  display.clearScreen();
  display.setRotation(0);
  display.setFullWindow();
  display.writeScreenBuffer();

  Serial.println("Drawing...");



  // Examples GxEPD2_4G
  //Serial.print("sizeof(Bitmap4g800x480_1) is "); Serial.println(sizeof(Bitmap4g800x480_1)); // 2-Bit = 4 graycales
  //display.epd2.drawImage_4G(Bitmap4g800x480_1, 2, 0, 0, 800, 480, true, false, true);

  // Test CPP - Monochrome, 1-Bit
  //Serial.print("sizeof(Bitmaps800x480_nh) is "); Serial.println(sizeof(Bitmaps800x480_nh)); // Monochrome
  //display.drawImage(Bitmaps800x480_nh, 0, 0, 0, 800, 480, true, false, true); // Works, but no Grayscale and not in "firstPage" loop
  
  // Test CPP - Grayscale, 2-Bit
  Serial.print("sizeof(Bitmaps4g800x480_nh) is "); Serial.println(sizeof(Bitmaps4g800x480_nh)); // 2-Bit = 4 Graustufen
  display.epd2.drawImage_4G(Bitmaps4g800x480_nh, 2, 0, 0, 800, 480, true, false, true); // Funktioniert leider nicht, zieht schlieren.

  // Test CPP - Grayscale, 2-Bit from https://github.com/florian-senn/wemos_d1_mini_esp32_epd_7in5_V2/
  //Serial.print("sizeof(bmp1) is "); Serial.println(sizeof(bmp1)); // 2-Bit = 4 Graustufen
  //display.epd2.drawImage_4G(bmp1, 2, 0, 0, 800, 480, true, false, true); // Funktioniert leider nicht, zieht schlieren.
  


  Serial.println("Image displayed successfully");



  /*
  Serial.println("Test boxes");

  uint16_t box_x = 0;
  uint16_t box_y = 0;
  uint16_t box_w = 800;
  uint16_t box_h = 20;
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  
  display.firstPage();
  do
  {
    //display.fillScreen(GxEPD_WHITE);
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
    display.fillRect(box_x, box_y+20, box_w, box_h, GxEPD_WHITE);
    display.fillRect(box_x, box_y+40, box_w, box_h, GxEPD_LIGHTGREY);
    display.fillRect(box_x, box_y+60, box_w, box_h, GxEPD_DARKGREY);
    display.fillRect(box_x, 480-20, box_w, box_h, GxEPD_BLACK);
    display.fillRect(box_x, 480-40, box_w, box_h, GxEPD_WHITE);
    display.fillRect(box_x, 480-60, box_w, box_h, GxEPD_LIGHTGREY);
    display.fillRect(box_x, 480-80, box_w, box_h, GxEPD_DARKGREY);
    
    //display.fillScreen(GxEPD_BLACK);
  }
  while (display.nextPage());

  Serial.println("Test boxes done");
  */
}

void loop() {
  // Nothing to do here
}

/*




  int16_t width = display.width();
  int16_t height = display.height();
  uint8_t pixel;
  const int blockHeight = 16; // Höhe des Blocks zum Schreiben

  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);


    for (int y = 0; y < height; y += blockHeight) {
      Serial.printf("Drawing block until height: %d\n", y);
      int currentBlockHeight = min(blockHeight, height - y);
      uint8_t* blockBuffer = (uint8_t*)malloc(width * currentBlockHeight);

      if (!blockBuffer) {
        Serial.println("Failed to allocate memory for block buffer");
        file.close();
        return;
      }

      // Lese einen Block aus der Datei
      file.read(blockBuffer, width * currentBlockHeight);

      // Schreibe den Block auf das Display
      //display.epd2.writeImagePart_4G(blockBuffer, width, y, width, currentBlockHeight, false);
      display.epd2.drawImagePart_4G(blockBuffer, 2, 0, y, width, currentBlockHeight, 0, y, width, currentBlockHeight, true, false, true);

      free(blockBuffer);
    }
  } while (display.nextPage());





  //display.setPartialWindow(0, 0, display.width(), display.height());
  //display.setFullWindow();

  //delay(2000);

  //display.epd2.drawImage_4G(Bitmap2g104x104, 2, display.epd2.WIDTH / 2 - 52, display.epd2.HEIGHT / 2 - 52, 104, 104, false, false, true);
  //delay(2000);

  //display.drawImage(Bitmaps2g800x480_nh, 0, 0, 0, 800, 480, false, false, true);

  //display.epd2.clearScreen();
  //display.epd2.drawImage_4G(Bitmap2g104x104, 2, display.epd2.WIDTH / 2 - 52, display.epd2.HEIGHT / 2 - 52, 104, 104, false, false, true);
  //delay(2000);

  ///*
  Serial.println("firstPage");
  display.firstPage();
  do
  {
    //delay(5000);
    Serial.println("fillScreen");
    display.fillScreen(GxEPD_WHITE);
    //delay(5000);
    //display.drawGreyPixmap(Bitmaps4g800x480_nh, 2, 0, 0, 800, 480);

    
    //display.drawGreyPixmap(Bitmaps4g800x480_nh, 4, 0, 0, 400, 240);
    //display.drawImage(Bitmaps4g800x480_nh, 0, 0, 0, 400, 240);
    //display.drawImage(Bitmaps4g800x480_nh, 0, 0, 400, 240, false, false, true);

    //Serial.print("sizeof(Bitmaps800x480_nh) is "); Serial.println(sizeof(Bitmaps800x480_nh)); // Monochrome
    //display.drawGreyPixmap(Bitmaps800x480_nh, 0, 0, 0, 800, 480); // 1-Bit per Pixel; // Zieht schlieren
    
    //display.drawImage(Bitmaps800x480_nh, 0, 0, 0, 800, 480, false, false, true); // Zieht schlieren

    //Serial.println("delay");
    //delay(5000);
  }
  while (display.nextPage());
  delay(2000);



  //display.epd2.drawImagePart_4G(Bitmaps4g800x480_nh, 2, 0, 0, 800, 480, 0, 0, 800, 100, true, false, true);
  
*/