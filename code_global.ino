#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

int livingroom = 12;
int bedroom = 7;
int diningroom = 8;
int  flamePin = 2;
int  flame;
int pinBuzzer = 9;
int fanPin = 4;
 



SoftwareSerial Bluetooth(0, 1);
char Data;
void sendData(String transmitData){
Bluetooth.println(transmitData);}

void setup(){
    Bluetooth.begin(9600);
    pinMode(livingroom,OUTPUT);
    pinMode(bedroom,OUTPUT);
    pinMode(diningroom,OUTPUT);
    //flamme
    pinMode(flamePin, INPUT);
    //buzzer
    pinMode(pinBuzzer, OUTPUT);
    //fan
    pinMode(fanPin, OUTPUT);    
    
}

void loop(){

//  fan

digitalWrite(fanPin, HIGH); // turn fan on
  delay(5000); // wait 5 seconds
  digitalWrite(fanPin, LOW); // turn fan off
  delay(5000); // wait 5 seconds

//gaz  
 int x= analogRead(A1);//lire output
  
  int y = map(x,0,1023,0,255);
  Serial.println(y);
  if(y <= 249){
    
    Serial.println("safe");
   noTone(pinBuzzer);  // désactiver le buzzer actif arduino
   delay(500);
   Bluetooth.print("Safe, gaz not detected !"); 
  }else if(y> 249 and y<252){
    
    Serial.println("Be careful");
    tone (pinBuzzer, 300); // allume le buzzer actif arduino
   delay(500);
Bluetooth.print("Be careful Gaz leak detected !");    
     
  }else{
    
    Serial.println("danger");
    tone(pinBuzzer, 500); // allume le buzzer actif arduino
   delay(500);
   Bluetooth.print("Gaz detected !"); 
    
  }
 Bluetooth.print("-");   
  //buzzer
//tone (11, 600); // allume le buzzer actif arduino
  // delay(500);
   //tone(11, 900); // allume le buzzer actif arduino
   //delay(500);
   //noTone(11);  // désactiver le buzzer actif arduino
   //delay(500);

//pir
int a = analogRead(A0);
 int b = map(a,0,1023,0,255);
  //int b = digitalRead(7);
  Serial.println(b);
  
  if(b > 100){
    
    Serial.println("Motion detected");  
    //digitalWrite(livingroom,HIGH);
    delay(1000);
    
  }else{
    //digitalWrite(livingroom,LOW);
    delay(1000);
  }
  //led
  
    if(Bluetooth.available()){
        Data=Bluetooth.read();
        if(Data==('4')){
            digitalWrite(livingroom,1);
            sendData("Living Room Light ON");
        }
        if(Data==('1')){
            digitalWrite(livingroom,0);
            sendData("Living Room Light OFF");
        }
        if(Data==('5')){
            digitalWrite(bedroom,1);
            sendData("Bedroom Light ON");
        }
        if(Data==('2')){
            digitalWrite(bedroom,0);
            sendData("Bedroom Light OFF");
        }
        if(Data==('6')){
            digitalWrite(diningroom,1);
            sendData("Dining Room Light ON");
        }
        if(Data==('3')){
            digitalWrite(diningroom,0);
            sendData("Dining Room Light OFF");
        }
        if(Data==('9')){
            digitalWrite(livingroom,1);
            digitalWrite(bedroom,1);
            digitalWrite(diningroom,1);
            sendData("ALL LIGHTS ON");
        }
        if(Data==('0')){
            digitalWrite(livingroom,0);
            digitalWrite(bedroom,0);
            digitalWrite(diningroom,0);
            sendData("ALL LIGHTS OFF");
        }
    }
    //flame
  flame = digitalRead(flamePin);

   Serial.print("Flame Sensor - ");
   Serial.println(flame);

   if (flame == LOW){
      digitalWrite(livingroom, HIGH);
      Bluetooth.print("Flame detected !");      
      
      }
   else{
      digitalWrite(livingroom, LOW);
      Bluetooth.print("Flame not detected !");      
      
}

              
              }
