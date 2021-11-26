#include <ThingSpeak.h>// always include thingspeak header file after other header files and custom macros
#include <ESP8266WiFi.h>

#define triggerPin D5
#define echoPin D6
#define LEDpin D2

#define WIFI_SSID " replace MySSID"    // replace MySSID with your WiFi network name
#define WIFI_PASSWORD replace MyPassword"  // replace MyPassword with your WiFi password


char ssid[] = WIFI_SSID;   // your network SSID (name)
char pass[] = WIFI_PASSWORD;   // your network password

// your network key Index number (needed only for WEP)
WiFiClient  client;


char* writeAPIKey = "writeAPIKey writeAPIKey";
char* readAPIKey = "readAPIKey ThingSpeak";
const long channelID = 1553591;   // replace 0000000 with your channel number
const unsigned int firstReadFieldNumber = 2;
const unsigned int secondReadFieldNumber = 3;
const unsigned int switchField = 4; // Field number (1-8) to use to change status of device.  Determines if data is read from ThingSpeak.

// Other constants
const unsigned long postingInterval = 60L * 1000L;   // Post data every 60 seconds

// Global variables
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;
float distanceThreshold = 0;
bool getInfo = 1;  // Set this to zero if you don’t want to read data from ThingSpeak anymore (i.e. calibration complete)
int points = 7;




int writeTSData(long TSChannel, unsigned int TSField, float data, char* ReadAPIKey) {
  int  writeSuccess = ThingSpeak.writeField(TSChannel, TSField, data, writeAPIKey); //write the data to the channel
  return writeSuccess;
}

// Use this function if you want multiple fields simultaneously.
/*
  int writeTDData(long TSChannel,unsigned int TSField1,float data1,unsigned int TSField2,data2,char* ReadAPIKey){
  ThingSpeak.setField(TSField1,data1);
  ThingSpeak.setField(TSField1,data2);

  writeSuccess = ThingSpeak.writeFields(TSChannel, writeAPIKey);
  return writeSuccess;
  }
*/

float readTSData(long TSChannel, unsigned int TSField, char* ReadAPIKey) {

  float data = 0;

  data = ThingSpeak.readFloatField(TSChannel, TSField, ReadAPIKey);
  Serial.println(" Data read from ThingSpeak " + String(data));
  return data;
}

float getDistance(int tPin, int ePin) {

  long duration, distance;

  digitalWrite(tPin, LOW);  // Reset the trigger pin.
  delayMicroseconds(2);
  digitalWrite(tPin, HIGH);  // Start a measurement.
  delayMicroseconds(10); //
  digitalWrite(tPin, LOW);   // Complete the pulse.
  duration = pulseIn(ePin, HIGH);  // Wait for a reflection pulse.
  distance = (duration/2) / 29.1;     // Calculate the appropriate distance using the estimated speed of sound.

  // This section is useful when debugging the sensor.
  /*
    if (distance >= 200 || distance <= 0){
      Serial.println("Out of range");
    }
    else {
     Serial.print(distance);
     Serial.println(" cm");
    }
  */
  return distance;
}
void setup()
{
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(LEDpin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Start");
  Serial.print("Connect Wifi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  Serial.println("Connected");
  ThingSpeak.begin(client);
  configTime(0, 0, "south-america.pool.ntp.org");

  WiFi.disconnect();
  delay(100);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".\n");
    delay(500);
  }

  Serial.print("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Check NTP/Time, usually it is instantaneous and you can delete the code below.
  Serial.print("Retrieving time: ");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".\n");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
  
  // Get the initial parameters from ThingSpeak.
  distanceThreshold = readTSData(channelID,firstReadFieldNumber,readAPIKey);
  points = readTSData(channelID,secondReadFieldNumber,readAPIKey);




}

void loop() {
  float distance = 0;  
      for (uint16_t loops = 0; loops < points; loops++){
      distance += getDistance(triggerPin,echoPin);  //make a measurement, store the sum of all measurements
      delay(5);  
     }
     


  distance = distance / points;

  if (distance < distanceThreshold) {
    digitalWrite(LEDpin, HIGH);
  }

  else {
    digitalWrite(LEDpin, LOW);
  }


  Serial.println("Media: " + String(distance) + " cm");

  if (millis() - lastUpdateTime >=  postingInterval) {
    lastUpdateTime = millis();
    if (!(getInfo == 0)) {
      distanceThreshold = readTSData(channelID, firstReadFieldNumber, readAPIKey);
      points = readTSData(channelID, secondReadFieldNumber, readAPIKey);
      getInfo = (bool)readTSData(channelID, switchField, readAPIKey);
    }
    if (distance < distanceThreshold) {
      writeTSData(channelID, 1, distance, writeAPIKey);
    }

  }
  delay(500);    // Provide some delay between measurements.

}
