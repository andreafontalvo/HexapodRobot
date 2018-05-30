
//LIBRARIES
#include <Servo.h>

//GLOBAL VARIABLES
int cc = 0;
void MoveCommand(int s11o, int s21o, int s31o, int s41o, int s51o, int s61o,
                 int s12o, int s22o, int s32o, int s42o, int s52o, int s62o,
                 int s13o, int s23o, int s33o, int s43o, int s53o, int s63o,
                 int DelayTime);
void wakeUp();
void Walk();
void WalkBackward();
void Left();
void Right();

//PAW1            //PAW2            //PAW3            //PAW4            //PAW5            //PAW6
int mpS11 = 94;   int mpS21 = 104;  int mpS31 = 90;   int mpS41 = 94;   int mpS51 = 85;   int mpS61 = 95;
int mpS12 = 102;  int mpS22 = 109;  int mpS32 = 101;  int mpS42 = 100;  int mpS52 = 99;   int mpS62 = 93;
int mpS13 = 94;   int mpS23 = 93;   int mpS33 = 98;   int mpS43 = 89;   int mpS53 = 90;   int mpS63 = 95;
int s11i = 97;    int s21i = 103;   int s31i = 91;    int s41i = 94;    int s51i = 86;    int s61i = 95;
int s12i = 90;    int s22i = 97;    int s32i = 89;    int s42i = 87;    int s52i = 85;    int s62i = 80;
int s13i = 13;    int s23i = 9;     int s33i = 15;    int s43i = 3;     int s53i = 5;     int s63i = 7;

//SERVO-PAW DISCRIMINATION
//PAW1    //PAW2    //PAW3    //PAW4    //PAW5    //PAW6
Servo S11; Servo S21; Servo S31; Servo S41; Servo S51; Servo S61;
Servo S12; Servo S22; Servo S32; Servo S42; Servo S52; Servo S62;
Servo S13; Servo S23; Servo S33; Servo S43; Servo S53; Servo S63;

void setup() {
  //COMUNICATION INITIALIZATION
  Serial.begin(9600);
  //SERVO-PIN ATTACH
  //PAW1            //PAW2            //PAW3            //PAW4            //PAW5            //PAW6
  S11.attach(2);    S21.attach(5);    S31.attach(8);    S41.attach(45);   S51.attach(42);   S61.attach(39);
  S12.attach(3);    S22.attach(6);    S32.attach(9);    S42.attach(44);   S52.attach(41);   S62.attach(38);
  S13.attach(4);    S23.attach(7);    S33.attach(10);   S43.attach(43);   S53.attach(40);   S63.attach(37);
  S11.write(s11i);  S21.write(s21i);  S31.write(s31i);  S41.write(s41i);  S51.write(s51i);  S61.write(s61i);
  S12.write(s12i);  S22.write(s22i);  S32.write(s32i);  S42.write(s42i);  S52.write(s52i);  S62.write(s62i);
  S13.write(s13i);  S23.write(s23i);  S33.write(s33i);  S43.write(s43i);  S53.write(s53i);  S63.write(s63i);
  delay(3000);
}

void loop() {
  if (cc == 0) {
    wakeUp();

    delay(10);
    cc = 1;
  }
}

