#include <Arduino.h>
#include <SPI.h>
#include <BleGamepad.h>

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
#define B_KEY 17 //0

void sendMessage(int key){
  Serial.printf("aaaaaaa: %d" , KEY_Keybord[key]);

}
int findKey(){
  int flag = 0;
  for (int num1 = 0 ; num1 < numBits ; num1++){
    if (KEY[num1] == 1){
      sendMessage(num1);
      flag++;
    }
  }
  if (!flag)return 0;
  else return 1;
}

void Key165(){
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
    }
    digitalWrite(CLK_165, HIGH); // Shift out the next bit
    digitalWrite(CLK_165, LOW);
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(DATA_165, INPUT);
  pinMode(CLK_165, OUTPUT);
  pinMode(PL_165, OUTPUT);
  pinMode(CS_165, OUTPUT);
  digitalWrite(CS_165, LOW);
}

void loop() {
  Key165();
  findKey();

  Serial.println();
  delay(1000);
}