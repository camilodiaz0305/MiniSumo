//#include <QTRSensors.h>

//Sensores laterales (Digitales)
#define SS_L 13 //D13
#define SS_R 2 //D2

//Sensores frente (Analogicos)
#define SF_L 17 //A3
#define SF_R 18 //A4

//Sensores QTR
#define SP_L 14 //A0
#define SP_R 16 //A2

//pines de conexión motores y PWM
#define PWM_A 5 //D5
#define AIN2 11 //D11
#define AIN1 10 //D10

#define PWM_B 6 //D6
#define BIN2 7 //D7
#define BIN1 8 //D8

#define on 15 //A1


//variables para guardar valor de sensores analogicos
float read_SF_L;
float read_SF_R;

//variables para guardar valor Sensores digitales
int read_SS_L;
int read_SS_R;
int read_SP_R;
int read_SP_L;
int read_on;

int distanceSFL, distanceSFR;

void setup() {
  pinMode(on, INPUT);
  Serial.begin(9600);
  inputs();
  outputs();
}

void inputs(){
  pinMode(SS_L, INPUT);
  pinMode(SS_R, INPUT);
  pinMode(SF_L, INPUT);
  pinMode(SF_R, INPUT);
  pinMode(SP_L, INPUT);
  pinMode(SP_R, INPUT);
}

void outputs(){
  pinMode(PWM_A, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
}

void loop() {
  //Rutinas de Testeo
  //sensorFrontLeft();
  //sensorFrontRight();

  //sensorSideLeft();
  //sensorSideRight();


  
  //detectionObjects();
  if(digitalRead(on) == 1){
    moveRobot();
  }else if(digitalRead(on) == 0){
    motores(0,0);
    }
  //sensorFloor();
  
  
  
   // if(read_on == 1){
       //Serial.println(read_on);
      //sensor digital 0=oponente, 1=nada
      /*
      if((read_SS_L==1)and(distanceSFL>11)and(read_SS_R==1)){motores(-200,200);}//+, - derecha
      if((read_SS_L==1)and(distanceSFL>11)and(read_SS_R==0)){motores(-200,200);}
      if((read_SS_L==1)and(distanceSFL<=11)and(read_SS_R==0)){motores(-200,200);}
      if((read_SS_L==1)and(distanceSFL<=10)and(read_SS_R==1)){motores(200,200);}
      if((read_SS_L==0)and(distanceSFL<=11)and(read_SS_R==1)){motores(200,-200);}
      if((read_SS_L==0)and(distanceSFL>11)and(read_SS_R==1)){motores(200,-200);}*/
    
      //if((read_SP_R<10)and(read_SS_L==1)and(distanceSFL>20)and(read_SS_R==1)){motores(-200,-200);}
      /*Serial.println(read_SP_R);
      delay(100);*/
 // }
  //if(read_on == 0){motores(0,0);}
}

//Valores aproximados de detección 15cm máximo. Objeto < 200, sin objeto > 1000/
float sensorFrontLeft(){
  read_SF_L = analogRead(SF_L);
  distanceSFL = pow(3027.4/read_SF_L,1.2134);
  //Serial.print("Distancia detectada objeto sensor Izquierdo: ");
  //Serial.println(distanceSFL);
  delay(1);
  return read_SF_L;
  }

float sensorFrontRight(){
  read_SF_R = analogRead(SF_R);
  distanceSFR = pow(3027.4/read_SF_R,1.2134);
  //Serial.print("Distancia detectada objeto sensor Derecho: ");
  //Serial.println(distanceSFR);
  delay(1);
  return read_SF_R;
  }

//Valores aproximados de detección 15cm máximo. Objeto = 0, sin objeto = 1
float sensorSideLeft(){
  read_SS_L = digitalRead(SS_L);
  delay(1);
  Serial.print("Valor detectado objeto sensor lado izquierdo a: ");
  Serial.println(read_SS_L);
  return read_SS_L;
  }

float sensorSideRight(){
  read_SS_R = digitalRead(SS_R);
  delay(1);
  Serial.print("Valor detectado objeto sensor lado derecho a: ");
  Serial.println(read_SS_R);
  return read_SS_R;
  }
  
float sensorFloor(){
   int Read_SP_L = digitalRead(SP_L);
  delay(1);
  Serial.print("Valor detectado objeto sensor lado izquierdo a: ");
  Serial.println(read_SP_L);
  return read_SP_L;
  }

void detectionObjects(){
  if((sensorFrontLeft()) < 200){
    Serial.println("Objeto Detectado Sensor frente Izquierdo");
    }else{
      Serial.println("Sensor Frente Izquierdo aún no detecta objeto");}
  if((sensorFrontRight()) < 200){
    Serial.println("Objeto Detectado Sensor frente Derecho");
    }else{
      Serial.println("Sensor Frente Derecho aún no detecta objeto");}
  /*if((sensorSideLeft()) == 0){
    Serial.println("Objeto Detectado Sensor Lado Izquierdo");
    }else{
      Serial.println("Sensor Lado Izquierdo aún no detecta objeto");}
  if((sensorSideRight()) == 0){
    Serial.println("Objeto Detectado Sensor Lado Derecho");
    }else{
      Serial.println("Sensor Lado Derecho aún no detecta objeto");}*/
  }

void moveRobot(){
  /*if((sensorFrontLeft() < 200) and (sensorFrontRight() < 200)){
    //Serial.println("Robot ataca");
    motores(200,-200);//Robot Ataca
    }else if((sensorFrontLeft() < 200)or (sensorFrontRight() < 200)){
      motores(200,-200);//Robot Ataca
    }else if(sensorSideRight() == 0 or sensorSideLeft() == 0){
      motores(-200,-200);
      }else{
      //Serial.println("Buscando Objeto");
      motores(-200,-200);//Robot busca
      }*/

   if((sensorFrontLeft() < 200) and (sensorFrontRight() < 200) or (sensorFrontLeft() < 200) or (sensorFrontRight() < 200)){
      Serial.println("Robot ataca");
      Serial.println(sensorFrontLeft(),sensorFrontRight());
      motores(200,200);//Robot Ataca 
    //delay(1500);
    //motores(200,-200);
    }else {
      Serial.println("Buscando Objeto");
      Serial.println(sensorFrontLeft(),sensorFrontRight());
      motores(200,-200);
      }
    if((sensorFrontLeft() < 200) or (sensorFrontRight() < 200)){
      motores(200,200);//Robot Ataca
      delay(500);
      motores(-200,200);
    }else if(sensorSideRight() == 0 or sensorSideLeft() == 0){
      motores(-200,-200);
      delay(300);
      motores(-200,200);
      }else{
      Serial.println("Buscando Objeto");
      motores(-200,-200);//Retrocede
      motores(200,-200);//Robot busca
      delay(700);
      motores(-200,200);
      delay(300);
      }
  }
  
void motores(int izq, int der){
  if (izq >= 0)//motor izquierdo hacia adelante 
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWM_A, izq);
    //Serial.println("Motor izquierdo hacia adelante");
  }
  if (izq < 0)//motor izquierdo hacia atras
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    izq = izq * -1;
    analogWrite(PWM_A, izq);
  }

  if (der >= 0)//motor derecha hacia adelante 
  {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWM_B, der);
    //Serial.println("Motor derecho hacia adelante");
  }
  if (der < 0)//motor derecho hacia atras
  {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    der = der * -1;
    analogWrite(PWM_B, der);
  }
}
