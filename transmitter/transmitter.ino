//SIMPLE RF TRANSMITTER BASED UPON THE CODE OF Kevin Darrah
//https://www.youtube.com/watch?v=3Rs3SJBsiYE&ab_channel=KevinDarrah
//
//MODIFICATIONS MADE BY: JRC - Tech OCT-2020


//The transmitter was tested with 12V and antenna (a piece of wire about 21cm)
//The communication was verified from one room to the next, even between walls.
//If the transmitter is powered with 5V the range is reduced.

const char message[]="Javier Ruzzante C! - JRC - Tech";

void setup(){
  pinMode(2, OUTPUT);
  
}

void loop(){
  for(int k=0; k<sizeof message;k++){
    rf_send((byte)message[k]);  
  }
  rf_send('#');
  delay(10000);     //Wait 10 seconds
  
}

void rf_send(byte input){
  int i;
  for(i=0;i<50;i++){      // This is for sending 50 training pulses, so the receiver can catch up the signal before we send the data. Original version did training pulses 20 times...
    digitalWrite(2,HIGH);
    delayMicroseconds(500);
    digitalWrite(2, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(2, HIGH);
  delayMicroseconds(3000);  //After training pulses we send a high for 3 ms, so the receiver can detect it...
  digitalWrite(2,LOW);
  delayMicroseconds(500);  //and next we send a low for 500 us, when this occur we've got sync between transmitter and receiver, and now were ready to send some data
  
  for (i=0;i<8; i++){           //Send the value of each bit and its complement in order to keep the output pin changing, mantaining RF link live...
    if(bitRead(input,i)==1)     //For 'ones' we send a high 500us and next a low 500us
      digitalWrite(2, HIGH);
    else                        //For 'zeros' we send a low 500us and next a high 500us
      digitalWrite(2, LOW);
    delayMicroseconds(500);
    
    if(bitRead(input,i)==1)     //For 'ones' we send a high 500us and next a low 500us
      digitalWrite(2, LOW);
    else                        //For 'zeros' we send a low 500us and next a high 500us
      digitalWrite(2, HIGH);
    delayMicroseconds(500);
  }
  
  digitalWrite(2,LOW);         //Ensure that the output pin remains in low state after finish transmission
}
