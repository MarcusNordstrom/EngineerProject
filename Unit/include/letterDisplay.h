#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Fonts/FreeMono9pt7b.h"

typedef enum {
    ONLYLETTER,
    RIGHT,
    WRONG
} displayResult;
void setupDisplay(Adafruit_SSD1306 &display);

void printLetter(Adafruit_SSD1306 &display, String letter, displayResult result = ONLYLETTER);

void displayTest(Adafruit_SSD1306 &display, String letter);

