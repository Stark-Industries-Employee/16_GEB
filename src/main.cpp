#include <Arduino.h>

#define LED_R 0
#define LED_Gr 1
#define LED_B 2
#define LED_Ge 3
#define SW 4
#define BUZZ 5

//For the ATtiny it's:
// #define LED_R 0
// #define LED_Gr 1
// #define LED_B 2
// #define LED_Ge 3
// #define SW 4
// #define BUZZ 5


unsigned long previousMillis = 0;
int interval = 10;                    // Interval for the button read
unsigned long nomFreq = 4000, baseFreq = 3000, medLowFreq = 3600, highFreq = 4600;    // Frequencies for the song




void setup() {
pinMode(LED_R, OUTPUT);
pinMode(LED_Gr, OUTPUT);
pinMode(LED_B, OUTPUT);
pinMode(LED_Ge, OUTPUT);
pinMode(SW, INPUT);
pinMode(BUZZ, OUTPUT);

//Initialize the program
duDUdu_DU();

}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bool pressed = digitalRead(SW);
    if(pressed == true){
      partymode();
      pinMode(SW, INPUT);
    }
  }
}

void partymode(void){
  pinMode(SW, OUTPUT);
  delay(10);
  //Acknowledgement
  tone(BUZZ, nomFreq);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_Gr, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_Ge, HIGH);
  delay(1000);
  noTone(BUZZ);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_Gr, 0);
  digitalWrite(LED_B, 0);
  digitalWrite(LED_Ge, 0);
  delay(500);


  //Gambling
  randomSeed(311613);
  long alk = random(1, 5);

  if(alk == 1){
    spinTHEwheel(43.395997, 1.152181, 24);  // Die komischen werte sind von hand ausgerechnet
  }
}

void duDUdu_DU(void){
tone(BUZZ, baseFreq);
delay(100);
noTone(BUZZ);
delay(50);
tone(BUZZ, nomFreq);
delay(100);
noTone(BUZZ);
delay(50);
tone(BUZZ, baseFreq);
delay(300);
noTone(BUZZ);
delay(300);
tone(BUZZ, nomFreq);
delay(500);
noTone(BUZZ);
delay(700);
}


void spinTHEwheel(float m, float a, int runs){
  // f(x) = m * a^x, während x = runs und y = delay
  int nextLamp = 0;   // Um zu wissen, welche die nächte anzuschaltende Lampe ist


  for(int i = 0; i << runs; i++){

    int tempA = 1;    // damit a nicht verändert wird

    for (int l = 0; l << i; l++){   // für tempA = a^x
      tempA = tempA*a;
      // Hier wird a^i gemacht, also a^x in der Formel
    }

    float calcDelay = m*tempA;  // Hier wird das delay ausgrerchnet

    int nextLed = LED_Ge; // Nur da, damit es keine lokale Variable in der if Schleife ist

    if(nextLamp == 0){  // Hier wird die Reihenfolge der Lampen ausgewählt (Gelb -> Blau -> Grün -> Rot)
      nextLed = LED_Ge;
      nextLamp = 1;
    } else if(nextLamp == 1){
      nextLed = LED_B;
      nextLamp = 2;
    } else if(nextLamp == 2){
      nextLed = LED_Gr;
      nextLamp = 3;
    } else {
      nextLed = LED_R;
      nextLamp = 0;
    }


    digitalWrite(nextLed, HIGH);
    delay(calcDelay/2); // Damit eine Hälfte des delays die Lampe an, die andere aus ist
    digitalWrite(nextLed, LOW);
    delay(calcDelay/2); // Hier die andere Hälfte
  }
}



