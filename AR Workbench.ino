 
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lights-7c4ff.firebaseio.com"
#define FIREBASE_AUTH "ueYOXTnCpAvfKySQirb3myeD6izfrTnViMbEF5JK"
#define WIFI_SSID "Manas"
#define WIFI_PASSWORD "Hello"

#include "DHT.h"

#define DHTPIN D5
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

float getTemp(String req)
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  // Compute heat index in Kelvin
  float k = t + 273.15;
  if (req == "c") {
    return t;//return Cilsus
  } else if (req == "f") {
    return f;// return Fahrenheit
  } else if (req == "h") {
    return h;// return humidity
  } else if (req == "hif") {
    return hif;// return heat index in Fahrenheit
  } else if (req == "hic") {
    return hic;// return heat index in Cilsus
  } else if (req == "k") {
    return k;// return temprature in Kelvin
  } else {
    return 0.000;// if no reqest found, retun 0.000
  }

}




void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx Robojax test!");


  dht.begin();
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

//water level
int WaterLevel_pin = A0;
int WaterLevel_Calibrated;


void loop() {

  // Water level Measurement
  int WaterLevel =  analogRead(WaterLevel_pin);
  WaterLevel_Calibrated = map(WaterLevel, 415, 205, 0, 100);
  Serial.println(WaterLevel);
  Serial.println(WaterLevel_Calibrated);

  Firebase.setFloat("WaterLevel", WaterLevel_Calibrated);
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;

  }

  // Robojax.com test video
  Serial.print("Temperature: ");

  Serial.print(getTemp("c"));

  Serial.print(" *C ");
  Serial.print(getTemp("f"));
  Serial.println (" *F");
  Serial.println("-----------------");
  Serial.print("Heat index: ");
  Serial.print(getTemp("hic"));
  Serial.print(" *C ");
  Serial.print(getTemp("hif"));
  Serial.println(" *F");
  Serial.print(getTemp("k"));
  Serial.println(" *K");
  Serial.println("-----------------");
  Serial.print("Humidity: ");
  Serial.print(getTemp("h"));
  Serial.println(" % ");
  Serial.println("===========================");


  // set value
  Firebase.setFloat("Temperature", getTemp("c"));
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }


  // update value
  Firebase.setFloat("Humidity", getTemp("h"));
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }


}



