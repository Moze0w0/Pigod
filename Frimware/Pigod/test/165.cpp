#include <SPI.h>
#include <Arduino.h>
#include <BleGamepad.h>

int pl= 21; //low 并行输入（8个io状态存入寄存器内） ，high 串行输出
int cp = 18; //时钟脉冲
int data_in = 19; //数据采集
unsigned long  lastdata =0; //最终采集到的数据

unsigned long readbyte(){
  unsigned long byte_temp = 0;
  long byte_ ;
  digitalWrite(pl,LOW);
  delayMicroseconds(5);
  digitalWrite(pl,HIGH);//从D7开始读取至D0
  for (int i = 0 ; i < 16 ; i++){ //从D0开始高位 D7是结束低位
    byte_ = digitalRead(data_in);
    byte_temp |= (byte_ << i);
    digitalWrite(cp,HIGH);
    delayMicroseconds(5);
    digitalWrite(cp,LOW);
    
    }
    return byte_temp;
  
  }
void setup() {
  Serial.begin(115200);
  pinMode(pl,OUTPUT);
  pinMode(cp,OUTPUT);
  pinMode(data_in,INPUT);
  digitalWrite(pl,HIGH);
  digitalWrite(cp,LOW);
   lastdata =readbyte();
  // put your setup code here, to run once:

}

void loop() {
  lastdata =readbyte();
  Serial.println(lastdata,BIN);
  delay(500);
  // put your main code here, to run repeatedly:

}