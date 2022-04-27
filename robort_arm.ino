#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;
SoftwareSerial ARM_BT(6, 5); 
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // 當前位置
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // 以前的位置
int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50], servo05SP[50], servo06SP[50]; // 用於存儲位置/步驟
int speedDelay = 50;
int index = 0;
int data[2];
void setup() {
  Serial.begin(9600);
  ARM_BT.begin(9600); // 藍牙的默認頻率
  //ARM_BT.setTimeout(1);
  //delay(20);
  // 機器人手臂初始位置
  
  servo01.attach(11);
  servo1PPos = 80;
  servo01SP[index] = servo1PPos;  
  servo01.write(servo1PPos);
  //delay(250);
  //servo01.detach();
  
  servo02.attach(12);
  servo2PPos = 90;
  servo02SP[index] = servo2PPos;
  servo02.write(servo2PPos);
  delay(250);
  servo02.detach();
  
  servo03.attach(10);
  servo3PPos = 50;
  servo03SP[index] = servo3PPos;
  servo03.write(servo3PPos);
  delay(250);
  servo03.detach();
  
  servo04.attach(9);
  servo4PPos = 100;
  servo04SP[index] = servo4PPos;
  servo04.write(servo4PPos);
  delay(250);
  servo04.detach();
  
  servo05.attach(8);
  servo5PPos = 135 ;
  servo05SP[index] = servo5PPos;
  servo05.write(servo5PPos);
  delay(250);
  servo05.detach();
  
  servo06.attach(7);
  servo6PPos = 95;
  servo06SP[index] = servo6PPos;
  servo06.write(servo6PPos);
  delay(250);
  servo06.detach();
  
  index++;
}
void loop() {  
  // 檢查傳入的數據
  if (ARM_BT.available() > 0) {
     for(int i=0; i<2 ; i++){
       data[i] = ARM_BT.read();
       Serial.println(data[i]);  
     }
    //速度控制
    if ( data[0]==71){
      speedDelay = data[1]*10;
    }
    
    //馬達控制部分
    // 如果“Waist”滑塊更改值 - 將伺服1馬達移動到位置
    if (data[0]==66) {
      //servo01.attach(11);
      servo1Pos = data[1];
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   //讓伺服馬達停下來
          servo01.write(j);
          //delay(speedDelay);    // 設定伺服馬達旋轉的速度
        }
        //delay(250);
        //servo01.detach();
      }
      // 如果先前的位置小於當前位置
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // 讓伺服馬達啟動
          servo01.write(j);
          //delay(speedDelay);
        }
        //delay(250);
        //servo01.detach();
      }
      //delay(speedDelay);
      servo1PPos = servo1Pos;   // 將當前位置設置為先前位置
    }

    // 移動伺服馬達 2
    if (data[0]==65) {
      servo02.attach(12);
      servo2Pos = data[1];
      if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo02.detach();
      }
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo02.detach();
      }
      //delay(speedDelay);
      servo2PPos = servo2Pos;
    }
    // 移動伺服馬達 3
    if (data[0]==67) {
     servo03.attach(10);
      servo3Pos = data[1];
      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
         //delay(speedDelay);
        }
        delay(250);
        servo03.detach();
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo03.detach();
      }
      //delay(speedDelay);
      servo3PPos = servo3Pos;
    }
    // 移動伺服馬達 4
    if (data[0]==68) {
      servo04.attach(9);
      servo4Pos = data[1];
      if (servo4PPos > servo4Pos) {
        for ( int j = servo4PPos; j >= servo4Pos; j--) {
          servo04.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo04.detach();
      }
      if (servo4PPos < servo4Pos) {
        for ( int j = servo4PPos; j <= servo4Pos; j++) {
          servo04.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo04.detach();
      }
      //delay(speedDelay);
      servo4PPos = servo4Pos;
    }
    // 移動伺服馬達 5
    if (data[0]==69) {
      servo05.attach(8);
      servo5Pos = data[1];
      if (servo5PPos > servo5Pos) {
        for ( int j = servo5PPos; j >= servo5Pos; j--) {
          servo05.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo05.detach();
      }
      if (servo5PPos < servo5Pos) {
        for ( int j = servo5PPos; j <= servo5Pos; j++) {
          servo05.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo05.detach();
      }
      //delay(speedDelay);
      servo5PPos = servo5Pos;
    }
    // 移動伺服馬達 6
    if (data[0]==70) {
      servo05.attach(7);
      servo6Pos = data[1];
      if (servo6PPos > servo6Pos) {
        for ( int j = servo6PPos; j >= servo6Pos; j--) {
          servo06.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo06.detach();
      }
      if (servo6PPos < servo6Pos) {
        for ( int j = servo6PPos; j <= servo6Pos; j++) {
          servo06.write(j);
          //delay(speedDelay);
        }
        delay(250);
        servo06.detach();
      }
      //delay(speedDelay);
      servo6PPos = servo6Pos; 
    }

    //button控制
    
    // 如果按下“SAVE”按鈕
    if (data[0]==72) {
      servo01SP[index] = servo1PPos;  
      servo02SP[index] = servo2PPos;
      servo03SP[index] = servo3PPos;
      servo04SP[index] = servo4PPos;
      servo05SP[index] = servo5PPos;
      servo06SP[index] = servo6PPos;
      index++;
      Serial.print("index: ");
      Serial.println(index);          
    }
    // 如果按下“RUN”按鈕
    if (data[0]==73) {
      runservo();  // 自動模式
    }
    // 如果按下“RESET”按鈕
    if ( data[0]==74) {
      memset(servo01SP, 0, sizeof(servo01SP)); // Clear(清除) the array data to 0
      memset(servo02SP, 0, sizeof(servo02SP));
      memset(servo03SP, 0, sizeof(servo03SP));
      memset(servo04SP, 0, sizeof(servo04SP));
      memset(servo05SP, 0, sizeof(servo05SP));
      memset(servo06SP, 0, sizeof(servo06SP));
      index = 1;  
      
   // servo01.attach(11);
    servo1PPos = 80;
    servo01.write(servo1PPos);
    //delay(250);
    //servo01.detach();
    
    servo02.attach(12);
    servo2PPos = 90;
    servo02.write(servo2PPos);
    delay(250);
    servo02.detach();
    
    servo03.attach(10);
    servo3PPos = 50;
    servo03.write(servo3PPos);
    delay(250);
    servo03.detach();
    
    servo04.attach(9);
    servo4PPos = 100;
    servo04.write(servo4PPos);
    delay(250);
    servo04.detach();
    
    servo05.attach(8);
    servo5PPos = 135;
    servo05.write(servo5PPos);
    delay(250);
    servo05.detach();
    
    servo06.attach(7);
    servo6PPos = 95;
    servo06.write(servo6PPos);
    delay(250);
    servo06.detach();
    
    delay(speedDelay);
    speedDelay=50;
    }
  }
  delay(5);
}

//  自動模式
void runservo() {
    while (data[0] != 75) {   // 反復運行步驟，直到按下“RESET”按鈕
    for (int i = 0; i < index-1; i++) {
      if(i==0){
        servo01.write(90);
        servo02.write(80);
        servo03.write(50);
        servo04.write(100);
        servo05.write(135);
        servo06.write(95);
      }
      Serial.print("i");
      Serial.println(i); 
      if (ARM_BT.available() > 0) {   
        for(int g=0; g<1 ; g++){
          data[g] = ARM_BT.read();
          Serial.println(data[g]);  
        } 
        if (data[0]==75){
          break;
        }
        if (data[0]==74) {
          memset(servo01SP, 1, sizeof(servo01SP)); // Clear(清除) the array data to 0
          memset(servo02SP, 1, sizeof(servo02SP));
          memset(servo03SP, 1, sizeof(servo03SP));
          memset(servo04SP, 1, sizeof(servo04SP));
          memset(servo05SP, 1, sizeof(servo05SP));
          memset(servo06SP, 1, sizeof(servo06SP));
          index = 0;  // Index to 0
          servo1PPos = 90;
          servo01.write(servo1PPos);
          servo2PPos = 80;
          servo02.write(servo2PPos);
          servo3PPos = 50;
          servo03.write(servo3PPos);
          servo4PPos = 100;
          servo04.write(servo4PPos);
          servo5PPos = 135;
          servo05.write(servo5PPos);
          servo6PPos = 95;
          servo06.write(servo6PPos);
          break;
        }
        if (data[0]==71) {
          speedDelay = data[1]; // 改變伺服馬達速度（延遲時間）
        }
      }
      if(i<index){
      // 伺服馬達 1
      if (servo01SP[i] > servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      // 伺服馬達 2
      if (servo02SP[i] > servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      // 伺服馬達 3
      if (servo03SP[i] > servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      // 伺服馬達 4
      if (servo04SP[i] > servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      // 伺服馬達 5
      if (servo05SP[i] > servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j >= servo05SP[i + 1]; j--) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      if (servo05SP[i] < servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j <= servo05SP[i + 1]; j++) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      // 伺服馬達 6
      if (servo06SP[i] > servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j >= servo06SP[i + 1]; j--) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
      if (servo06SP[i] < servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j <= servo06SP[i + 1]; j++) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
    }
    }
  }
}
