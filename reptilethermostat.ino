#include <DS18B20.h>

#include "DHT.h"
#define DHTPIN 15
#define DHTTYPE DHT11   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     5 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DS18B20 ds(6);

int relay1 = 14;
int relay2 = 16;
int relay3 = 10;

void setup() {
  Serial.begin(9600);
  Serial.print("Devices: ");
  Serial.println(ds.getNumberOfDevices());
  Serial.println();

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  dht.begin();
  
  display.clearDisplay();

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  
}

void loop() {
  /*
  digitalWrite(relay1, HIGH);
  delay(200);
  digitalWrite(relay2, HIGH);
  delay(200);
  digitalWrite(relay3, HIGH);
  delay(1000);

  digitalWrite(relay1, LOW);
  delay(200);
  digitalWrite(relay2, LOW);
  delay(200);
  digitalWrite(relay3, LOW);
*/
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Patch");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(ds.getTempF()); // modify with if cammo lower than statement
  display.setCursor(40, 20);
  display.print("Spot Temp");
  display.setCursor(0, 30);
  display.print(dht.readTemperature(true));
  display.setCursor(40, 30);
  display.print("Ambient Temp");
  display.setCursor(0, 40);
  display.print(dht.readHumidity());
  display.setCursor(40, 40);
  display.print("% Humidity");
  
  display.display();

  delay(5000);
}
