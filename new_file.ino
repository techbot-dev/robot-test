#define LEFT_SENSOR 11
#define RIGHT_SENSOR 8
#define MIDDLE_LEFT_SENSOR 10
#define MIDDLE_RIGHT_SENSOR 9

#define SPEED 60
#define LINE_BLACK_VALUE 0
#define LINE_WHITE_VALUE 1


#define LEFT_DISTANCE_SENSOR A1
#define RIGHT_DISTANCE_SENSOR A0
#define CENTER_DISTANCE_SENSOR A2


int ENA = 3; // PWM
int IN1 = 2; 
int IN2 = 4;

int ENB = 5; // PWM
int IN3 = 6;
int IN4 = 7;

int mode = 0;

int status = 0;

void TURN_RIGHT() {
    digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void TURN_LEFT() {
    digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void BACKWARD() {
    digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void TURN_AHEAD() {
    digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void turnDistanceLeft(int left_speed_front, int right_speed_front) {

      left_speed_front = 0;
       right_speed_front = 0;
      analogWrite(ENB, left_speed_front);
      analogWrite(ENA, right_speed_front);


         // lui lai
          BACKWARD();
          left_speed_front = 80;
          right_speed_front = 80;
         analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(100);

      TURN_AHEAD();
        // re phai
        left_speed_front = 0;
        right_speed_front = 120;
          analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(650);

        // left_speed_front = 70;
        //   right_speed_front = 70;
        //  analogWrite(ENB, left_speed_front);
        //  analogWrite(ENA, right_speed_front);
        // delay(40);

        left_speed_front = 0;
        right_speed_front = 0;
        analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(200);

        left_speed_front = 140;
        right_speed_front = 0;
          analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(750);
        status = 1;

}

void turnDistanceRight(int left_speed_front, int right_speed_front) {

  left_speed_front = 0;
       right_speed_front = 0;
      analogWrite(ENB, left_speed_front);
      analogWrite(ENA, right_speed_front);


         // lui lai
          BACKWARD();
          left_speed_front = 80;
          right_speed_front = 80;
         analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(100);

      TURN_AHEAD();
        // re phai
        left_speed_front = 140;
        right_speed_front = 0;
          analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(750);

        // left_speed_front = 70;
        //   right_speed_front = 70;
        //  analogWrite(ENB, left_speed_front);
        //  analogWrite(ENA, right_speed_front);
        // delay(50);

            left_speed_front = 0;
          right_speed_front = 0;
         analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(200);

        left_speed_front = 0;
        right_speed_front = 120;
          analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
        delay(650);

}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int right = digitalRead(RIGHT_SENSOR);
  int left = digitalRead(LEFT_SENSOR);
  int middle_right = digitalRead(MIDDLE_RIGHT_SENSOR);
  int middle_left = digitalRead(MIDDLE_LEFT_SENSOR);


//#define LEFT_DISTANCE_SENSOR A1
#define RIGHT_DISTANCE_SENSOR A0
#define CENTER_DISTANCE_SENSOR A2

  int left_distance_sensor = analogRead(LEFT_DISTANCE_SENSOR);
  int right_distance_sensor = analogRead(RIGHT_DISTANCE_SENSOR);
  int center_distance_sensor = analogRead(CENTER_DISTANCE_SENSOR);


  




  // Serial.print("SENSOR Val: ");
  // Serial.print("left: ");
  // Serial.print(left);
  // Serial.print(" - ");
  // Serial.print("right: ");
  // Serial.print(right);
  //  Serial.print(" - ");
  // Serial.print("middle right: ");
  // Serial.print(middle_right);

  //  Serial.print(" - ");
  // Serial.print("middle left: ");
  // Serial.print(middle_left);
  //    Serial.println("");
  if ((right == LINE_WHITE_VALUE && middle_right == LINE_WHITE_VALUE) || (left ==  LINE_WHITE_VALUE && middle_left == LINE_WHITE_VALUE) ) {
    TURN_AHEAD();
    mode = 0;

  }

   int left_speed_front = (mode == 0 ? 80 : 0);
   int right_speed_front = (mode == 0 ? 80 : 0);



   if (mode == 0) {
     if (center_distance_sensor < 200 || left_distance_sensor < 200) {
       if (status == 0) {
            turnDistanceLeft(left_speed_front, right_speed_front);
       } else if (status == 1) {
          turnDistanceRight(left_speed_front, right_speed_front);
       }

       // dung lai
       

    //     TURN_AHEAD();
    // // left_speed_front = SPEED;
    // // right_speed_front = SPEED;


    //    analogWrite(ENB, 0);
    //      analogWrite(ENA, 0);


     }  else {
           TURN_AHEAD();
    left_speed_front = 80;
    right_speed_front = 80;
         analogWrite(ENB, left_speed_front);
         analogWrite(ENA, right_speed_front);
     }
   }




   if (mode == 2) {

  if ((middle_left == LINE_WHITE_VALUE   || middle_right == LINE_WHITE_VALUE) && left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE) {
    Serial.println("FORWARD");
    TURN_AHEAD();
    left_speed_front = SPEED;
    right_speed_front = SPEED;
  }
  else  if ( (middle_left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE && middle_right == LINE_BLACK_VALUE ) || (middle_left == LINE_BLACK_VALUE && left == LINE_BLACK_VALUE && middle_right == LINE_BLACK_VALUE) 
  || (right == LINE_WHITE_VALUE)  ||  (left == LINE_WHITE_VALUE)  )
    
     {
          if ((middle_left == LINE_BLACK_VALUE && left == LINE_BLACK_VALUE && middle_right == LINE_BLACK_VALUE) || (left == LINE_WHITE_VALUE))    {
            Serial.println("TURN RIGHT");
             TURN_RIGHT();
            left_speed_front = 80;
            right_speed_front = 120;
          } else {
            Serial.println("TURN LEFT");
             TURN_LEFT();
            left_speed_front = 120;
            right_speed_front = 80;
          }


    } 



   else if (middle_left == LINE_WHITE_VALUE && (middle_right == LINE_BLACK_VALUE || right == LINE_BLACK_VALUE) )  
    {
      
    Serial.println("TURN RIGHT");
      TURN_AHEAD();

    left_speed_front = 0;
    right_speed_front = SPEED;
  } else if ((middle_right == LINE_WHITE_VALUE && (middle_left == LINE_BLACK_VALUE || left == LINE_BLACK_VALUE) ) ) {
   Serial.println("TURN LEFT");
   TURN_AHEAD();
    left_speed_front = SPEED;
    right_speed_front = 0;
  } else {
    TURN_AHEAD();

    left_speed_front = 0;
    right_speed_front = SPEED;

  }
   }
   




   if (mode == 1) {
      analogWrite(ENB, left_speed_front);
      analogWrite(ENA, right_speed_front);

   }


 
}
