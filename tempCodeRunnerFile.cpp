#include <Keypad.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


// Your existing variables and definitions...

int score = 0; 
int gameTime = 0;  //遊戲時間
#define DEFAULT_MOLE_TIME 800;
int gameMode = 0; // 0 for game A, 1 for game B
int Ascore = 0;
int Bscore = 0;
bool executed = false;
bool twoexecuted = false;
bool threeexecuted = false;
bool fiveexecuted = false;
bool sixexecuted = false;


uint8_t A[] = { 0x03, 0x0C, 0x34, 0xC4, 0xC4, 0x34, 0x0C, 0x03 };
uint8_t B[] = { 0x00, 0x6E, 0x91, 0x91, 0x91, 0x91, 0xFF, 0x00 };


#define MAX7219_CS_PIN 53
#define MAX7219_CLK_PIN 52
#define MAX7219_DIN_PIN 51

#define ROW_NUM 4
#define COL_NUM 4

char keys[ROW_NUM][COL_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rowsB[ROW_NUM] = {32,34,36,38};
byte pin_columnB[COL_NUM] = {22,24,26,28};

byte pin_rows[ROW_NUM] = {29,27,25,23};
byte pin_column[COL_NUM] = {39,37,35,33};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COL_NUM );
 
#define MAX_DEVICES 1
#define CLK_PIN   MAX7219_CLK_PIN
#define DATA_PIN  MAX7219_DIN_PIN
#define CS_PIN    MAX7219_CS_PIN
MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, CS_PIN, MAX_DEVICES);

int moleTime = DEFAULT_MOLE_TIME;

unsigned long MoleAppearTime = 0;
int MolePosition = 0;

int holePositions[9][2] = {
  {1, 1}, {1, 3}, {1, 5},
  {3, 1}, {3, 3}, {3, 5},
  {5, 1}, {5, 3}, {5, 5}
};

bool gameStarted = false;
bool BgameStarted = false;


#define DS_PIN 49
#define SHCP_PIN 47
#define STCP_PIN 45

#define DS_PIN_2 44  //第二顆74HC595的 DS_PIN
#define SHCP_PIN_2 46 //第二顆74HC595的 SHCP_PIN
#define STCP_PIN_2 48 //第二顆74HC595的 STCP_PIN


unsigned long gameStartTime = 0;
unsigned long lastTimeUpdated = 0;

byte sevenSegDigits[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};

void displayNumber(int number, int pin, int ds_pin, int shcp_pin) {
  digitalWrite(pin, LOW);
  shiftOut(ds_pin, shcp_pin, MSBFIRST, sevenSegDigits[number / 10]);
  shiftOut(ds_pin, shcp_pin, MSBFIRST, sevenSegDigits[number % 10]);
  digitalWrite(pin, HIGH);
}


char keysB[ROW_NUM][COL_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


Keypad keypadB = Keypad( makeKeymap(keysB), pin_rowsB, pin_columnB, ROW_NUM, COL_NUM );

int calcScore = 6;
bool CgameStarted = false;
unsigned long keyTime = 0;
int keyErrorCountA = 0;
int keyErrorCountB = 0;

void setup() {

mx.begin();
  pinMode(DS_PIN, OUTPUT);
  pinMode(SHCP_PIN, OUTPUT);
  pinMode(STCP_PIN, OUTPUT);

  pinMode(DS_PIN_2, OUTPUT); //第二顆74HC595的 pinMode設置
  pinMode(SHCP_PIN_2, OUTPUT);
  pinMode(STCP_PIN_2, OUTPUT);
  score = 0;
  gameTime = 0;

  displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
  displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);

  // Your existing setup...
}

