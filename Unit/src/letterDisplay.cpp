#include "letterDisplay.h"

void setupDisplay(Adafruit_SSD1306 &display)
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(2);
    display.setFont(&FreeMono9pt7b);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();
}

void printLetter(Adafruit_SSD1306 &display, String letter, displayResult result)
{
    display.clearDisplay();
    int16_t curX = 23;
    int16_t curY = 40;
    display.setCursor(curX, curY);
    display.print(letter);
    if (letter == "Å")
    {
        display.print('A');
        display.drawCircle((curX + 9), (curY - 24), 2, WHITE);
        display.drawCircle((curX + 9), (curY - 24), 3, WHITE);
    }
    else if (letter == "Ä")
    {
        display.print('A');
        display.fillCircle((curX + 4), (curY - 23), 2, WHITE);
        display.fillCircle((curX + 14), (curY - 23), 2, WHITE);
    }
    else if (letter == "Ö")
    {
        display.print('O');
        display.fillCircle((curX + 4), (curY - 23), 2, WHITE);
        display.fillCircle((curX + 14), (curY - 23), 2, WHITE);
    }
    else
    {
        display.print(letter);
    }
    switch (result)
    {
    case RIGHT:
        display.invertDisplay(1);
        break;
    case WRONG:
        display.invertDisplay(0);
        display.drawLine(0, 0, 64, 48, WHITE);
        display.drawLine(0, 48, 64, 0, WHITE);
        break;
    case ONLYLETTER:
        display.invertDisplay(0);
        break;
    }

    display.display();
}

static int loopvar = 0;
void displayTest(Adafruit_SSD1306 &display, String letter)
{
    switch (loopvar)
    {
        {
        case 1:
            printLetter(display, letter, RIGHT);
            break;
        case 2:
            printLetter(display, letter);
            break;
        case 3:
            printLetter(display, letter, WRONG);
            break;
        case 4:
            printLetter(display, letter, ONLYLETTER);
        }
    }
    if (++loopvar == 5)
    {
        loopvar = 1;
    }
}