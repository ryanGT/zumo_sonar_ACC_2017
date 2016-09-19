/*
 * Demo line-following code for the Pololu Zumo Robot
 *
 * This code will follow a black line on a white background, using a
 * PID-based algorithm.  It works decently on courses with smooth, 6"
 * radius curves and has been tested with Zumos using 30:1 HP and
 * 75:1 HP motors.  Modifications might be required for it to work
 * well on different courses or with different motors.
 *
 * http://www.pololu.com/catalog/product/2506
 * http://www.pololu.com
 * http://forum.pololu.com
 */

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#include <NewPing.h>

#define TRIGGER_PIN  A4
#define ECHO_PIN     A5
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
int inByte;

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 400;

int stop_at = 30;
int cur_dist;
bool move;
int error;
float kp;
int cur_speed;
int mycase;
int n_steps=501;
int t0;
int cur_t;

void setup()
{
  // Play a little welcome song
  buzzer.play(">g32>>c32");
  Serial.begin(115200);
  //move = false;
  move = true;
  mycase = 2;
  //kp = 50;//pretty good - borderline with battery
  //kp = 100;//small overshoot
  //kp = 150;//overshoot
  kp = 70;
  //kp = 1;//low damping
  // Initialize the reflectance sensors module
  //reflectanceSensors.init();

  // Wait for the user button to be pressed and released
  //button.waitForButton();

  // Turn on LED to indicate we are in calibration mode
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  //motors.setSpeeds(400,400);
  //delay(100);
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  /* delay(1000); */
  /* int i; */
  /* for(i = 0; i < 80; i++) */
  /* { */
  /*   if ((i > 10 && i <= 30) || (i > 50 && i <= 70)) */
  /*     motors.setSpeeds(-200, 200); */
  /*   else */
  /*     motors.setSpeeds(200, -200); */
  /*   reflectanceSensors.calibrate(); */

  /*   // Since our counter runs to 80, the total delay will be */
  /*   // 80*20 = 1600 ms. */
  /*   delay(20); */
  /* } */
  motors.setSpeeds(0,0);

  // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);
  buzzer.play(">g32>>c32");

  // Wait for the user button to be pressed and released
  //button.waitForButton();

  // Play music and wait for it to finish before we start driving.
  //buzzer.play("L16 cdegreg4");
  //while(buzzer.isPlaying());
}

void loop()
{
  delay(30);
  int uS = sonar.ping();
  cur_dist = uS / US_ROUNDTRIP_CM;

  if ( n_steps < 200 ){
    n_steps++;
    cur_t = millis()-t0;
    Serial.print(n_steps);
    Serial.print(",");    
    Serial.print(cur_t);
    Serial.print(",");    
    Serial.println(cur_dist);

    if ( cur_dist > 0 ){//zero seems to indicate a read error from ping
      // P Control
      error = cur_dist - stop_at;
      cur_speed = kp*error;
      motors.setSpeeds(cur_speed, cur_speed);
    }
  }
  
  else{
    motors.setSpeeds(0,0);
    Serial.println("Input Kp:");
    while (Serial.available() == 0){
	delay(10);
      }
    kp = Serial.parseInt();
    /* inByte = Serial.read()-'0'; */
    /*   if (inByte == 1){ */
    /* 	kp = 5; */
    /*   } */
    /*   else if (inByte == 2){ */
    /* 	kp = 10; */
    /*   } */
    /*   else if (inByte == 3){ */
    /* 	kp = 20; */
    /*   } */
    /*   else if (inByte == 4){ */
    /* 	kp = 30; */
    /*   } */
    /*   else if (inByte == 5){ */
    /* 	kp = 40; */
    /*   } */
    /*   else if (inByte == 6){ */
    /* 	kp = 50; */
    /*   } */
    /*   else if (inByte == 7){ */
    /* 	kp = 75; */
    /*   } */
    /*   else if (inByte == 8){ */
    /* 	kp = 100; */
    /*   } */
    /*   else if (inByte == 9){ */
    /* 	kp = 150; */
    /*   } */
      Serial.print("#kp = ");
      Serial.println(kp);
      delay(200);
      n_steps = 0;
      t0 = millis();
      Serial.println("#n_steps,t (ms),dist (cm)");
  }
}
