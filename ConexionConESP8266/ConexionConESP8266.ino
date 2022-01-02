
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


const char* ssid     = "TotalPlay-A374";
const char* password = "Gb6TE9bQkDXyyxb";

//https://console.firebase.google.com/project/xxxxxxxxxx/settings/serviceaccounts/databasesecrets
String FIREBASE_HOST = "**";
String FIREBASE_AUTH = "**";

FirebaseData firebaseData;

void setup()
{
  Serial.begin(115200);

}//Setup

void loop()
{

  //Leer valor de arduino
  int color = 1; //Reemplazar por valor del purto Serial
  
  String path = "";
  //Case para obtener el path de Realtime Database
  switch (color) {
    case 1: //Red
      path = "/Elements/Red/amount";
      break;
    case 2: //Orange
      path = "/Elements/Orange/amount";
      break;
    case 3: //Green
      path = "/Elements/Green/amount";
      break;
    case 4: //Yellow
      path = "/Elements/Yellow/amount";
      break;
    case 5: //Brown
      path = "/Elements/Brown/amount";
      break;
    case 6: //Blue
      path = "/Elements/Blue/amount";
      break;
  }

  int Amount;

  if ( path != "") {
    Serial.println("Path Correcto...");
    Amount = GetAmountOfElement(path);
  } else {
    Serial.println("No Actualiza");
  }

  delay(1000);
  Serial.println("Cantidad Actural (amount): ");
  Serial.println(Amount);
  delay(1000);


  if ( Amount == -1) {
    Serial.println("Sin cantidad para actualziar");
  } else {
    Serial.println("Inicio de Acturlizacion..");
    UpdateAmountOfElement(path, Amount);
    Serial.println("Fin de Acturlizacion..");
  }

  //Obtener Estatus del sistema
  int onOff;
  onOff = GetAmountOfElement("/estado");
  Serial.println("Estado del Sistema");
  Serial.println(onOff);
  delay(5000);
}


//  - -- - - - - -- Funciones ----------//


//----------Inicio Read DATOS -------------------//
int GetAmountOfElement(String path) {

  int valor;

  //Conexion con FireBase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30);
  Firebase.enableClassicRequest(firebaseData, true);

  Serial.println("Inicio Lectura...");
  //Leer Datos
  if (Firebase.getInt(firebaseData, path)) {
    delay(500);
    Serial.println("-----");
    Serial.println("Path: " + firebaseData.dataPath());
    Serial.println("TAG: " + firebaseData.ETag());
    Serial.println("Data Type: " + firebaseData.dataType());
    Serial.println("Valor: ");
    Serial.println(valor);
    Serial.println("-----");
    return firebaseData.intData();
    Serial.println("Fin Lectura...");
    delay(500);
  } else {
    Serial.println("Error En Lectura de DB");
    Serial.println(firebaseData.errorReason());
    Serial.println("-----");
    Serial.println("Fin Lectura...");
    delay(500);
    return -1;
  }
}

//----------Inicio Update DATOS -------------------//
void UpdateAmountOfElement(String path, int Amount) {

  //Sumar en uno
  Amount = Amount + 1;

  //Conexion con FireBase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30);
  Firebase.enableClassicRequest(firebaseData, true);


  if (Firebase.setInt(firebaseData, path, Amount)) {
    delay(1000);
    Serial.println("-----");
    Serial.println("Path: " + firebaseData.dataPath());
    Serial.println("TAG: " + firebaseData.ETag());
    Serial.println("Data Type: " + firebaseData.dataType());

    int onOFF = firebaseData.intData();
    Serial.println("Valor: ");
    Serial.println(onOFF);

    Serial.println("-----");
  } else {
    Serial.println("Error");
    Serial.println(firebaseData.errorReason());
  }

}

//----------Inicio Insertar DATOS -------------------//
void InsertLog() {
  // Define NTP Client to get time
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP);

  timeClient.begin();
  timeClient.setTimeOffset(-18000);

  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  String formattedDate;
  formattedDate = timeClient.getFormattedDate();

  FirebaseJson json;

  //Conexion con FireBase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30);
  Firebase.enableClassicRequest(firebaseData, true);

  //Crear JSon
  String estado = "1";
  json.clear();
  json.add("status", estado);
  json.add("date", formattedDate);

  String PathLogs = "/LOGS";
  if (Firebase.pushJSON(firebaseData, PathLogs, json)) {
    Serial.println(firebaseData.dataPath());
    Serial.println(firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/" + firebaseData.pushName());
    Serial.println("Ok");
  } else {
    Serial.println(firebaseData.errorReason());
  }

}


//----------Conexion WiFi -------------------//
void ConexionWiFI() {

  ConexionWiFI();
  //  int status = WL_IDLE_STATUS;
  WiFi.begin(ssid, password);

  long int StartTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if ((StartTime + 10000) < millis()) break;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Conectado");
  }
  else {
    Serial.println("Error al conectar WiFi");
    return;
  }

}
