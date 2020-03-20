volatile int item;

void setup(){
  Serial.begin(9600);
  item = 0;
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop(){
  item = digitalRead(A0) + (digitalRead(A1) + (digitalRead(A2) + digitalRead(A3)));

  if (item != 4) {
     tone(13, 600, 20);// 播放音频  接arduino9号端口，thispitch为播放频率，10为维持时间

delay(200);




  }

}