
String data;
String url;
String id = "", letter = "";
int splitter = 0, splitter2;
String response = "";
String incoming = "HTTP/1.1 200 OK Date: Sun, 13 Oct 2019 12:38:33 GMT Server: Apache X-Powered-By: PHP/7.2.10 Content-Length: 6 Content: 12-Å!";

void setup() {
    Serial.begin(115200);
    Serial.println("----- NEW SESSION -----");
}

void loop() {

 if(response.charAt(response.length()-1) == '!'){
    splitter2 = splitter-8;
    if(isDigit(response.charAt(splitter2))){
      id += response.charAt(splitter2);
      splitter++;
      splitter2++;
      if(response.charAt(splitter2) == '-'){
        splitter2++;
        letter = response.substring(splitter2, response.length()-1);
      }
    } else { splitter++; }
    if(id != "" && letter != ""){
      Serial.println("------------------");
      Serial.println("ID: " + id + " / Letter: " + letter);
      Serial.println("------------------");
      id = "";
      letter = "";
      splitter = 0;
      while(1){ delay(500000); }
    }
    
  } else {
    response += incoming.charAt(splitter);
    Serial.println(response);
    splitter++;
    delay(50);
  }
}
