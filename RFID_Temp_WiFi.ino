#include "WiFiEsp.h"
#include "ThingSpeak.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN); // Create object Instance
MFRC522::MIFARE_Key key; //create variable “key” with MIFARE_Key structure
//MFRC522::StatusCode status;
// Init array that will store new NUID


#define ESP_BAUDRATE 115200
char ssid[] = "EE3070_P1404_1"; // your network SSID (name)
char pass[] = "EE3070P1404"; // your network password

int status = WL_IDLE_STATUS; // the Wifi radio's status
float val, number;
int Pin=A0;
int R = 12, G = 13;
int flag = 0;
String rfid_uid = "";
int Buzz = 8;
unsigned long myTime;

struct record{
  char bank_balance[30];
  char BankAccountNum [30];
  char CreditCardNum [30];
  char Name [30];
  char ContactNum [30];
  char SID [30];
  char Gender [30];
  char Department [30];
  char HomeAddress [30];
};

typedef struct record Record;
Record Yuvraj = {"Bank Bal: 45000","CC No.: 1111222234","123456789","Yuvraj","Contact: +85264305836","SID: 55907774","Male","EE Dept","Address: 804A Hall6"};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiEspClient client;

unsigned long myChannelNumber = 1541801;
const char * myWriteAPIKey = "G5Y0W4F5GJQHQ8EL";

long long a = 0;

void setup()
{
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  
  
  // Init the RFID MFRC522 chip
  
  rfid.PCD_Init(); 
  for (byte i = 0; i < 6; i++)
  {
      key.keyByte[i] = 0xFF;
  }
  
  
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
  
  //Buzzer Setup
  
  pinMode(Buzz, OUTPUT);
  
  //OLED Setup

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  //ESP8266 WiFi Module Setup
  
  // initialize serial for debugging
  Serial1.begin(ESP_BAUDRATE);
  
  // initialize ESP module
  WiFi.init(&Serial1);
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
  }
  while(WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network
    Serial.print(".");
    delay(2000);
  }
  
  Serial.println("\nConnected");
  
  ThingSpeak.begin(client);
  millis();

}

void loop() {

  number = printtemp();
  if (rfid.PICC_IsNewCardPresent()) // Check whether there is PICC card
  {
    if (rfid.PICC_ReadCardSerial()) // Verify if the NUID has been read
    {
        Serial.println(F("The NUID tag is:"));
        Serial.print(F("In hex: "));
        printHex(rfid.uid.uidByte, rfid.uid.size);
        Serial.println();
        Serial.print(F("In dec: "));
        printDec(rfid.uid.uidByte, rfid.uid.size);
  
        //Storing RFID as string
        rfid_uid = "";
        for (int i = 0; i < 4; i++)
        {
            String uid_part = String(rfid.uid.uidByte[i], HEX); 
            rfid_uid += uid_part;
        }
  
        ThingSpeak.setField(1,number); //Setting first field for temperature data
        
        if(rfid_uid.equals("7c132430")) //User Authentication Check
        {
          Serial.println("Matching");
          ThingSpeak.setField(2,"Yuvraj : Authorized User");
          digitalWrite(G, HIGH);
          delay(1000);
          digitalWrite(G, LOW);
          tone(Buzz, 1000, 2000); // Send 1KHz sound signal...
          delay(1000);        // ...for 1 sec
          noTone(Buzz);
          
          display_info(Yuvraj);
        }
        
        else //Unauthorized break-in attempt detected
        
        {
          ThingSpeak.setField(2,"Unknown: Unauthorized");
          Serial.println("UNAUTHORIZED ALERT");
          digitalWrite(R, HIGH);
          delay(1000);
          digitalWrite(R, LOW);
          for(int i=0; i<3; ++i) //trigerring alarm with buzzer
          {
            tone(Buzz, 1000); // Send 1KHz sound signal...
            delay(500);        // ...for 1 sec
            noTone(Buzz);
            tone(Buzz, 2000); // Send 1KHz sound signal...
            delay(500);        // ...for 1 sec
            noTone(Buzz);
          }
          
        }
        
        ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);    //send sensor data to ThingSpeak using the Internet
  
        if(ThingSpeak.getLastReadStatus() == 200)
        {
            Serial.println("Channel update successful.");
        }
        else{
            Serial.println("Problem updating channel. HTTP error code ");
        }
        
        Serial.println();
        rfid.PICC_HaltA();// Halt PICC
        rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    }
  }

  
  if((millis()-a)>60000) //send temperature data to ThingSpeak every 60 seconds
  {
    
      ThingSpeak.setField(1,number);
      ThingSpeak.setField(2,"No RFID");      
      ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
      a = millis();
  
      //CHECK READ STATUS OF CHANNEL     
      
      if(ThingSpeak.getLastReadStatus() == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code ");
      }
  }

}
/**
* Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);
  }
}
/**
* Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {  
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], DEC);
  }
}

float printtemp() //converting analog value read into temperature in degree celcius
{
    val=analogRead(Pin);
    float mv = (val/1024.0)*5000;
    mv=mv/10;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(3,3);
    Serial.print("Temperature in *C :");
    Serial.println(mv);
    display.print("Temperature:");
    display.print(mv); //displaying temperature on OLED display
    display.println("*C ");
    display.display();
    delay(1000);
    return mv;
}

void display_info(Record A) //display data of authrized user from database in Arduino (data stored in a user defined datatype called Record.
{

display.clearDisplay();

display.setTextSize(1);
display.setTextColor(WHITE);

display.setCursor(3,3);

//display private and sensitive data
display.println(A.bank_balance);
display.println(A.BankAccountNum);
display.println(A.Name);
display.println(A.ContactNum);
display.println(A.SID);
display.println(A.HomeAddress);

//display temperature
display.print("Temperature: ");
display.print(number);
display.println(" *C ");

display.display();
delay(6000); //display information for 6 seconds using delay

display.clearDisplay();
display.display(); //clear OLED screen
}
