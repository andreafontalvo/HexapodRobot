//LIBRARIES
#include <Servo.h>

//GLOBAL VARIABLES
char input_console;
int string_cursor = 0;
int paw_selected;
int servo_selected;
int Angle;
int centinela;
int aux;
String aux2 = "";
void Sniffer();
void PrintList();
int CharParser(char in);
void CommandParser(int paw, int servo, int angle);

//PAW1            //PAW2            //PAW3            //PAW4            //PAW5            //PAW6
int mpS11 = 94;   int mpS21 = 104;  int mpS31 = 93;   int mpS41 = 94;   int mpS51 = 85;   int mpS61 = 100;
int mpS12 = 102;  int mpS22 = 109;  int mpS32 = 101;  int mpS42 = 100;  int mpS52 = 99;   int mpS62 = 90;
int mpS13 = 94;   int mpS23 = 93;   int mpS33 = 98;   int mpS43 = 89;   int mpS53 = 90;   int mpS63 = 90;
int s11i = 97;    int s21i = 103;   int s31i = 91;    int s41i = 94;    int s51i = 86;    int s61i = 95;
int s12i = 90;    int s22i = 97;    int s32i = 89;    int s42i = 87;    int s52i = 85;    int s62i = 80;
int s13i = 13;    int s23i = 9;     int s33i = 15;    int s43i = 3;     int s53i = 5;     int s63i = 7;

//SERVO-PAW DISCRIMINATI    |ON
//PAW1    //PAW2    //PAW3    //PAW4    //PAW5    //PAW6
Servo S11; Servo S21; Servo S31; Servo S41; Servo S51; Servo S61;
Servo S12; Servo S22; Servo S32; Servo S42; Servo S52; Servo S62;
Servo S13; Servo S23; Servo S33; Servo S43; Servo S53; Servo S63;

void setup() {
  //COMUNICATION INITIALIZATION
  Serial.begin(9600);
  //SERVO-PIN ATTACH
  //PAW1            //PAW2            //PAW3            //PAW4            //PAW5            //PAW6
  S11.attach(40);    S21.attach(44);    S31.attach(32);    S41.attach(36);   S51.attach(24);   S61.attach(28);
  S12.attach(39);    S22.attach(43);    S32.attach(31);    S42.attach(35);   S52.attach(23);   S62.attach(27);
  S13.attach(38);    S23.attach(42);    S33.attach(30);    S43.attach(34);   S53.attach(22);   S63.attach(26);
  S11.write(s11i);   S21.write(s21i);   S31.write(s31i);   S41.write(s41i);  S51.write(s51i);  S61.write(s61i);
  S12.write(s12i);   S22.write(s22i);   S32.write(s32i);   S42.write(s42i);  S52.write(s52i);  S62.write(s62i);
  S13.write(s13i);   S23.write(s23i);   S33.write(s33i);   S43.write(s43i);  S53.write(s53i);  S63.write(s63i);
  Serial.println("MOVES CREATOR");
  Serial.println("");
}

