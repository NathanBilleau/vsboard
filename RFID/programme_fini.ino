#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>
#include <DS3232RTC.h> //http://github.com/JChristensen/DS3232RTC
#include <Time.h>

#include <RTClib.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial rfid(8, 9); // RX, TX
Adafruit_INA219 ina219;
RTC_DS3231 rtc;

#define RELAIS 7     //Broche du relais
#define SYNC   13    // SYNC pin, actif au NL10

tmElements_t tm;     // ?

void setup() {

  lcd.begin();       //Initialisation de l'écran LCD
  lcd.setCursor(0, 1);    //Mettre le curseur à x=0 et y=1
  lcd.print("Tag : ");
  ina219.begin();
  Serial.begin(57600);// Initialisation de la liaison série
  uint32_t currentFrequency;
  pinMode(SYNC, OUTPUT);  // ?
  digitalWrite(SYNC, LOW); //?
  pinMode(RELAIS, OUTPUT);     //Mettre la broche RELAIS (7) en sortie

  rfid.begin(9600);        //Initialisation de la liaison du RFID
  majRtc();                // reset horloge


}


String arbitre = "820059DC696E";    // Tag arbitre
String entraineur = "820059FB1E3E";   // Tag entraineur
int majRTC;     // Déclare une variable int qui permet de reset l'horloge
String rfidTag; // Déclare une variable String qui Stocke le rfid Tag qui vient d'être scanner
String ancienBadge;  //Déclare une variable String qui Stocke l'ancien badge pour éviter une répétition
int refresh = 0;  //Déclare une variable int qui empêche la répetition de la lecture
bool etatPanneau = false;
String trame_pross_H;
String trame_pross_M;
String trame_pross_S;
String trame_pross_D;
String trame_pross_Mo;
String trame_pross_Y;



void afficherDate() //Fonction pour afficher l'heure
{
  String Months[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};
  String actualMonth = Months[tm.Month - 1].substring(0, 3);
  int actualYear = 1970 + tm.Year;

  lcd.setCursor (0, 0);
  lcd.print((String) tm.Day + " " + actualMonth + " " + actualYear);
  lcd.setCursor(0, 1);

  if (tm.Hour < 10) {
    lcd.print("0");
  }
  lcd.print(tm.Hour);
  lcd.print(":");
  if (tm.Minute < 10) {
    lcd.print("0");
  }
  lcd.print(tm.Minute + 1);
  lcd.print(":");
  if (tm.Second < 10) {
    lcd.print("0");
  }
  lcd.print((String)tm.Second + "       ");

}

void relaisLow()  //Fonction pour mettre le relais au niveau logique 0 (Contact fermé)
{
  digitalWrite(RELAIS, LOW);
}


void majRtc()
{
  relaisLow();

  trame_pross_H = Serial.readStringUntil(',');
  trame_pross_M = Serial.readStringUntil(',');
  trame_pross_S = Serial.readStringUntil(',');
  trame_pross_D = Serial.readStringUntil(',');
  trame_pross_Mo = Serial.readStringUntil(',');
  trame_pross_Y = Serial.readStringUntil(10);

  time_t t;

  tm.Month = trame_pross_Mo.toInt();
  tm.Day = trame_pross_D.toInt();
  tm.Hour = trame_pross_H.toInt();
  tm.Minute = trame_pross_M.toInt();
  tm.Second = trame_pross_S.toInt();
  t = makeTime(tm);
  // RTC.set(t);        //use the time_t value to ensure correct weekday is set
  setTime(t);
}


void rfidAfficher(String text) //Affiche les personne passant le badge
{
  lcd.setCursor(0, 1);
  lcd.print("Tag :             ");
  lcd.setCursor(0, 1);
  lcd.print("Tag : ");
  lcd.print(text);
}


void panneauSwitch() {
  if (etatPanneau) {
    digitalWrite(RELAIS, LOW);
  }
  else {
    digitalWrite(RELAIS, HIGH);
  }

  etatPanneau = !etatPanneau;
}


void panneauEteindre() {
  digitalWrite(RELAIS, LOW);
  etatPanneau = false;
}

void mesureCurrent ()
{
  String trame;
  float current_mA = 0;
  int tension = 12;


  current_mA = ina219.getCurrent_mA();

  float power_W = tension * (current_mA / 1000);
  lcd.setCursor (0, 0);
  lcd.print ("                                ");
  lcd.setCursor (0, 1);
  lcd.print ("                                ");
  lcd.setCursor (0, 0);
  lcd.print ("Puissance :" + (String)power_W + "W");
  lcd.setCursor (0, 1);
  lcd.print ((String)current_mA + "mA" + "    " + (String)tension + "V");


  trame = ("$" + (String)tension  + ";" + (String)current_mA + ";" + (String)power_W + ";" + "\n");
  Serial.print (trame);


  delay(1000);
}

void loop() {

  digitalWrite(SYNC, HIGH);   // ?
  RTC.read(tm);               //Lis les données fournis par le module RTC
  digitalWrite(SYNC, LOW);    // ?
  if (etatPanneau)
    mesureCurrent();
  else
  {
  lcd.setCursor (12,0);
   lcd.print ("                         ");
  
    afficherDate();
  }
  if (rfid.available())       //Vérifie si la liaison du rfid est disponible
  {
    rfidTag = rfid.readStringUntil(03);  //Lis jusqu'au charactère '03' en ASCII
    refresh++;  //Incrémente la variable refresh toutes les secondes


    if ((ancienBadge != rfidTag || refresh > 3) && rfidTag.length() == 13)  //Vérifie si l'ancien badge est différent que le badge scanné ou si la variable refresh est superieur à 3 et que la longeur du rfidTag ne dépasse 12 caractère
    {
      refresh = 0;  //Stocke 0 dans la variable refresh
      ancienBadge = rfidTag;



      if (rfidTag.equals(entraineur))//Si le Tag est celui de l'arbitre alors ...
      {
        panneauSwitch();
        rfidAfficher("Entraineur");
        delay(750);
        rfidAfficher("Autorise");
      }

      else if (rfidTag.equals(arbitre)) //Si le Tag est celui de l'entraineur alors ...
      {

        if ( tm.Hour >= 16 && tm.Hour < 20)

        {
          panneauSwitch();
          rfidAfficher("Arbitre");
          delay(750);
          rfidAfficher("Autorise");
        }
        else {
          rfidAfficher("Arbitre");
          delay(750);
          rfidAfficher("Erreur");
        }
      }
      else //Si le Tag n'est ni celui de l'arbitre ni l'entraineur alors ...
      {
        rfidAfficher("Rejete");
      }
      delay(1000); // delay de 1s avant d'effacer le panneau
      rfidTag = " ";  //Rénitialise la variable rfidTag
    }
  }
}

