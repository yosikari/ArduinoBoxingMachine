#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define CLK_PIN 13  // CLK or SCK
#define DATA_PIN 11 // DIN or MOSI
#define CS_PIN 10   // CS or SS
#define MAX_DEVICES 3

#define PIR_SENSOR1_PIN 3 // Pin for PIR motion sensor 1
#define PIR_SENSOR2_PIN 4 // Pin for PIR motion sensor 2

#define RESTART_BUTTON_PIN 2 // Pin for reset button

MD_Parola myDisplay = MD_Parola(MD_MAX72XX::FC16_HW, CS_PIN, MAX_DEVICES);
// Adjust the MAX_DEVICES value to match the number of connected 788AS modules

const uint8_t charWidth = 6;                  // Width of each character in pixels
const uint8_t displayWidth = MAX_DEVICES * 8; // Total width of the display in pixels

char message[] = "GO GO GO";
char wonMessage[] = "BooM";
char lossMessage[] = "Fail";
uint16_t messageLength;
int16_t textPosition = displayWidth;
int score = 0;
int defaultMinRange = 0;
int defaultMaxRange = 1000;
int defaultMinOutput = 0;
int defaultMaxOutput = 999;

unsigned long firstSensorTime = 0;  // Time when first sensor detects movement
unsigned long secondSensorTime = 0; // Time when second sensor detects movement

unsigned long previousMillis = 0; // Variable to store the previous time
unsigned long interval = 1500;    // Interval in milliseconds
int currentText = 0;

void setup()
{
    myDisplay.begin();
    pinMode(PIR_SENSOR1_PIN, INPUT);
    pinMode(PIR_SENSOR2_PIN, INPUT);

    pinMode(RESTART_BUTTON_PIN, INPUT_PULLUP);

    myDisplay.setInvert(false);
    myDisplay.setIntensity(8); // Set the display intensity (0-15, lower value for dimmer display)

    messageLength = strlen(message) * charWidth; // Calculate the total width of the text

    myDisplay.displayReset(); // Reset the display to prepare for new content
    myDisplay.displayZoneText(0, message, PA_LEFT, 35, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    myDisplay.displayAnimate();
}

void loop()
{
    if (myDisplay.displayAnimate())
    {
        // If the scrolling animation is complete, restart it
        myDisplay.displayReset();
        myDisplay.displayZoneText(0, message, PA_LEFT, 35, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        myDisplay.displayAnimate(); // Start the animation again
    }

    // Check if the first sensor detects movement
    if (digitalRead(PIR_SENSOR1_PIN) == LOW && firstSensorTime == 0)
    {
        firstSensorTime = millis(); // Record the time when first sensor detects movement
        Serial.println("First sensor detected movement");
    }

    // Check if the second sensor detects movement
    if (digitalRead(PIR_SENSOR2_PIN) == LOW && firstSensorTime > 0 && secondSensorTime == 0)
    {
        secondSensorTime = millis();                                       // Record the time when second sensor detects movement
        unsigned long timeDifference = secondSensorTime - firstSensorTime; // Calculate the time difference

        if (timeDifference > 500)
        {
            timeDifference = timeDifference * 1.5;
        }
        else if (timeDifference > 400)
        {
            timeDifference = timeDifference * 2;
        }
        else if (timeDifference > 300)
        {
            timeDifference = timeDifference * 2.5;
        }
        else if (timeDifference > 200)
        {
            timeDifference = timeDifference * 4;
        }
        else
        {
            timeDifference = timeDifference * 8;
        }

        // Map the timeDifference to a reversed range of 0-999
        int mappedScore;

        if (timeDifference > 1000)
        {
            mappedScore = 1;
        }
        else
        {
            mappedScore = map(timeDifference, 0, 1000, 999, 1);
        }

        if (mappedScore > 999)
        {
            mappedScore = 999;
        }

        while (score != mappedScore)
        {
            // Check if reset button is pressed
            if (digitalRead(RESTART_BUTTON_PIN) == LOW)
            {
                rebootArduino();
            }
            score++;
            sprintf(message, "%d", score);
            myDisplay.displayReset();
            myDisplay.displayZoneText(0, message, PA_CENTER, 35, 0, PA_PRINT, PA_PRINT);
            myDisplay.displayAnimate();
            if ((score + 30) >= mappedScore)
            {
                delay(100);
            }
            else if ((score + 10) >= mappedScore)
            {
                delay(600);
            }
            else if ((score + 7) >= mappedScore)
            {
                delay(1500);
            }
            else
            {
                delay(30);
            }
            if (score == mappedScore - 1 || score == mappedScore)
            {
                sprintf(message, "%d", mappedScore);
                while (true)
                {
                    // Check if reset button is pressed
                    if (digitalRead(RESTART_BUTTON_PIN) == LOW)
                    {
                        rebootArduino();
                    }

                    unsigned long currentMillis = millis(); // Get the current time

                    if (currentMillis - previousMillis >= interval)
                    {
                        previousMillis = currentMillis; // Update the previous time

                        myDisplay.displayReset();

                        switch (currentText)
                        {
                        case 0:
                            myDisplay.displayZoneText(0, message, PA_CENTER, 35, 0, PA_PRINT, PA_PRINT);
                            currentText = 1;
                            break;

                        case 1:
                            score < 300 ? myDisplay.displayZoneText(0, lossMessage, PA_CENTER, 35, 0, PA_PRINT, PA_PRINT) : myDisplay.displayZoneText(0, wonMessage, PA_CENTER, 35, 0, PA_PRINT, PA_PRINT);
                            currentText = 0;
                            break;
                        }

                        myDisplay.displayAnimate();
                    }
                }
            }
        }
    }
}

void rebootArduino()
{
    asm volatile("jmp 0"); // Perform a software reset by jumping to address 0
}