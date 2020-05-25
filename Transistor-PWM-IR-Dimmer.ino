#include "IRremote.h"

IRrecv irrecv(12);                                                         // IR sensor PIN
#define PIN_G 10                                                           // Gate PIN

byte pwm = 125;                                                            // value pwm at first power on after restart (0 - 255)                                                       
int ind = 0;                                                               // ind - powers indicator;
uint32_t val;                                                              // box for "results.value" for IR sensor

decode_results results;

void setup() {
      Serial.begin(9600);                                                   // speed of COM port 
      irrecv.enableIRIn();                                                  // waiting signal
  }

void loop() {
      
       
       if ( irrecv.decode( &results )) {                                     // if the signal came
        Serial.println( results.value, HEX );                                // translate in the COM port

      val = results.value;                                                   // remember the pressed button
     
     if (val == 0x55AA38C7){                                                 // if pressed button "Power"
           
           if(ind == 0){                                                     // if light turn off
            for(int i = 0; i <= pwm; i++)analogWrite(PIN_G, i), delay(10);   // smooooothly turn of the light
            ind = 1;                                                         // remember that the light is on
            delay(300);                                                      // anti-short-press 
            }
           
           
           else{
            for(int i = pwm; i >= 0; i--) analogWrite(PIN_G, i), delay(5);   // smoothly extingush the light
            ind = 0;                                                         // remember that the light is off
            delay(300);                                                      // anti-short-press 
            }
       }
       
     if(val == 0x55AAD02F && pwm != 0 && pwm > 10 && ind == 1){              // if pressed button"-"
            pwm -= 5;                                                        // step down
            analogWrite(PIN_G, pwm);
            }


     if(val == 0x55AA50AF && pwm < 255 && ind == 1){                         // if pressed button +
            pwm += 5;                                                        // step up
            analogWrite(PIN_G, pwm);                                       
            }

     

    irrecv.resume();                                                         // wating the next command 
    }
}



 
