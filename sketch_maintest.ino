#include <math.h>
#include <Servo.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

//const variables


//sets lcd back color to red
const int colorR = 255; //for LCD Display
const int colorG = 0; //for LCD Display
const int colorB = 0; //for LCD Display

//temperature sensor
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0

//increase and decrease buttons for setting desired temp
const int buttonUPPin = 2;     // the number of the pushbuttonUP pin
const int buttonDownPin = 3;     // the number of the pushbuttonDown pin
const int ledPin =  13;      // the number of the LED pin


const float desiredTempHigh = 80.0; //highest desired value

const float desiredTempLow = 55.5;  //lowest desired value

// variables will change:
int buttonUpState = 0;         // variable for reading the increase pushbutton status
int buttonDownState = 0;      // variable for reading the decrease pushbutton status
bool tempIncrease = false;    // sets state 
bool tempDecrease = false;    // sets state
int desiredTemp = 72.0;       // desired temp value that can be adjusted

int servoPos = 30;            //starting position of servo

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //initial value for temp
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object


   // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonUPPin, INPUT);
     // initialize the pushbutton pin as an input:
    pinMode(buttonDownPin, INPUT);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    //intial LCD's color display:  
    lcd.setRGB(colorR, colorG, colorB);

    delay(1000);

    
}

void loop() {
  // put your main code here, to run repeatedly:

    ///////////////////////TempSensor code/////////////////////////////////////  
    int a = analogRead(pinTempSensor);

    float R = 1023.0/a-1.0;
    R = R0*R;

    float temperature_C = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    float temperature_F = (temperature_C * 9/5) + 32; // convert to degrees Farenheit 
    Serial.print("temperature = ");
    Serial.println(temperature_F);

    delay(100);
    ////////////////////////ServoCode//////////////////////////////////////////
   
   if((temperature_F <= (desiredTemp - 20.0)) || (temperature_F <= (desiredTempLow)) ){
    tempIncrease = true; //temperature should increase if 20 degrees colder than desired temp or hits low threshold
    } 
   else if((temperature_F >= (desiredTemp + 20.0)) || (temperature_F >= (desiredTempHigh)) ){
    tempDecrease = true; //temperature should decrease if 20 degrees hotter than desired temp or hits high threshold
   } 
   else
   {
    //maintain the current temp
    tempIncrease = false; 
    tempDecrease = false;
   }
   
   
   
   if((tempIncrease == true) && (servoPos <= 90))
   {myservo.write(80);
   servoPos = 90; //servo moves switch to off
   delay(45); 
   }
  else if ((tempDecrease == true) && (servoPos >= 15)){
   myservo.write(-20); //servo moves switch to on
   servoPos = 0;
   delay(45);
  }
  else{
    //myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //myservo.write(91); 
    delay(45);                       // waits 45ms for the servo to reach the position
    
  }
    // read the state of the pushbutton value:
    buttonUpState = digitalRead(buttonUPPin);
    buttonDownState = digitalRead(buttonDownPin);
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonUpState == HIGH) {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
        Serial.println("Up button pressed");
        desiredTemp++; //increase desired temp
    }
    else if (buttonDownState == HIGH){
        // turn LED off:
        digitalWrite(ledPin, LOW);
        Serial.println("Down button pressed");
        desiredTemp--; //decrease desired temp
    }
    else
    {
      Serial.println("Neither button pressed");
      }
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 0);
    // print the Desired Temp:
     lcd.print("Desire temp ");
     lcd.setCursor(12,0);
     lcd.print(desiredTemp);
    // print the current temp
     lcd.setCursor(0, 1);
     lcd.print("Room Temp");
     lcd.setCursor(12,1);
     lcd.print(temperature_F);
    delay(100);
}