void loop() {
jump0:
  Serial.println("COMMAND STRUCTURE : PSABC");
  Serial.println("P : PAW NUMBER");
  Serial.println("S : SERVO NUMBER");
  Serial.println("A : 'M' MIDDLE POINT PLUS OR 'N' MIDDLE POINT SUBTRACTION OR HUNDRED NUMBER");
  Serial.println("B : TEN NUMBER");
  Serial.println("C : UNIT NUMBER");
  Serial.println("");
  Serial.println("TYPE A COMMAND...");
jump00:
  char configuration_word[4];
jump1:
  Sniffer();
  configuration_word[string_cursor] = input_console;
  string_cursor = string_cursor + 1;
  if (string_cursor < 5) {
    goto jump1;
  } else {
    goto jump2;
  }
jump2:
  string_cursor = 0;
  Serial.print("COMMAND: ");
  Serial.println(configuration_word);
  paw_selected = CharParser(configuration_word[0]);
  servo_selected = CharParser(configuration_word[1]);
  Serial.print("PAW: ");
  Serial.println(paw_selected);
  Serial.print("SERVO: ");
  Serial.println(servo_selected);
  Serial.print("ANGLE: ");
  if (isDigit(configuration_word[2])) {
    Angle = CharParser(configuration_word[2]) * 100;
    centinela = 1;
  } else {
    aux = CharParser(configuration_word[4]) + CharParser(configuration_word[3]) * 10;
    aux2 = configuration_word[2];
    if (aux2 == "M") {
      Serial.print("MP + ");
      Serial.print(aux);
      centinela = 1;
    } else {
      Serial.print("MP - ");
      Serial.print(aux);
      centinela = 2;
    }
    Serial.print(" = ");
    if (paw_selected == 1 && servo_selected == 1) {
      Angle = mpS11;
    }
    if (paw_selected == 1 && servo_selected == 2) {
      Angle = mpS12;
    }
    if (paw_selected == 1 && servo_selected == 3) {
      Angle = mpS13;
    }
    if (paw_selected == 2 && servo_selected == 1) {
      Angle = mpS21;
    }
    if (paw_selected == 2 && servo_selected == 2) {
      Angle = mpS22;
    }
    if (paw_selected == 2 && servo_selected == 3) {
      Angle = mpS13;
    }
    if (paw_selected == 3 && servo_selected == 1) {
      Angle = mpS31;
    }
    if (paw_selected == 3 && servo_selected == 2) {
      Angle = mpS32;
    }
    if (paw_selected == 3 && servo_selected == 3) {
      Angle = mpS33;
    }
    if (paw_selected == 4 && servo_selected == 1) {
      Angle = mpS41;
    }
    if (paw_selected == 4 && servo_selected == 2) {
      Angle = mpS42;
    }
    if (paw_selected == 4 && servo_selected == 3) {
      Angle = mpS43;
    }
    if (paw_selected == 5 && servo_selected == 1) {
      Angle = mpS51;
    }
    if (paw_selected == 5 && servo_selected == 2) {
      Angle = mpS52;
    }
    if (paw_selected == 5 && servo_selected == 3) {
      Angle = mpS53;
    }
    if (paw_selected == 6 && servo_selected == 1) {
      Angle = mpS61;
    }
    if (paw_selected == 6 && servo_selected == 2) {
      Angle = mpS62;
    }
    if (paw_selected == 6 && servo_selected == 3) {
      Angle = mpS63;
    }
  }
  if (centinela == 1) {
    Angle = Angle + CharParser(configuration_word[4]) + CharParser(configuration_word[3]) * 10;
  } else {
    Angle = Angle - CharParser(configuration_word[4]) - CharParser(configuration_word[3]) * 10;
  }

  Serial.println(Angle);
  if (Angle > 180) {
    Angle = 180;
  }
  CommandParser(paw_selected, servo_selected, Angle);
  Serial.println("TO PRINT THE LIST OF ANGLES TYPE 'Y' OR 'N' TO GO ON WITH OTHER MOVE");
  Serial.println("");
jump3:
  Sniffer();
  if (input_console == 'Y') {
    PrintList();
  } else if (input_console == 'N') {
    Serial.println("");
    goto jump00;
  } else {
    goto jump3;
  }
  delay(100);
}

