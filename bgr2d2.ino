#include <MeAuriga.h>

#define AURIGARINGLEDNUM  12
#define RINGALLLEDS        0

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
char *parts[2];
char *cols[3];
#ifdef MeAuriga_H
MeRGBLed led_ring( 0, 12 );
#endif


void setup()
{
    Serial.begin( 9600 );
    Serial2.begin( 115200 );
    #ifdef MeAuriga_H
      led_ring.setpin( 44 );
    #endif
}

void loop()
{
  recvWithStartEndMarkers();
  showNewData();
}

void setRing(int r, int g, int b)
{
  led_ring.setColor( RINGALLLEDS, r, g, b );
  led_ring.show();
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial2.available() > 0 && newData == false) {
        rc = Serial2.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        if (strstr(receivedChars, "color")) {
          parseColor(receivedChars);
        }
        newData = false;
    }
}

void parseColor(char* colors) {
    Serial.print(colors);
    int i = 0;
    char *token = strtok(colors, ":");
    while (token != NULL)
    {
        parts[i++] = token;
        token = strtok (NULL, ":");
    }
    Serial.print("part one");
    Serial.print(parts[0]);
    Serial.print("part two");
    Serial.print(parts[1]);
    char *col = strtok(parts[1], ",");
    i = 0;
    while (col != NULL)
    {
        cols[i++] = col;
        col = strtok (NULL, ",");
    }
    Serial.print("one");
    Serial.print(cols[0]);
    Serial.print("two");
    Serial.print(cols[1]);
    Serial.print("three");
    Serial.print(cols[2]);
    setRing(atoi(cols[0]), atoi(cols[1]), atoi(cols[2])); 
}

