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
  float signalvalue__0;      //1st signal read variable for 1st mic
  float new_sv__0;           //2nd signal read variable
  float oldplusnew_sv__0;    //Sum of the 2 signal values
  float integral_value__0;   //Approximate definite integral value for 1 trapezium
  float total_iv__0 = 0;     //Total integral value so far
  float t0__0;               //Time of 1st signal read
  float t1__0;               //Time of 2nd signal read
  float t10__0;              //Time difference (h of trapezium)
  
  float signalvalue__1;      //2nd mic variables
  float new_sv__1;
  float oldplusnew_sv__1;
  float integral_value__1;
  float total_iv__1 = 0;
  float t0__1;
  float t1__1;
  float t10__1;
  
  float signalvalue__2;     //3rd mic variables
  float new_sv__2;
  float oldplusnew_sv__2;
  float integral_value__2;
  float total_iv__2 = 0;
  float t0__2;
  float t1__2;
  float t10__2;
  
  float signalvalue__3;     //4th mic variables
  float new_sv__3;
  float oldplusnew_sv__3;
  float integral_value__3;
  float total_iv__3 = 0;
  float t0__3;
  float t1__3;
  float t10__3;
  int n2;

  t0__0 = micros();                             //Record time microprocessor has been operating when first signal is read
  signalvalue__0 = analogRead(A0);              //Read signal from mic circuit
  if (signalvalue__0 <= 0)                      
       {                                        //Convert signal value to positive if negative
        signalvalue__0 = signalvalue__0 * -1;
       }
  
  t0__1 = micros();
  signalvalue__1 = analogRead(A1);
  if (signalvalue__1 <= 0)
       {
        signalvalue__1 = signalvalue__1 * -1;
       }
  
  t0__2 = micros();
  signalvalue__2 = analogRead(A2);
  if (signalvalue__2 <= 0)
       {
        signalvalue__2 = signalvalue__2 * -1;
       }
  
  t0__3 = micros();
  signalvalue__3 = analogRead(A3);
  if (signalvalue__3 <= 0)
       {
        signalvalue__3 = signalvalue__3 * -1;
       }
  
  for(n2 = 0;n2 <= 1000;n2++)
    {                                                  
     t1__0 = micros();                               //Mic 1
     new_sv__0 = analogRead(A0);
     if (new_sv__0 <= 0)
       {
        new_sv__0 = new_sv__0 * -1;
       }
     oldplusnew_sv__0 = signalvalue__0 + new_sv__0;
     t10__0 = t1__0 - t0__0;
     integral_value__0 = (oldplusnew_sv__0 / 2) * t10__0;
     total_iv__0 = total_iv__0 + integral_value__0;
     signalvalue__0 = new_sv__0;
     t0__0 = t1__0;

     t1__1 = micros();                              //Mic 2
     new_sv__1 = analogRead(A1);
     if (new_sv__1 <= 0)
       {
        new_sv__1 = new_sv__1 * -1;
       }
     oldplusnew_sv__1 = signalvalue__1 + new_sv__1;
     t10__1 = t1__1 - t0__1;
     integral_value__1 = (oldplusnew_sv__1 / 2) * t10__1;
     total_iv__1 = total_iv__1 + integral_value__1;
     signalvalue__1 = new_sv__1;
     t0__1 = t1__1;

     t1__2 = micros();                              //Mic 3
     new_sv__2 = analogRead(A2);
     if (new_sv__2 <= 0)
       {
        new_sv__2 = new_sv__2 * -1;
       }
     oldplusnew_sv__2 = signalvalue__2 + new_sv__2;
     t10__2 = t1__2 - t0__2;
     integral_value__2 = (oldplusnew_sv__2 / 2) * t10__2;
     total_iv__2 = total_iv__2 + integral_value__2;
     signalvalue__2 = new_sv__2;
     t0__2 = t1__2;

     t1__3 = micros();                              //Mic 4
     new_sv__3 = analogRead(A3);
     if (new_sv__3 <= 0)
       {
        new_sv__3 = new_sv__3 * -1;
       }
     oldplusnew_sv__3 = signalvalue__3 + new_sv__3;
     t10__3 = t1__3 - t0__3;
     integral_value__3 = (oldplusnew_sv__3 / 2) * t10__3;
     total_iv__3 = total_iv__3 + integral_value__3;
     signalvalue__3 = new_sv__3;
     t0__3 = t1__3;
     
     delay(10);
     }
  
  if (integral_value__0 >= integral_value__1 && integral_value__0 >= integral_value__2 && integral_value__0 >= integral_value__3)
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
  else if (integral_value__1 >= integral_value__0 && integral_value__1 >= integral_value__2 && integral_value__1 >= integral_value__3)
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
  else if (integral_value__2 >= integral_value__0 && integral_value__2 >= integral_value__1 && integral_value__2 >= integral_value__3)
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
  else if(integral_value__3 >= integral_value__0 && integral_value__3 >= integral_value__1 && integral_value__3 >= integral_value__2)
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
