#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "FirebaseESP32.h"

const char* ssid = "TotalPlay-A374";
const char* password = "**";

//https://console.firebase.google.com/project/xxxxxxxxxx/settings/serviceaccounts/databasesecrets
String FIREBASE_HOST = "**";
String FIREBASE_AUTH = "**";

FirebaseData firebaseData;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("ssid: " + (String)ssid);
  Serial.println("password: " + (String)password);
  
  WiFi.begin(ssid, password);

  long int StartTime=millis();
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      if ((StartTime+10000) < millis()) break;
  } 

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Conectado");
  }
  else {
    Serial.println("Error al conectar WiFi");
    return;
  } 

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30); 
  Firebase.enableClassicRequest(firebaseData, true);

  FirebaseJson json;

  timeClient.begin();
  timeClient.setTimeOffset(-18000);

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  
  formattedDate = timeClient.getFormattedDate();
  
  String estado = "1";
  json.clear();
  json.add("status", estado);
  json.add("date", formattedDate);
  
  String photoPath = "/LOGS";
  if (Firebase.pushJSON(firebaseData,photoPath,json)) {
    Serial.println(firebaseData.dataPath());
    Serial.println(firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());
    Serial.println("Ok");
  } else {
    Serial.println(firebaseData.errorReason());
  }                           

  FirebaseData firebaseData2;
  
  Firebase.get(firebaseData2,"estado"); // recuperamos el valor del objeto led
  Serial.println("led:");
  //Serial.println(firebaseData2.jsonString());
  Serial.println("-----");
   
} 
 
void loop() {
  delay(10000);
}
