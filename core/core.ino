#include <Average.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

#define PIN 1
int CLOUDBIT = A1;
int AVERAGE_READINGS = 20;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(CLOUDBIT, INPUT);

  matrix.begin();
  matrix.setBrightness(40);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);
}

String getSMS() {
  String sms;
  int average;
  Average<int> readings(AVERAGE_READINGS);

  for (int i = 0; i < AVERAGE_READINGS; i++) {
    int read = analogRead(CLOUDBIT);
    readings.push(read);
    delay(100);
  }

  average = readings.mean();

  String letter = getLetter(average);

  Serial.println(String(average));
  Serial.println(letter);

  sms = letter;

  return sms;
}

String getLetter(int value) {
  switch (value) {
    case 15 ... 54:
      return "A";
    case 55 ... 84:
      return "B";
    case 85 ... 114:
      return "C";
    case 115 ... 144:
      return "D";
    case 145 ... 174:
      return "E";
    case 175 ... 204:
      return "F";
    case 205 ... 234:
      return "G";
    case 235 ... 264:
      return "H";
    case 265 ... 294:
      return "I";
    case 295 ... 324:
      return "J";
    case 325 ... 354:
      return "K";
    case 355 ... 384:
      return "L";
    case 385 ... 404:
      return "M";
    case 405 ... 434:
      return "N";
    case 435 ... 464:
      return "O";
    case 465 ... 494:
      return "P";
    case 495 ... 524:
      return "Q";
    case 525 ... 554:
      return "R";
    case 555 ... 584:
      return "S";
    case 585 ... 604:
      return "T";
    case 605 ... 634:
      return "U";
    case 635 ... 664:
      return "V";
    case 665 ... 694:
      return "W";
    case 695 ... 724:
      return "X";
    case 725 ... 754:
      return "Y";
    case 755 ... 784:
      return "Z";
    case 785 ... 804:
      return " ";
    case 805 ... 834:
      return ".";
    case 835 ... 864:
      return "!";
    case 865 ... 894:
      return "?";
    case 895 ... 924:
      return "EOC";
    case 925 ... 954:
      return "EOF";
    case 955 ... 204:
      return "F";
    default:
      return "";
  }
}

void loop() {
  String sms = getSMS();
  scrollText(sms);
}

void oldLoop() {
  /* Serial.println(analogRead(button)); */
  crossFade(off, white, 50, 3);
  delay(1000);

  colorWipe(purple, 15);

  drawLogoRound();
  delay(1200);

  colorWipe(orange, 15);
  delay(1200);

  drawLogo();
  delay(1200);

  colorWipe(yellow, 15);
  drawPhone();
  delay(1200);

//  colorWipe(purple, 15);
//  drawSMS();
//  delay(1200);

  crossFade(purple, teal, 15, 5);

  matrix.show();

  String twitterHandle = "#signalconf";
  scrollText(twitterHandle);
  scrollText(twitterHandle);
  delay(500);

  crossFade(purple, white, 120, 5);
  crossFade(white, off, 120, 5);
  delay(2000);
}

// Fill the dots one after the other with a color
void colorWipe(RGB color, uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
      matrix.show();
      delay(wait);
    }
  }
}

// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

// Crossfade entire screen from startColor to endColor
void crossFade(RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

     matrix.fillScreen(matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

void drawLogo() {
  // This 8x8 array represents the LED matrix pixels.
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };

  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, purple, white, 30, 0);
     }
   }
  }
}

void drawLogoRound(){
  // This 8x8 array represents the LED matrix pixels.
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };

  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, purple, white, 30, 0);
     }
   }
  }
}

void drawPhone(){
  // This 8x8 array represents the LED matrix pixels.
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 1, 1, 1, 1, 1, 1, 0}
  };

  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, purple, white, 8, 0);
     }
   }
  }
}

void drawSMS(){
  // This 8x8 array represents the LED matrix pixels.
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 0, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 1, 0}
  };

  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, purple, white, 30, 0);
     }
   }
  }
}

void scrollText(String textToDisplay) {
  int x = matrix.width();
  int pixelsInText = textToDisplay.length() * 7;

  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();

  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(matrix.Color(red.r, red.g, red.b));
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(150);
  }
}
