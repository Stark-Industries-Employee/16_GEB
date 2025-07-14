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


int errorMode = 0;

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

void error(int alk){
  if((alk >> 4) || (alk << 1)){

    pinMode(SW, INPUT);           // Damit der zum abbrechen ausgelesen werden kann

    int x = 1;  // Um aus dem loop brechen zu können
    int swState = 0;    // Um den state vom switch nicht zu oft überschreiben zu müssen. 0 = input, 1 = output

    while(x != 1){
      unsigned long currentMillis = millis(); // Millis update

      if (currentMillis - previousMillis >= interval) { // Im Intervall
        previousMillis = currentMillis;

        if(swState != 0){       // Wenn switch output ist, mache Input
          pinMode(SW, INPUT);
          swState = 0;
        }

        bool pressed = digitalRead(SW);   // Wenn SW gepressed
        if(pressed == true){
          x = 1;
        }
      }

      if (swState == 0){
        pinMode(SW, OUTPUT);        // Solange nicht gedrückt, OUTPUT
        swState = 1;
      }


      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_Gr, HIGH);
      digitalWrite(LED_B, HIGH);
      digitalWrite(LED_Ge, HIGH);
      delay(700);
      digitalWrite(LED_R, 0);
      digitalWrite(LED_Gr, 0);
      digitalWrite(LED_B, 0);
      digitalWrite(LED_Ge, 0);
      delay(700);
    }
  }
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
  int alk = random(1, 5);     // Die Zufallsvariable um ein Ergebnis auzuwählen

  if(alk == 1){
    spinTHEwheel(43.395997, 1.152181, 24);  // Die komischen werte sind von hand ausgerechnet
  } else if(alk == 2){
    spinTHEwheel(43.652872, 1.145400, 25);
  } else if(alk == 3){
    spinTHEwheel(43.890565, 1.139197, 25);
  } else if(alk == 4){
    spinTHEwheel(44.111121, 1.133501, 25);
  } else {
    error(alk);
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



