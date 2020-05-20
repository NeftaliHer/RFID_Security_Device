/*Name: Neftali Hernandez
  Team Members: Neftali Hernandez
  Description: Receiving cloud commands being sent by ARGON device. Using RGB Led to confirm
  whether RFID tag is valid (Green) or invalid(Red)


*/

// RGB LED Pins on RPI Model 3 being used
const int redPin = D1;
const int greenPin = D2;
const int bluePin = D3;
const int buzzer = D0;


void setup() {
    // RGB LED set up. Output pins
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    // Buzzer set up pin
    pinMode(buzzer, OUTPUT);
    
    
    Particle.subscribe("NeftaliHer/RFID_ID", cloudEventHandler, MY_DEVICES);
    
    //Serial.begin(9600);
}

void loop() {
    // analogWrite(redPin, 0);
    // analogWrite(greenPin,0);
    // analogWrite(bluePin, 0);
    digitalWrite(greenPin, 0);
    digitalWrite(redPin, 148);
    digitalWrite(bluePin, 211);

}

void cloudEventHandler(const char* event, const char* data)
{
    //In here I would call LCD screen with access denied or accepted with RGB Backlight
    String dataStr = String(data);
    if(dataStr == "464538AA86481" || dataStr == "DE8A816A"){
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        //Serial.println("Access Granted");
        // analogWrite(redPin, 0);
        // analogWrite(greenPin,255);
        // analogWrite(bluePin, 0);
        delay(2500);
    }else if(dataStr != "464538AA86481" && dataStr != "DE8A816A"){
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        // Playing alarm sounds for incorrect
        for(int i=0;i<3;i++){
            digitalWrite(buzzer, 90000);
            delay(200);
            digitalWrite(buzzer,0);
            delay(100);
            digitalWrite(buzzer, 10000);
            delay(300);
        }
        delay(1500);
    }

}