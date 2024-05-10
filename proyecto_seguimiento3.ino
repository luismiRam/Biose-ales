#include <stdint.h>
#define FIR_FILTER_LENGTH 31

typedef struct {
  float out;
  float buf[FIR_FILTER_LENGTH];
  uint8_t bufIndex;
} FIRFilter ;


static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH]={-7.70126052e-04, -8.71097333e-04, -1.16377756e-03, -1.63778486e-03,
       -2.27430927e-03, -3.04691529e-03, -3.92270741e-03, -4.86380561e-03,
       -5.82906285e-03, -6.77594461e-03, -7.66248230e-03, -8.44920851e-03,
       -9.10098252e-03, -9.58861950e-03, -9.89024593e-03,  9.89239364e-01,
       -9.89024593e-03, -9.58861950e-03, -9.10098252e-03, -8.44920851e-03,
       -7.66248230e-03, -6.77594461e-03, -5.82906285e-03, -4.86380561e-03,
       -3.92270741e-03, -3.04691529e-03, -2.27430927e-03, -1.63778486e-03,
       -1.16377756e-03, -8.71097333e-04, -7.70126052e-04};

/*#endif*/
uint8_t nf = 0;
int outByte = 0;               // variable para enviar al puerto usb
FIRFilter *fir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      // abre el puerto serie a 9600 bps: 
  FIRFilter *fir;
    fir->out = 0.0f;
  fir->bufIndex = 0;

  for (uint8_t n = 0; n < FIR_FILTER_LENGTH; n++) {
    fir->buf[n] = 0.0f;
    //Serial.println(fir->buf[n]);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  outByte = analogRead(A0);         // leer dato analógico
  //Serial.println(outByte);          // enviar dato
  /*FIRFilter_Update(&FIRFilter,outByte);*/
   // FIRFilter *fir;
    fir->buf[fir->bufIndex] = outByte;
    /* Increment buffer index */
    Serial.println(fir->bufIndex);
    //fir->bufIndex++;
    if (fir->bufIndex == FIR_FILTER_LENGTH) {
        fir->bufIndex = 0;
    }
    //fir->out = 0.0f;
    
    /* Compute filter output */
    uint8_t sumIndex = fir->bufIndex;
    //Serial.println(sumIndex);
   
  //  for (uint8_t n = 0; n < FIR_FILTER_LENGTH; n++) {
     
      if(nf<FIR_FILTER_LENGTH){
        if (sumIndex > 0) {
            sumIndex--;
        } else {
           sumIndex=FIR_FILTER_LENGTH-1; 
        }
        fir->out +=FIR_IMPULSE_RESPONSE[nf]*fir->buf[sumIndex];
        
    //}
    }
    else{
      nf=0;
      }
    nf++;
    fir->bufIndex++;
    //Serial.println(FIR_IMPULSE_RESPONSE[nf]);
    
    
    /* Return output */
  //Serial.println(fir->out);
  delay(10);
}