//FUNCTION MOVES PER AXIS
void MoveCommand(int s11o, int s21o, int s31o, int s41o, int s51o, int s61o,
                 int s12o, int s22o, int s32o, int s42o, int s52o, int s62o,
                 int s13o, int s23o, int s33o, int s43o, int s53o, int s63o,
                 int DelayTime) {
  //CALCULATE SWEEP ANGLES
  float SweepAngles[18];
  SweepAngles[0] = s11o - s11i;  SweepAngles[1] = s12o - s12i;  SweepAngles[2] = s13o - s13i;
  SweepAngles[3] = s21o - s21i;  SweepAngles[4] = s22o - s22i;  SweepAngles[5] = s23o - s23i;
  SweepAngles[6] = s31o - s31i;  SweepAngles[7] = s32o - s32i;  SweepAngles[8] = s33o - s33i;
  SweepAngles[9] = s41o - s41i;  SweepAngles[10] = s42o - s42i; SweepAngles[11] = s43o - s43i;
  SweepAngles[12] = s51o - s51i; SweepAngles[13] = s52o - s52i; SweepAngles[14] = s53o - s53i;
  SweepAngles[15] = s61o - s61i; SweepAngles[16] = s62o - s62i; SweepAngles[17] = s63o - s63i;
  //CALCULATE FOR LOOP LIMIT
  int Limit = 180;
  for (int j = 0 ; j <= 17 ; j++) {
    if (SweepAngles[j] != 0) {
      Limit = min(abs(SweepAngles[j]), Limit);
    }
  }
  if (Limit == 1) {
    Limit = 30;
  }
  //EXECUTE SERVO MOVES
  for (int k = 0 ; k <= Limit ; k++) {
    if (SweepAngles[0] == 0) {
      S11.write(s11o);
    } else {
      S11.write(s11i + (SweepAngles[0] / Limit)*k);
    }
    if (SweepAngles[1] == 0) {
      S12.write(s12o);
    } else {
      S12.write(s12i + (SweepAngles[1] / Limit)*k);
    }
    if (SweepAngles[2] == 0) {
      S13.write(s13o);
    } else {
      S13.write(s13i + (SweepAngles[2] / Limit)*k);
    }
    if (SweepAngles[3] == 0) {
      S21.write(s21o);
    } else {
      S21.write(s21i + (SweepAngles[3] / Limit)*k);
    }
    if (SweepAngles[4] == 0) {
      S22.write(s22o);
    } else {
      S22.write(s22i + (SweepAngles[4] / Limit)*k);
    }
    if (SweepAngles[5] == 0) {
      S23.write(s23o);
    } else {
      S23.write(s23i + (SweepAngles[5] / Limit)*k);
    }
    if (SweepAngles[6] == 0) {
      S31.write(s31o);
    } else {
      S31.write(s31i + (SweepAngles[6] / Limit)*k);
    }
    if (SweepAngles[7] == 0) {
      S32.write(s32o);
    } else {
      S32.write(s32i + (SweepAngles[7] / Limit)*k);
    }
    if (SweepAngles[8] == 0) {
      S33.write(s33o);
    } else {
      S33.write(s33i + (SweepAngles[8] / Limit)*k);
    }
    if (SweepAngles[9] == 0) {
      S41.write(s41o);
    } else {
      S41.write(s41i + (SweepAngles[9] / Limit)*k);
    }
    if (SweepAngles[10] == 0) {
      S42.write(s42o);
    } else {
      S42.write(s42i + (SweepAngles[10] / Limit)*k);
    }
    if (SweepAngles[11] == 0) {
      S43.write(s43o);
    } else {
      S43.write(s43i + (SweepAngles[11] / Limit)*k);
    }

    if (SweepAngles[12] == 0) {
      S51.write(s51o);
    } else {
      S51.write(s51i + (SweepAngles[12] / Limit)*k);
    }
    if (SweepAngles[13] == 0) {
      S52.write(s52o);
    } else {
      S52.write(s52i + (SweepAngles[13] / Limit)*k);
    }
    if (SweepAngles[14] == 0) {
      S53.write(s53o);
    } else {
      S53.write(s53i + (SweepAngles[14] / Limit)*k);
    }
    if (SweepAngles[15] == 0) {
      S61.write(s61o);
    } else {
      S61.write(s61i + (SweepAngles[15] / Limit)*k);
    }
    if (SweepAngles[16] == 0) {
      S62.write(s62o);
    } else {
      S62.write(s62i + (SweepAngles[16] / Limit)*k);
    }
    if (SweepAngles[17] == 0) {
      S63.write(s63o);
    } else {
      S63.write(s63i + (SweepAngles[17] / Limit)*k);
    }
    delay(DelayTime);
  }
  //ASSIGN FINAL ANGLES AS BEGIN ANGLES
  s11i = s11o;  s21i = s21o;  s31i = s31o;  s41i = s41o;  s51i = s51o;  s61i = s61o;
  s12i = s12o;  s22i = s22o;  s32i = s32o;  s42i = s42o;  s52i = s52o;  s62i = s62o;
  s13i = s13o;  s23i = s23o;  s33i = s33o;  s43i = s43o;  s53i = s53o;  s63i = s63o;
}

void wakeUp() {
//11094N12102N13094N21104N22109N23094N31091N32101N33098N
//41094N42100N43089N51085N52099N53090N61095N62093N63095N
MoveCommand( 94, 104, 91, 94, 85, 95, 
             102, 109, 101, 100, 99, 93, 
             94, 94, 98, 89, 90, 95, 
             10);

//11094N12102N13094N21044N22109N23094N31091N32101N33068N
//41094N42100N43059N51025N52099N53090N61095N62093N63095N
MoveCommand( 94, 44, 91, 94, 25, 95, 
             102, 109, 101, 100, 99, 93, 
             94, 94, 68, 59, 90, 95, 
             10);

//11094N12102N13064N21164N22109N23094N31091N32101N33098N
//41094N42100N43089N51145N52099N53090N61095N62093N63065N
MoveCommand( 94, 164, 91, 94, 145, 95, 
             102, 109, 101, 100, 99, 93, 
             64, 94, 98, 89, 90, 65, 
             10);

//11094N12102N13094N21104N22109N23094N31091N32101N33098N
//41094N42100N43089N51085N52099N53090N61095N62093N63095N
MoveCommand( 94, 104, 91, 94, 85, 95, 
             102, 109, 101, 100, 99, 93, 
             94, 94, 98, 89, 90, 95, 
             10);

          


}

