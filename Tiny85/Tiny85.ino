//kurzer Tastendruck
#define SHORT_PRESS_TIME 250 // Millisekunden
//langer Tastendruck
#define LONG_PRESS_TIME  800 // Millisekunden

//Verzögerung der Meldung bei Stromausfall
#define SHORT_PRESS_DELAY 10000 // Millisekunden
//Verzögerung der Meldung bei Stromrückkehr
#define LONG_PRESS_DELAY  10000 // Millisekunden

unsigned long PowerOffMillis = 0;
unsigned long PowerOnMillis = 0;
bool SHORT_PRESS_SENT = false;
bool LONG_PRESS_SENT = false;
bool hasPower = false;

void setup() {
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(1, HIGH);
}

void loop() {
  if (PowerOnMillis > millis())
    PowerOnMillis = millis();
  if (PowerOffMillis > millis())
    PowerOffMillis = millis();

  if (analogRead(1) < 900) {
    if (hasPower) {
      PowerOnMillis = 0;
      PowerOffMillis = millis();
      hasPower = false;
    }
  } else {
    if (!hasPower) {
      PowerOffMillis = 0;
      PowerOnMillis = millis();
      hasPower = true;
    }
  }

  if (!hasPower && !SHORT_PRESS_SENT && millis() - PowerOffMillis > SHORT_PRESS_DELAY) {
    SHORT_PRESS_SENT = true;
    LONG_PRESS_SENT = false;
    digitalWrite(1, LOW);
    delay(SHORT_PRESS_TIME);
    digitalWrite(1, HIGH);
  }

  if (hasPower && !LONG_PRESS_SENT && millis() - PowerOnMillis > LONG_PRESS_DELAY) {
    SHORT_PRESS_SENT = false;
    LONG_PRESS_SENT = true;
    digitalWrite(1, LOW);
    delay(LONG_PRESS_TIME);
    digitalWrite(1, HIGH);
  }
}
