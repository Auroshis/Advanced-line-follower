
int num_Measure = 128 ; // Set the number of measurements   
int pinSignal1 = A0;
int pinSignal2 = A1;// pin connected to pin O module sound sensor   
long Sound_signal1;
long Sound_signal2;// Store the value read Sound Sensor   
long sum1 = 0 ;
long sum2 = 0 ;// Store the total value of n measurements   
long level1 = 0 ;
long level2 = 0 ;// Store the average value   
 
#define S0 4
#define S1 8
#define S2 7
#define S3 2
#define sensorOut 13
int fr = 0,fb = 0,fg = 0;

#define irl 10
#define irm 11
#define irr 12
int l=0, m=0, r=0;
#define in1 3
#define in2 5
#define in4 6
#define in3 9

int frequency = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
 
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);

  pinMode(irl,INPUT);
  pinMode(irr,INPUT);
  pinMode(irm,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode (pinSignal1, INPUT);
  pinMode (pinSignal2, INPUT);// Set the signal pin as input   
  
}
void loop() 
{
l=digitalRead(irl);
m=digitalRead(irm);  
r=digitalRead(irr);
if(l==1&&m==1&&r==1)
{
    forward();
}
else if(l==1&&m==1&&r==0)
{
  while(digitalRead(irr)!=1)
  {
    right();
  }
}

else if(l==0&&m==1&&r==0)
{
    if(colour()==1)
    {
      if(sound()==3)//right
      {
        while(digitalRead(irl)!=1)
        {
         left();
        }
      }
      else if(sound()==4)
      {
        while(digitalRead(irr)!=1)
        {
          right();
        }
      }
    }
    else if(colour()==2)
    {
      if(sound()==3)
      {
        while(digitalRead(irr)!=1)
        {
          right();
        }
      }
      else if(sound()==4)
      {
        while(digitalRead(irl)!=1)
        {
          left();
        }
      }
      else if(sound()==5)
      {
        while(digitalRead(irl)!=1)
        {
          forward();
        }
      }
    }
    else
    {
      while(digitalRead(irr)!=1)
      {
        right();
      }
    } 
}
else if(l==0&&m==1&&r==1)
{
  while(digitalRead(irl)!=1)
  {
    left();
  } 
}
else if(l==1&&m==0&&r==1)
{
  while(digitalRead(irm)!=1)
  {
    deadend();
  }
}
}

void deadend()
{
  analogWrite(in1,50);
  analogWrite(in2,0);
  analogWrite(in3,55);
  analogWrite(in4,0); 
  Serial.println("deadend");
}
/*void backward()
{
   digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH); 
 }*/
 void left()
 {
  Serial.println("left");
   analogWrite(in1,0);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,50); 
 }
void right()
{
  Serial.println("right");
   analogWrite(in1,55);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,0); 
}
void forward()
{
  Serial.println("forward");
   analogWrite(in1,55);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,50);
}
int colour()
{
// Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  fr = pulseIn(sensorOut, LOW);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  fg = pulseIn(sensorOut, LOW);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  fb = pulseIn(sensorOut, LOW);
 if(fr<220&& fr>180 && fg<320 && fg>270 && fb<230 && fb>190)
  {
    return(1);
  }
  else if(fr<310 && fr>270 && fg<290 && fg>260 && fb<220 && fb>190)
  {
    return(2);
  }
  else
  {
      return(0);
  }
}
int sound()
{
  // Performs 128 signal readings   
  for( int i = 0 ; i <num_Measure; i++)  
  {  
   Sound_signal1 = analogRead (pinSignal1);
   Sound_signal2 = analogRead (pinSignal2);  
    sum1 =sum1 + Sound_signal1;
    sum2 =sum2 + Sound_signal2;  
  }  
 
  level1 = sum1 / num_Measure;
  level2 = sum2 / num_Measure;// Calculate the average value   
  if(level2>level1)
  {
    return(3);//left 
    }
  else if(level2<level1)
  {
    return(4);//right
    }
  else if((level1-level2)<=50 && (level1-level2)>=0||(level1-level2)>=-50 && (level1-level2)<=0)
  {  
    return(5);
  }
  sum1 = 0 ;
  sum2 = 0 ;// Reset the sum of the measurement values 
  delay(1000);
}


