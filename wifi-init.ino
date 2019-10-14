/*
 *  Denna sketch ansluter till vår SQL-server och skickar information via
 *  GET/POST requests. 
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Connectify-Gothi"
#define STAPSK  "gruppgothi"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.137.101";
const uint16_t port = 8888;
// String data;
String url, response;
String id = "", letter = "";
int splitter = 0, splitter2;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  /*  Använd WiFiClient biblioteket för att ansluta till servern
   *  på en bestämd IP-address med port.
   */
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  
  /* Följande kod skickar en get-request till servern. */
  Serial.println("Requesting id and character from server...");
  if (client.connected()) {
    // GET request för att begära ID+bokstav direkt via URL:en.
    url = "GET /id.php HTTP/1.0";
    client.println(url);
    client.println();
    /*
     * POST request för att hantera utgående meddelanden till SQL-databasen
    client.println("POST /data.php HTTP/1.1");
    client.println("Host: 192.168.0.2"); Använd antingen denna eller
    client.println(concat("Host: ", host); denna raden för host
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
    */
  }

  /* Kan inte nå servern */
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("Väntar på ledig plats...");
      client.stop();
      // 120s är lagom tid för att en plats ska bli ledig
      delay(120000);
      return;
    }
  }

  /* Läs in svaret från servern och behandla informationen 
     beroende på längden (1 eller 2-siffrigt ID). */

  /* Läs in hela meddelandet och lägg till det på Stringen
     'response', öka också splittern för att fånga hela 
     meddelandets längd.                          */
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    response.concat(ch);
    splitter++;
  }
    /* Om meddelandet är komplett så ska det finnas ett utrops
       -tecken på slutet. Bara då så ska meddelandet behandlas.
       Kontrollera var meddelandet börjar genom att hitta första
       siffran närmst slutet. När nästkommande tecken är ett
       bindestreck så summeras resten av tecknen (1-2byte) som
       ett tecken. På detta sättet så kan man också fånga svenska
       tecken vilket inte går vanligtvis ifall man sparar det som
       en bokstav. */
  if(response.charAt(response.length()-1) == '!'){
    Serial.println("RESPONSE IS VALID!");
    splitter -= 8;
    while(letter == ""){
      if(isDigit(response.charAt(splitter))){
        id += response.charAt(splitter);
        splitter++;
        if(response.charAt(splitter) == '-'){
          splitter++;
          letter = response.substring(splitter, response.length()-1);
        }
      } else { splitter++; }
      /* Skriv ut ID och bokstav. Återställ alla värden
      till 0, behövs kanske inte ¯\_(ツ)_/¯ */
      if(id != "" && letter != ""){
        Serial.println("------------------");
        Serial.println("ID: " + id + " / Letter: " + letter);
        Serial.println("------------------");
        id = "";
        letter = "";
        splitter = 0;
        while(1){ delay(500000); }
      }
    }
  }
  
  /* Test för att se vad informationen innehåller. *//*
  // Serial.println(response);
  // Serial.println(isDigit(response.charAt(179)));
  // Serial.println("Length - " + response.length());
  // Serial.println("Last char - " + response.charAt(response.length()-1));
  // Serial.println("ID + letter - " + response.substring(response.length()-8, response.length()));
  // Serial.println(isUpperCase(response.charAt(response.length()-1)));
  */
  response = "";

  // Avslutar anslutningen
  Serial.println("Avslutar anslutningen till server");
  client.stop();
  delay(500000); // execute once every 5 minutes, don't flood remote service
}
