#define LEFT_SENSOR 11
#define RIGHT_SENSOR 8
#define MIDDLE_LEFT_SENSOR 10
#define MIDDLE_RIGHT_SENSOR 9

#define IR_MIDDLE A2


#define SPEED 80
#define LINE_BLACK_VALUE 0
#define LINE_WHITE_VALUE 1

int EN_RIGHT = 3; // PWM
int IN1 = 2; 
int IN2 = 4;

int EN_LEFT = 5; // PWM
int IN3 = 6;
int IN4 = 7;
bool lock = false;



void TURN_LEFT() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void TURN_RIGHT() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void TURN_AHEAD() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void TURN_BACK() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(EN_RIGHT, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(EN_LEFT, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(EN_RIGHT, 100);
  analogWrite(EN_LEFT, 100);

  
  
}

int left_speed_front = 0;
int right_speed_front = 0;


unsigned long tag = 0, interval = 500;
// lui - phai - thang - trai - thang - trai - thang - phai - thang
int delays[9] = {100, 500, 200, 500, 1000, 500, 200, 500, 1000};
uint8_t sequence = 255;

bool vatCan = false;
bool done = false;
bool line = false;

void loop() {

    int irSensorCenter = analogRead(IR_MIDDLE);

    int right = digitalRead(RIGHT_SENSOR);
    int left = digitalRead(LEFT_SENSOR);
    int middle_right = digitalRead(MIDDLE_RIGHT_SENSOR);
    int middle_left = digitalRead(MIDDLE_LEFT_SENSOR);

    if (left == LINE_WHITE_VALUE  || right == LINE_WHITE_VALUE ) {
        lock = true;
    } 

    
    // Serial.print("right:");
    // Serial.print(right);
    // Serial.print(" - ");
    // Serial.print("middle right:");
    // Serial.print(middle_right);
    // Serial.print(" - ");
    // Serial.print("leftt:");
    // Serial.print(left);
    // Serial.print(" - ");
    // Serial.print("middle left:");
    // Serial.print(middle_left);
    // Serial.println("");
    // delay(800);


   if (line == false) {
  if (irSensorCenter < 500 && done == false) {
    
    sequence = 0;    
    tag = millis();
    done = true;
  }
  
    
  if (sequence < 9 && (millis() - tag > delays[sequence])) {
    tag = millis();
    if (sequence != 255 && sequence < 9) sequence++;
     Serial.println(sequence);
  }
   

  switch (sequence) {
    case 0:
    TURN_BACK();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;
    
    case 1:
    TURN_RIGHT();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;
    
    case 2:
    TURN_AHEAD();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;
    
    case 3:
    TURN_LEFT();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;
    
    case 4:
    TURN_AHEAD();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);;
    break;
    
    case 5:
    TURN_LEFT();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;
    
    case 6:
    TURN_AHEAD();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;

    case 7:
    TURN_RIGHT();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;

    case 8:
    TURN_AHEAD();
    left_speed_front = 100;
    right_speed_front = 100;
    analogWrite(EN_LEFT, left_speed_front);
    analogWrite(EN_RIGHT, right_speed_front);
    break;
    
  }
   }



  // // END
  if ((sequence > 8 && sequence != 255) || (left == LINE_WHITE_VALUE && middle_left == LINE_WHITE_VALUE) || (right == LINE_WHITE_VALUE && middle_right == LINE_WHITE_VALUE)) { 
    // AHEAD
    sequence = 255;
    // DO LINE
    line = true;
  }

 if (line == true) {

   if (right == LINE_BLACK_VALUE &&  middle_right == LINE_BLACK_VALUE && left == LINE_BLACK_VALUE && middle_left == LINE_BLACK_VALUE && !lock) {
        Serial.println("TURN RIGHT");
        TURN_RIGHT();
        left_speed_front = 70;
        right_speed_front = 100;
    }
  

    // 90
    else if ( left == LINE_WHITE_VALUE && (left == LINE_WHITE_VALUE && middle_left == LINE_WHITE_VALUE) || 
    (left == LINE_WHITE_VALUE && middle_left == LINE_WHITE_VALUE && middle_right == LINE_WHITE_VALUE )  && lock ) {
      
        Serial.println("TURN RIGHT AA");
        TURN_RIGHT();
        left_speed_front = 100;
        right_speed_front = 180;
          if (left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE ) {
                  lock = false;
        }
    } 
     else if ( right == LINE_WHITE_VALUE && (right == LINE_WHITE_VALUE && middle_right == LINE_WHITE_VALUE) || (right == LINE_WHITE_VALUE && middle_right == LINE_WHITE_VALUE && middle_left == LINE_WHITE_VALUE) && lock ) {
        Serial.println("TURN LEFT BB");
       
        TURN_LEFT();
        left_speed_front = 180;
        right_speed_front = 100;
         if (left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE  ) {
             lock = false;
        }
    }
    else if ((middle_left == LINE_WHITE_VALUE   || middle_right == LINE_WHITE_VALUE) && (left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE )    ) {
      Serial.println("FORWARD");
      lock = false;

      TURN_AHEAD();
      left_speed_front = 80;
      right_speed_front = 80;
    } 
     else  if (left == LINE_BLACK_VALUE && !lock) {
        Serial.println("TURN LEFT CC");
        TURN_AHEAD();

        if (middle_left ==  LINE_BLACK_VALUE && middle_right ==  LINE_WHITE_VALUE) {
          left_speed_front = 80;
          right_speed_front = 80;
        } else {
          left_speed_front = 100;
           right_speed_front = 70;
        }
      
    }
    else  if (right == LINE_BLACK_VALUE   && !lock )  {
        Serial.println("TURN RIGHT");
        TURN_AHEAD();
       
           if (middle_right ==  LINE_BLACK_VALUE && middle_left == LINE_WHITE_VALUE) {
          left_speed_front = 80;
          right_speed_front = 80;
        } else {
          left_speed_front = 70;
          right_speed_front = 100;
        }
    } 


   
  
  
     analogWrite(EN_LEFT, left_speed_front);
     analogWrite(EN_RIGHT, right_speed_front);
  
   }
}
