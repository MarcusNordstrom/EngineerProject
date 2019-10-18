#include "wifiCom.h"

void setupWiFi(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFISSID, WIFIPW);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void getWiFi(uint8_t &id, String &letter)
{
    WiFiClient client;
    String response, url;
    String _id = "";
    int splitter = 0;
    if (!client.connect(WIFIHOST, WIFIPORT))
    {
        Serial.println("connection failed");
        //delay(5000);
        id = 0;
        letter = "";
        return;
    }
    if (client.connected())
    {
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
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("Väntar på ledig plats...");
            client.stop();
            id = 0;
            letter = "";
            return;
        }
    }
    /* Läs in svaret från servern och behandla informationen 
     beroende på längden (1 eller 2-siffrigt ID). */

    /* Läs in hela meddelandet och lägg till det på Stringen
     'response', öka också splittern för att fånga hela 
     meddelandets längd.                          */
    while (client.available())
    {
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
    if (response.charAt(response.length() - 1) == '!')
    {
        Serial.println("RESPONSE IS VALID!");
        splitter -= 8;
        while (letter == "")
        {
            if (isDigit(response.charAt(splitter)))
            {
                _id += response.charAt(splitter);
                splitter++;
                if (response.charAt(splitter) == '-')
                {
                    splitter++;
                    letter = response.substring(splitter, response.length() - 1);
                }
            }
            else
            {
                splitter++;
            }
            /* Skriv ut ID och bokstav.*/
            if (_id != "" && letter != "")
            {
                Serial.println("------------------");
                Serial.println("ID: " + _id + " / Letter: " + letter);
                Serial.println("------------------");
                id = (uint8_t)_id.toInt();
            }
        }
        return;
    }
}

void sendNeighborsWiFi(uint8_t id, irDir neighbors)
{
    // GET /data.php?id=(ID)&vgranne=(WEST)&hgranne=(EAST) HTTP/1.1
    WiFiClient client;
    if (!client.connect(WIFIHOST, WIFIPORT))
    {
        Serial.println("connection failed");
        return;
    }
    if (client.connected())
    {
        // GET request för att skicka sina grannar
        String url = "/data.php?id=" + String(id) + "&vgranne=" + String(neighbors.values[WEST]) + "&hgranne=" + String(neighbors.values[EAST]) + " HTTP/1.1";
        client.println(url);
        client.println();
    }
}

bool sendWordWiFi(void)
{
    //TODO: fråga henrik om var detta ska skickas
    WiFiClient client;
    if (!client.connect(WIFIHOST, WIFIPORT))
    {
        Serial.println("connection failed");
        return false;
    }
    if (client.connected())
    {
        String url = "/checkWord.php?id= HTTP/1.1";
        client.println(url);
        client.println();
    }
    String response = "";
    while (client.available())
    {
        char ch = static_cast<char>(client.read());
        response.concat(ch);
    }
    if(response == "1")
    {
        return true;
    } else {
        return false;
    }
}