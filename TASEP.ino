//#include <DHT.h>

//#define DHTPIN 6     // what pin we're connected to
//#define DHTTYPE DHT11   // DHT 22  (AM2302)
//DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
//int chk;
//float hum;  //Stores humidity value
//float temp; //Stores temperature value

// LEDs
long red;
long green;
long blue;


#include <SPI.h>
#include <SD.h>

File myFile;

long lastNow;
long Time;
//---------------------

#define in1 7
#define in2 8
#define button 4
unsigned long ch1;

#define battery 0

void setup() {
 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(button, INPUT);

  pinMode(battery, INPUT);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  red = 255;
  green = 0;
  blue = 255;
  
  Serial.begin(9600);

//--------------
  lastNow = millis();
  Time = 0;

  //dht.begin();

  
  // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  myFile = SD.open("tasep.txt", FILE_WRITE);
  myFile.println("TEMP HUM CH1");
  myFile.close();
//-----------------
  
  
}

void loop() {
  
   analogWrite(A1, red);
   analogWrite(A2, green);
   analogWrite(A3, blue);
   red=rand()*255;
   green=rand()*255;
   blue=rand()*255;  
  ch1 = pulseIn(button, HIGH);
  Serial.println(analogRead(battery)/205.0);


  if((analogRead(battery)/205.0)>2.75){
  
    if ( ch1 < 1200)
  
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
    if( ch1 > 1650)
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
    if( ch1 < 1650 && ch1 > 1200)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
  }else{
          digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
  }

  // -----------------------------------

  Time += millis() - lastNow;
  lastNow = millis();

  if(Time >= 1000)
  {
    Time = 0;

        // if the file opened okay, write to it:
     myFile = SD.open("tasep.txt", FILE_WRITE);
    if (myFile) {
      
      //hum = dht.readHumidity();
      //temp= dht.readTemperature();

      //myFile.println(String(temp) + " " + String(hum) + " " + String(ch1));
      
      myFile.close();
      Serial.println("Writing to file done");
    } 
    else {
      // if the file didn't open, print an error:
      Serial.println("error opening file");
    }
  
  }
}
