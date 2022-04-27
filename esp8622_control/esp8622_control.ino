
String devicename;
#define DEBUG true
String cl = "";
String sendData(String command, const int timeout, boolean debug) { //esp8266副程式
  String response = "";
  Serial1.print(command); // send the read character to the esp8266
  long int time = millis();
  while ( (time + timeout) > millis()) {
    while (Serial1.available()) {
      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      delay(10);
      response += c;
    }
  }
  if (debug)    {
    Serial.print(response);
  }
  return response;
}
void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  Serial.begin(115200); //RX1 TX1，即 Pin18 及 Pin19
  Serial1.begin(115200);
  sendData("AT+RST\r\n", 2000, DEBUG); //重啟ESP8266
  sendData("AT+CWMODE=3\r\n", 200, DEBUG); //設置Wi-Fi模式 STA+AP
  if (sendData("AT+CWJAP=\"suck\",\"000000008\"\r\n", 2000, DEBUG)) { //連結Wi-Fi AP模式
    Serial.print("Join AP success\r\n");
    Serial.print("IP:");
    sendData("AT+CIFSR\r\n", 10000, DEBUG); //查詢連接IP位置
  }
  sendData("AT+CIPMUX=1\r\n", 500, DEBUG); //設置多連接模式
  sendData("AT+CIPSERVER=1,80\r\n", 500, DEBUG); //設置TCP 80 Port

}
void loop() {
  if (Serial1.available())   {
    if (Serial1.find("+IPD,"))
    {
      delay(500); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = Serial1.read() - 48; // subtract 48 because the read() function returns //讀取資料ASCII編碼 -48等於我們要的數值
      // the ASCII decimal value and 0 (the first decimal number) starts at 48
      Serial1.find("pin="); // advance cursor to "pin="
      int pinNumber = (Serial1.read() - 48) * 10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
      pinNumber += (Serial1.read() - 48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number

      Serial1.find("val="); // advance cursor to "pin="
      int val = (Serial1.read() - 48); // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
      //digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin
      if (val == 1) { //判斷式等於1開燈等於0關燈
        digitalWrite(12, HIGH);
      } else if (val == 0) {
        digitalWrite(12, LOW);
      }
      if (pinNumber == 10) {
        devicename = "fan";
        val = !val;
      } else if (pinNumber == 12) {
        devicename = "led";
      }
      Serial.println(pinNumber);
      Serial.println(devicename);
      Serial.println(val);
      cl = "AT+CIPCLOSE="; //關閉TCP傳輸
      cl += connectionId;
      cl += "\r\n";
      sendData(cl, 1000, DEBUG);
      sendData("AT+CIPSERVER=0\r\n", 500, DEBUG); //關閉TCP
      sendData("AT+CIPMUX=0\r\n", 500, DEBUG); //關閉連接模式
      sendData("AT+CIPSTART=\"TCP\",\"192.168.43.128\",80\r\n", 1000, DEBUG); //連接TCP 透過80 Port 進入192.168.43.73伺服器

      String aa = "GET /led.php?name=light&value="; //輸入網址
      aa += val;
      aa += " HTTP/1.1\r\nHost: 192.168.43.128\r\n\r\n";  //輸入網址
      String cipSend = "AT+CIPSEND=";  //發送數據
      cipSend += aa.length(); //輸入網址
      cipSend += "\r\n";

      sendData(cipSend, 1000, DEBUG);
      sendData(aa, 1000, DEBUG);
      delay(100);
      sendData("AT+RST\r\n", 2000, DEBUG); //重啟esp8266
      sendData("AT+CIPMUX=1\r\n", 500, DEBUG); //開啟連接模式
      sendData("AT+CIPSERVER=1,80\r\n", 500, DEBUG); ////設置TCP 80 Port


    }
  }

}
