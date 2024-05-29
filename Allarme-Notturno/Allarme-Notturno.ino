#include <LiquidCrystal.h>

// Inizializza la libreria con i numeri dei pin usati per l'interfaccia LCD
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);

// Definizione dei pin
const int button1Pin = 7;
const int button2Pin = 8;
const int buzzerPin = 13;
const int ledAllarmeAttivoPin = 9;
const int ledAllarmeDisattivoPin = 10;

// Variabili di stato
bool alarmActive = false;
unsigned long previousMillis = 0;  // Store the last time LED was updated
const long interval = 500;         // Interval at which to blink (milliseconds)
bool ledState = LOW;               // State of the LED

void setup() {
  // Imposta i pin dei bottoni come input
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  
  // Imposta i pin del buzzer e dei LED come output
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledAllarmeAttivoPin, OUTPUT);
  pinMode(ledAllarmeDisattivoPin, OUTPUT);
  
  // Inizializza l'LCD
  lcd.begin(16, 2);
  
  // Messaggio iniziale
  lcd.print("Pronto");

  // Stato iniziale dei LED
  digitalWrite(ledAllarmeAttivoPin, LOW);
  digitalWrite(ledAllarmeDisattivoPin, LOW);
}

void loop() {
  // Leggi lo stato dei bottoni
  bool button1State = digitalRead(button1Pin) == LOW;
  bool button2State = digitalRead(button2Pin) == LOW;

  // Se il bottone 1 è premuto, attiva l'allarme
  if (button1State) {
    alarmActive = true;
  }

  // Se il bottone 2 è premuto, disattiva l'allarme
  if (button2State) {
    alarmActive = false;
  }

  // Ottieni il tempo corrente
  unsigned long currentMillis = millis();

  // Controlla se è ora di aggiornare il LED
  if (currentMillis - previousMillis >= interval) {
    // Salva il tempo corrente
    previousMillis = currentMillis;

    // Se l'allarme è attivo, lampeggia il LED allarme attivo
    if (alarmActive) {
      lcd.clear();
      lcd.print("Pericolo!");
      tone(buzzerPin, 1000); // Suona il buzzer a 1000 Hz

      // Cambia stato del LED
      ledState = !ledState;
      digitalWrite(ledAllarmeAttivoPin, ledState);
      digitalWrite(ledAllarmeDisattivoPin, LOW); // Assicurati che l'altro LED sia spento
    } else {
      lcd.clear();
      lcd.print("Pronto");
      noTone(buzzerPin); // Ferma il suono del buzzer

      // Cambia stato del LED
      ledState = !ledState;
      digitalWrite(ledAllarmeDisattivoPin, ledState);
      digitalWrite(ledAllarmeAttivoPin, LOW); // Assicurati che l'altro LED sia spento
    }
  }
}
