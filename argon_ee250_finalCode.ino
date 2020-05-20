/*
 * Project rfid_code_Argon
 * Description: RFID Reader and writer(RFID-RC522) using Particle Argon + Pushing info to the cloud.
 *              Essentially this code logs all the 13.6 MHz rfid tags that get swiped on the RC522
 *              RFID reader. Pushes it to Particle Cloud for storage.  
 * Author: Neftali Hernandez
 * Date: May 06, 2020
 * Team Members: Neftali Hernandez
 */
#include "MFRC522.h"

const int SDA_PIN = D3; //SS_Pin in documentation forums
const int RST_PIN = D2;
const int Button_Switch = D6;

// Creates MFRC522 object instance
MFRC522 rfid(SDA_PIN, RST_PIN);


void setup() {
  //To set up serial communication and print to screen on VSCode
  Serial.begin(9600);
  // ---------------------------------
  //So will subscribe to the same event I am publishing to here for Serial printing purposes
  Particle.subscribe("NeftaliHer/RFID_ID", eventHandler, MY_DEVICES);
  //----------------------------------
  pinMode(Button_Switch, INPUT);
  
  //Header file initializes pins as Output input
  rfid.setSPIConfig();
  rfid.PCD_Init();
  Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  // Using a button to start reading. Was going to provide an override option by
  // clicking the button but ran out of time
  int buttonRead = digitalRead(Button_Switch);

  if (buttonRead == 0)
  {
    // THEN JUST READING CARD
    //Look for new cards
    if(!rfid.PICC_IsNewCardPresent()){
      return;
    }
    //Select one of the cards
    if(!rfid.PICC_ReadCardSerial()){
      return;
    }

    //Serial Monitor Data printed to Particle from pages of PICC to determine chip running
    rfid.PICC_DumpToSerial(&(rfid.uid));

    String idNum = "";
    //Turning UID bytes to hex
    for (byte i = 0; i < rfid.uid.size; i++) {
      // Create a RFID Hexdecimal String by adding and converting the binary
      idNum += String(rfid.uid.uidByte[i], HEX);
    }
    // Convert to Uppercase
    //idNum now has tag ID we want
    idNum.toUpperCase();
    // Print the RFID id
    Serial.println("RFID Tag ID Num: " + idNum);

    if(idNum.length() > 0){
      Serial.println(".....");
      Serial.println("Tag ID Valid");
      Serial.println("->Publishing Tag ID Number to the cloud");
      //Publishing private events to my devices
      Particle.publish("NeftaliHer/RFID_ID", idNum, PRIVATE);
    }

    // Reset Id
    idNum = "";
    Serial.println();
    // Stop the reading after one tap
    rfid.PICC_HaltA();
    // Exit the PCD from authenticated state.
    // This will allow new communications to start.
    rfid.PCD_StopCrypto1();
    
    //Ask for next rfid tag
    Serial.println("Please wait");
    delay(2500);
    Serial.println("Scan PICC to see UID and type...");
  }
}

// When we get data from cloud when publishing this function is called
void eventHandler(const char* event, const char* data)
{
  String sentMail = String(data);
  Serial.println(" ");
  if(sentMail == "DE8A816A")
  {
    String userName = "Neftali Hernandez";
    Serial.println("* * * Receiving Data from cloud * * *");
    Serial.println("ACCESS GRANTED");
    Serial.println("Welcome, " + userName);
  }
  else if(sentMail == "464538AA86481")
  {
    String userName = "Bhaskar";
    Serial.println("* * * Receiving Data from cloud * * *");
    Serial.println("ACCESS GRANTED");
    Serial.println("Welcome, Professor " + userName);
  }
  else{
    Serial.println("!ACCESS DENIED!");
  }

}