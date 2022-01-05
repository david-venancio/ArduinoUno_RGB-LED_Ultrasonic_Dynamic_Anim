// ArduinoUno_RGB-LED_Ultrasonic_Dynamic_Anim v0.0.1 
// Code by Louis David Venancio 01.01.2022
// meta_4@massmulti.org

#include <Ultrasonic.h>
#include <RGB_LED.h>

#define LOG_TIMER_DELAY 100
#define WHAT_IS_CLOSE   10  //closer than that = slowest speed anim
#define WHAT_IS_FAR     50  //further than that = max speed anim

RGB_LED LED(9,10,11);
unsigned int speed = 5000;
int log_timer_k=0;


Ultrasonic ultrasonic(4,3); // (Trig PIN,Echo PIN)
int last_range=0;

void setup() 
{ 
  //LED.setFunction(StepRandom);
  LED.setFunction(FadeRandom);
  LED.setSpeed(speed);

  Serial.begin(250000);
  Serial.println("----------------------------------------");
  Serial.println("- RGB-LED Ultrasonic Dynamic Animation");
  Serial.println("----------------------------------------  ");
  Serial.println("- Meta_4 2022.01"); 
  Serial.println("- LED PWM pins R:9 G:10 B:11");
  Serial.println("- HR-SC04 pins Trig:4 Echo:3");
  Serial.println("- Hardware: Arduino UNO and compatibles");
  Serial.println("- Init Complete. <3.");
  Serial.println("-------------------------------- HELP --");
  Serial.print("- messages sent every ");
  Serial.print(LOG_TIMER_DELAY);
  Serial.println(" loops :");
  Serial.println("- distance in cm / anim speed");
  Serial.println("----------------------------------------");
}

void loop() 
{
  if(log_timer_k<LOG_TIMER_DELAY){
    log_timer_k++;
  }else{
    log_timer_k=0;
    last_range = ultrasonic.Ranging(CM);
    Serial.print(last_range);
    //using the the log_timer var to also time the sensor read = realtime answer+log.
    //wanted : close = slow anim, distant or nothing = fast anim
    if(last_range < WHAT_IS_CLOSE){
      speed = 20000;
    }
    if(last_range > WHAT_IS_FAR){
      speed = 100;
    }
    if(last_range > WHAT_IS_CLOSE && last_range < WHAT_IS_FAR){
      speed = map(last_range, WHAT_IS_CLOSE, WHAT_IS_FAR, 20000, 100  );
    }
    Serial.print(" / ");
    Serial.println(speed);
    LED.setSpeed(speed);
    LED.delay(10);
  }
  LED.run();
}
