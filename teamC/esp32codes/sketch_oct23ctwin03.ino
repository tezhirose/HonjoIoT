// circuit
// connect IO16 to IO17 using jumperwire

#define PIN_US_RET 17
#define PIN_US_SENS01 16
#define PIN_US_SENS02 04
//#define PIN_US_SENS01 04
//#define PIN_US_SENS02 16
volatile unsigned long gulRetTime=0;
volatile bool gbFlagGettingTime = 0;

float gfTimeCur01=0;
float gfTimeCur02=0;
float gfTimePre01=0;
float gfTimePre02=0;
#define N_AVE 50


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN_US_SENS01,OUTPUT);
  pinMode(PIN_US_SENS02,OUTPUT);
  pinMode(PIN_US_RET,INPUT);
  attachInterrupt(PIN_US_RET, isrRun, FALLING);
  Serial.println("setup done");

}

void isrRun(){
  gulRetTime = micros();
  gbFlagGettingTime =0;
}

void loop() {
  // put your main code here, to run repeatedly:
  float fRresult=0;
  gbFlagGettingTime =1;
  unsigned long ulTxTime= micros();  
  digitalWrite( PIN_US_SENS01,1);
    delayMicroseconds(10);
//  Serial.println("pulse done");
  digitalWrite( PIN_US_SENS01,0);
//  while(gbFlagGettingTime==1){}
  for(long i=0;i<65536*1024;i++){
    if(gbFlagGettingTime==0){
//      Serial.print(("S01: "));
      fRresult=gulRetTime-ulTxTime;
      gfTimeCur01=(float)(1/(float)N_AVE)*fRresult+((N_AVE-1)/(float)N_AVE)*gfTimePre01;
      gfTimePre01=gfTimeCur01;
      Serial.print((gfTimeCur01));
//      Serial.print((gulRetTime-ulTxTime));
      Serial.print(("\t"));
      break;
    }
  }
  delay(10);
    gbFlagGettingTime =1;
  ulTxTime= micros();  
  digitalWrite( PIN_US_SENS02,1);
    delayMicroseconds(10);
  digitalWrite( PIN_US_SENS02,0);
  for(long i=0;i<65536*1024;i++){
    if(gbFlagGettingTime==0){
//      Serial.print(("S02: "));
      fRresult=gulRetTime-ulTxTime;
      gfTimeCur02=(1/(float)N_AVE)*fRresult+(float)((N_AVE-1)/(float)N_AVE)*gfTimePre02;
      gfTimePre02=gfTimeCur02;
      Serial.println((gfTimeCur02));
//      Serial.println((gulRetTime-ulTxTime));
      break;
    }
  }
  delay(100);
}
