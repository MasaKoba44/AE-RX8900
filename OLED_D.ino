/////////////////////////////////////////////
// 有機ＥＬを使用したキャラクタ表示器
// SO1602AWWB-UC-WB（１６文字×２桁）
//
// 1:VCC
// 2:VDD
// 3:/CS
// 4:SA0
// 5:NC
// 6:NC
// 7:SCL
// 8:SDA in
// 9:SDA out
// 10:NC
// 11:NC
// 12:NC
// 13:NC
// 14:NC
//
// 作成日：2022/10/07
// 作成者：M.K
//

#include <Wire.h>
#define OLED_ADRS 0x3C //SA0=L(SA0=H の場合は 0x3D)
int DisplayON = 0x0F;
int ClearDisplay = 0x01;
int ReturnHome = 0x02;

/*
 * OLEDの初期化処理
 */
void Oled_setup() {
  Wire.begin();     //Wire ﾗｲﾌﾞﾗﾘを初期化し、I2C ﾏｽﾀとしてﾊﾞｽに接続
  init_oled();
  contrast_max();   //輝度を最大に設定
}
/*
 * 表示処理
 *
 * 引数１：１行目の表示文字列データをセット 
 * 引数２：２行目の表示文字列データをセット
 * 戻り値：なし
 *
 */
void Display_Rrocess(char moji1[], char moji2[])
{
  for(int i = 0; i < 20; i++) {
    writeData(moji1[i]);
  }

  writeCommand(0x20+0x80); //2 行目の先頭
  
  for(int i = 0; i < 20; i++) {
    writeData(moji2[i]);
  } 
}
/*
 * OLED()を初期化する。
 *
 * 引数：なし
 * 戻り値：なし
 *
 */
void init_oled() 
{
  delay(100);
  
  writeCommand(0x01);   // Clear Display
  delay(20);
  writeCommand(0x02);   // ReturnHome 
  delay(2);
  writeCommand(0x0f);   // Send Display on command 
  delay(2);
  writeCommand(0x01);   // Clear Display 
  delay(20);
}

/*
 * OLEDにデータを書き込む
 *
 * 引数１：書き込み文字列のポインター
 * 戻り値：なし
 *
 */
void writeData(byte t_data)
{
  Wire.beginTransmission(OLED_ADRS);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
}
/*
 * OLEDにコマンドを書き込む
 *
 * 引数：コマンドの書き込みデータのポインター
 * 戻り値：なし
 *
 */
void writeCommand(byte t_command)
{
  Wire.beginTransmission(OLED_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}
/*
 * OLEDの輝度を最大に設定する
 *
 * 引数：なし
 * 戻り値：なし
 */
void contrast_max()
{
  writeCommand(0x2a);   //RE=1
  writeCommand(0x79);   //SD=1
  writeCommand(0x81);   //コントラストセット
  writeCommand(0xFF);   //輝度ＭＡＸ
  writeCommand(0x78);   //SD を０にもどす
  writeCommand(0x28);   //2C=高文字　28=ノーマル
  delay(100);
}
/*
 * OLEDの輝度を最大に設定する
 *
 * 引数：なし
 * 戻り値：なし
 */
void Display_Clear()
{
  writeCommand(0x01);   // Clear Display
  delay(10);
  writeCommand(0x02);   // ReturnHome 
  delay(1);
  writeCommand(0x0f);   // Send Display on command 
  delay(1);
  writeCommand(0x01);   // Clear Display 
  delay(10);
}
