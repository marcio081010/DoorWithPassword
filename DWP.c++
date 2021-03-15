#include <Keypad.h> // LIBRARY FOR THE OPERATION OF THE MEMBRANE KEYBOARD
#include <Servo.h> // LIBRARY FOR SERVO OPERATION

Servo servo_Motor; //SERVANT OBJECT
char* password = "123"; //CORRECT PASSWORD TO UNLOCK THE LOCK
int position = 0; //VARIABLE FOR POSITION READING OF THE PRESSED KEY
const byte ROWS = 4; //NUMBER OF KEYBOARD LINES
const byte COLS = 4; //NUMBER OF KEYBOARD SPEAKERS
char keys[ROWS][COLS] = { //DECLARATION OF KEYBOARD NUMBERS, LETTERS AND CHARACTERS
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 8, 7, 6, 1 }; //KEYBOARD LINES CONNECTION PINS
byte colPins[COLS] = { 5, 4, 3, 0 }; //KEYBOARD SPEAKER CONNECTION PINS
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//THE VARIABLE rowPins AND colPins WILL RECEIVE THE READ VALUE OF THE PINS OF THE ROWS AND COLUMNS RESPECTIVELY

const int ledVermelho = 12; //PIN ON WHICH THE RED LED IS CONNECTED
const int ledVerde = 13; //PIN ON WHICH THE GREEN LED IS CONNECTED

void setup(){
  pinMode(ledVermelho, OUTPUT); //DECLARES PIN AS OUTPUT
  pinMode(ledVerde, OUTPUT); //DECLARES PIN AS OUTPUT

  servo_Motor.attach(11); //SERVO MOTOR CONTROL PIN
  setLocked(true); //INITIAL LOCK STATUS (LOCKED)
}

void loop(){
  char key = keypad.getKey(); //READING THE PRESSED KEYS
  if (key == '*' || key == '#') { //IF THE KEY PRESSED EQUALTO THE CHARACTER "*" OR "#", MAKE
      position = 0; //READING POSITION OF THE PRESSED KEY STARTS AT 0
      setLocked(true); //LOCK LOCKED
}
if (key == password[position]){ //IF THE PRESSED KEY MATCHES THE PASSWORD SEQUENCE, MAKE
      position ++;//JUMP TO THE NEXT POSITION
}
if (position == 3){ // IF VARIABLE IS EQUAL To 3 DO (WHEN THE PRESSED KEYS REACH 3 POSITIONS, IT MEANS THAT THE PASSWORD IS CORRECT)
      setLocked(false); //UNLOCKED LOCK
}
delay(100);//100 MILLISECOND INTERVAL
}
void setLocked(int locked){ //TREATING THE STATE OF THE LOCK
if (locked){ //IF LOCK LOCKED, DOES
    digitalWrite(ledVermelho, HIGH);// RED LED LIGHTS UP
    digitalWrite(ledVerde, LOW);// GREEN LED ERASE
    servo_Motor.write(0); //SERVO POSITION IS 0º (LOCK LOCKED)
}
else{ //IF NOT, IT DOES
    digitalWrite(ledVerde, HIGH);// GREEN LED UP
    digitalWrite(ledVermelho, LOW);// RED LED ERASE
    servo_Motor.write(82);// SERVO ROTATES AT 82º (LOCK UNLOCKED)     By: Marcio Vinicius
}
}
