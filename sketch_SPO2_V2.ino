#include <PinChangeInt.h>
#include <eHealth.h>

float DEMO_DATA[] = { 0.02, 0.02, 0.02, 0.02, 0.05, 0.07, 0.06, 0.09,
0.06,-0.2, 0.9, 0.5, -0.1, 0.02, 0.02, 0.04, 0.1, 0.08, 0.03, 0.02, 0.02, 0.02, 0.02, 0.02};

int cont = 0;
int i = 0;


void setup() {
  Serial.begin(115200);  
  eHealth.initPulsioximeter();

  //Attach the inttruptions for using the pulsioximeter.   
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
}

void loop() {
  while(1){
    
    float temperature = eHealth.getTemperature();
    //float temperature = 35;
    int BPM = eHealth.getBPM();     
    int SPO2 = eHealth.getOxygenSaturation();
    float ECG = eHealth.getECG();
    //float ECG = DEMO_DATA[i];
    
    //Data sensor must be sent in this order
    
    Serial.print(eHealth.getBPM());  
    Serial.print(",");
    Serial.print(eHealth.getOxygenSaturation());  
    Serial.print(",");
    Serial.print(int(temperature)); 
    Serial.print(",");
    Serial.print(int(ECG));
    Serial.print("\n");    
   
   
//   i++;   
//   if(i == 23){
//    i=0;
//   }
   delay(1000); 
  
 }
  
  
}


//Include always this code when using the pulsioximeter sensor
//=========================================================================
void readPulsioximeter(){  

  cont ++;

  if (cont == 50) { //Get only of one 50 measures to reduce the latency
    eHealth.readPulsioximeter();  
    cont = 0;
  }
}


