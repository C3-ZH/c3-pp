int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control
void setup(void)
{
  pinMode(A0, INPUT);   //Enabling analog input pins for microphones
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  int i;                      //Enabling digital pins for output to motors
  for (i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop(){
 
 int n1;
 for (n1 = 0; n1 <= 3; n1++)
 {
  float signalvalue0;      //1st signal read variable for 1st mic
  float new_sv0;           //2nd signal read variable
  float oldplusnew_sv0;    //Sum of the 2 signal values
  float integral_value0;   //Approximate definite integral value for 1 trapezium
  float total_iv0 = 0;     //Total integral value so far
  float t0_0;               //Time of 1st signal read
  float t1_0;               //Time of 2nd signal read
  float t10_0;              //Time difference (h of trapezium)
  
  float signalvalue1;      //2nd mic variables
  float new_sv1;
  float oldplusnew_sv1;
  float integral_value1;
  float total_iv1 = 0;
  float t0_1;
  float t1_1;
  float t10_1;
  
  float signalvalue2;     //3rd mic variables
  float new_sv2;
  float oldplusnew_sv2;
  float integral_value2;
  float total_iv2 = 0;
  float t0_2;
  float t1_2;
  float t10_2;
  
  float signalvalue3;     //4th mic variables
  float new_sv3;
  float oldplusnew_sv3;
  float integral_value3;
  float total_iv3 = 0;
  float t0_3;
  float t1_3;
  float t10_3;
  int n2;

  t0_0 = micros();                             //Record time microprocessor has been operating when first signal is read
  signalvalue0 = analogRead(A0);              //Read signal from mic circuit
  if (signalvalue0 <= 0)                      
       {                                        //Convert signal value to positive if negative
        signalvalue0 = signalvalue0 * -1;
       }
  
  t0_1 = micros();
  signalvalue1 = analogRead(A1);
  if (signalvalue1 <= 0)
       {
        signalvalue1 = signalvalue1 * -1;
       }
  
  t0_2 = micros();
  signalvalue2 = analogRead(A2);
  if (signalvalue2 <= 0)
       {
        signalvalue2 = signalvalue2 * -1;
       }
  
  t0_3 = micros();
  signalvalue3 = analogRead(A3);
  if (signalvalue3 <= 0)
       {
        signalvalue3 = signalvalue3 * -1;
       }
  
  for(n2 = 0;n2 <= 500;n2++)
    {                                                  
     t1_0 = micros();                               //Mic 1
     new_sv0 = analogRead(A0);
     if (new_sv0 <= 0)
       {
        new_sv0 = new_sv0 * -1;
       }
     oldplusnew_sv0 = signalvalue0 + new_sv0;
     t10_0 = t1_0 - t0_0;
     integral_value0 = (oldplusnew_sv0 / 2) * t10_0;
     total_iv0 = total_iv0 + integral_value0;
     signalvalue0 = new_sv0;
     t0_0 = t1_0;

     t1_1 = micros();                              //Mic 2
     new_sv1 = analogRead(A1);
     if (new_sv1 <= 0)
       {
        new_sv1 = new_sv1 * -1;
       }
     oldplusnew_sv1 = signalvalue1 + new_sv1;
     t10_1 = t1_1 - t0_1;
     integral_value1 = (oldplusnew_sv1 / 2) * t10_1;
     total_iv1 = total_iv1 + integral_value1;
     signalvalue1 = new_sv1;
     t0_1 = t1_1;

     t1_2 = micros();                              //Mic 3
     new_sv2 = analogRead(A2);
     if (new_sv2 <= 0)
       {
        new_sv2 = new_sv2 * -1;
       }
     oldplusnew_sv2 = signalvalue2 + new_sv2;
     t10_2 = t1_2 - t0_2;
     integral_value2 = (oldplusnew_sv2 / 2) * t10_2;
     total_iv2 = total_iv2 + integral_value2;
     signalvalue2 = new_sv2;
     t0_2 = t1_2;

     t1_3 = micros();                              //Mic 4
     new_sv3 = analogRead(A3);
     if (new_sv3 <= 0)
       {
        new_sv3 = new_sv3 * -1;
       }
     oldplusnew_sv3 = signalvalue3 + new_sv3;
     t10_3 = t1_3 - t0_3;
     integral_value3 = (oldplusnew_sv3 / 2) * t10_3;
     total_iv3 = total_iv3 + integral_value3;
     signalvalue3 = new_sv3;
     t0_3 = t1_3;
     
     delay(10);
     }
  
  if (integral_value0 <= integral_value1 && integral_value0 <= integral_value2 && integral_value0 <= integral_value3)
  {
      analogWrite (E1, 255);        //Move forward if mic0 has highest integral value
      digitalWrite(M1, 0);
      analogWrite (E2, 255);
      digitalWrite(M2, 0);
      delay(500);
      analogWrite (E1, 0);            
      digitalWrite(M1, 0);
      analogWrite (E2, 0);
      digitalWrite(M2, 0);
  }
  else if (integral_value1 <= integral_value0 && integral_value1 <= integral_value2 && integral_value1 <= integral_value3)
  {
      analogWrite (E1, 255);        //Rotate right 90 degrees and then move forward if mic1 has highest integral value
      digitalWrite(M1, 1);
      analogWrite (E2, 255);
      digitalWrite(M2, 0);
      delay(500);
      analogWrite (E1, 255);        
      digitalWrite(M1, 0);
      analogWrite (E2, 255);
      digitalWrite(M2, 0);
      delay(500);
      analogWrite (E1, 0);            
      digitalWrite(M1, 0);
      analogWrite (E2, 0);
      digitalWrite(M2, 0);
  }
  else if (integral_value2 <= integral_value0 && integral_value2 <= integral_value1 && integral_value2 <= integral_value3)
  {
      analogWrite (E1, 255);        //Rotate right 180 degrees and then move forward if mic2 has highest integral value
      digitalWrite(M1, 1);
      analogWrite (E2, 255);
      digitalWrite(M2, 0);
      delay(1000);
      analogWrite (E1, 255);        
      digitalWrite(M1, 0);
      analogWrite (E2, 255);
      digitalWrite(M2, 0);
      delay(500);
      analogWrite (E1, 0);            
      digitalWrite(M1, 0);
      analogWrite (E2, 0);
      digitalWrite(M2, 0);
  }
  else if(integral_value3 <= integral_value0 && integral_value3 <= integral_value1 && integral_value3 <= integral_value2)
  {
      analogWrite (E1, 255);        //Rotate left 90 degrees and then move forward if mic3 has highest integral value
      digitalWrite(M1, 0);
      analogWrite (E2, 255);
      digitalWrite(M2, 1);
      delay(500);
      analogWrite (E1, 255);        
      digitalWrite(M1, 0);
      analogWrite (E2, 255);
      digitalWrite(M2, 0);
      delay(500);
      analogWrite (E1, 0);            
      digitalWrite(M1, 0);
      analogWrite (E2, 0);
      digitalWrite(M2, 0);
  }
 }  
}
