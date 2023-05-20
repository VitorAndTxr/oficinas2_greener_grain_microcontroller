const int DIR = 14;
const int STEP = 12;
const int  steps_per_rev = 200;

void setup()
{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}
const int delayPassos = 3000;

void gira(int sentido, int passos)
{
    if (sentido == 0){ 
      digitalWrite(DIR, HIGH);
      Serial.println("Spinning Clockwise...");
      
      for(int i = 0; i<passos; i++)
      {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(delayPassos);
        digitalWrite(STEP, LOW);
        delayMicroseconds(delayPassos);
      }
    }
    else if (sentido == 1){
      digitalWrite(DIR, LOW);
      Serial.println("Spinning Anti-Clockwise...");

      for(int i = 0; i<passos; i++)
      {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(delayPassos);
        digitalWrite(STEP, LOW);
        delayMicroseconds(delayPassos);
      }
    }

}

void loop()
{
  gira(1, 40);
  gira(0, 80);
}
