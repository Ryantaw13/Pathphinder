const int dotButtonPin = 26;
const int dashButtonPin = 27;
const int slashButtonPin = 28;
const int recordButtonPin = 29;
const int dotLedPin = 6;
const int dashLedPin = 7;
const int slashLedPin = 0;
const int replayLedPin = 1;

String morseSequence = "";
bool recording = false;
bool replaying = false;

void setup() {
  pinMode(dotButtonPin, INPUT_PULLUP);
  pinMode(dashButtonPin, INPUT_PULLUP);
  pinMode(slashButtonPin, INPUT_PULLUP);
  pinMode(recordButtonPin, INPUT_PULLUP);

  pinMode(dotLedPin, OUTPUT);
  pinMode(dashLedPin, OUTPUT);
  pinMode(slashLedPin, OUTPUT);
  pinMode(replayLedPin, OUTPUT);

  digitalWrite(dotLedPin, LOW);
  digitalWrite(dashLedPin, LOW);
  digitalWrite(slashLedPin, LOW);
  digitalWrite(replayLedPin, LOW);
}

void loop() {
  if (digitalRead(recordButtonPin) == LOW) {
    delay(50); // debounce
    if (!recording && !replaying) {
      morseSequence = "";
      recording = true;
      while (digitalRead(recordButtonPin) == LOW) delay(10); // wait for release
    } else if (recording) {
      recording = false;
      replaying = true;
      while (digitalRead(recordButtonPin) == LOW) delay(10); // wait for release
    }
  }

  if (recording) {
    if (digitalRead(dotButtonPin) == LOW) {
      lightOne(dotLedPin);
      morseSequence += ".";
      while (digitalRead(dotButtonPin) == LOW) delay(10);
    } else if (digitalRead(dashButtonPin) == LOW) {
      lightOne(dashLedPin);
      morseSequence += "-";
      while (digitalRead(dashButtonPin) == LOW) delay(10);
    } else if (digitalRead(slashButtonPin) == LOW) {
      lightOne(slashLedPin);
      morseSequence += "/";
      while (digitalRead(slashButtonPin) == LOW) delay(10);
    } else {
      lightOne(-1); // turn off all LEDs
    }
  } else {
    lightOne(-1);
  }

  if (replaying) {
    replayMorseCode();
    replaying = false;
  }
}

void lightOne(int ledPin) {
  digitalWrite(dotLedPin, ledPin == dotLedPin ? HIGH : LOW);
  digitalWrite(dashLedPin, ledPin == dashLedPin ? HIGH : LOW);
  digitalWrite(slashLedPin, ledPin == slashLedPin ? HIGH : LOW);
}

void replayMorseCode() {
  for (unsigned int i = 0; i < morseSequence.length(); i++) {
    char c = morseSequence[i];
    if (c == '.') {
      digitalWrite(replayLedPin, HIGH);
      delay(200); // dot duration
    } else if (c == '-') {
      digitalWrite(replayLedPin, HIGH);
      delay(600); // dash duration
    } else if (c == '/') {
      digitalWrite(replayLedPin, LOW);
      delay(1000); // word space
      continue;
    }
    digitalWrite(replayLedPin, LOW);
    delay(200); // symbol space
  }
  digitalWrite(replayLedPin, LOW);
}
