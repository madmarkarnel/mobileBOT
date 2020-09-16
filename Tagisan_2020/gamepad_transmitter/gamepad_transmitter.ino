//map buttons analog
const int rightjButton = A0;
const int leftjButton = A1;
const int leftjXaxis = A4;
const int leftjYaxis = A5;
const int rightjXaxis = A2;
const int rightjYaxis = A3;

//map buttons digital
const int vibrate = 2;
const int selectButton = 3;
const int startButton = 4;
const int upButton = 5;
const int leftButton = 6;
const int downButton = 7;
const int rightButton = 8;
const int oneButton = 9;
const int fourButton = 10;
const int twoButton = 11;
const int threeButton = 12;
const int rightZButton1 = 13;
const int rightZButton2 = 14;
const int leftZButton1 = 15;
const int leftZButton2 = 16;

void setup()
{
  // put your setup code here, to run once:
  Serial1.begin(115200);
  for (int i = 0; i < 17; i++)
    pinMode(i, INPUT);
  pinMode(vibrate, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int leftJX = analogRead(leftjXaxis);
  int leftJY = analogRead(leftjYaxis);
  int rightJX = analogRead(rightjXaxis);
  int rightJY = analogRead(rightjYaxis);

  //analog joystick
  if (leftJX < 500 || leftJX > 530)
  {
    // Serial1.println("LeftJ-X: ");
    Serial1.println(leftJX);
    delay(50);
  }
  if (leftJY < 500 || leftJY > 530)
  {
    // Serial1.println("LeftJ-Y: ");
    Serial1.println(leftJY);
    delay(50);
  }
  if (rightJX < 500 || rightJX > 530)
  {
    // Serial1.println("RightJ-X: ");
    Serial1.println(rightJX);
    delay(50);
  }
  if (rightJY < 500 || rightJY > 530)
  {
    // Serial1.println("RightJ-Y: ");
    Serial1.println(rightJY);
    delay(50);
  }

  //joystick digital buttons

  if (digitalRead(leftjButton) == 0)
  {
    Serial1.println("LEFTJ");
    delay(200);
  }
  if (digitalRead(rightjButton) == 0)
  {
    Serial1.println("RIGHTJ");
    delay(200);
  }

  //digital buttons

  if (digitalRead(upButton) == 0)
  {
    Serial1.println("UP");
    delay(200);
  }
  if (digitalRead(downButton) == 0)
  {
    Serial1.println("DOWN");
    delay(200);
  }
  if (digitalRead(leftButton) == 0)
  {
    Serial1.println("LEFT");
    delay(200);
  }
  if (digitalRead(rightButton) == 0)
  {
    Serial1.println("RIGHT");
    delay(200);
  }

  // right buttons
  if (digitalRead(oneButton) == 0)
  {
    Serial1.println("D1");
    delay(200);
  }
  if (digitalRead(twoButton) == 0)
  {
    Serial1.println("D2");
    delay(200);
  }
  if (digitalRead(threeButton) == 0)
  {
    Serial1.println("D3");
    delay(200);
  }
  if (digitalRead(fourButton) == 0)
  {
    Serial1.println("D4");
    delay(200);
  }

  //menu buttons
  if (digitalRead(selectButton) == 0)
  {
    Serial1.println("SELECT");
    delay(200);
  }
  if (digitalRead(startButton) == 0)
  {
    Serial1.println("START");
    delay(200);
  }

  // trigger buttons

  if (digitalRead(rightZButton1) == 0)
  {
    Serial1.println("RIGHTZ-1");
    delay(200);
  }
  if (digitalRead(rightZButton2) == 0)
  {
    Serial1.println("RIGHTZ-2");
    delay(200);
  }

  if (digitalRead(leftZButton1) == 0)
  {
    Serial1.println("LEFTZ-1");
    delay(200);
  }
  if (digitalRead(leftZButton2) == 0)
  {
    Serial1.println("LEFTZ-2");
    delay(200);
  }
}
