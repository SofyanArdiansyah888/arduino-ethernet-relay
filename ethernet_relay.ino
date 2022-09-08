#include <SPI.h>
#include <Ethernet.h>
  
    
// RELAY ON PORT 2    
int relay = 2;

boolean statusRelay = false;
boolean isEnable = true;

String readString; 
char c;

byte mac[] = {0xDA, 0xAD, 0xBE, 0xEB, 0xFE, 0xFB};
IPAddress ip(192, 168, 1, 182);
EthernetServer server(80);

//SETUP INIT    
void setup() {
  // SETUP RELAY PORT AS OUTPUT
  pinMode(relay, OUTPUT);
  
  // INIT SERIAL
  Serial.begin(9600);
  while (!Serial) { ; }

  // INIT ETHERNET
  Ethernet.begin(mac, ip);
  server.begin();
}

// LOOP
void loop() {
  EthernetClient client = server.available();
  if (client) {
      while (client.connected()) {   
        if (client.available()) {
          c = client.read(); 
          if (readString.length() < 100) {
            readString += c;
          }
          if (c == '\n') {
          //      client.println("HTTP/1.1 200 OK");
          //      client.println("Content-Type: application/json");
          //      client.println();     
          //      client.println("<HTML>");
          //      client.println("<HEAD>");
          //      client.println("<meta http-equiv=\"Refresh\" content=\"4; url=/home\" />");
          //      client.println("<meta http-equiv=\"Content-Type\" content=\"application/vnd.wap.xhtml+xml; charset=utf-8\" />");
          //      client.println("</HEAD>");
          //      client.println("<BODY align=\"center\">");
          //      client.println("<table align=\"center\"><tr>");
          //      client.println("<th width=\"10%\">Nama Perangkat</th>");
          //      client.println("<th width=\"10%\">Status Perangkat</th>");
          //      client.println("<th width=\"10%\">Saklar ON/OFF</th></tr>");
          //      client.println("<tr class=\"trh1\"><td align=\"left\">");
          //      client.println("Relay 1");
          //      client.println("</td><td align=\"center\">");
          //      if (statusRelay == false) {
          //        client.println("<b>MATI</b>");
          //      } else {
          //        client.println("<b>HIDUP</b>");
          //      }
          //        client.println("</td><td align=\"center\">");
          //      if (statusRelay == false) {
          //        client.println("<a href=\"/1on\" />HIDUP</a>");
          //      } else {
          //        client.println("<a href=\"/1off\" />MATI</a>");
          //      }
          //      client.println("</td></tr>");
          //      client.println();
          //      client.println("</BODY>");  
            delay(1);
            client.stop();
            
            if (readString.indexOf("disable") > 0){ 
                isEnable = false; 
            }else if(readString.indexOf("enable") > 0){
                isEnable = true;
            }
            
            // IF ENABLE THEN CAN DO ON/OFF RELAY
            if(isEnable){
              // IF URL CONTAINS ON THEN TURN ON RELAY
              if (readString.indexOf("on") >0){ 
                digitalWrite(relay, HIGH); 
                statusRelay = true; 
              }
              
              // IF URL CONTAINS OFF THEN TURN OFF RELAY
              if (readString.indexOf("off") >0){ 
                digitalWrite(relay, LOW); 
                statusRelay = false; 
              }
            }
            readString=""; 
          }  
      } 
    } 
  }
}
