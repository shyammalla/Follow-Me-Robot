#define TRIG 5
#define ECHO 18

#define LEFT_IR 34
#define RIGHT_IR 35

#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 12

long duration;
int distance;

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  // Ultrasonic distance
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);
  distance = duration * 0.034 / 2;

  int leftIR = digitalRead(LEFT_IR);
  int rightIR = digitalRead(RIGHT_IR);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" | L:");
  Serial.print(leftIR);
  Serial.print(" | R:");
  Serial.println(rightIR);

  if(distance <= 5)
  {
    Serial.println("STOP");

    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
  else
  {
    // IR based direction
    if(leftIR == LOW && rightIR == HIGH)
    {
      Serial.println("LEFT");

      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
    }

    else if(rightIR == LOW && leftIR == HIGH)
    {
      Serial.println("RIGHT");

      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
    }

    else
    {
      Serial.println("FORWARD");

      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
    }
  }

  delay(100);
}        