//SNIFFER FUNCTION
void Sniffer() {
  input_console = 42; // ascii = *
leer:
  char a = (char)Serial.read();
  if (isUpperCase(a) || isDigit(a)) {
    input_console = a;
  } else {
    goto leer;
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

void CommandParser(int paw, int servo, int angle) {
  if (paw == 1 && servo == 1) {
    S11.write(angle);
    s11i = angle;
  }
  if (paw == 1 && servo == 2) {
    S12.write(angle);
    s12i = angle;
  }
  if (paw == 1 && servo == 3) {
    S13.write(angle);
    s13i = angle;
  }
  if (paw == 2 && servo == 1) {
    S21.write(angle);
    s21i = angle;
  }
  if (paw == 2 && servo == 2) {
    S22.write(angle);
    s22i = angle;
  }
  if (paw == 2 && servo == 3) {
    S23.write(angle);
    s23i = angle;
  }
  if (paw == 3 && servo == 1) {
    S31.write(angle);
    s31i = angle;
  }
  if (paw == 3 && servo == 2) {
    S32.write(angle);
    s32i = angle;
  }
  if (paw == 3 && servo == 3) {
    S33.write(angle);
    s33i = angle;
  }
  if (paw == 4 && servo == 1) {
    S41.write(angle);
    s41i = angle;
  }
  if (paw == 4 && servo == 2) {
    S42.write(angle);
    s42i = angle;
  }
  if (paw == 4 && servo == 3) {
    S43.write(angle);
    s43i = angle;
  }
  if (paw == 5 && servo == 1) {
    S51.write(angle);
    s51i = angle;
  }
  if (paw == 5 && servo == 2) {
    S52.write(angle);
    s52i = angle;
  }
  if (paw == 5 && servo == 3) {
    S53.write(angle);
    s53i = angle;
  }
  if (paw == 6 && servo == 1) {
    S61.write(angle);
    s61i = angle;
  }
  if (paw == 6 && servo == 2) {
    S62.write(angle);
    s62i = angle;
  }
  if (paw == 6 && servo == 3) {
    S63.write(angle);
    s63i = angle;
  }
}

void PrintList() {
  String row;
  Serial.println("  PAW  |  SERVO  |  ANGLE");
  Serial.println("---------------------------------");
  row = "   1   |    1    |       " + String(s11i);
  Serial.println(row);
  row = "   1   |    2    |       " + String(s12i);
  Serial.println(row);
  row = "   1   |    3    |       " + String(s13i);
  Serial.println(row);
  Serial.println("---------------------------------");
  row = "   2   |    1    |       " + String(s21i);
  Serial.println(row);
  row = "   2   |    2    |       " + String(s22i);
  Serial.println(row);
  row = "   2   |    3    |       " + String(s23i);
  Serial.println(row);
  Serial.println("---------------------------------");
  row = "   3   |    1    |       " + String(s31i);
  Serial.println(row);
  row = "   3   |    2    |       " + String(s32i);
  Serial.println(row);
  row = "   3   |    3    |       " + String(s33i);
  Serial.println(row);
  Serial.println("---------------------------------");
  row = "   4   |    1    |       " + String(s41i);
  Serial.println(row);
  row = "   4   |    2    |       " + String(s42i);
  Serial.println(row);
  row = "   4   |    3    |       " + String(s43i);
  Serial.println(row);
  Serial.println("---------------------------------");
  row = "   5   |    1    |       " + String(s51i);
  Serial.println(row);
  row = "   5   |    2    |       " + String(s52i);
  Serial.println(row);
  row = "   5   |    3    |       " + String(s53i);
  Serial.println(row);
  Serial.println("---------------------------------");
  row = "   6   |    1    |       " + String(s61i);
  Serial.println(row);
  row = "   6   |    2    |       " + String(s62i);
  Serial.println(row);
  row = "   6   |    3    |       " + String(s63i);
  Serial.println(row);
  Serial.println("---------------------------------");
  Serial.println("");


  Serial.print("//11");
  if (s11i > 99) {
    Serial.print(s11i);
    Serial.print("N");
  } else if (s11i > 9) {
    Serial.print("0");
    Serial.print(s11i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s11i);
    Serial.print("N");
  }
  Serial.print("12");
  if (s12i > 99) {
    Serial.print(s12i);
    Serial.print("N");
  } else if (s12i > 9) {
    Serial.print("0");
    Serial.print(s12i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s12i);
    Serial.print("N");
  }
  Serial.print("13");
  if (s13i > 99) {
    Serial.print(s13i);
    Serial.print("N");
  } else if (s13i > 9) {
    Serial.print("0");
    Serial.print(s13i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s13i);
    Serial.print("N");
  }

  Serial.print("21");
  if (s21i > 99) {
    Serial.print(s21i);
    Serial.print("N");
  } else if (s21i > 9) {
    Serial.print("0");
    Serial.print(s21i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s21i);
    Serial.print("N");
  }
  Serial.print("22");
  if (s22i > 99) {
    Serial.print(s22i);
    Serial.print("N");
  } else if (s22i > 9) {
    Serial.print("0");
    Serial.print(s22i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s22i);
    Serial.print("N");
  }
  Serial.print("23");
  if (s23i > 99) {
    Serial.print(s23i);
    Serial.print("N");
  } else if (s23i > 9) {
    Serial.print("0");
    Serial.print(s23i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s23i);
    Serial.print("N");
  }
  Serial.print("31");
  if (s31i > 99) {
    Serial.print(s31i);
    Serial.print("N");
  } else if (s31i > 9) {
    Serial.print("0");
    Serial.print(s31i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s31i);
    Serial.print("N");
  }
  Serial.print("32");
  if (s32i > 99) {
    Serial.print(s32i);
    Serial.print("N");
  } else if (s32i > 9) {
    Serial.print("0");
    Serial.print(s32i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s32i);
    Serial.print("N");
  }
  Serial.print("33");
  if (s33i > 99) {
    Serial.print(s33i);
    Serial.println("N");
  } else if (s33i > 9) {
    Serial.print("0");
    Serial.print(s33i);
    Serial.println("N");
  } else {
    Serial.print("00");
    Serial.print(s33i);
    Serial.println("N");
  }
  Serial.print("//41");
  if (s41i > 99) {
    Serial.print(s41i);
    Serial.print("N");
  } else if (s41i > 9) {
    Serial.print("0");
    Serial.print(s41i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s41i);
    Serial.print("N");
  }
  Serial.print("42");
  if (s42i > 99) {
    Serial.print(s42i);
    Serial.print("N");
  } else if (s42i > 9) {
    Serial.print("0");
    Serial.print(s42i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s42i);
    Serial.print("N");
  }
  Serial.print("43");
  if (s43i > 99) {
    Serial.print(s43i);
    Serial.print("N");
  } else if (s43i > 9) {
    Serial.print("0");
    Serial.print(s43i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s43i);
    Serial.print("N");
  }
  Serial.print("51");
  if (s51i > 99) {
    Serial.print(s51i);
    Serial.print("N");
  } else if (s51i > 9) {
    Serial.print("0");
    Serial.print(s51i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s51i);
    Serial.print("N");
  }
  Serial.print("52");
  if (s52i > 99) {
    Serial.print(s52i);
    Serial.print("N");
  } else if (s52i > 9) {
    Serial.print("0");
    Serial.print(s52i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s52i);
    Serial.print("N");
  }
  Serial.print("53");
  if (s53i > 99) {
    Serial.print(s53i);
    Serial.print("N");
  } else if (s53i > 9) {
    Serial.print("0");
    Serial.print(s53i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s53i);
    Serial.print("N");
  }

  Serial.print("61");
  if (s61i > 99) {
    Serial.print(s61i);
    Serial.print("N");
  } else if (s61i > 9) {
    Serial.print("0");
    Serial.print(s61i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s61i);
    Serial.print("N");
  }
  Serial.print("62");
  if (s62i > 99) {
    Serial.print(s62i);
    Serial.print("N");
  } else if (s62i > 9) {
    Serial.print("0");
    Serial.print(s62i);
    Serial.print("N");
  } else {
    Serial.print("00");
    Serial.print(s62i);
    Serial.print("N");
  }
  Serial.print("63");
  if (s63i > 99) {
    Serial.print(s63i);
    Serial.println("N");
  } else if (s63i > 9) {
    Serial.print("0");
    Serial.print(s63i);
    Serial.println("N");
  } else {
    Serial.print("00");
    Serial.print(s63i);
    Serial.println("N");
  }
  Serial.print("MoveCommand( "); Serial.print(String(s11i) + ", "); Serial.print(String(s21i) + ", "); Serial.print(String(s31i) + ", "); Serial.print(String(s41i) + ", "); Serial.print(String(s51i) + ", "); Serial.println(String(s61i) + ", ");
  Serial.print("             "); Serial.print(String(s12i) + ", "); Serial.print(String(s22i) + ", "); Serial.print(String(s32i) + ", "); Serial.print(String(s42i) + ", "); Serial.print(String(s52i) + ", "); Serial.println(String(s62i) + ", ");
  Serial.print("             "); Serial.print(String(s13i) + ", "); Serial.print(String(s23i) + ", "); Serial.print(String(s33i) + ", "); Serial.print(String(s43i) + ", "); Serial.print(String(s53i) + ", "); Serial.println(String(s63i) + ", ");
  Serial.print("             "); Serial.println("10);"); Serial.println("");
}
