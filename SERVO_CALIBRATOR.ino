//LIBRARIES
#include <Servo.h>

//GLOBAL VARIABLES
void Sniffer();
void PrintList();
void ServoCalibrator();
int CharParser(char in);
char input_console;
int paw_selected = 0;
int servo_selected = 0;
//int mpS11 = 94; int mpS21 = 104; int mpS31 = 89; int mpS41 = 94; int mpS51 = 85; int mpS61 = 95;
//int mpS12 = 102; int mpS22 = 109; int mpS32 = 101; int mpS42 = 100; int mpS52 = 99; int mpS62 = 93;
//int mpS13 = 94; int mpS23 = 93; int mpS33 = 98; int mpS43 = 89; int mpS53 = 90; int mpS63 = 95;

int mpS11 = 94;   int mpS21 = 104;  int mpS31 = 90;   int mpS41 = 94;   int mpS51 = 85;   int mpS61 = 95;
int mpS12 = 102;  int mpS22 = 109;  int mpS32 = 101;  int mpS42 = 100;  int mpS52 = 99;   int mpS62 = 93;
int mpS13 = 94;   int mpS23 = 93;   int mpS33 = 98;   int mpS43 = 89;   int mpS53 = 90;   int mpS63 = 95;

//SERVO-PAW DISCRIMINATION
//PAW1    //PAW2    //PAW3    //PAW4    //PAW5    //PAW6
Servo S11; Servo S21; Servo S31; Servo S41; Servo S51; Servo S61;
Servo S12; Servo S22; Servo S32; Servo S42; Servo S52; Servo S62;
Servo S13; Servo S23; Servo S33; Servo S43; Servo S53; Servo S63;

void setup() {
  Serial.begin(9600);
  //SERVO-PIN ATTACH
  //PAW1        //PAW2        //PAW3        //PAW4         //PAW5         //PAW6
  S11.attach(40);    S21.attach(44);    S31.attach(32);    S41.attach(36);   S51.attach(24);   S61.attach(28);
  S12.attach(39);    S22.attach(43);    S32.attach(31);    S42.attach(35);   S52.attach(23);   S62.attach(27);
  S13.attach(38);    S23.attach(42);    S33.attach(30);   S43.attach(34);   S53.attach(22);   S63.attach(26);
  S11.write(mpS11);S21.write(mpS21);S31.write(mpS31);S41.write(mpS41);S51.write(mpS51);S61.write(mpS61);
  S12.write(mpS12);S22.write(mpS22);S32.write(mpS32);S42.write(mpS42);S52.write(mpS52);S62.write(mpS62);
  S13.write(mpS13);S23.write(mpS23);S33.write(mpS33);S43.write(mpS43);S53.write(mpS53);S13.write(mpS63);
  Serial.println("SERVO MOTOR CALIBRATOR TOOL");
}

void loop() {
salto1:
  Serial.println("TYPE IN PAW NUMBER (1 - 6):");
salto2:
  Sniffer();
  paw_selected = CharParser(input_console);
  if (paw_selected != 0 && paw_selected < 7) {
    Serial.print("THE PAW SELECTED WAS ");
    Serial.print(paw_selected);
    Serial.println(".");
    Serial.println("");
    goto salto3;
  } else if (paw_selected != 0) {
    Serial.println("SELECTED PAW DOESN'T EXIST, TRY AGAIN.");
    goto salto1;
  }
  goto salto2;
salto3:
  Serial.println("TYPE IN SERVO MOTOR NUMBER (1 - 3) OR 'Q' TO RETURN");
salto4:
  Sniffer();
  if (input_console == 'Q') {
    Serial.println("");
    goto salto1;
  } else if (isDigit(input_console)) {
    servo_selected = CharParser(input_console);
    if (servo_selected > 3) {
      Serial.println("SELECTED SERVO DOESN'T EXIST, TRY AGAIN.");
      goto salto3;
    } else {
      Serial.print("THE SERVO MOTOR SELECTED WAS ");
      Serial.print(servo_selected);
      Serial.print(" FROM PAW NUMBER ");
      Serial.print(paw_selected);
      Serial.println(".");
      Serial.println("");
    }
  } else {
    goto salto4;
  }
  ServoCalibrator();
  Serial.println("TO PRINT THE LIST OF MIDDLE POINTS TYPE 'Y' OR 'N' TO GO ON WITH OTHER SERVO MOTOR CALIBRATION");
  Serial.println("");
salto24:
  Sniffer();
  if (input_console == 'Y') {
    PrintList();
  } else if (input_console == 'N') {
    Serial.println("");
    goto salto1;
  } else {
    goto salto24;
  }
}

//SNIFFER FUNCTION
void Sniffer() {
  input_console = '0';
  if (Serial.available() > 0) {
    input_console = Serial.read();
  }
}

//FUNCTION PARSER: CHAR TO INT
int CharParser(char in) {
  int result;
  String parser;
  parser = in;
  result = parser.toInt();
  return result;
}

