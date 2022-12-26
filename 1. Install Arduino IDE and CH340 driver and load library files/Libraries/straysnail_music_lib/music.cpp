#include"music.h"
#include"array.h"

///////////////////////////////////////俄罗斯方块/////////////////////////////////
//节拍数,改变这个使歌曲变慢或变快
int tempo=144; 
// sizeof给出字节数，每个int值由两个字节(16位)组成
//每个音符有两个值(音调和持续时间)，所以每个音符有四个字节
int notes=sizeof(melody)/sizeof(melody[0])/2;    //得出音符数量为99
//计算整个音符的持续时间(60秒/节拍)*4拍  //一个四分音符的时值是144,也就是每分钟144拍的速度
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
///////////////////////////////////////俄罗斯方块结束/////////////////////////////////

////////////////////////////////////Ode_to_Joy/////////////////////////////////////
int length=sizeof(tune)/sizeof(tune[0]);
//////////////////////////////////Ode_to_Joy end///////////////////////////////////

////////////////////////////////////圣诞歌///////////////////////////////////////////
//定义蜂鸣器引脚，音符长度变量
int length_christmas = sizeof(tune_christmas)/sizeof(tune_christmas[0]);
//////////////////////////////////圣诞歌 end/////////////////////////////////////////

music::music(char pin)
{
  buzzer_pin = pin;
}

void music::birthday(void)
{
  tone(buzzer_pin,294);
  delay(250);
  tone(buzzer_pin,440);
  delay(250);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,532);
  delay(250);
  tone(buzzer_pin,494);
  delay(500);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,440);
  delay(250);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,587);
  delay(250);
  tone(buzzer_pin,532);
  delay(500);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,784);
  delay(250);
  tone(buzzer_pin,659);
  delay(250);
  tone(buzzer_pin,532);
  delay(250);
  tone(buzzer_pin,494);
  delay(250);
  tone(buzzer_pin,440);
  delay(250);
  tone(buzzer_pin,698);
  delay(375);
  tone(buzzer_pin,659);
  delay(250);
  tone(buzzer_pin,532);
  delay(250);
  tone(buzzer_pin,587);
  delay(250);
  tone(buzzer_pin,532);
  delay(500);
  noTone(buzzer_pin);
}
/////////////////////////////////////////////
void music::star_war_tone(void)
{
  //Play first section
  firstSection();
 
  //Play second section
  secondSection();
 
  //Variant 1
  beep(NOTE_F4, 250);  
  beep(NOTE_GS4, 500);  
  beep(NOTE_F4, 350);  
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 500);
  beep(NOTE_A4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_E5, 650);
 
  delay(500);
 
  //Repeat second section
  secondSection();
 
  //Variant 2
  beep(NOTE_F4, 250);  
  beep(NOTE_GS4, 500);  
  beep(NOTE_F4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 500);  
  beep(NOTE_F4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 650);  
 
  delay(650);
}
/////////////////////////////////////////////
void music::firstSection(void)
{
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);    
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);  
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);  
  beep(NOTE_F5, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_GS4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
}
/////////////////////////////////////////////
void music::secondSection(void)
{
  beep(NOTE_A5, 500);
  beep(NOTE_A4, 300);
  beep(NOTE_A4, 150);
  beep(NOTE_A5, 500);
  beep(NOTE_GS5, 325);
  beep(NOTE_G5, 175);
  beep(NOTE_FS5, 125);
  beep(NOTE_F5, 125);    
  beep(NOTE_FS5, 250);
 
  delay(325);
 
  beep(NOTE_AE4, 250);
  beep(NOTE_DS5, 500);
  beep(NOTE_D5, 325);  
  beep(NOTE_CS5, 175);  
  beep(NOTE_C5, 125);  
  beep(NOTE_AS4, 125);  
  beep(NOTE_C5, 250);  
 
  delay(350);
}
/////////////////////////////////////////////
void music::beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzer_pin, note, duration);
 
  //Play different LED depending on value of 'counter'

  delay(duration);

 
  //Stop tone on buzzerPin
  noTone(buzzer_pin);
 
  delay(50);
}
/////////////////////////////////////////////
void music::tetris(void)    //俄罗斯方块曲
{
  //注意，该数组是notes (notes +期限)数量的两倍
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
  {
    //计算每个音符的持续时间
    divider = melody[thisNote + 1];
    if (divider > 0) 
    {
      noteDuration = (wholenote) / divider;
    } 
    else if (divider < 0) 
    {
      //负数，是加点的音符
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; //点状音符的持续时间为 二分音符 + 四分音符
    }
    //我们只在90%的时间里播放音符，剩下10%的时间用来暂停
    tone(buzzer_pin, melody[thisNote], noteDuration*0.9);
    //在播放下一个音符之前，等待指定的持续时间。
    delay(noteDuration);
    //在下一个音符之前停止波形生成。
    noTone(buzzer_pin);
  }
}
/////////////////////////////////////////////
void music::super_mario(void)
{
  sing(1);
  sing(1);
  sing(2);  
}
/////////////////////////////////////////////
void music::sing(int s)
{
  if (s == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody_mario) / sizeof(int);
    Serial.println(sizeof(underworld_melody_mario));
    Serial.println(size);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / underworld_tempo_mario[thisNote];
      buzz(buzzer_pin, underworld_melody_mario[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(buzzer_pin, 0, noteDuration);

    }

  } else {
    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody_mario) / sizeof(int);   //sizeof(int) = 2
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo_mario[thisNote];
      buzz(buzzer_pin, melody_mario[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzz(buzzer_pin, 0, noteDuration);

    }
  }  
}
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
void music::buzz(int targetPin, long frequency, long length)    
{
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;

  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
}
/////////////////////////////////////////////
void music::Ode_to_Joy(void)
{
  for(int x=0;x<length;x++)
  {
    tone(buzzer_pin,tune[x]);
    delay(300*durt[x]);
  }
  noTone(buzzer_pin);  
}
/////////////////////////////////////////////
void music::christmas(void)
{
   //for循环演奏曲子
  for(int x=0;x<length_christmas;x++)
  {
    tone(buzzer_pin, tune_christmas[x]);
    delay(500*durt_christmas[x]);         //这里的500为控制每个音符的时长来定曲子的节奏
    noTone(buzzer_pin);
  } 
  
}
