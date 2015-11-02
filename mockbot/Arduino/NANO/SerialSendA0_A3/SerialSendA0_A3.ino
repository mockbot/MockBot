#define NUM_SAMPLES 10

int inA0 = 0;
int inA1 = 0;
int inA2 = 0;
int inA3 = 0;

float inA0v = 0;
float inA1v = 0;
float inA2v = 0;
float inA3v = 0;

float R1=10000;
float R2=3300;
float Vmax = 20.0;
float Valert = 12.0;
float ADCmax = 1024.0;
float calibrate = 0.85;
int sample_count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop()
{
  inA0 = 0;
  inA1 = 0;
  inA2 = 0;
  inA3 = 0;
 
  sample_count = 0;
  
  while (sample_count < NUM_SAMPLES) {
    inA0 += analogRead(A0);
    inA1 += analogRead(A1);
    inA2 += analogRead(A2);
    inA3 += analogRead(A3);
    sample_count++;
    delay(10);
  }

  inA0v = calibrate * ((float)inA0 / (float)NUM_SAMPLES * Vmax ) / ADCmax;
  inA1v = calibrate * ((float)inA1 / (float)NUM_SAMPLES * Vmax ) / ADCmax;
  inA2v = calibrate * ((float)inA2 / (float)NUM_SAMPLES * Vmax ) / ADCmax;
  inA3v = calibrate * ((float)inA3 / (float)NUM_SAMPLES * Vmax ) / ADCmax;

  if (inA0v < Valert){
    for (int i=1;i<10;i++){
      digitalWrite(13,HIGH);
      delay(100);
      digitalWrite(13,LOW);
      delay(100);
    }
   
  }
  /*
  Serial.print("[{\"A0\":\"");
  Serial.print(inA0v);
  Serial.print("\"},{\"A1\":\"");
  Serial.print(inA1v);
  Serial.print("\"},{\"A2\":\"");
  Serial.print(inA2v);
  Serial.print("\"},{\"A3\":\"");
  Serial.print(inA3v);
  Serial.print("\"}]\r\n");
  */

  Serial.print("[{\"A0\":\"");
  Serial.print(inA0v);
  Serial.print("\",\"A1\":\"");
  Serial.print(inA1v);
  Serial.print("\",\"A2\":\"");
  Serial.print(inA2v);
  Serial.print("\",\"A3\":\"");
  Serial.print(inA3v);
  Serial.print("\"}]\r\n");

  delay(1000);
}