void loop() {
  // Your existing loop for mode A and mode B...
  //char key = keypad.getKey();
  char keyB = keypadB.getKey();

char key = keypad.getKey();
  if (key == 'A') {
    mx.clear();
    Ascore = 0;
    displayNumber(Ascore, STCP_PIN, DS_PIN, SHCP_PIN);
    Bscore = 0;
    displayNumber(Bscore, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);

    score = 0;
    displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
    gameMode = 0;
    BgameStarted = false;
    gameStarted = false;
    CgameStarted = false;
    gameTime = 90;
    displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
    executed = false;

  } else if (key == 'B') {
    mx.clear();
    displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
    Ascore = 0;
    displayNumber(Ascore, STCP_PIN, DS_PIN, SHCP_PIN);
    Bscore = 0;
    displayNumber(Bscore, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);

    score = 0;
    displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
    gameMode = 1;
    gameTime = 70;
    displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
    gameStarted = false;
    BgameStarted = false;
    CgameStarted = false;
    executed = false;
    twoexecuted = false;
    threeexecuted = false;
    fiveexecuted = false;
    sixexecuted = false;

  } else if (key == 'C' || keyB == 'C') {
    // clear score, start new game mode
    mx.clear();
    calcScore = 6;
    CgameStarted = false;
    gameStarted = false;
    BgameStarted = false;
    gameMode = 2;
    displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
    Ascore = 0;
    displayNumber(Ascore, STCP_PIN, DS_PIN, SHCP_PIN);
    Bscore = 0;
    displayNumber(Bscore, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
    executed = false;

  }

if (gameMode == 0) {
    if (key == '0') {
      gameStarted = true;
      gameStartTime = millis();
    }
    if (gameStarted) {
      if (millis() - lastTimeUpdated >= 1000) {
        gameTime--;
        displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
        lastTimeUpdated = millis();
      }
      if (gameTime <= 0) {
        gameStarted = false;
        mx.clear();
        if (key == '0'){
          gameTime = 90;
          gameStarted = true;
          score = 0;
          displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
          displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
        }
      }
      if (millis() - MoleAppearTime > moleTime) {
        MolePosition = random(0, 9);
        mx.clear();
        int row = holePositions[MolePosition][0];
        int col = holePositions[MolePosition][1];
        mx.setPoint(row, col, true);
        mx.setPoint(row+1, col, true);
        mx.setPoint(row, col+1, true);
        mx.setPoint(row+1, col+1, true);
        mx.transform(MD_MAX72XX::TRC);
        MoleAppearTime = millis();
      }
      if (key) {
        int keyNumber = key - '1';
        if (keyNumber == MolePosition) {
          if(score >= 99){
            gameStarted = false;
            mx.clear();
            score = 0;
            gameTime = 91;
          }
          else{
            score++;
          }
          displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
          mx.clear();
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              if (i == 0 || i == 7 || j == 0 || j == 7) {
                mx.setPoint(i, j, true);
              }
            }
          }
          delay(150);
          mx.clear();
        }
        else{
          if(score>0){
            score--;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
          }
        }
      }
    }
  } else if (gameMode == 1) {
    if (key == '0') {
      BgameStarted = true;
      gameStartTime = millis();
      twoexecuted = false;
      threeexecuted = false;
      fiveexecuted = false;
      sixexecuted = false;
    }
    if (BgameStarted) {
      if (millis() - lastTimeUpdated >= 1000) {
        gameTime--;
        displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
        lastTimeUpdated = millis();
      }
      if (gameTime <= 0) {
        BgameStarted = false;
        mx.clear();
        if (key == '0'){
          gameTime = 70;
          BgameStarted = true;
          score = 0;
          displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
          displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
        }
      }
      if (millis() - MoleAppearTime > moleTime - score*5) {
        MolePosition = random(0, 9);
        mx.clear();
        int row = holePositions[MolePosition][0];
        int col = holePositions[MolePosition][1];
        mx.setPoint(row, col, true);
        mx.setPoint(row+1, col, true);
        mx.setPoint(row, col+1, true);
        mx.setPoint(row+1, col+1, true);
        mx.transform(MD_MAX72XX::TRC);
        MoleAppearTime = millis();
      }
      if (key) {
        int keyNumber = key - '1';
        if (keyNumber == MolePosition) {
          if(score >= 99){
            BgameStarted = false;
            mx.clear();
            score = 0;
            gameTime = 71;
          }
          else if(score>=20 && score <=40){
            score+=2;
            if (!twoexecuted){
              gameTime+=10;
              displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
              twoexecuted = !twoexecuted;
            }
            if(score>38 && !threeexecuted){
              gameTime+=15;
              displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
              threeexecuted = !threeexecuted;
            }
          }
          else if(score>40 && score <=60){
            score+=3;
            if(score>=50 && !fiveexecuted){
              gameTime+=20;
              displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
              fiveexecuted = !fiveexecuted;
            }
          }
          else if(score>60){
            score+=4;
            if(score>=63 && !sixexecuted){
              gameTime+=30;
              displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
              sixexecuted = !sixexecuted;
            }
          }

          else{
            score++;
          }
          displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
          mx.clear();
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              if (i == 0 || i == 7 || j == 0 || j == 7) {
                mx.setPoint(i, j, true);
              }
            }
          }
          delay(150);
          mx.clear();
        }
        else{
          displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          if(score>0 && score <=30){
            gameTime--;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
            score--;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
          }
          else if(score > 30 && score <=35){
            gameTime--;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
            score-=2;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);

          }
          else if (score > 35 && score <=40){
            score-=2;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
            gameTime-=2;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          }
          else if(score > 40 && score <=50){
            score-=3;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
            gameTime-=2;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          }
          else if (score > 50 && score <= 70){
            score-=3;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
            gameTime-=3;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          }
          else if (score > 70 && score <= 80){
            score-=4;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
            gameTime-=4;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          }
          else if (score > 80 && score <= 90){
            score-=5;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
            gameTime-=5;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          }
          else if (score > 90){
            score-=7;
            displayNumber(score, STCP_PIN, DS_PIN, SHCP_PIN);
            gameTime-=7;
            displayNumber(gameTime, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
          }


        }
      }
    }

  }

  else if (gameMode == 2) {
    if (key == '0' || keyB == '0') {
      CgameStarted = true;
      MoleAppearTime = millis();
      keyTime = millis();
      Ascore = 0;
      displayNumber(Ascore, STCP_PIN, DS_PIN, SHCP_PIN);
      Bscore = 0;
      displayNumber(Bscore, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);

    }
    if (calcScore == 1 || calcScore == 11) {
      mx.clear();
      CgameStarted = false;
      if (calcScore == 1 && executed == false){
        for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
          mx.setPoint(row, col, bitRead(B[row], 7-col));

          }
        }
        delay(100);
        Bscore++;
        displayNumber(Bscore, STCP_PIN_2, DS_PIN_2, SHCP_PIN_2);
        executed = true;

      }else if(calcScore == 11 && executed == false){
          for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
            mx.setPoint(row, col, bitRead(A[row], 7-col));

            }
          }
        //delay(100);
        Ascore++;
        displayNumber(Ascore, STCP_PIN, DS_PIN, SHCP_PIN);
        executed = true;

      }
    }
    if (!CgameStarted && executed == true) {
      delay(800);
    CgameStarted = true;
    executed = false;
    MoleAppearTime = millis();
    keyTime = millis();
    // Reset score
    calcScore = 6;
    // Reset error count
    keyErrorCountA = 0;
    keyErrorCountB = 0;
    }
    if (CgameStarted) {
      if (millis() - MoleAppearTime > moleTime) {
        MolePosition = random(0, 9);
        mx.clear();
        int row = holePositions[MolePosition][0];
        int col = holePositions[MolePosition][1];
        mx.setPoint(row, col, true);
        mx.setPoint(row+1, col, true);
        mx.setPoint(row, col+1, true);
        mx.setPoint(row+1, col+1, true);
          mx.transform(MD_MAX72XX::TRC);

        MoleAppearTime = millis();
      }
      if (key) { 
        int keyNumber = key - '1';
        if (keyNumber == MolePosition) {
          calcScore++;
          MolePosition = random(0, 9);
        mx.clear();
        }
        else if (key == 'A'){
          CgameStarted = false;
          gameMode = 0;
          executed = false;
          // Reset score
          calcScore = 6;
          // Reset error count
          keyErrorCountA = 0;
          keyErrorCountB = 0;
          Ascore = 0;
          Bscore = 0;
        }
        else if (key == 'B'){
          CgameStarted = false;
          gameMode = 1;
          executed = false;
          // Reset score
          calcScore = 6;
          // Reset error count
          keyErrorCountA = 0;
          keyErrorCountB = 0;
          Ascore = 0;
          Bscore = 0;

        }

        else {
          keyErrorCountA++;
        }
      }
      if (keyB) {
        int keyNumber = keyB - '1';
        if (keyNumber == MolePosition) {
          calcScore--;
          MolePosition = random(0, 9);
        mx.clear();
        }

        else if (keyB == 'A'){
          CgameStarted = false;
          gameMode = 0;
          executed = false;
          // Reset score
          calcScore = 6;
          // Reset error count
          keyErrorCountA = 0;
          keyErrorCountB = 0;
          Ascore = 0;
          Bscore = 0;

        }

        else if (keyB == 'B'){
          CgameStarted = false;
          gameMode = 1;
          executed = false;
          // Reset score
          calcScore = 6;
          // Reset error count
          keyErrorCountA = 0;
          keyErrorCountB = 0;
          Ascore = 0;
          Bscore = 0;

        }

        else {
          keyErrorCountB++;
        }
      }
      if(millis() - keyTime > 1000) {
        if(keyErrorCountA >= 3) {
          calcScore--;
          keyErrorCountA = 0;
        }
        if(keyErrorCountB >= 3) {
          calcScore++;
          keyErrorCountB = 0;
        }
        keyTime = millis();
      }
      //if(key || keyB){

    
        if (calcScore != 6) {
if (calcScore == 5) {
            mx.setPoint(0,0,false);
  mx.setPoint(0,1,false);
  mx.setPoint(0,2,false);
  mx.setPoint(0,3,false);
  mx.setPoint(0,4,false);
  mx.setPoint(0,5,false);
  mx.setPoint(0,6,false);
  mx.setPoint(0,7,false);
  mx.setPoint(1,0,false);
  mx.setPoint(1,7,false);
  mx.setPoint(2,0,false);
  mx.setPoint(2,7,false);
  mx.setPoint(3,0,false);
  mx.setPoint(3,7,false);
  mx.setPoint(4,0,false);
  mx.setPoint(4,7,false);
  mx.setPoint(5,0,false);
  mx.setPoint(5,7,false);
  mx.setPoint(6,0,true);
  mx.setPoint(6,7,true);
  mx.setPoint(7,0,true);
  mx.setPoint(7,1,true);
  mx.setPoint(7,2,true);
  mx.setPoint(7,3,true);
  mx.setPoint(7,4,true);
  mx.setPoint(7,5,true);
  mx.setPoint(7,6,true);
  mx.setPoint(7,7,true);
          }
          else if (calcScore == 4) {
            mx.setPoint(0,0,false);
    mx.setPoint(0,1,false);
    mx.setPoint(0,2,false);
    mx.setPoint(0,3,false);
    mx.setPoint(0,4,false);
    mx.setPoint(0,5,false);
    mx.setPoint(0,6,false);
    mx.setPoint(0,7,false);
    mx.setPoint(1,0,false);
    mx.setPoint(1,7,false);
    mx.setPoint(2,0,false);
    mx.setPoint(2,7,false);
    mx.setPoint(3,0,false);
    mx.setPoint(3,7,false);            
    mx.setPoint(4,0,true);
    mx.setPoint(4,7,true);
    mx.setPoint(5,0,true);
    mx.setPoint(5,7,true);
    mx.setPoint(6,0,true);
    mx.setPoint(6,7,true);
    mx.setPoint(7,0,true);
    mx.setPoint(7,1,true);
    mx.setPoint(7,2,true);
    mx.setPoint(7,3,true);
    mx.setPoint(7,4,true);
    mx.setPoint(7,5,true);
    mx.setPoint(7,6,true);
    mx.setPoint(7,7,true);
          }
          else if (calcScore == 3) {
            mx.setPoint(0,0,false);
    mx.setPoint(0,1,false);
    mx.setPoint(0,2,false);
    mx.setPoint(0,3,false);
    mx.setPoint(0,4,false);
    mx.setPoint(0,5,false);
    mx.setPoint(0,6,false);
    mx.setPoint(0,7,false);
    mx.setPoint(1,0,false);
    mx.setPoint(1,7,false);
    mx.setPoint(2,0,true);
    mx.setPoint(2,7,true);
    mx.setPoint(3,0,true);
    mx.setPoint(3,7,true);
    mx.setPoint(4,0,true);
    mx.setPoint(4,7,true);
    mx.setPoint(5,0,true);
    mx.setPoint(5,7,true);
    mx.setPoint(6,0,true);
    mx.setPoint(6,7,true);
    mx.setPoint(7,0,true);
    mx.setPoint(7,1,true);
    mx.setPoint(7,2,true);
    mx.setPoint(7,3,true);
    mx.setPoint(7,4,true);
    mx.setPoint(7,5,true);
    mx.setPoint(7,6,true);
    mx.setPoint(7,7,true);
          }
          else if (calcScore == 2) {
            mx.setPoint(0,0,true);
            mx.setPoint(0,1,true);
            mx.setPoint(0,2,true);
            mx.setPoint(0,3,true);
            mx.setPoint(0,4,true);
            mx.setPoint(0,5,true);
            mx.setPoint(0,6,true);
            mx.setPoint(0,7,true);
            mx.setPoint(1,0,true);
            mx.setPoint(1,7,true);
            mx.setPoint(2,0,true);
            mx.setPoint(2,7,true);
            mx.setPoint(3,0,true);
            mx.setPoint(3,7,true);            
            mx.setPoint(4,0,true);
            mx.setPoint(4,7,true);
            mx.setPoint(5,0,true);
            mx.setPoint(5,7,true);
            mx.setPoint(6,0,true);
            mx.setPoint(6,7,true);
            mx.setPoint(7,0,true);
            mx.setPoint(7,1,true);
            mx.setPoint(7,2,true);
            mx.setPoint(7,3,true);
            mx.setPoint(7,4,true);
            mx.setPoint(7,5,true);
            mx.setPoint(7,6,true);
            mx.setPoint(7,7,true);

          }
          else if (calcScore == 7) {
  mx.setPoint(0, 0, true);
  mx.setPoint(0, 1, true);
  mx.setPoint(0, 2, true);
  mx.setPoint(0, 3, true);
  mx.setPoint(0, 4, true);
  mx.setPoint(0, 5, true);
  mx.setPoint(0, 6, true);
  mx.setPoint(0, 7, true);
  mx.setPoint(1, 0, true);
  mx.setPoint(1, 7, true);
  mx.setPoint(2, 0, false);
  mx.setPoint(2, 7, false);
  mx.setPoint(3, 0, false);
  mx.setPoint(3, 7, false);
  mx.setPoint(4, 0, false);
  mx.setPoint(4, 7, false);
  mx.setPoint(5, 0, false);
  mx.setPoint(5, 7, false);
  mx.setPoint(6, 0, false);
  mx.setPoint(6, 7, false);
  mx.setPoint(7, 0, false);
  mx.setPoint(7, 1, false);
  mx.setPoint(7, 2, false);
  mx.setPoint(7, 3, false);
  mx.setPoint(7, 4, false);
  mx.setPoint(7, 5, false);
  mx.setPoint(7, 6, false);
  mx.setPoint(7, 7, false);
} else if (calcScore == 8) {
  mx.setPoint(0, 0, true);
  mx.setPoint(0, 1, true);
  mx.setPoint(0, 2, true);
  mx.setPoint(0, 3, true);
  mx.setPoint(0, 4, true);
  mx.setPoint(0, 5, true);
  mx.setPoint(0, 6, true);
  mx.setPoint(0, 7, true);
  mx.setPoint(1, 0, true);
  mx.setPoint(1, 7, true);
  mx.setPoint(2, 0, true);
  mx.setPoint(2, 7, true);
  mx.setPoint(3, 0, true);
  mx.setPoint(3, 7, true);
  mx.setPoint(4, 0, false);
  mx.setPoint(4, 7, false);
  mx.setPoint(5, 0, false);
  mx.setPoint(5, 7, false);
  mx.setPoint(6, 0, false);
  mx.setPoint(6, 7, false);
  mx.setPoint(7, 0, false);
  mx.setPoint(7, 1, false);
  mx.setPoint(7, 2, false);
  mx.setPoint(7, 3, false);
  mx.setPoint(7, 4, false);
  mx.setPoint(7, 5, false);
  mx.setPoint(7, 6, false);
  mx.setPoint(7, 7, false);
} else if (calcScore == 9) {
  mx.setPoint(0, 0, true);
  mx.setPoint(0, 1, true);
  mx.setPoint(0, 2, true);
  mx.setPoint(0, 3, true);
  mx.setPoint(0, 4, true);
  mx.setPoint(0, 5, true);
  mx.setPoint(0, 6, true);
  mx.setPoint(0, 7, true);
  mx.setPoint(1, 0, true);
  mx.setPoint(1, 7, true);
  mx.setPoint(2, 0, true);
  mx.setPoint(2, 7, true);
  mx.setPoint(3, 0, true);
  mx.setPoint(3, 7, true);
  mx.setPoint(4, 0, true);
  mx.setPoint(4, 7, true);
  mx.setPoint(5, 0, true);
  mx.setPoint(5, 7, true);
  mx.setPoint(6, 0, false);
  mx.setPoint(6, 7, false);
  mx.setPoint(7, 0, false);
  mx.setPoint(7, 1, false);
  mx.setPoint(7, 2, false);
  mx.setPoint(7, 3, false);
  mx.setPoint(7, 4, false);
  mx.setPoint(7, 5, false);
  mx.setPoint(7, 6, false);
  mx.setPoint(7, 7, false);
} else if (calcScore == 10) {
  mx.setPoint(0, 0, true);
  mx.setPoint(1, 0, true);
  mx.setPoint(2, 0, true);
  mx.setPoint(3, 0, true);
  mx.setPoint(4, 0, true);
  mx.setPoint(5, 0, true);
  mx.setPoint(6, 0, true);
  mx.setPoint(7, 0, true);
  mx.setPoint(0, 1, true);
  mx.setPoint(7, 1, true);
  mx.setPoint(0, 2, true);
  mx.setPoint(7, 2, true);
  mx.setPoint(0, 3, true);
  mx.setPoint(7, 3, true);
  mx.setPoint(0, 4, true);
  mx.setPoint(7, 4, true);
  mx.setPoint(0, 5, true);
  mx.setPoint(7, 5, true);
  mx.setPoint(0, 6, true);
  mx.setPoint(7, 6, true);
  mx.setPoint(0, 7, true);
  mx.setPoint(1, 7, true);
  mx.setPoint(2, 7, true);
  mx.setPoint(3, 7, true);
  mx.setPoint(4, 7, true);
  mx.setPoint(5, 7, true);
  mx.setPoint(6, 7, true);
  mx.setPoint(7, 7, true);
}

          
        }  
      //}
    }
  }
}


