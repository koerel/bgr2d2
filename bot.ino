#include <MeAuriga.h>

#define AURIGARINGLEDNUM  12
#define RINGALLLEDS        0


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
  if (Serial2.available()) {
    String message = Serial2.readString();
    Serial.print(message);
  }
}

void setRing()
{
  led_ring.setColor( RINGALLLEDS, 0, 0, 255 );
  led_ring.show();
}