/*
   lecture de la trame RFID brute

*/

#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial rfid(8, 9); // RX, TX

int compteur = 0;

void setup() {
  // Open serial communications and wait for port to open:

  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Placez un tag");

  
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("lecture RFID : ASCII (HEXADECIMAL)");

  // set the data rate for the SoftwareSerial port
  rfid.begin(9600);

}

// pendant les horaires d'ouverturew
char arbitre = ;
// en dehors des horaires d'ouverture
char entraineur = ;

void loop() {
  char car;
  
  if (rfid.available()) {
    car = rfid.read();


    if (car == arbitre) {
      
    }
    else if (car == entraineur) {
      
    }
    else {
      
    }

    
    Serial.print(car);
    Serial.print("(");
    Serial.print(car, HEX);
    Serial.print("),");
    compteur++;
    if (compteur == 14) {
      Serial.println();
      compteur = 0;
    }
  }
}
