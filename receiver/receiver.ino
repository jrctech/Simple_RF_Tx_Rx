//SIMPLE RF RECEIVER BASED UPON THE CODE OF Kevin Darrah
//https://www.youtube.com/watch?v=3Rs3SJBsiYE&ab_channel=KevinDarrah
//
//MODIFICATIONS MADE BY: JRC - Tech OCT-2020

int i, good, k;
byte data_in;
void setup(){
  attachInterrupt(1,data_incoming,RISING);    //Interrupt on the rising edge of the signal at the input pin
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}//setup

void loop(){
  
  
}//loop

void data_incoming(){
    
    //Filter for noise and training pulses...
    for(i=0; i<100; i++){    //This loop ensures that the input pin is high for at least 2000us.  So, this will discard all the training pulses and good=1 when the pin is in the long high (3ms) sent by the transmitter.
      delayMicroseconds(20);
      good=1;
      if(digitalRead(3)==LOW){  //If the pin is low before 2ms then jump off.
      good=0;
      i=100;
      }
    }//for

    //Here we have detected the long high, and after switch off interrupt, wait for the input pin becomes low.  When this occur, transmitter and receiver are sync  
    if(good==1){
    detachInterrupt(1);
    while(1){
      if(digitalRead(3)==LOW){    //Sync!!
        delayMicroseconds(750);   //Now, wait 500us (low pulse duration) + 250us, (half pulse duration of the first data bit).  So, this will give an offset for checking the input at the middle of the pulse.

        for(i=0; i<8; i++){       //Start receiving the 8 bits, checking every 1000us (it has the 250us offset already when did the delay...)
          if(digitalRead(3)==HIGH)
            bitWrite(data_in, i, 1);
          else
            bitWrite(data_in, i, 0);
          delayMicroseconds(1000);
        }//for
        if(data_in=='#')        //This is a special char used to indicate the end of the message transmission
        Serial.println("");
        else
        Serial.print(char(data_in));

       break;//while
      }//low kickoff
      
    }//second while
    
    }//good check

  attachInterrupt(1,data_incoming,RISING);  
}//routine
