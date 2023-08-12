#include <BleGamepad.h>


BleGamepad bleGamepad("ESP Controller", "ElectroPoint4u", 100);


// LEFT-JOYSTICK
#define LH 39
#define LV 36


// RIGHT-JOYSTICK
#define RH 35
#define RV 34

/*************************botton************************************/
#define DATA_165 19
#define CLK_165 18
#define PL_165 21
#define CS_165 5

const int numBits = 16;   /* Set to 8 * number of shift registers */
bool KEY[numBits] = {0};
int KEY_Keybord[numBits] = {
  15 , 13 , 12 , 14 , 4 , 6 , 8 , 9 ,// 0 - 7
  17 , 18 , 2 , 3 , 5 , 7 , 10 , 11  // 8 - 15
};
#define A_KEY 16 //0
#define B_KEY 17 //1

void sendMessage(int key){
  Serial.printf("aaaaaaa: %d" , KEY_Keybord[key]);
  Serial.println(F("Right Trigger"));
  bleGamepad.press(KEY_Keybord[key] + 1);
  bleGamepad.sendReport();
  delay(10);
  bleGamepad.release(KEY_Keybord[key] + 1);
  bleGamepad.sendReport();
}
int findKey(){
  
  for (int num1 = 0 ; num1 < numBits ; num1++){
    if (KEY[num1] == 1){
      sendMessage(num1);
    }
  }
}

int Key165(){
  int flag = 0;
  digitalWrite(PL_165, LOW);
  digitalWrite(PL_165, HIGH);

  // Step 2: Shift
  Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++) {
    int bit = digitalRead(DATA_165);
    if (bit == HIGH) {
      Serial.print("1");
      KEY[i] = 0;
    } else {
      Serial.print("0");
      KEY[i] = 1;
      flag++;
    }
    digitalWrite(CLK_165, HIGH); // Shift out the next bit
    digitalWrite(CLK_165, LOW);
  }
  if (!flag)return 0;
  else return 1;
}



void setup() {
  Serial.begin(115200);

  bleGamepad.begin();
  //bleGamepad.setAutoReport(false); // to disable auto reporting, and then use bleGamepad.sendReport(); as needed
  Serial.println("Starting BLE work!");


  Serial.begin(115200);
  pinMode(DATA_165, INPUT);
  pinMode(CLK_165, OUTPUT);
  pinMode(PL_165, OUTPUT);
  pinMode(CS_165, OUTPUT);
  digitalWrite(CS_165, LOW);

  pinMode(A_KEY, INPUT|PULLUP);
  pinMode(B_KEY, INPUT|PULLUP);
  
}

void loop() {
  if (bleGamepad.isConnected()) {


    if (Key165()){
      findKey();
    }

    

    /***************************8
    if (digitalRead(LT) == LOW) {
      Serial.println(F("Left Trigger"));
      bleGamepad.press(BUTTON_5);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_5);
      bleGamepad.sendReport();
    }
    if (digitalRead(RT) == LOW) {
      Serial.println(F("Right Trigger"));
      bleGamepad.press(BUTTON_6);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_6);
      bleGamepad.sendReport();
    }
    
    if (digitalRead(LS) == LOW) {
      Serial.println(F("Left Joystick"));
      bleGamepad.press(BUTTON_11);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_11);
      bleGamepad.sendReport();
    }
    if (digitalRead(RS) == LOW) {
      Serial.println(F("Right Joystick"));
      bleGamepad.press(BUTTON_12);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_12);
      bleGamepad.sendReport();
    }

    if (digitalRead(R1) == LOW) {
      Serial.println(F("Right Button 1"));
      bleGamepad.press(BUTTON_1);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_1);
      bleGamepad.sendReport();
    }
    if (digitalRead(R2) == LOW) {
      Serial.println(F("Right Button 2"));
      bleGamepad.press(BUTTON_2);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_2);
      bleGamepad.sendReport();
    }
    if (digitalRead(R3) == LOW) {
      Serial.println(F("Right Button 3"));
      bleGamepad.press(BUTTON_3);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_3);
      bleGamepad.sendReport();
    }
    if (digitalRead(R4) == LOW) {
      Serial.println(F("Right Button 4"));
      bleGamepad.press(BUTTON_4);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_4);
      bleGamepad.sendReport();
    }


    if (digitalRead(L1) == LOW) {
      Serial.println(F("Left Button 1"));
      bleGamepad.press(BUTTON_13);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_13);
      bleGamepad.sendReport();
    }
    if (digitalRead(L2) == LOW) {
      Serial.println(F("Left Button 2"));
      bleGamepad.press(BUTTON_14);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_14);
      bleGamepad.sendReport();
    }
    if (digitalRead(L3) == LOW) {
      Serial.println(F("Left Button 3"));
      bleGamepad.press(BUTTON_15);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_15);
      bleGamepad.sendReport();
    }
    if (digitalRead(L4) == LOW) {
      Serial.println(F("Left Button 4"));
      bleGamepad.press(BUTTON_16);
      bleGamepad.sendReport();
      delay(debounceDelay);
      bleGamepad.release(BUTTON_16);
      bleGamepad.sendReport();
    }

    *************************************************************/
    // Map analog reading from 0 ~ 4095 to 32737 ~ -32737 for use as an axis reading
    //int value1 = map(analogRead(LH), 0, 4095, 32737, -32737);
    //int value2 = map(analogRead(LV), 0, 4095, 32737, -32737);

    int value1 = map(analogRead(LH), 0, 4095, 32767, 0);
    int value2 = map(analogRead(LV), 0, 4095, 32767, 0);

    bleGamepad.setLeftThumb(value1, value2);
  

    //Serial.println(value1);
    //int value3 = map(analogRead(RH), 0, 4095, 0, 65475);
    //int value4 = map(analogRead(RV), 0, 4095, 0, 65475);

    int value3 = map(analogRead(RH), 0, 4095, 32767, 0);
    int value4 = map(analogRead(RV), 0, 4095, 32767, 0);

    bleGamepad.setRightThumb(value3, value4);
    
    //Send the gamepad report
    bleGamepad.sendReport();
    delay(1);
  }
 
}

