/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "pM7G3kOJmWL5u7Tq95dW1-UTxUTlvpYw";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "meena";
char pass[] = "12345678";

Servo liga[4][2];
const int liga_pin[4][2]={ { 5, 4 }, { 2, 0 }, { 14,12 }, { 13, 15 } } ;

const int qspeed=10;

const int ipo=110;

const int var=40;

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if(pinValue==1)// process received value
  {
    forward();
  }
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if(pinValue==1)// process received value
  {
    backward();
  }
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if(pinValue==1)// process received value
  {
   left();
  }
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if(pinValue==1)// process received value
  {
    right();
  }
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if(pinValue==1)// process received value
  {
   rotate_right();
  }
}

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if(pinValue==1)// process received value
  {
    rotate_left();
  }
}



void setup()
{
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  servo_attach();


}


void loop()
{
  Blynk.run();
}

void servo_attach(void)
{
  liga[0][0].attach(5);
  liga[0][1].attach(4);
  liga[1][0].attach(2);
  liga[1][1].attach(0);
  liga[2][0].attach(14);
  liga[2][1].attach(12);
  liga[3][0].attach(13);
  liga[3][1].attach(15);
}

//_______________________________________________________________


void polar_to_servo(int leg,int angle)
{
  if(leg == 0)
  {
    angle=angle-30;
    
  }

  int x=liga[leg][0].read();
  
  liga[leg][1].write(160);
  delay(100);
  
  if(x < angle)
  {
   for(int i=x;i<=angle;i +=qspeed)
   {
   liga[leg][0].write(i);
   delay(15);
   }
  }

  if(x > angle)
  {
   for(int i=x;i>=angle;i -=qspeed)
   {
   liga[leg][0].write(i);
   delay(15);
   }   
  }

  if(leg == 0)
  {
    liga[leg][1].write(10);
  }
  
  liga[leg][1].write(20);
  delay(100);
}


//_______________________________________________________________


void drag(int leg,int angle)
{

  if(leg == 0)
   {
    angle=angle-30;
    
   }

  
  int x=liga[leg][0].read();
  
  if(x<angle)
  {
    for(int i=x;i<=angle;i +=qspeed)
    {
   liga[leg][0].write(i);
    }
  }

  else if(x>angle)
  {
    for(int i=x;i>=angle;i -=qspeed)
    {
      liga[leg][0].write(i);
    }
  }
}


//_______________________________________________________________


void forward()
{
  
//Step 1
  polar_to_servo(0,ipo); // 0th position -->30
  polar_to_servo(1,ipo+var); // 0th position -->60
  polar_to_servo(2,ipo-var); // 0th position -->60
  polar_to_servo(3,ipo); // 0th position -->60
  
 //step2
polar_to_servo(1,ipo-var);


//step3
drag(0,ipo-var);
drag(1,ipo);
drag(2,ipo);
drag(3,ipo-var);
delay(300);

//step4
polar_to_servo(3,ipo+var);

//step5
polar_to_servo(0,ipo+var);

//step6
drag(0,ipo);
drag(1,ipo+var);
drag(2,ipo+var);
drag(3,ipo);
delay(300);

//step7
polar_to_servo(2,ipo-var);
}


//_______________________________________________________________


void backward()
{

//Step 1
  polar_to_servo(2,ipo); // 0th position -->30
  polar_to_servo(3,ipo+var); // 0th position -->60
  polar_to_servo(0,ipo-var); // 0th position -->60
  polar_to_servo(1,ipo); // 0th position -->60
  
 //step2
polar_to_servo(3,ipo-var);


//step3
drag(2,ipo-var);
drag(3,ipo);
drag(0,ipo);
drag(1,ipo-var);
delay(300);

//step4
polar_to_servo(1,ipo+var);

//step5
polar_to_servo(2,ipo+var);

//step6
drag(2,ipo);
drag(3,ipo+var);
drag(0,ipo+var);
drag(1,ipo);
delay(300);

//step7
polar_to_servo(0,ipo-var);

}


//_______________________________________________________________


void right()
{
  
//Step 1
  polar_to_servo(1,ipo); // 0th position -->30
  polar_to_servo(2,ipo+var); // 0th position -->60
  polar_to_servo(3,ipo-var); // 0th position -->60
  polar_to_servo(0,ipo); // 0th position -->60
  
 //step2
polar_to_servo(2,ipo-var);


//step3
drag(1,ipo-var);
drag(2,ipo);
drag(3,ipo);
drag(0,ipo-var);
delay(300);

//step4
polar_to_servo(0,ipo+var);

//step5
polar_to_servo(1,ipo+var);

//step6
drag(1,ipo);
drag(2,ipo+var);
drag(3,ipo+var);
drag(0,ipo);
delay(300);

//step7
polar_to_servo(3,ipo-var);
}


//_______________________________________________________________


void left()
{
  
//Step 1
  polar_to_servo(3,ipo); // 0th position -->30
  polar_to_servo(0,ipo+var); // 0th position -->60
  polar_to_servo(1,ipo-var); // 0th position -->60
  polar_to_servo(2,ipo); // 0th position -->60
  
 //step2
polar_to_servo(0,ipo-var);


//step3
drag(3,ipo-var);
drag(0,ipo);
drag(1,ipo);
drag(2,ipo-var);
delay(300);

//step4
polar_to_servo(2,ipo+var);

//step5
polar_to_servo(3,ipo+var);

//step6
drag(3,ipo);
drag(0,ipo+var);
drag(1,ipo+var);
drag(2,ipo);
delay(300);

//step7
polar_to_servo(1,ipo-var);
}

void rotate_right()
{
  //Step 1
  polar_to_servo(0,ipo); // 0th position -->30
  polar_to_servo(1,ipo+var); // 0th position -->60
  polar_to_servo(2,ipo-var); // 0th position -->60
  polar_to_servo(3,ipo); // 0th position -->60
  
 //step2
polar_to_servo(1,ipo-var);


//step3
drag(0,ipo+var);
drag(1,ipo-var);
drag(2,ipo);
drag(3,ipo+var);
delay(300);

//step4
polar_to_servo(0,ipo-var);

//step5
polar_to_servo(1,ipo-var);

polar_to_servo(3,ipo-var);

//step6
drag(0,ipo);
drag(1,ipo+var);
drag(2,ipo+var);
drag(3,ipo);
delay(300);

//step7
polar_to_servo(2,ipo-var);
polar_to_servo(3,ipo+var);
}

void rotate_left()
{
    //Step 1
  polar_to_servo(1,ipo); // 0th position -->30
  polar_to_servo(2,ipo+var); // 0th position -->60
  polar_to_servo(3,ipo-var); // 0th position -->60
  polar_to_servo(0,ipo); // 0th position -->60
  
 //step2
polar_to_servo(2,ipo-var);


//step3
drag(1,ipo+var);
drag(2,ipo-var);
drag(3,ipo);
drag(0,ipo+var);
delay(300);

//step4
polar_to_servo(1,ipo-var);

//step5
polar_to_servo(2,ipo-var);

polar_to_servo(0,ipo-var);

//step6
drag(1,ipo);
drag(2,ipo+var);
drag(3,ipo+var);
drag(0,ipo);
delay(300);

//step7
polar_to_servo(3,ipo-var);
polar_to_servo(0,ipo+var);
}




