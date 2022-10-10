// ---------------------------------------------------------------------
// RX8900ICからリアルタイム時刻を取得する関数
//
// USE +3.3V PWR
// AE-RX8900 SCL  =  A5
// AE-RX8900 SDA  =  A4
// AE-RX8900 FOE  =  GND
// AE-RX8900 VBAT =  3.3V
//
// "TEMP" IS NOT OUTSIDE TEMP. IT IS INTERNAL CORE TEMP OF RX8900.
// WHEN TIMER COUNT OVER,RX8900A's INT-PIN LET LOW 7.813mS THEN Hi-Z
//
// 作成日：2022/10/07
// 作成者：M.K
//

#include <Wire.h>
#include "RX8900.h"

int LED_PINX1 = 2;
unsigned char OLD_SEC1 = 0;

/************************************
 *  初期化処理
 ************************************/
void setup() {
  delay(100);
  Wire.begin();

  init_oled();
  contrast_max();  //輝度を最大に設定

  Serial.begin(9600);

  pinMode(LED_PINX1, OUTPUT);  // X1を出力に設定
}
/***************************************
 * メイン処理
 ***************************************/
void loop() {
  Debug_Rrocess();

  char moji1[20];
  char moji2[20];

  if (SEC == 0 && SEC != OLD_SEC1) {
    for(int i = 0; i < 20; i++) {
      moji1[i] = " ";
      moji2[i] = " ";
    }

    // 時刻読み取り
    Read_Date(moji1, moji2);
    // OLED表示
    Display_Rrocess(moji1, moji2);
    OLD_SEC1 = SEC;
  } else {
    OLD_SEC1 = SEC;
  }
  if (SEC%2 == 1) {
    digitalWrite(LED_PINX1, HIGH);
  } else {
    digitalWrite(LED_PINX1, LOW);
  }
}

/*
 *  シリアル処理のメイン処理
 */
void Debug_Rrocess(void) {
  // 時刻のシリアル出力
  READ_AND_TX();
}
/*
 * 取得した時刻を表示する処理
 */
void READ_AND_TX(void) {
  // RX8900からデータを取得する
  RegisterRead();

  //取得した時刻が前回と同じ場合には表示処理を行わない。
  if (SEC != OLD_SEC) {
    // 時刻表示処理
    TX_DATE();
    OLD_SEC = SEC;
  }
}
/*
 * 時刻データをバッファに詰める
 */
void Read_Date(char buff1[], char buff2[]) {
  int WD;
  WD = GET_WEEK(WEEK);

  sprintf(buff1, "%d%x/%x/%x       ", 20, YEAR, MONTH, DAY);
  sprintf(buff2, " (%4s) %02x:%02x    ", WEEK_D[WD], HOUR, MIN);
}
/*
 *  時刻データをシリアル出力する
 */
void TX_DATE() {
  int WD;
  char buff1[20];
  char buff2[20];

  WD = GET_WEEK(WEEK);

  sprintf(buff1, "%d%x/%x/%x %4s \n", 20, YEAR, MONTH, DAY, WEEK_D[WD]);
  Serial.print(buff1);

  sprintf(buff2, "%02x:%02x:%02x  %d         ", HOUR, MIN, SEC,OLD_SEC1);
  Serial.print(buff2);
}
/*
 * 週データを取得する。
 */
unsigned char GET_WEEK(unsigned char data) {
  unsigned char c = 0;
  while ((data & 0x01) != 0x01) {
    c++;
    data = data >> 1;
  }
  return c;
}
/*
 * RX8900のアドレスからデータを読出し。
 */
void RegisterRead(void) {
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(SEC_reg);  //set 0x00(SEC)Register address
  Wire.endTransmission(false);
  Wire.requestFrom(RX8900A_ADRS, Control_Register_reg);  //set 0x0F(Control Register)Register address
  SEC = Wire.read();                                     //0x00
  MIN = Wire.read();                                     //0x01
  HOUR = Wire.read();                                    //0x02
  WEEK = Wire.read();                                    //0x03
  DAY = Wire.read();                                     //0x04
  MONTH = Wire.read();                                   //0x05
  YEAR = Wire.read();                                    //0x06
  RAM = Wire.read();                                     //0x07
  MIN_Alarm = Wire.read();                               //0x08
  HOUR_Alarm = Wire.read();                              //0x09
  WEEK_DAY_Alarm = Wire.read();                          //0x0A
  Timer_Counter_0 = Wire.read();                         //0x0B
  Timer_Counter_1 = Wire.read();                         //0x0C
  Extension_Register = Wire.read();                      //0x0D
  Flag_Register = Wire.read();                           //0x0E
  Control_Register = Wire.read();                        //0x0F
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(TEMP_reg);  //set TEMP_reg 0x17
  Wire.endTransmission(false);
  Wire.requestFrom(RX8900A_ADRS, 2);  //Backup_Function_reg ～ TEMP_reg
  TEMP = Wire.read();                 //0x17
  Backup_Function = Wire.read();      //0x18
}
/*
 * バイト書き込み
 */
void ByteWrite(byte reg, byte data) {
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}
/*
 * バイト読み込み
 */
byte ByteRead(byte reg) {
  byte data = 0;
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(RX8900A_ADRS, 1);
  data = Wire.read();  //RECEIVE 1BYTE
  return data;
}