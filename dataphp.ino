#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(2, 3); // TX, RX

DFRobotDFPlayerMini myDFPlayer;

#define SS_PIN 8
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
String conteudo;
String line;
String mensagem;

StaticJsonDocument<128> doc;

String url = "GET /mercado.php?uid=";

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192, 168, 0, 100); // numeric IP for Google (no DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 137, 177);
IPAddress myDns(192, 168, 137, 1);

char serverName[] = "www.google.com";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  mySoftwareSerial.begin(9600);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println(F("Inicializando modulo DFPlayer... (3~5 segundos)"));
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("Nao inicializado:"));
    while (true);
  }

  Serial.println(F("Modulo DFPlayer Mini inicializado!"));

  myDFPlayer.setTimeOut(1200); //Timeout serial 500ms
  myDFPlayer.volume(1); //Volume 5
  myDFPlayer.EQ(0); //Equalizacao normal


  Serial.print("Numero de arquivos no cartao SD: ");
  Serial.println(myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD));

 Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to configure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
}

void banco(String st) {
  st.replace(" ", "");

  mensagem = url + st;

  Serial.println(mensagem);

  client.stop();
  if (client.connect(serverName, 80)) {
    Serial.println("Connected to server!");
    //client.setConnectionTimeout(2000);
    //client.println(mensagem);
    while (client.connected()) {
      if (client.available()) {
        line = client.readStringUntil('\r');
        Serial.print(line);
        Serial.println();
        delay(10);
      }
      delay(100);
    }
    client.stop();
  } else {
    Serial.println("Conexão falhou");

  }

  mensagem = "";
  conteudo = "";
}

void loop() {
  delay(1000);

  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  banco(conteudo);

  //Serial.println(line);

  char cline[200];
  line.toCharArray(cline, 200);
  line = "";

  

  Serial.println(cline);
  Serial.println("*" + line + "*");

  DeserializationError error = deserializeJson(doc, cline);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  String d = doc[0][0];
  int id = d.toInt();

  Serial.println(id);

  myDFPlayer.play(id);

  switch (id) {
    case 1:
      myDFPlayer.play(1);
      delay(3000);
      break;
    case 2:
      myDFPlayer.play(2);
      delay(3000);
      break;
    case 3:
      myDFPlayer.play(3);
      delay(3000);
      break;
    case 4:
      myDFPlayer.play(4);
      delay(3000);
      break;
  }

  delay(3000);

}
