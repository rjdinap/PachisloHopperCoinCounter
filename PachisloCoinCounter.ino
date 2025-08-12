//Robert DiNapoli - 2025


#include <SoftwareSerial.h>
#include <AbleButtons.h> //John Scott
#include <Arduino.h>
#include <digitalWriteFast.h>


#define START_SWITCH 51
#define COIN_COUNTER_SWITCH 18
#define MOTOR 23 //through relay pin IN1



//button setup
using Button = AblePullupClickerButton;
Button CoinCounterSwitch(COIN_COUNTER_SWITCH);
using Button = AblePullupClickerButton;
Button StartSwitch(START_SWITCH);



//variables setup
int coinCounter = 0;
int coinsToCount = 40; //change this to the number of coins to count before stopping. Set to a high number for continous counting.
int msgFlag = 0; //allow message display


//timers
uint16_t rotateNowMillis = millis(); // more than 3 seconds without a coin release, stop motor
uint16_t rotatePrevMillis = millis();


/*====================================================================================================================*/
/*====================================================================================================================*/

void setup() {
delay(1000); //stabilize before starting
//pin setup  
pinMode(COIN_COUNTER_SWITCH,INPUT_PULLUP); //49
pinMode(START_SWITCH,INPUT_PULLUP); //51
pinMode(MOTOR, OUTPUT);  //23
digitalWriteFast(MOTOR, HIGH); //motor off



Serial.begin(38400);
while (!Serial) {
  delay(10);
}

Serial.print("Trigger button to start coin count for " + String(coinsToCount) + " coins.\r\n");


Button::setDebounceTime(50);


//key setup
CoinCounterSwitch.begin();
StartSwitch.begin();

} //end setup function



/* ---------------------------------------------------------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------------------------------------------------------------*/

void loop() {




//check for start button and turn motor on when triggered
StartSwitch.handle();
if (StartSwitch.resetClicked())  {
  coinCounter = 0;
  msgFlag = 1;
  Button::setDebounceTime(2);
  rotateNowMillis = millis(); 
  rotatePrevMillis = millis();
  digitalWriteFast(MOTOR,LOW); //motor on 
}  

CoinCounterSwitch.handle();
if (CoinCounterSwitch.resetClicked()) {
      coinCounter = coinCounter + 1;
      Serial.print("Coin Counter: " + String(coinCounter) + "\r\n");
      rotateNowMillis = millis();
      rotatePrevMillis = millis();

}

//if we get 3 seconds without a coin being expelled, turn off the motor
rotateNowMillis = millis();
if ((uint16_t) (rotateNowMillis - rotatePrevMillis) >= 3000) { 
    rotatePrevMillis = rotateNowMillis;
    digitalWriteFast(MOTOR, HIGH); //motor off
    if (msgFlag == 1) {
      Serial.print("No coins counted in 3 seconds. Hopper empty? \r\n");
      msgFlag = 0;  
      Button::setDebounceTime(50);
    }
}    


//if we have reached the amount of coins to count, turn off the motor
if (coinCounter >= coinsToCount) {
  digitalWriteFast(MOTOR, HIGH); //motor off
  Serial.print("Finished counting " + String(coinsToCount) + " coins.\r\n");
  coinCounter = 0;
  msgFlag = 0;
  Button::setDebounceTime(50);
}



} //end loop
