#include "deneyap.h"


#define PWM_FREQ  5000                                  // PWM frekansi
#define PWM_CH    0                                     // PWM kanali (0-15)
#define PWM_RES   8  


#define MOT_PIN   PWM0                                  // DENEYAP KART ve DENEYAP KART 1A için   Motor PWM pini (PWM0-PWM1) 

#define MOT_DIR1  D12                                    // Motor yon secme pin1
#define MOT_DIR2  D13                                   // Motor yon secme pin2
#define MOT2_DIR1  D14                                    // Motor yon secme pin1
#define MOT2_DIR2  D15

uint8_t dutyCycle     = 100;                              // Motor hiz kontrol degiskeni (0-255) (8 bit cozunurluk)
uint8_t accAmount     = 1;                              // Ivmelenme adimi
uint8_t motorDir      = 1;                              // Motor yon secimi 1--> Ileri, 0--> Geri
uint8_t dirCounter    = 0;                              // Yon degisimi icin sayac
uint8_t changeDirFlag = 1;                              // Yon degisim bayragi


int gelen_veri[15];



void setup() {  

  pinMode(MOT_PIN, OUTPUT);                             // Motor PWM pini cikis olarak ayarlandi
  
  pinMode(MOT_DIR1, OUTPUT);                            // Motor yon secme pin1 cikis olarak ayarlandi
  pinMode(MOT_DIR2, OUTPUT);                            // Motor yon secme pin2 cikis olarak ayarlandi
  pinMode(MOT2_DIR1, OUTPUT);
  pinMode(MOT2_DIR2, OUTPUT);
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);                 // PWM zamanlayicisi ayarlandi 
  ledcAttachPin(MOT_PIN, PWM_CH);                       // Motor PWM pini ile zamanlayici iliskilendirildi
  
  Serial.begin(115200);                                                   // Seri haberlesme baslatildi
 
  

}

void loop() {

char string[] = "";

int availableBytes = Serial.available();
for(int i=0; i<availableBytes; i++)
{
    gelen_veri[i] = Serial.read();
}
  
int k=0;

while(gelen_veri[k]!='$'){
  k+=1;
}
int m=k+1;
int l=0;
char sag[4];
m+=1;
while(gelen_veri[m]!=','){
  sag[l] = gelen_veri[m];
  m+=1;
  l+=1;
  if(m>13 || l>3){
    break;
  }
}

sag[l] = '\0';

int  n;
n = atoi(sag);

m+=1;
l=0;
char sol[4];
while(gelen_veri[m]!='.'){
  sol[l] = gelen_veri[m];
  m+=1;
  l+=1;
  if(m>13 || l>3){
    break;
  }
}

sol[l] = '\0';

n = atoi(sol);

Serial.println(n);

  ledcWrite(PWM_CH, dutyCycle);                         // Motor PWM hiz ayari yapildi

    if(gelen_veri[k+1]=='F'){
      digitalWrite(MOT_DIR1, HIGH);
      digitalWrite(MOT2_DIR1, HIGH);

      digitalWrite(MOT_DIR2, LOW);
      digitalWrite(MOT2_DIR2, LOW);

      Serial.println("ileri gidiliyor");
    }
    else if(gelen_veri[k+1]=='B'){
      digitalWrite(MOT_DIR2, HIGH);
      digitalWrite(MOT2_DIR2, HIGH);

      digitalWrite(MOT_DIR1, LOW);
      digitalWrite(MOT2_DIR1, LOW);

      Serial.println("geri gidiliyor");
    }
    else if(gelen_veri[k+1]=='R'){
      digitalWrite(MOT_DIR2, HIGH);
      digitalWrite(MOT2_DIR1, HIGH);

      digitalWrite(MOT_DIR1, LOW);
      digitalWrite(MOT2_DIR2, LOW);

      Serial.println("saga gidiliyor");
    }
    else if(gelen_veri[k+1]=='L'){
      digitalWrite(MOT_DIR1, HIGH);
      digitalWrite(MOT2_DIR2, HIGH);

      digitalWrite(MOT_DIR2, LOW);
      digitalWrite(MOT2_DIR1, LOW);

      Serial.println("sola gidiliyor");
    }
    
    else{
      digitalWrite(MOT_DIR1, LOW);
      digitalWrite(MOT_DIR2, LOW);
      
      digitalWrite(MOT2_DIR1, LOW);
      digitalWrite(MOT2_DIR2, LOW);

      Serial.println("robot duruyor");
    }
  delay(20);

 
}
