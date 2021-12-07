int trig=9; int echo=11; double duration;
int buzz=8;
float val;
int Pin=A0;
int flag = 0;

int Buzz = 8;

const int ldrPin = A0; //Light Dependent Resistor (LDR) Pin
const int ledPin = 4; //Led relay Pin
const int fanPin = 12; //Fan relay Pin
float number;
int tempPin=A1;
String btstring; //to read string sent via bluetooth app
int t =-1; // to convert btstring to integer





long long a = 0;
//long long b;

void setup()
{
  Serial.begin(115200);
  
  //Buzzer Setup
  
  pinMode(Buzz, OUTPUT);

  //LED Setup

  pinMode(ledPin, OUTPUT); // Relay pin for LED Setup (ledPin = 5)
  pinMode(ldrPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(6, OUTPUT); //PWM Pin for LED


  //Fan Setup
  pinMode(fanPin, OUTPUT); // Relay pin for LED Setup (fanPin = 7)
  pinMode(2, OUTPUT); //PWM Pin for FAN
  
  
  //Bluetooth Setup
  
  Serial2.begin(9600);
  
  //Ultrasonic Setup
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(buzz,OUTPUT);


}

void Lamp_control()
{
  int ldrStatus = analogRead(ldrPin);
  Serial.print(ldrStatus);
  Serial.print("\n");
  if (ldrStatus <= 30)
  {
    analogWrite(2,1023);
    Serial.println(ldrStatus);
  }

  else if (ldrStatus > 30 && ldrStatus <200)
  {
    analogWrite(2,900);
    Serial.println(ldrStatus);
  }

  else if (ldrStatus > 200 && ldrStatus < 350  )
  {
    analogWrite(2,800);
    Serial.println(ldrStatus);
  }
  else if ( ldrStatus >350 && ldrStatus <600 )
  {
    analogWrite(2,450);
    Serial.println(ldrStatus);
  }
 else if(ldrStatus>=600)
 {
   analogWrite(2,10);
 }
//  delay(500);
}


void Fan_control(float temp)
{
  if(temp>29)
   {
    analogWrite(3,1023);
   }
  else if(temp>26)
   {
    analogWrite(3,900);
   }
   else
   {
     analogWrite(3,875);
   }
}
float printtemp()
{
  val=analogRead(tempPin);
  float mv = (val/1024.0)*5000;
  mv=mv/10;
  // Serial.print("Temperature in *C :");
  // Serial.println(mv);
  delay(1000);
  return mv;
}

void loop() {

  number = printtemp();

  // put your main code here, to run repeatedly:
  digitalWrite(trig,LOW);
  delayMicroseconds(2); 
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  double d=(double)(duration*0.0340)/2.0;
  
  // if(d<35 && d>15)
  // {
  //   tone(buzz, 100); // Send 1KHz sound signal...
  //   delay(1000);        // ...for 1 sec
  //   noTone(buzz);     // Stop sound...
  //   delay(1000);        // ...for 1sec
  // }
   if (d<20)
{
  tone(buzz, 400, 500); //the buzzer emit sound at 400 Hz for 500 millis
  delay(500); //wait 500 millis
  tone(buzz, 650, 500); //the buzzer emit sound at 650 Hz for 500 millis
  delay(500); //wait 500 millis  
  Serial.print("distance:");
  Serial.println(d);
}
  
  if(Serial2.available())
  {
    btstring = Serial2.readString();
    Serial.println(btstring);
    t = btstring.toInt();
    //A = String(btstring);
  
    if(t==1) //both on
    {
      Serial.println(t);
      digitalWrite(ledPin, HIGH);
      digitalWrite(fanPin, HIGH); 
      // while(t==1)
      // {
      //Lamp_control();
          
      // }
    }
    if(t== 0) //both off
    {
      Serial.println(t);
      digitalWrite(ledPin, LOW);    
      analogWrite(6,0);
      digitalWrite(fanPin, LOW);    
      analogWrite(7,0);
    }
    if(t== 2) // f on, led off
    {
      Serial.println(t);
      
      digitalWrite(fanPin, HIGH); 
      digitalWrite(ledPin, LOW);    
      analogWrite(6,0); 
      // number=printtemp();  
      // Fan_control(number);
    }
    if(t==3) // f off, led on
    {
      Serial.println(t);
      digitalWrite(ledPin, HIGH);
      digitalWrite(fanPin, LOW); 
      analogWrite(7,0);
    }
  }
if(t==1)  
{
  number=printtemp(); 
  Serial.print("Temp: ");
  Serial.print(number);
  Serial.print('\n');
  Fan_control(number);
  Lamp_control();  

}
if(t==2)
{
  number=printtemp();  
  Serial.print(number);
  Fan_control(number);
}
if(t==3)
{
  Lamp_control();   
}
}





// void loop() {
//   // put your main code here, to run repeatedly:
//   digitalWrite(trig,LOW);
//   delayMicroseconds(2); 
//   digitalWrite(trig,HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trig,LOW);
//   duration=pulseIn(echo,HIGH);
//   double d=(double)(duration*0.0340)/2.0;
  
//   if(d<35 && d>15)
//   {
//     tone(buzz, 100); // Send 1KHz sound signal...
//     delay(1000);        // ...for 1 sec
//     noTone(buzz);     // Stop sound...
//     delay(1000);        // ...for 1sec
//   }
// if (d<15)
// {
// tone(buzz, 400, 500); //the buzzer emit sound at 400 MHz for 500 millis
//   delay(500); //wait 500 millis
//   tone(buzz, 650, 500); //the buzzer emit sound at 650 MHz for 500 millis
//   delay(500); //wait 500 millis  
//   Serial.print("distance:");
//   Serial.println(d);
// }
 

// }



