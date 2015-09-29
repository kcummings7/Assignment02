unsigned long lastTime = 0UL;
char publishString[64];
int door = D0;
int led = D7;
int visit = 0;
int lastStatus = HIGH;
int photoresistor = A0;
int energy = A5;
int analogValue;
int shine = 0;

/*
 *Author: Katherine Cummings
 *Reads data from the photon's magnetic door senor and photoresistor, lights up the LED when the door is closed, and sends it to the HTML page for interpretation and visualization.
 *Some lines of code have inspiration from examples on the photon forums/tutorials.
*/

void setup(){//assigns duties to the photon's pins
    pinMode(door,INPUT);
    pinMode(led, OUTPUT);
    pinMode(photoresistor,INPUT);
    pinMode(energy, OUTPUT);
    
    digitalWrite(energy,HIGH);
}

void loop(){//loop checks data incoming from the pins
    unsigned long now = millis();
    int status;
    
    status = digitalRead(door);
    analogValue = analogRead(photoresistor);
    
    if (now-lastTime>1000UL) {
        if (status == HIGH){
            digitalWrite(led, HIGH);
            lastStatus = status;
        }
        else{
            digitalWrite(led, LOW);
            if(lastStatus != LOW){
                visit = visit + 1;
            }
            lastStatus = status;
        }
        lastTime = now;
        shine = analogValue;
        
        unsigned nowSec = now/1000UL;
        unsigned sec = nowSec%60;
        unsigned min = (nowSec%3600)/60;
        unsigned hours = (nowSec%86400)/3600;

        sprintf(publishString,"{\"Hours\": %u, \"Minutes\": %u, \"Seconds\": %u, \"Persons\": %u, \"Light\": %u}",hours,min,sec,visit,shine);
        Spark.publish("run",publishString);
    }
}