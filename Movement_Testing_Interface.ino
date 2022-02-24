int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control
void setup(void)
{
  int i;
  for (i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
}
void loop(void)
{
  int rightspeed = 0;    /*Setting all variables to zero for when the program loop*/
  int leftspeed = 0;
  int rightdirection = 0;
  int leftdirection = 0;
  int delay_time = 0;

  Serial.println("Enter Right Motor Direction (0 for forward or 1 for reverse):\n");  /*Asking user for input in Serial Monitor*/
  while (Serial.available() == 0){}      /*Wait for user input*/
  rightdirection = Serial.parseInt();    /*Read user input value*/
  Serial.println(rightdirection);
    while (Serial.available() > 0) {     /*Reset value in serial monitor*/
    Serial.read();
  }

  Serial.println("Enter Left Motor Direction (0 for forward or 1 for reverse):\n");
  while (Serial.available() == 0){}
  leftdirection = Serial.parseInt();
  Serial.println(leftdirection);
  while (Serial.available() > 0) {
    Serial.read();
  }
  
  Serial.println("Enter Right Motor Speed (0 to 255):\n");
  while (Serial.available() == 0){}
  rightspeed = Serial.parseInt();
  Serial.println(rightspeed);
  while (Serial.available() > 0) {
    Serial.read();
  }

  Serial.println("Enter Left Motor Speed (0 to 255):\n");
  while (Serial.available() == 0){}
  leftspeed = Serial.parseInt();
  Serial.println(leftspeed);
  while (Serial.available() > 0) {
    Serial.read();
  }
  
  Serial.println("Enter the time the robot should move for (ms):\n");
  while (Serial.available() == 0){}
  delay_time = Serial.parseInt();
  Serial.println(delay_time);
  while (Serial.available() > 0) {
    Serial.read();
  }

  analogWrite (E1, leftspeed);        /*Deploy user inputs to robot to make it move*/
  digitalWrite(M1, leftdirection);
  analogWrite (E2, rightspeed);
  digitalWrite(M2, rightdirection);
  delay(delay_time);

  analogWrite (E1, 0);            /*Stop the robot*/
  digitalWrite(M1, 0);
  analogWrite (E2, 0);
  digitalWrite(M2, 0);
  delay(500);
}
