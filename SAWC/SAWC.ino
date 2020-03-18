#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(10, 11, 4, 5, 6, 7);

//const int xpin = A2;                  // x-axis of the accelerometer
//const int ypin = A1;                  // y-axis of the accelerometer
//const int zpin = A0;                    // z-axis of the accelerometer
const int relay1Pin = A4;  //A4 connected to Relay 1
const int relay2Pin = A5;   //A5 connected to Relay 1
const int inpin = A2;
const int inpinn = A1;
const int irPin = 3;
int pinNumber;
int irState = 0;
int inpinstate = 0;
int inpinnstate = 0;
int relay1State = 0;
int relay2State = 0;



SoftwareSerial bluetooth(12, 13); // RX, TX --Bluetooth TX to pin12(RX) - crosspaired

void setup()
{
  pinMode(inpin, INPUT_PULLUP);//defining the pin configuration i.e weather it is a input or output
  pinMode(inpinn, INPUT_PULLUP);
  pinMode(irPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  relay1State = LOW;
  relay2State = LOW;
  digitalWrite(relay1Pin, relay1State);
  digitalWrite(relay2Pin, relay2State);
  Serial.begin(9600);
  bluetooth.begin(9600);
  lcd.begin(16, 2);
  lcd.print("1.MANUAL CONTROL");
  lcd.setCursor(0, 1);
  lcd.print("2.AUTO CONTROL");
  delay(2000);
}

void loop()
{

  //lcd.clear();
  //lcd.print("Checking Data...");

label0:

  inpinstate = digitalRead(inpin);//it will read the pin weather it is high or low
  inpinnstate = digitalRead(inpinn);

  if (inpinstate == LOW)
  {
    lcd.clear();
    lcd.print("Manual Mode....");
    delay(2000);
    goto manualmode;
  }


  if (inpinnstate == LOW)
  {
    lcd.clear();
    lcd.print("Auto Mode....");
    delay(2000);
    goto automode;
  }

  goto label0;


manualmode:
  inpinstate = digitalRead(inpin);
  inpinnstate = digitalRead(inpinn);
  lcd.clear();
  lcd.print("MANUAL CONTROL");
  delay(2000);
    if (inpinnstate == LOW)
  {
    lcd.clear();
    lcd.print("Auto Mode....");
    delay(2000);
    goto automode;
  }
  while (bluetooth.available())  //check if any data received in rx(Pin 0) pin from ESP8266-----
  {
    delay(100);
    if (bluetooth.find("$"))
    {
      delay(100);
      char d = bluetooth.read();
      delay(100);
      lcd.clear();
      lcd.print(d);

      if (d == '1')
      {
        relay1State = HIGH;
        relay2State = HIGH;
        digitalWrite(relay1Pin, relay1State);
        digitalWrite(relay2Pin, relay2State);
        lcd.clear();
        lcd.print(" RELAY IS ON");
        delay(2000);
      }
      if (d == '2')
      {

        relay1State = LOW;
        relay2State = LOW;
        digitalWrite(relay1Pin, relay1State);
        digitalWrite(relay2Pin, relay2State);
        lcd.clear();
        lcd.print(" RELAY IS OFF");
        delay(2000);
      }
    }
  }
goto manualmode;


///////...................................................................................................................................

automode:
  inpinstate = digitalRead(inpin);
  inpinnstate = digitalRead(inpinn);
  lcd.clear();
  lcd.print("AUTO CONTROL");
  delay(2000);
if (inpinstate == LOW)
  {
    lcd.clear();
    lcd.print("Manual Mode....");
    delay(2000);
    goto manualmode;
  }

   irState = digitalRead(irPin);
  
  if (irState == LOW)
  { inpinstate = digitalRead(inpin);
    inpinnstate = digitalRead(inpinn);
   // delay(1000);  
  if (inpinstate == LOW)
  {
    lcd.clear();
    lcd.print("Manual Mode....");
    delay(2000);
    goto manualmode;
  }
    relay1State = LOW;
    relay2State = LOW;
    digitalWrite(relay1Pin, relay1State);
    digitalWrite(relay2Pin, relay2State);
    lcd.clear();
    lcd.println("RELAY IS OFF");
       delay(1000);
  }

  if (irState == HIGH)
  {   inpinstate = digitalRead(inpin);
    inpinnstate = digitalRead(inpinn);
    //delay(1000);  
  if (inpinstate == LOW)
  {
    lcd.clear();
    lcd.print("Manual Mode....");
    delay(2000);
    goto manualmode;
  }
    relay1State = HIGH;
    relay2State = HIGH;
    digitalWrite(relay1Pin, relay1State);
    digitalWrite(relay2Pin, relay2State);
    lcd.clear();
    lcd.println("RELAY IS ON..");
    delay(1000);
  }
  delay(500);
goto automode;

}





/////................................................................
