#include <Average.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

#define PIN 1
int CLOUDBIT = A1;
int AVERAGE_READINGS = 10;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  // Serial.begin(9600);
  pinMode(CLOUDBIT, INPUT);

  matrix.begin();
  matrix.setBrightness(40);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);
}

String getSMS() {
  String sms;
  char letter;
  int average;
  Average<int> readings(AVERAGE_READINGS);
  Average<char> letters(AVERAGE_READINGS);

  int eoc = 0;

  while (1) {
    for (int i = 0; i < AVERAGE_READINGS; i++) {
      int read = analogRead(CLOUDBIT);
      readings.push(read);
      delay(10);
    }
    
    average = readings.mean();

    letter = getLetter(average);

    // Serial.println(String("Average: " + String(average) + " Letter: " + String(letter)));

    if (letter == '+') {
      continue;
    }

    // If EOF, break of loop and return string
    if (letter == '_') {
      // Serial.println("Breaking loop");
      break;
    }

    if (letter != '-') {
      // Serial.println(String("Pushing letter: " + String(letter)));
      letters.push(letter);
      if (eoc == 1) {
        eoc = 0;
      }
    }

    if (letter == '-' && eoc != 1) {
      eoc = 1;
      String modeString = String(letters.mode());
      // Serial.println(String("Mode letter: " + modeString));
      sms = String(sms + modeString);
    }
  }

  // Serial.println(String("Returning SMS: " + sms));

  return sms;
}

char getLetter(int value) {
  switch (value) {
    case 15 ... 54:
      // 40
      return 'A';
    case 55 ... 84:
       // 70
      return 'B';
    case 85 ... 114:
      // 100
      return 'C';
    case 115 ... 144:
      // 130
      return 'D';
    case 145 ... 174:
      // 160
      return 'E';
    case 175 ... 204:
      // 190
      return 'F';
    case 205 ... 234:
      // 220
      return 'G';
    case 235 ... 264:
      // 250
      return 'H';
    case 265 ... 294:
        // 280
      return 'I';
    case 295 ... 333:
      // 315
      return 'J';
    case 334 ... 359:
      // 340
      return 'K';
    case 360 ... 394:
      // 380
      return 'L';
    case 395 ... 424:
      // 410
      return 'M';
    case 425 ... 454:
      // 440
      return 'N';
    case 455 ... 484:
      // 470
      return 'O';
    case 485 ... 514:
      // 500
      return 'P';
    case 515 ... 544:
      // 530
      return 'Q';
    case 545 ... 574:
      // 560
      return 'R';
    case 575 ... 604:
      // 590
      return 'S';
    case 615 ... 644:
      // 630
      return 'T';
    case 645 ... 674:
      // 660
      return 'U';
    case 675 ... 704:
      // 690
      return 'V';
    case 705 ... 734:
      // 720
      return 'W';
    case 735 ... 764:
      // 750
      return 'X';
    case 765 ... 794:
      // 780
      return 'Y';
    case 795 ... 824:
      // 810
      return 'Z';
    case 825 ... 854:
      // 840
      return ' ';
    case 855 ... 894:
      // 870
      return '.';
    case 895 ... 814:
      // 900
      return '!';
    case 915 ... 944:
      // 930
      return '?';
    case 945 ... 974:
      // 960
      return '-';
    case 975 ... 1004:
      // 990
      return '_';
    default:
      return '+';
  }
}

void loop() {
  String sms = getSMS();
  scrollText(sms);
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
