#include "letterDisplay.h"

void setupDisplay(Adafruit_SSD1306 &display)
{
    //Konfigurerar skärmen till 2x font med FreeMono9pt7b typsnittet
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(2);
    display.setFont(&FreeMono9pt7b);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();
}

void printLetter(Adafruit_SSD1306 &display, String letter, irDir irdir, displayResult result)
{
    //Skriver ut bokstav (även å/ä/ö)
    display.clearDisplay();
    display.setTextSize(2);
    int16_t curX = 23;
    int16_t curY = 40;
    display.setCursor(curX, curY);
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
    //inverterar/ritar ett kryss vid rätt/fel
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
    //ritar en prick på sidan med kommunikation
    for (size_t i = 0; i < 4; i++)
    {
        switch (i)
        {
            {
            case WEST:
                if (irdir.values[WEST] != 0)
                {
                    display.fillCircle(3, 24, 2, WHITE);
                }
                break;
            case EAST:
                if (irdir.values[EAST] != 0)
                {
                    display.fillCircle(61, 24, 2, WHITE);
                }
                break;
            default:

                break;
            }
        }
    }

    display.display();
}

static int loopvar = 0;
void displayTest(Adafruit_SSD1306 &display, String letter)
{
    //test av skärmen
    irDir dir;
    switch (loopvar)
    {
        {
        case 1:
            printLetter(display, letter, dir, RIGHT);
            break;
        case 2:
            printLetter(display, letter, dir);
            break;
        case 3:
            printLetter(display, letter, dir, WRONG);
            break;
        case 4:
            printLetter(display, letter, dir, ONLYLETTER);
        }
    }
    if (++loopvar == 5)
    {
        loopvar = 1;
    }
}