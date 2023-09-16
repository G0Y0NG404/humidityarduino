// CODE EDITED 4RCHDvk3Gr43
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include "U8glib.h"  //Download Library

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE, 6);

char str[10];

void drawTest(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, "WHAHAHAHAHA");
}

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  u8g.firstPage(); 
  do {
    drawTest();
  } while( u8g.nextPage() );
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
 
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
 
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
 
  // picture loop
  u8g.firstPage(); 
  do {
    u8g.setFont(u8g_font_helvB08);
   
    u8g.drawStr( 0, 15, "Humidity:");
    u8g.drawStr( 80, 15, dtostrf(h, 5, 2, str));
    u8g.drawStr( 115, 15, "%");
   
    u8g.drawStr( 0, 30, "Temperature:");
    u8g.drawStr( 80, 30, dtostrf(t, 5, 2, str));
    u8g.drawStr( 115, 30, "\260C");
   
    u8g.drawStr( 80, 45, dtostrf(f, 5, 2, str));
    u8g.drawStr( 115, 45, "\260F");
   
    u8g.drawStr( 0, 60, "Heat index:");
    u8g.drawStr( 80, 60, dtostrf(hi, 5, 2, str));
    u8g.drawStr( 115, 60, "\260F");
   
  } while( u8g.nextPage() );
}
