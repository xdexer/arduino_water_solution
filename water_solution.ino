#define RELAY_PIN 4
#define MOISTURE_PIN A0

#define THRESHOLD 350 // minimum moisture level that is classified as suitable
#define SECOND 1000

int suitableTimeForWatering()
{
  return 1;
}
bool moistEnough(int moistureValue)
{
  return moistureValue < THRESHOLD;
}

int calculateAverageMoistureValueDuringTheDay()
{
  return 0;
}

void setup()
{
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

// high level - CLOSED
// low level - OPEN
void loop()
{
  int moistureValue = analogRead(MOISTURE_PIN);
  Serial.println(moistureValue);

  if (suitableTimeForWatering() && !moistEnough(moistureValue))
  {
    digitalWrite(RELAY_PIN, HIGH);
    delay(2 * SECOND);
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
    delay(2 * SECOND);
  }
  digitalWrite(RELAY_PIN, LOW);
  delay(2 * SECOND);
}
