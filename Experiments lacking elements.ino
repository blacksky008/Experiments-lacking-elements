//头文件
#include <dht.h>
#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
//定义温湿度传感器引脚
dht myDHT_A5;
//温度
int dht_A5_gettemperature() {
  int chk = myDHT_A5.read11(A5);
  int value = myDHT_A5.temperature;
  return value;
}
//湿度
int dht_A5_gethumidity() {
  int chk = myDHT_A5.read11(A5);
  int value = myDHT_A5.humidity;
  return value;
}

//混合液比例
int A[4]={1,1,1,1};
int B[4]={1,1,1,1};
int C[4]={1,1,1,1};
int D[4]={1,1,1,1};
//放水时间
int Wateringtime=10000;
//循环时间
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
  //oled显示屏
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
  } while( u8g.nextPage());
  delay(1000);

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
  //继电器高电平触发
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

  //判断水位变量为0
  item=0;
  Serial.begin(9600);
}
void loop() {
  u8g.firstPage();
  do {
    //显示：温度：C   湿度：%RH
    u8g.setPrintPos(0,14);
    u8g.print("temperature:");
    u8g.setPrintPos(0,30);
    u8g.print(String(dht_A5_gettemperature()) + String("C"));
    u8g.setPrintPos(0,46);
    u8g.print("humidity:");
    u8g.setPrintPos(0,62);
    u8g.print(String(dht_A5_gethumidity()) + String("%RH"));
  }
  while( u8g.nextPage() );
  //模式开关：1023为清水模式，0为混合模式，因为会有干扰，取500信号值
  if (analogRead(A4) <=500) {
    //串口监视，方便排障
    Serial.println("hunhe");
    Serial.println(analogRead(A4));
    //判断方法：只要有一个水位传感器不满足条件，程序不进行，且蜂鸣器报警
    item = digitalRead(A0) + digitalRead(A1) + digitalRead(A2) + digitalRead(A3);
    //不满足条件时
    if(item!=4) {
      tone(13, 600, 20);// 播放音频  接arduino9号端口，thispitch为播放频率，10为维持时间
      delay(200);
      Serial.println("warning!");
    }

    else{
      //满足条件时，开始进行混合模式工作
      //打开电机，开始工作
      digitalWrite(Mot1,HIGH);
      //A为空白水，可进行管道清洗
      //混合溶液a
      //B+C+A
      //step1
      Serial.println("B+C doing");
      //001110
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,HIGH);
      digitalWrite(Swt4,HIGH);
      digitalWrite(Swt5,HIGH);
      digitalWrite(Swt6,LOW);
      Serial.println("B doing");
      delay(A[0]*60000/(A[0]+A[1]+A[2]+A[3]));

      //step2
      //010110
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,HIGH);
      digitalWrite(Swt3,LOW);
      digitalWrite(Swt4,HIGH);
      digitalWrite(Swt5,HIGH);
      digitalWrite(Swt6,LOW);
      Serial.println("C doing");
      delay(A[0]*60000/(A[0]+A[1]+A[2]+A[3]));

      //step3
      //101110
      digitalWrite(Swt1,HIGH);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,HIGH);
      digitalWrite(Swt4,HIGH);
      digitalWrite(Swt5,HIGH);
      digitalWrite(Swt6,LOW);
      Serial.println("A doing");
      delay(A[0]*60000/(A[0]+A[1]+A[2]+A[3]));

      //------------------------------------------------------
      //混合溶液b
      //C+D+A
      //step1
      //010100
      Serial.println("C+D doing");
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,HIGH);
      digitalWrite(Swt3,LOW);
      digitalWrite(Swt4,HIGH);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,LOW);
      Serial.println("C doing");
      delay(B[1]*60000/(B[0]+B[1]+B[2]+B[3]));

      //step2
      //000100
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,LOW);
      digitalWrite(Swt4,HIGH);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,LOW);
      Serial.println("D doing");
      delay(B[1]*60000/(B[0]+B[1]+B[2]+B[3]));

      //step3
      //101100
      digitalWrite(Swt1,HIGH);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,HIGH);
      digitalWrite(Swt4,HIGH);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,LOW);
      Serial.println("A doing");
      delay(B[1]*60000/(B[0]+B[1]+B[2]+B[3]));

      //--------------------------------------------------
      //混合溶液c
      //D+B+A
      //step1
      //000001
      Serial.println("D+B doing");
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,LOW);
      digitalWrite(Swt4,LOW);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,HIGH);
      Serial.println("D doing");
      delay(C[2]*60000/(C[0]+C[1]+C[2]+C[3]));

      //step2
      //001001
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,HIGH);
      digitalWrite(Swt4,LOW);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,HIGH);
      Serial.println("B doing");
      delay(C[2]*60000/(C[0]+C[1]+C[2]+C[3]));

      //step3
      //101001
      digitalWrite(Swt1,HIGH);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,HIGH);
      digitalWrite(Swt4,LOW);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,HIGH);
      Serial.println("A doing");
      delay(C[2]*60000/(C[0]+C[1]+C[2]+C[3]));

      //-------------------------------------------------------
      //混合溶液d
      //D+A
      //step1
      //000000
      Serial.println("ONLY D doing");
      digitalWrite(Swt1,LOW);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,LOW);
      digitalWrite(Swt4,LOW);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,LOW);
      Serial.println("C doing");
      delay(D[3]*60000/(D[0]+D[1]+D[2]+D[3]));

      //step2
      //101000
      digitalWrite(Swt1,HIGH);
      digitalWrite(Swt2,LOW);
      digitalWrite(Swt3,HIGH);
      digitalWrite(Swt4,LOW);
      digitalWrite(Swt5,LOW);
      digitalWrite(Swt6,LOW);
      Serial.println("A doing");
      delay(D[3]*60000/(D[0]+D[1]+D[2]+D[3]));

      //停止工作
      digitalWrite(Mot1,LOW);
      //------------------------------------------------------
      //放出混合溶液
      digitalWrite(Mot2,HIGH);
      digitalWrite(Mot3,HIGH);
      digitalWrite(Mot4,HIGH);
      digitalWrite(Mot5,HIGH);
      //放水10s
      delay(Wateringtime);
      //停止工作
      digitalWrite(Mot2,LOW);
      digitalWrite(Mot3,LOW);
      digitalWrite(Mot4,LOW);
      digitalWrite(Mot5,LOW);

      //2.4小时循环一次
      delay(Interval);
    }      


  } else {
    //清水模式，方法为将A溶液通过混合液的abcd中
    Serial.println("qingshui");
    Serial.println(analogRead(A4));
    //打开电机，开始工作
    digitalWrite(Mot1,HIGH);

    //混合溶液a
    //step1
    //101110
    digitalWrite(Swt1,HIGH);
    digitalWrite(Swt2,LOW);
    digitalWrite(Swt3,HIGH);
    digitalWrite(Swt4,HIGH);
    digitalWrite(Swt5,HIGH);
    digitalWrite(Swt6,LOW);
    delay(A[0]*60000/(A[0]+A[1]+A[2]+A[3]));

    //step2
    //101100
    digitalWrite(Swt1,HIGH);
    digitalWrite(Swt2,LOW);
    digitalWrite(Swt3,HIGH);
    digitalWrite(Swt4,HIGH);
    digitalWrite(Swt5,LOW);
    digitalWrite(Swt6,LOW);
    delay(B[1]*60000/(B[0]+B[1]+B[2]+B[3]));

    //step3
    //101001
    digitalWrite(Swt1,HIGH);
    digitalWrite(Swt2,LOW);
    digitalWrite(Swt3,HIGH);
    digitalWrite(Swt4,LOW);
    digitalWrite(Swt5,LOW);
    digitalWrite(Swt6,HIGH);
    delay(C[2]*60000/(C[0]+C[1]+C[2]+C[3]));
    
    //step4
    //101000
    digitalWrite(Swt1,HIGH);
    digitalWrite(Swt2,LOW);
    digitalWrite(Swt3,HIGH);
    digitalWrite(Swt4,LOW);
    digitalWrite(Swt5,LOW);
    digitalWrite(Swt6,LOW);
    delay(D[3]*60000/(D[0]+D[1]+D[2]+D[3]));
    
    //停止工作
    digitalWrite(Mot1,LOW);
    
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
  }
}
