#include<SoftwareSerial.h>
#include <Servo.h>
Servo myservo; 
int pos = 0;   
SoftwareSerial BT(10,11);
String state;
int count=0;
  int x=0;
void setup()
{
BT.begin(9600);
Serial.begin(9600);
  myservo.attach(9); 
myservo.write(15); 
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(6,OUTPUT);
}
void home_auto(String state)
{
  int flag=0;
  if(state=="light on")
  flag=1;
  else if(state=="light off")
  flag=2;
  else if(state=="TV on")
  flag=3;
  else if(state=="TV off")
  flag=4;
  else if(state=="cool")
  flag=5;
  else if(state=="hot")
  flag=6;
  switch(flag)
  {
    case 1:digitalWrite(13,HIGH);break;
    case 2:digitalWrite(13,LOW);break;
    case 3:digitalWrite(12,HIGH);break;
    case 4:digitalWrite(12,LOW);break;
    case 5:digitalWrite(6,HIGH);break;
    case 6:digitalWrite(6,LOW);break;
    }
  count=0;
  }
void error()
{
  int i=0;
  for(i=0;i<10;i++)
  {
  digitalWrite(12,HIGH);  
  delay(500);                     
  digitalWrite(12, LOW);   
  delay(500);     
  }
count=0;
  }
void loop(){
while(BT.available()){
delay(10);
char c=BT.read();
state+=c;
} 
if(state.length()>0)
{
  if(state=="light on"||state=="light off"||state=="TV on"||state=="TV off"||state=="cool"||state=="hot")
 {
  home_auto(state);
 state="";
 }
 else
 {
Serial.println(state);
if(state=="turn on")
{
//digitalWrite(13,HIGH);
delay(1000);
myservo.write(110); 
}
else if(state=="turn off")
{
//digitalWrite(13,LOW);
delay(1000);
  myservo.write(15); 
}
if(state!="turn on" and state!="turn off" )
{count+=1;}
else if(state=="turn on" or state=="turn off")
{count=0;}
if(count>=3)
{error();}
//else
//{digitalWrite(12,LOW);}
state="";
if(count!=x)
{
  x=count;
  Serial.println(x);
  }
 }
 }
}
