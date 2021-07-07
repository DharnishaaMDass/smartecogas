#include <DHT.h>                                      //Declarate DHT Library
#include <ESP8266WiFi.h>                              //Declarate ESP8266 Board Library
#include <BlynkSimpleEsp8266.h>
#define DHTPIN 14    //D5 of NodeMCU is GPIO14
//#define DHTPIN 5                                      //Pin of DHT 22
#define DHTTYPE DHT11                                 //Type of DHT

                                      
DHT dht(DHTPIN, DHTTYPE);                             //Declarate dht

int val = 0;                                          //Declarate val variable
const int buzzpin = 4; // select the pin for the red LED
int greenpin = 2 ;// select the pin for the green LED
int bluepin = 13; // select the pin for the blue LED
 
char auth[] = "4Sy3fwXd7hewLrqfZT7QiCuDoskbYek-";                 //Put your blink token
char ssid[] = "SP";                                             //Put your SSID of your connection
char pass[] = "dancenow77";                            //Put your Password of your connection
 
void setup() { 
  Serial.begin(9600);
  Serial.print("Smart ECO Gas");
  pinMode(buzzpin, OUTPUT);
  Blynk.begin(auth, ssid, pass);                      //Connect the blynk to esp8266 board                          
  dht.begin();                                        //Start DHT sensor 
  //delay(10000);                                             
}

void loop() {
  Blynk.run();                                       //Run the Blynk 
  Serial.print("Smart ECO Gas"); 
  digitalWrite(bluepin, HIGH);                                                                            
  float h = dht.readHumidity();                       //Read humidity and put it in h variable
  Serial.print(h,1);
  Serial.print("\n");                            
  float t = dht.readTemperature();                    //Read temperature and put it in t variable
  Serial.print(t,1);
  Serial.print("\n");                          
  float q = analogRead(A0);                           //Read air quality and put it into q variable
  float p = q-150;  
  Serial.print(p,1);
  Serial.print("\n");                                  
  Blynk.virtualWrite(V5, t);                          //Send t value to blynk in V5 virtual pin                                 
  Blynk.virtualWrite(V6, h);                          //Send h value to blynk in V6 virtual pin                                 
  Blynk.virtualWrite(V0, p);                          //Send q value to blynk in V0 virtual pin        
   
   if (p > 90)
  {
    Blynk.notify(" Yellow Zone : Please clean your area, air quality alert !!");     //Blynk will send notify if q>70
    digitalWrite(greenpin, HIGH);
    delay(1000);
    }
    else if (p >= 100 && p <= 300)
  {
       digitalWrite(buzzpin, HIGH);
       delay(500);
       digitalWrite(buzzpin, LOW);
       delay(500);  
    digitalWrite(greenpin, HIGH);
    Blynk.notify(" Orange Zone : Environment air quality is severe, please take action !!");     //Blynk will send notify if q>70

    }
   else if (p > 300)
  {
    digitalWrite(bluepin, HIGH);
    Blynk.notify(" Red Zone : Environment is not safe, High level of  NH3/NO2/MH4/CO2 detected.  !!");     //Blynk will send notify if q>70   
    }
  else if (t>40) {
    Blynk.notify("Emergency Alert : High temperature detected , Fire may occur");      //Blynk will send notify if t>40
    delay(1000);
  }
  delay(10000);
  digitalWrite(bluepin, LOW);
  digitalWrite(buzzpin, LOW); 
  digitalWrite(greenpin, LOW);   
}
