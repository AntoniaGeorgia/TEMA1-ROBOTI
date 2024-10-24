#include <Arduino.h> 

// Definirea pinurilor
#define R 6
#define G 5
#define B 4 
#define led1 10
#define led2 9
#define led3 8
#define led4 7
#define BSTART 3
#define BSTOP 2

// Variabile pentru debounce (eliminarea zgomotului la apăsarea butoanelor)
int buttonStateStart;             
int lastButtonStateStart = LOW;   
int buttonStateStop;             
int lastButtonStateStop = LOW;   
unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeStop = 0;
unsigned long debounceDelay = 50; 

bool chargingActive = false;  // Variabilă pentru a urmări dacă încărcarea este activă
bool stopCharging = false;    // Variabilă pentru a urmări dacă s-a apăsat butonul de stop

void setup() {
  // Configurarea pinurilor LED și a butoanelor
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BSTART, INPUT_PULLUP);
  pinMode(BSTOP, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Inițializarea stării LED-urilor
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(G, HIGH);  // Pornirea LED-ului verde la început
}

void delayCheck(unsigned long ms) {
  // Verifică starea butonului BSTOP în timpul întârzierii
  unsigned long start = millis();
  while (millis() - start < ms) {
    int stopReading = digitalRead(BSTOP);
    if (stopReading != lastButtonStateStop) {
      lastDebounceTimeStop = millis();
    }
    if ((millis() - lastDebounceTimeStop) > debounceDelay) {
      if (stopReading != buttonStateStop) {
        buttonStateStop = stopReading;
        if (buttonStateStop == LOW) {  // Dacă s-a apăsat butonul de stop
          stopCharging = true;
          turnOffAllLEDs();  // Oprește toate LED-urile când s-a apăsat stop
          return;
        }
      }
    }
    lastButtonStateStop = stopReading;
  }
}

void incarcare() {
  digitalWrite(G, LOW); // Oprește LED-ul verde, începe încărcarea
  digitalWrite(R, HIGH); // Aprinde LED-ul roșu

  // Începe cu led1
  digitalWrite(led1, HIGH);
  delayCheck(2500);
  if (stopCharging) return;  // Verifică dacă butonul de stop a fost apăsat

  digitalWrite(led1, LOW);
  delayCheck(500);
  if (stopCharging) return;

  digitalWrite(led1, HIGH);
  int k = 0;
  
  // Clipirea led2 de trei ori
  while (k < 3) {
    digitalWrite(led2, HIGH);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led2, LOW);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led2, HIGH);
    k++;
  }
  
  k = 0;
  // Clipirea led3 de trei ori
  while (k < 3) {
    digitalWrite(led3, HIGH);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led3, LOW);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led3, HIGH);
    k++;
  }

  k = 0;
  // Clipirea led4 de trei ori
  while (k < 3) {
    digitalWrite(led4, HIGH);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led4, LOW);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led4, HIGH);
    k++;
  }

  k = 0;
  // Clipirea tuturor LED-urilor împreună de trei ori
  while (k < 3) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delayCheck(500);
    if (stopCharging) return;

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delayCheck(500);
    if (stopCharging) return;

    k++;
  }

  digitalWrite(R, LOW);   // Oprește LED-ul roșu
  digitalWrite(G, HIGH);  // Pornește LED-ul verde, indicând că încărcarea s-a terminat
}

void turnOffAllLEDs() {
  // Oprește toate LED-urile și resetează starea de încărcare
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(R, LOW);   // Oprește LED-ul roșu
  digitalWrite(G, HIGH);  // Pornește LED-ul verde pentru a indica resetarea
}

void loop() {
  // Citește starea butonului BSTART
  int readingStart = digitalRead(BSTART);

  // Verifică dacă starea butonului BSTART s-a schimbat (debouncing)
  if (readingStart != lastButtonStateStart) {
    lastDebounceTimeStart = millis();  // Resetează temporizatorul de debounce
  }

  // Verifică dacă întârzierea de debounce a trecut pentru BSTART
  if ((millis() - lastDebounceTimeStart) > debounceDelay) {
    if (readingStart != buttonStateStart) {
      buttonStateStart = readingStart;

      // Dacă s-a apăsat BSTART și nu este activă încărcarea
      if (buttonStateStart == LOW && !chargingActive) {
        chargingActive = true;
        stopCharging = false;  // Resetează semnalul de stop înainte de a începe încărcarea
        incarcare();           // Începe procesul de încărcare
        chargingActive = false;  // Resetează indicatorul de încărcare
      }
    }
  }

  lastButtonStateStart = readingStart;  // Actualizează starea butonului pentru următoarea iterație
}
