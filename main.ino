
// Constantes Botões para ligar e inverter o sentido da rotação
#define pinBotaoA 5
#define pinBotaoB 4

// Cconstantes de Regulação do potenciometro
#define pinPotenciometro A0
#define pinEnableMotorA 9      //Porta Digital PWM Ligação com Ponte H
#define pinEnableMotorB 10     //Porta Digital PWM Ligação com Ponte H


#define pinSentido1MotorA 3
#define pinSentido2MotorA 2

#define pinSentido1MotorB 7
#define pinSentido2MotorB 6

byte stateA = 0;
bool buttonStateA = true;
bool buttonBeforeStateA = true;
//Efeito Bounce do arduino
unsigned long buttonDelayA;

byte stateB = 0;
bool buttonStateB = true;
bool buttonBeforeStateB = true;
//Efeito Bounce do arduino
unsigned long delayBotaoB;

void setup() {
  pinMode(pinBotaoA, INPUT_PULLUP);
  pinMode(pinBotaoB, INPUT_PULLUP);
  pinMode(pinEnableMotorA, OUTPUT);
  pinMode(pinEnableMotorB, OUTPUT);

  pinMode(pinSentido1MotorA, OUTPUT);
  pinMode(pinSentido2MotorA, OUTPUT);
  pinMode(pinSentido1MotorB, OUTPUT);
  pinMode(pinSentido2MotorB, OUTPUT);
}

void loop() {

  buttonStateA = digitalRead(pinBotaoA);
  if (!buttonStateA && buttonBeforeStateA) {
     if ((millis() - buttonDelayA) > 20) {
        stateA++;
        if (stateA > 3) {
           stateA = 0;
        }
        buttonDelayA = millis();
     }
  } else if (buttonStateA != buttonBeforeStateA) {
        buttonDelayA = millis();    
  }
  buttonBeforeStateA = buttonStateA;

  buttonStateB = digitalRead(pinBotaoB);
  if (!buttonStateB && buttonBeforeStateB) {
     if ((millis() - delayBotaoB) > 20) {
        stateB++;
        if (stateB > 3) {
           stateB = 0;
        }
        delayBotaoB = millis();
     }
  } else if (buttonStateB != buttonBeforeStateB) {
        delayBotaoB = millis();    
  }
  buttonBeforeStateB = buttonStateB;


  if (stateA == 0) {
     analogWrite(pinEnableMotorA, 0);
     
  } else if (stateA == 2) {
     analogWrite(pinEnableMotorA, 255); 
     digitalWrite(pinSentido1MotorA, HIGH);
     digitalWrite(pinSentido2MotorA, HIGH);    
     
  } else {    
     analogWrite(pinEnableMotorA, map(analogRead(pinPotenciometro), 0, 1023, 0, 255)); 

     if (stateA == 1) {
        digitalWrite(pinSentido1MotorA, LOW);
        digitalWrite(pinSentido2MotorA, HIGH);
        
     } else { // stateA == 3
        digitalWrite(pinSentido1MotorA, HIGH);
        digitalWrite(pinSentido2MotorA, LOW);      
     }
  } 


  if (stateB == 0) {
     analogWrite(pinEnableMotorB, 0);
     
  } else if (stateB == 2) {
     analogWrite(pinEnableMotorB, 255); 
     digitalWrite(pinSentido1MotorB, HIGH);
     digitalWrite(pinSentido2MotorB, HIGH);
    
  } else {
     analogWrite(pinEnableMotorB, map(analogRead(pinPotenciometro), 0, 1023, 0, 255)); 

     if (stateB == 1) {
        digitalWrite(pinSentido1MotorB, LOW);
        digitalWrite(pinSentido2MotorB, HIGH);
        
     } else { // estadoB == 3
        digitalWrite(pinSentido1MotorB, HIGH);
        digitalWrite(pinSentido2MotorB, LOW);      
     }
  } 
  
}
