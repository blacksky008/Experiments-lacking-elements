  //混合液比例
  int A[4]={1,1,1,1};
  int B[4]={1,1,1,1};
  int C[4]={1,1,1,1};
  int D[4]={1,1,1,1};
  
  int Wateringtime=10000;
  
  int Interval=8640000;
  //定义引脚
  //选择器开关
  int Swt1=2;
  int Swt2=3;
  int Swt3=4;
  int Swt4=5;
  int Swt5=6;
  int Swt6=7;
  //总开关
  int Mot1=12;
  //混合液输出开关
  int Mot2=8;
  int Mot3=9;
  int Mot4=10;
  int Mot5=11;
  //判断水位的参数item
  volatile int item;
  int i;
  
void setup() {
//定义输出
  pinMode(Swt1,OUTPUT);
  pinMode(Swt2,OUTPUT);
  pinMode(Swt3,OUTPUT);
  pinMode(Swt4,OUTPUT);
  pinMode(Swt5,OUTPUT);
  pinMode(Swt6,OUTPUT);
  //定义输出
  pinMode(Mot1,OUTPUT);
  
  pinMode(Mot2,OUTPUT);
  pinMode(Mot3,OUTPUT);
  pinMode(Mot4,OUTPUT);
  pinMode(Mot5,OUTPUT);

  //水位传感器引脚定义
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
//初始化
  digitalWrite(Swt1,LOW);
  digitalWrite(Swt2,LOW);
  digitalWrite(Swt3,LOW);
  digitalWrite(Swt4,LOW);
  digitalWrite(Swt5,LOW);
  digitalWrite(Swt6,LOW);
  
  digitalWrite(Mot1,LOW);
  
  digitalWrite(Mot2,LOW);
  digitalWrite(Mot3,LOW);
  digitalWrite(Mot4,LOW);
  digitalWrite(Mot5,LOW);
item=0;
  Serial.begin(9600);
}

void Water_level(){
  item = digitalRead(A0) + digitalRead(A1) + digitalRead(A2) + digitalRead(A3);
  if (item != 4) {
     tone(13, 600, 20);// 播放音频  接arduino9号端口，thispitch为播放频率，10为维持时间
delay(200);
}
}
void loop() {
//  Water_level();


  //打开电机，开始工作
  digitalWrite(Mot1,HIGH);

  //混合溶液a（ABCD各1/4）
  //step1
  digitalWrite(Swt5,HIGH);
  digitalWrite(Swt4,HIGH);
  digitalWrite(Swt3,HIGH);
  digitalWrite(Swt1,HIGH);
  delay(A[0]*0000/(A[0]+A[1]+A[2]+A[3]));
//step2
  digitalWrite(Swt1,LOW);
  delay(A[1]*20000/(A[0]+A[1]+A[2]+A[3]));
//step3
  digitalWrite(Swt3,LOW);
  digitalWrite(Swt2,HIGH);
  delay(A[2]*20000/(A[0]+A[1]+A[2]+A[3]));
//step4
  digitalWrite(Swt2,LOW);
  delay(A[3]*20000/(A[0]+A[1]+A[2]+A[3]));
//------------------------------------------------------
//混合溶液b（ABCD各1/4）
//step1
  digitalWrite(Swt5,LOW);
  digitalWrite(Swt3,HIGH);
  digitalWrite(Swt1,HIGH);
  delay(B[0]*20000/(B[0]+B[1]+B[2]+B[3]));
//step2
  digitalWrite(Swt1,LOW);
  delay(B[1]*20000/(B[0]+B[1]+B[2]+B[3]));
//step3
  digitalWrite(Swt3,LOW);
  digitalWrite(Swt2,HIGH);
  delay(B[2]*20000/(B[0]+B[1]+B[2]+B[3]));
//step4
  digitalWrite(Swt2,LOW);
  delay(B[3]*20000/(B[0]+B[1]+B[2]+B[3]));
//--------------------------------------------------
//混合溶液c（ABCD各1/4）
//step1
  digitalWrite(Swt4,LOW);
  digitalWrite(Swt6,HIGH);
  digitalWrite(Swt3,HIGH);
  digitalWrite(Swt1,HIGH);
  delay(C[0]*20000/(C[0]+C[1]+C[2]+C[3]));
//step2
  digitalWrite(Swt1,LOW);
  delay(C[1]*20000/(C[0]+C[1]+C[2]+C[3]));
//step3
  digitalWrite(Swt3,LOW);
  digitalWrite(Swt2,HIGH);
  delay(C[2]*20000/(C[0]+C[1]+C[2]+C[3]));
//step4
  digitalWrite(Swt2,LOW);
  delay(C[3]*20000/(C[0]+C[1]+C[2]+C[3]));
//-------------------------------------------------------
//混合溶液d（ABCD各1/4）
//step1
  digitalWrite(Swt6,LOW);
  digitalWrite(Swt3,HIGH);
  digitalWrite(Swt1,HIGH);
  delay(D[0]*20000/(D[0]+D[1]+D[2]+D[3]));
//step2
  digitalWrite(Swt1,LOW);
  delay(D[1]*20000/(D[0]+D[1]+D[2]+D[3]));
//step3
  digitalWrite(Swt3,LOW);
  digitalWrite(Swt2,HIGH);
  delay(D[2]*20000/(D[0]+D[1]+D[2]+D[3]));
//step4
  digitalWrite(Swt2,LOW);
  delay(D[3]*20000/(D[0]+D[1]+D[2]+D[3]));
  //停止工作
  digitalWrite(Mot1,LOW);
//------------------------------------------------------
//放混合溶液
  digitalWrite(Mot2,HIGH);
  digitalWrite(Mot3,HIGH);
  digitalWrite(Mot4,HIGH);
  digitalWrite(Mot5,HIGH);
  //放水10s
  delay(Wateringtime);
  
  digitalWrite(Mot2,LOW);
  digitalWrite(Mot3,LOW);
  digitalWrite(Mot4,LOW);
  digitalWrite(Mot5,LOW);

  
  //2.4小时循环一次
  delay(Interval);
}