//FUNCTION SERVO CALIBRATOR
void ServoCalibrator() {
salto5:
  Serial.println("CALIBRATION IN PROCCESS... DONT TOUCH");
  Serial.println("SETTING UP THE POSITION TO 90 GRADES... DONT TOUCH");
  Serial.println("");
  delay(1000);
  switch (paw_selected) {
    case 1://CALIBRATE SERVOS FROM PAW NUMBER 1
      switch (servo_selected) {
        case 1:
          mpS11 = 90;
          S11.write(mpS11);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto6:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS11 = mpS11 + 1;
            S11.write(mpS11);
            goto salto6;
          } else if (input_console == '-') {
            mpS11 = mpS11 - 1;
            S11.write(mpS11);
            goto salto6;
          } else {
            goto salto6;
          }
          break;
        case 2:
          mpS12 = 90;
          S12.write(mpS12);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto7:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS12 = mpS12 + 1;
            S12.write(mpS12);
            goto salto7;
          } else if (input_console == '-') {
            mpS12 = mpS12 - 1;
            S12.write(mpS12);
            goto salto7;
          } else {
            goto salto7;
          }
          break;
        case 3:
          mpS13 = 90;
          S13.write(mpS13);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto8:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS13 = mpS13 + 1;
            S13.write(mpS13);
            goto salto8;
          } else if (input_console == '-') {
            mpS13 = mpS13 - 1;
            S13.write(mpS13);
            goto salto8;
          } else {
            goto salto8;
          }
          break;
      }
      break;
    case 2://CALIBRATE SERVOS FROM PAW NUMBER 2
      switch (servo_selected) {
        case 1:
          mpS21 = 90;
          S21.write(mpS21);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto9:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS21 = mpS21 + 1;
            S21.write(mpS21);
            goto salto9;
          } else if (input_console == '-') {
            mpS21 = mpS21 - 1;
            S21.write(mpS21);
            goto salto9;
          } else {
            goto salto9;
          }
          break;
        case 2:
          mpS22 = 90;
          S22.write(mpS22);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto10:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS22 = mpS22 + 1;
            S22.write(mpS22);
            goto salto10;
          } else if (input_console == '-') {
            mpS22 = mpS22 - 1;
            S22.write(mpS22);
            goto salto10;
          } else {
            goto salto10;
          }
          break;
        case 3:
          mpS23 = 90;
          S23.write(mpS23);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto11:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS23 = mpS23 + 1;
            S23.write(mpS23);
            goto salto11;
          } else if (input_console == '-') {
            mpS23 = mpS23 - 1;
            S23.write(mpS23);
            goto salto11;
          } else {
            goto salto11;
          }
          break;
      }
      break;
    case 3://CALIBRATE SERVOS FROM PAW NUMBER 3
      switch (servo_selected) {
        case 1:
          mpS31 = 90;
          S31.write(mpS31);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto12:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS31 = mpS31 + 1;
            S31.write(mpS31);
            goto salto12;
          } else if (input_console == '-') {
            mpS31 = mpS31 - 1;
            S31.write(mpS31);
            goto salto12;
          } else {
            goto salto12;
          }
          break;
        case 2:
          mpS32 = 90;
          S32.write(mpS32);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto13:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS32 = mpS32 + 1;
            S32.write(mpS32);
            goto salto13;
          } else if (input_console == '-') {
            mpS32 = mpS32 - 1;
            S32.write(mpS32);
            goto salto13;
          } else {
            goto salto13;
          }
          break;
        case 3:
          mpS33 = 90;
          S33.write(mpS33);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto14:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS33 = mpS33 + 1;
            S33.write(mpS33);
            goto salto14;
          } else if (input_console == '-') {
            mpS33 = mpS33 - 1;
            S33.write(mpS33);
            goto salto14;
          } else {
            goto salto14;
          }
          break;
      }
      break;
    case 4://CALIBRATE SERVOS FROM PAW NUMBER 4
      switch (servo_selected) {
        case 1:
          mpS41 = 90;
          S41.write(mpS41);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto15:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS41 = mpS41 + 1;
            S41.write(mpS41);
            goto salto15;
          } else if (input_console == '-') {
            mpS41 = mpS41 - 1;
            S41.write(mpS41);
            goto salto15;
          } else {
            goto salto15;
          }
          break;
        case 2:
          mpS42 = 90;
          S42.write(mpS42);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto16:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS42 = mpS42 + 1;
            S42.write(mpS42);
            goto salto16;
          } else if (input_console == '-') {
            mpS42 = mpS42 - 1;
            S42.write(mpS42);
            goto salto16;
          } else {
            goto salto16;
          }
          break;
        case 3:
          mpS43 = 90;
          S43.write(mpS43);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto17:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS43 = mpS43 + 1;
            S43.write(mpS43);
            goto salto17;
          } else if (input_console == '-') {
            mpS43 = mpS43 - 1;
            S43.write(mpS43);
            goto salto17;
          } else {
            goto salto17;
          }
          break;
      }
      break;
    case 5://CALIBRATE SERVOS FROM PAW NUMBER 5
      switch (servo_selected) {
        case 1:
          mpS51 = 90;
          S51.write(mpS51);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto18:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS51 = mpS51 + 1;
            S51.write(mpS51);
            goto salto18;
          } else if (input_console == '-') {
            mpS51 = mpS51 - 1;
            S51.write(mpS51);
            goto salto18;
          } else {
            goto salto18;
          }
          break;
        case 2:
          mpS52 = 90;
          S52.write(mpS52);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto19:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS52 = mpS52 + 1;
            S52.write(mpS52);
            goto salto19;
          } else if (input_console == '-') {
            mpS52 = mpS52 - 1;
            S52.write(mpS52);
            goto salto19;
          } else {
            goto salto19;
          }
          break;
        case 3:
          mpS53 = 90;
          S53.write(mpS53);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto20:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS53 = mpS53 + 1;
            S53.write(mpS53);
            goto salto20;
          } else if (input_console == '-') {
            mpS53 = mpS53 - 1;
            S53.write(mpS53);
            goto salto20;
          } else {
            goto salto20;
          }
          break;
      }
      break;
    case 6://CALIBRATE SERVOS FROM PAW NUMBER 6
      switch (servo_selected) {
        case 1:
          mpS61 = 90;
          S61.write(mpS61);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto21:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS61 = mpS61 + 1;
            S61.write(mpS61);
            goto salto21;
          } else if (input_console == '-') {
            mpS61 = mpS61 - 1;
            S61.write(mpS61);
            goto salto21;
          } else {
            goto salto21;
          }
          break;
        case 2:
          mpS62 = 90;
          S62.write(mpS62);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto22:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS62 = mpS62 + 1;
            S62.write(mpS62);
            goto salto22;
          } else if (input_console == '-') {
            mpS62 = mpS62 - 1;
            S62.write(mpS62);
            goto salto22;
          } else {
            goto salto22;
          }
          break;
        case 3:
          mpS63 = 90;
          S63.write(mpS63);
          Serial.println("   TYPE   |     ACTION  ");
          Serial.println("----------------------------");
          Serial.println("    +     |   PLUS GRADE ");
          Serial.println("    -     | SUBTRACT GRADE ");
          Serial.println("    R     |   RECALIBRATE ");
          Serial.println("    Q     |      EXIT ");
