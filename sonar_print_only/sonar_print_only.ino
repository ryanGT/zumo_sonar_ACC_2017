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

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 400;

int stop_at = 30;
int cur_dist;

void setup()
{
  // Play a little welcome song
  buzzer.play(">g32>>c32");
  Serial.begin(115200);

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
  delay(50);
  int uS = sonar.ping();
  cur_dist = uS / US_ROUNDTRIP_CM;
  Serial.print("Ping: ");
  Serial.print(cur_dist);
  Serial.println("cm");

}
