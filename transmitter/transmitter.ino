//SIMPLE RF TRANSMITTER BASED UPON THE CODE OF Kevin Darrah
//https://www.youtube.com/watch?v=3Rs3SJBsiYE&ab_channel=KevinDarrah
//
//MODIFICATIONS MADE BY: JRC - Tech OCT-2020

const char message[]="Javier Ruzzante C! - JRC - Tech";

void setup(){
  pinMode(2, OUTPUT);
  
}

void loop(){
  for(char k=0; k<sizeof message;k++){
    rf_send((byte)message[k]);  
  }
  rf_send('#');
  delay(5000);
  
}

void rf_send(byte input){
  int i;
  for(i=0;i<20;i++){
    digitalWrite(2,HIGH);
    delayMicroseconds(500);
    digitalWrite(2, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(2, HIGH);
  delayMicroseconds(3000);
  digitalWrite(2,LOW);
  delayMicroseconds(500);
  
  for (i=0;i<8; i++){
    if(bitRead(input,i)==1)
      digitalWrite(2, HIGH);
    else
      digitalWrite(2, LOW);
    delayMicroseconds(500);
    
    if(bitRead(input,i)==1)
      digitalWrite(2, LOW);
    else
      digitalWrite(2, HIGH);
    delayMicroseconds(500);
  }
  
  digitalWrite(2,LOW);
}
