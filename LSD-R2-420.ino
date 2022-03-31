#include <Wire.h>
#include "Adafruit_TCS34725.h"

int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control
 
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
 
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);
 
void setup(void) 
{
  pinMode(A0, INPUT);   //Front mic
  pinMode(A1, INPUT);   //Right mic
  pinMode(A2, INPUT);   //Rear mic
  pinMode(A3, INPUT);   //Left mic
  pinMode(A5, INPUT);
  int i;
  for (i = 5; i <= 8; i++)
  pinMode(i, OUTPUT);
  Serial.begin(9600);
 
if (tcs.begin()) 
{
Serial.println("Found sensor");
} 
else 
{
Serial.println("No TCS34725 found ... check your connections");
while (1);
} 
}
 
void loop(void) {

float final_value = 50000000;
 float total_iv0 = 0;     //Total integral value so far
 float total_iv1 = 0;     //Total integral value so far
 float total_iv2 = 0;     //Total integral value so far
 float total_iv3 = 0;     //Total integral value so far
 int halfrange = 10000;
 
 while (total_iv0 <  final_value || total_iv1 < final_value || total_iv2 < final_value || total_iv3 < final_value)   //Execute moves until certain sound value is reached
 {
  float signalvalue0;      //1st signal read variable for 1st mic
  float new_sv0;           //2nd signal read variable
  float integral_value0;   //Approximate definite integral value for 1 trapezium
  float t0_0;               //Time of 1st signal read
  float t1_0;               //Time of 2nd signal read
  float t10_0;              //Time difference (h of trapezium)
  int offset0 = 511;
  
  float signalvalue1;      //2nd mic variables
  float new_sv1;
  float integral_value1;
  float t0_1;
  float t1_1;
  float t10_1;
  int offset1 = 511;
  
  float signalvalue2;     //3rd mic variables
  float new_sv2;
  float integral_value2;
  float t0_2;
  float t1_2;
  float t10_2;
  int offset2 = 511;
  
  float signalvalue3;     //4th mic variables
  float new_sv3;
  float integral_value3;
  float t0_3;
  float t1_3;
  float t10_3;
  int offset3 = 511;
   
  int n;
  int sample_no = 5000;
   
  total_iv0 = 0;    
  total_iv1 = 0;     
  total_iv2 = 0;     
  total_iv3 = 0;

  t0_0 = micros();                             //Record time microprocessor has been operating when first signal is read
  signalvalue0 = analogRead(A0);              //Read signal from mic circuit
  
  t0_1 = micros();
  signalvalue1 = analogRead(A1);
  
  t0_2 = micros();
  signalvalue2 = analogRead(A2);
  
  t0_3 = micros();
  signalvalue3 = analogRead(A3);
   
  signalvalue0 = signalvalue0 - offset0;           //Account for offset in read signal value
  if (signalvalue0 <= 0)                      
       {                                        //Convert signal value to positive if negative
        signalvalue0 = signalvalue0 * -1;
       }
  
  signalvalue1 = signalvalue1 - offset1;
  if (signalvalue1 <= 0)
       {
        signalvalue1 = signalvalue1 * -1;
       }
  
  signalvalue2 = signalvalue2 - offset2;
  if (signalvalue2 <= 0)
       {
        signalvalue2 = signalvalue2 * -1;
       }
   
  signalvalue3 = signalvalue3 - offset3;
  if (signalvalue3 <= 0)
       {
        signalvalue3 = signalvalue3 * -1;
       }
  
  for(n = 0; n <= sample_no; n++)      //Execute sound input processing x amount of times
    {                                                  
     t1_0 = micros();                               //Microprocessor time operating when next signal is read
     new_sv0 = analogRead(A0);                      //Read analog signal again

     t1_1 = micros();                              //Repeat for Mic 2
     new_sv1 = analogRead(A1);

     t1_2 = micros();                              // Reapeat for Mic 3
     new_sv2 = analogRead(A2);
     
     t1_3 = micros();                              //Repeat for Mic 4
     new_sv3 = analogRead(A3);
    
     new_sv0 = new_sv0 - offset0;
     if (new_sv0 <= 0)                              //If signal value is negative convert to positive
       {
        new_sv0 = new_sv0 * -1;
        }
     t10_0 = t1_0 - t0_0;                           //Find time difference between when the values were read
     integral_value0 = ((signalvalue0 + new_sv0) / 2) * t10_0; //Use trapezium rule to aprroximate part of the definite integral
     total_iv0 = total_iv0 + integral_value0;        //Add area of this trapezium to total integral value calculated so far
     signalvalue0 = new_sv0;                         //Overwrite first signal value to the value of the second signal read
     t0_0 = t1_0;                                    //Overwrite first time to the value of the second time
    
     new_sv1 = new_sv1 - offset1;
     if (new_sv1 <= 0)
       {
        new_sv1 = new_sv1 * -1;
       }
     t10_1 = t1_1 - t0_1;
     integral_value1 = ((signalvalue1 + new_sv1) / 2) * t10_1;
     total_iv1 = total_iv1 + integral_value1;
     signalvalue1 = new_sv1;
     t0_1 = t1_1;
    
     new_sv2 = new_sv2 - offset2;
     if (new_sv2 <= 0)
       {
        new_sv2 = new_sv2 * -1;
       }
     t10_2 = t1_2 - t0_2;
     integral_value2 = ((signalvalue2 + new_sv2) / 2) * t10_2;
     total_iv2 = total_iv2 + integral_value2;
     signalvalue2 = new_sv2;
     t0_2 = t1_2;
    
     new_sv3 = new_sv3 - offset3;
     if (new_sv3 <= 0)
       {
        new_sv3 = new_sv3 * -1;
       }
     t10_3 = t1_3 - t0_3;
     integral_value3 = ((signalvalue3 + new_sv3) / 2) * t10_3;
     total_iv3 = total_iv3 + integral_value3;
     signalvalue3 = new_sv3;
     t0_3 = t1_3;
   
     }
  
  if (total_iv0 >= total_iv1 && total_iv0 >= total_iv2 && total_iv0 >= total_iv3) //If mic 1 detects a louder sound
  {
      if (total_iv0 >= total_iv1 >= (total_iv0 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate right 45 degrees and then move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 128);
       digitalWrite(M2, 1);
       delay(750);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }
     
      else if (total_iv0 >= total_iv3 >= (total_iv0 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate left 45 degrees and then move forward
       digitalWrite(M1, 1);
       analogWrite (E2, 128);
       digitalWrite(M2, 0);
       delay(750);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }  
      
      else
      {
       analogWrite (E1, 125);        //Move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }
  }
   
   
  else if (total_iv1 >= total_iv0 && total_iv1 >= total_iv2 && total_iv1 >= total_iv3) //If mic 2 detects a louder sound
  {
    
      if (total_iv1 >= total_iv0 >= (total_iv1 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate right 45 degrees and then move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 128);
       digitalWrite(M2, 1);
       delay(750);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }
     
      else if (total_iv1 >= total_iv2 >= (total_iv1 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate right 135 degrees and then move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 128);
       digitalWrite(M2, 1);
       delay(2550);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }  
      
     else
     {
       analogWrite (E1, 128);        //Rotate right 90 degrees and then move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 128);
       digitalWrite(M2, 1);
       delay(1800);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
    }
  }
  else if (total_iv2 >= total_iv0 && total_iv2 >= total_iv1 && total_iv2 >= total_iv3) //If mic 3 detects a louder sound
  {  
      if (total_iv2 >= total_iv1 >= (total_iv2 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate right 135 degrees and then move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 128);
       digitalWrite(M2, 1);
       delay(2550);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }
     
      else if (total_iv2 >= total_iv3 >= (total_iv2 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate left 135 degrees and then move forward
       digitalWrite(M1, 1);
       analogWrite (E2, 128);
       digitalWrite(M2, 0);
       delay(2550);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }  
    
      else
      {
       analogWrite (E1, 130);        //Rotate right 180 degrees and then move forward
       digitalWrite(M1, 0);
       analogWrite (E2, 130);
       digitalWrite(M2, 1);
       delay(3500);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }
  }
  
  else if(total_iv3 >= total_iv0 && total_iv3 >= total_iv1 && total_iv3 >= total_iv2) //If mic 4 detects a louder sound
  {  
     if (total_iv3 >= total_iv0 >= (total_iv3 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate left 45 degrees and then move forward
       digitalWrite(M1, 1);
       analogWrite (E2, 128);
       digitalWrite(M2, 0);
       delay(750);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }
     
      else if (total_iv3 >= total_iv2 >= (total_iv3 - halfrange))
      {
       analogWrite (E1, 128);        //Rotate left 135 degrees and then move forward
       digitalWrite(M1, 1);
       analogWrite (E2, 128);
       digitalWrite(M2, 0);
       delay(2550);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
      }  
    
      else
      {
       analogWrite (E1, 127);        //Rotate left 90 degrees and then move forward
       digitalWrite(M1, 1);
       analogWrite (E2, 127);
       digitalWrite(M2, 0);
       delay(1800);
       analogWrite (E1, 125);        
       digitalWrite(M1, 0);
       analogWrite (E2, 125);
       digitalWrite(M2, 0);
       delay(1500);
       analogWrite (E1, 0);            
       digitalWrite(M1, 0);
       analogWrite (E2, 0);
       digitalWrite(M2, 0);
     }
  }
 }  
  
uint16_t r, g, b, c, colorTemp, lux;
 
tcs.getRawData(&r, &g, &b, &c);
colorTemp = tcs.calculateColorTemperature(r, g, b);
lux = tcs.calculateLux(r, g, b);
 
Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
Serial.println(" ");

while (r<=2000) /*0x7D0*/
{
if (r>= 200)/*0xC8*/ /* Have to check if the b and g values also fluctuate when using the red light to get a more accurate measure*/
{  
Serial.print("This is the direction");
Serial.println(" ");
}
else
{
Serial.print("No red light present"); 
Serial.println(" ");
}
}
}