salto23:
          Sniffer();
          if (input_console == 'Q') {
            Serial.println("");
          } else if (input_console == 'R') {
            Serial.println("");
            goto salto5;
          } else if (input_console == '+') {
            mpS63 = mpS63 + 1;
            S63.write(mpS63);
            goto salto23;
          } else if (input_console == '-') {
            mpS63 = mpS63 - 1;
            S63.write(mpS63);
            goto salto23;
          } else {
            goto salto23;
          }
          break;
      }
      break;
  }
}
void PrintList(){
  String row;
  Serial.println("  PAW  |  SERVO  |  MIDDLE POINT");
  Serial.println("---------------------------------");
  row ="   1   |    1    |       " + String(mpS11);
  Serial.println(row);
  row ="   1   |    2    |       " + String(mpS12);
  Serial.println(row);
  row ="   1   |    3    |       " + String(mpS13);
  Serial.println(row);
  Serial.println("---------------------------------");
  row ="   2   |    1    |       " + String(mpS21);
  Serial.println(row);
  row ="   2   |    2    |       " + String(mpS22);
  Serial.println(row);
  row ="   2   |    3    |       " + String(mpS23);
  Serial.println(row);
  Serial.println("---------------------------------");
  row ="   3   |    1    |       " + String(mpS31);
  Serial.println(row);
  row ="   3   |    2    |       " + String(mpS32);
  Serial.println(row);
  row ="   3   |    3    |       " + String(mpS33);
  Serial.println(row);
  Serial.println("---------------------------------");
  row ="   4   |    1    |       " + String(mpS41);
  Serial.println(row);
  row ="   4   |    2    |       " + String(mpS42);
  Serial.println(row);
  row ="   4   |    3    |       " + String(mpS43);
  Serial.println(row);
  Serial.println("---------------------------------");
  row ="   5   |    1    |       " + String(mpS51);
  Serial.println(row);
  row ="   5   |    2    |       " + String(mpS52);
  Serial.println(row);
  row ="   5   |    3    |       " + String(mpS53);
  Serial.println(row);
  Serial.println("---------------------------------");
  row ="   6   |    1    |       " + String(mpS61);
  Serial.println(row);
  row ="   6   |    2    |       " + String(mpS62);
  Serial.println(row);
  row ="   6   |    3    |       " + String(mpS63);
  Serial.println(row);
  Serial.println("---------------------------------");
  Serial.println("");
  }
