
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int sum=0;
int c1=0,c2=0,c3=0;

char t;

void setup() {

pinMode(7,OUTPUT);   //left motors forward
pinMode(6,OUTPUT);   //left motors reverse
pinMode(5,OUTPUT);   //right motors forward
pinMode(4,OUTPUT);   //right motors reverse
Serial.begin(9600); 

 // while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
 
}

void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
if(t=='1' || t=='2' || t=='3' || t=='4' || t=='5'){
  
if(t == '1'){            //move forward(all motors rotate in forward direction)
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
}

else if(t == '2'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
}

else if(t == '3'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
}

else if(t == '4'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
}
 
else if(t == '5'){      //STOP (all motors stop)
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
}
delay(100);

  }
  
  
  
  
 else{ 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
 

  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  Serial.println(content);
  if (content.substring(1) == "B1 B7 53 C3" ){
    if(c1%2==0){
    Serial.print("item 1 Price: ");
    Serial.println(10);
    sum=sum+10;
    Serial.print("Your Sum: ");
     Serial.println(sum);}
     else{
      Serial.print("item 1 deleted New sum ");
      sum=sum-10;
      Serial.println(sum);
         
      }
      c1++;
    }
   else if(content.substring(1) == "C5 6E E2 10"){
    if(c2%2==0){
    Serial.print("item 2 Price: ");
    Serial.println(20);
    sum=sum+20;
    Serial.print("Your Sum: ");
     Serial.println(sum);
    }
    else{
      Serial.print("item 2 deleted New sum ");
      sum=sum-20;
      Serial.println(sum);
      }
      c2++;
     }
   else{
    if(c3%2==0){
      Serial.print("item 3 Price: ");
    Serial.println(30);
    sum=sum+30;
    Serial.print("Your Sum: ");
     Serial.println(sum);
    }
    else{
      Serial.print("item 3 deleted New sum ");
      sum=sum-30;
      Serial.println(sum);
    }
    c3++;
    }  

 }




}
