#include <ESP8266WiFi.h>  
 char k;
const char* ssid = "SERVYBOT";
const char* password = "electroverts";
char server[] = "mail.smtpcorp.com";
ADC_MODE(ADC_VCC);

WiFiClient client;
void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IPess: ");
  Serial.println(WiFi.localIP());
//  byte ret = sendEmail();
}

void loop()
{ 
  if(Serial.available()>0)
     k= (char)Serial.read();
     if(k=='d'||k=='s')
     {
      Serial.println("asd");
      Serial.println(k);
      byte ret = sendEmail();}
}

byte sendEmail()
{
  byte thisByte = 0;
  byte respCode;

  if (client.connect(server, 2525) == 1) {
    Serial.println(F("connected"));
  } else {
    Serial.println(F("connection failed"));
    return 0;
  }
//  if (!eRcv()) return 0;

  Serial.println(F("Sending EHLO"));
  client.println("EHLO www.example.com");
  if (!eRcv()) return 0;
  Serial.println(F("Sending auth login"));
  client.println("auth login");
  if (!eRcv()) return 0;
  Serial.println(F("Sending User"));
  // Change to your base64, ASCII encoded user
  client.println("a2F2aW5rdW1hNg=="); // SMTP UserID
  if (!eRcv()) return 0;
  Serial.println(F("Sending Password"));
  // change to your base64, ASCII encoded password
  client.println("S2F2aU5hdmlVdjI=");//  SMTP Passw
  if (!eRcv()) return 0;
  Serial.println(F("Sending From"));   // change to your email address (sender)
  client.println(F("MAIL From: kavinkumar1543884@gmail.com"));// not important
  if (!eRcv()) return 0;   // change to recipient address
  Serial.println(F("Sending To"));
  client.println(F("RCPT To: rahulraj.2305@gmail.com"));
  if (!eRcv()) return 0;
  Serial.println(F("Sending DATA"));
  client.println(F("DATA"));
  if (!eRcv()) return 0;
  Serial.println(F("Sending email"));   // change to recipient address
  client.println(F("To: rahulraj.2305@gmail.com"));   // change to your address
  client.println(F("From: kavinkumar1543884@gmail.com"));
  client.println(F("Subject: Alert mail from RTHMS\r\n"));
 if(k=='d')
 {Serial.println("drop");
  client.println(F("Alert! your old man is fainted just now at somewhere"));}
  if(k=='s')
  {Serial.println("stand");
  client.println(F("Your old man is fine"));}
//  client.print(ESP.getVcc());
//  client.println(F("mV"));
//  client.print(F("Device ID: "));
//  client.println(ESP.getChipId());
//  Serial.print(F("Voltage"));
//  Serial.print(ESP.getVcc());
  client.println(F("."));
  if (!eRcv()) return 0;
  Serial.println(F("Sending QUIT"));
  client.println(F("QUIT"));
  if (!eRcv()) return 0;
  client.stop();
  Serial.println(F("disconnected"));
  return 1;
}
byte eRcv()
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;
  while (!client.available())
  {
    delay(1);
    loopCount++;     // if nothing received for 10 seconds, timeout
    if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }

  if (respCode >= '4')
  {
    //  efail();
    return 0;
  }
  return 1;
}
