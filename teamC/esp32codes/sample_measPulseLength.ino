// circuit
// connect IO16 to IO17 using jumperwire

#define PIN_US_RET 17
#define PIN_US_SENS01 16
volatile unsigned long gulRetTime=0;
volatile bool gbFlagGettingTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN_US_SENS01,OUTPUT);
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
  gbFlagGettingTime =1;
  unsigned long ulTxTime= micros();  
  digitalWrite( PIN_US_SENS01,1);
  Serial.println("pulse done");
  digitalWrite( PIN_US_SENS01,0);
  while(gbFlagGettingTime==1){}
  Serial.println((gulRetTime-ulTxTime));
  delay(10);
}
