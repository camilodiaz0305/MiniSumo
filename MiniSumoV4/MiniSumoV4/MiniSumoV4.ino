// Define los estados HIGH,LOW de cada led 
#define led1on digitalWrite(led1, HIGH);
#define led2on digitalWrite(led2, HIGH);
#define led3on digitalWrite(led3, HIGH);
#define led1off digitalWrite(led1, LOW);
#define led2off digitalWrite(led2, LOW);
#define led3off digitalWrite(led3, LOW);

//Crea una variable a cada led 
const int led1 = 13; 
const int led2 = 12; 
const int led3 = 11; 

int adcd=0; //sensor de piso derecho QTR1
int adci=0; //sensor de piso izquierdo QTR2
int sharpd = 0; //sensor proximidad derecho QTR1 A4
int sharpi = 0; //sensor proximidad izquierdo QTR1 A2
int QT1=0;
int QT2=0;

const int in1a = 19; //direccion motor 1(derecho) hacia adelante
const int in1b = 3; //direccion motor 1(derecho) reversa

const int in2a = 4; //direccion motor 2(izquierdo) hacia adelante
const int in2b = 2; //direccion motor 2(izquierdo) reversa

const int pwm1 = 5; //PWM motor 1 Derecho
const int pwm2 = 6; //PWM motor 2 Izquierdo

const int limite = 50;

typedef enum{
  BUSCANDO = 0,
  ATAQUE,
  EVADIR
}ST_ROBOT;

ST_ROBOT st_robot = BUSCANDO;


void setup() {
 //configuracion de condiciones iniciales
 variables();
}

void variables(){
  //configuracion de condiciones iniciales
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  
  pinMode(in1a,OUTPUT);
  pinMode(in1b,OUTPUT);
  pinMode(in2a,OUTPUT);
  pinMode(in2b,OUTPUT);
  
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
}

void lecturaSensores(){
  //lectura de los sensores de piso y los sharp:
 adcd = analogRead(1); // Lee sensor Derecho
 adci = analogRead(3); // Lee sensor Izquierdo
 sharpi = analogRead(2);
 sharpd = analogRead(0);
}

void robot_buscando(){
    /* poner sensado aca, de todos los sensores*/
    
    if(sharpi<400 && sharpd<400){
       if(adcd >= limite && adcd >= limite){
          //Comienza la busqueda:
          motors(200,0);
          delay(300);
          motors(0,0);
          //
          if(sharpi<400 && sharpd<400){
            motors(200,200);
            delay(200);
            motors(0,0);
            if(sharpi<400 && sharpd<400){
              //
              motors(-90,200);
              delay(200);
              motors(0,0);
            }
          }
       }else{
        st_robot = EVADIR;    
       }
    }else if(sharpi>=400 && sharpd>=400){
      st_robot = ATAQUE;
    }
}

void robot_ataque(){

  if(sharpi>400 && sharpd>400){
    if(adcd >= limite && adcd >= limite){
      motors(255,255);
      delay(1000);
      motors(0,0);
      //delay(5000);
      //motors(0,0);  
    }else{
      st_robot = EVADIR;
    }
  }else{
    st_robot = BUSCANDO;
  }
  
  
}

void robot_evadir(){
   //Tener en cuenta que puede llegar a colocar problemas por no tener luz en el hueco.
  int velocidadEvasion = 255;
  
  if(adcd <= limite && adci >= limite){
    //Evada hacia la izquierda:
    led1on;
    motors(velocidadEvasion, -velocidadEvasion);
    delay(500);
    motors(0,0);
  }else if(adcd >= limite && adci <= limite){
    //Evada hacia la derecha:
    led2on;
    motors(-velocidadEvasion, velocidadEvasion);
    delay(500);
    motors(0,0);
  }else if(adcd >= limite && adci <= limite){
    //Cambie de posición 180°:
    led3on;
    motors(-velocidadEvasion, velocidadEvasion);
    delay(500);
    motors(0,0);
  }else{
    led1off;
    led2off;
    led3off;
    st_robot = BUSCANDO;
    
  }
}

void robot_process(){
    switch (st_robot)
    {
    case BUSCANDO:
        robot_buscando();
      break;
    case ATAQUE:
        if(sharpi>=400 && sharpd>=400){
             // enviamos valor porcentual de 100 y lo convertimos en la funcion robot_ataque()
            robot_ataque();
        }else if(sharpi<400 && sharpd<400){
            st_robot = BUSCANDO;
        }
      break;
    case EVADIR:
        robot_evadir();
      break;          
    default: 
        st_robot = BUSCANDO;
      break;
    }
}

void loop() {
  lecturaSensores();
  robot_process();
}

int motors(int speedL, int speedR){
  if(speedL>0 && speedR<0){ // detecta sensor derecho llanta derecha
    
      digitalWrite(in1b,LOW); //lanta der adelante
      digitalWrite(in1a,LOW); //llanta iz atras
      digitalWrite(in2b,HIGH); //lanta der atras
      digitalWrite(in2a,HIGH); //llanta iz adelante
      
      
  }else if(speedL<0 && speedR>0){//sensor izquierdo se prende llante izquierda
    
      digitalWrite(in2b,LOW); //lanta der atras
      digitalWrite(in2a,LOW); //llanta iz adelante
      digitalWrite(in1b,HIGH); //lanta der adelante
      digitalWrite(in1a,HIGH); //llanta iz atras
      
      
  }else if(speedL>0 && speedR>0){
      
      digitalWrite(in2b,LOW); //lanta der atras
      digitalWrite(in1a,LOW); //llanta iz atras
      digitalWrite(in1b,HIGH); //lanta der adelante
      digitalWrite(in2a,HIGH); //llanta iz adelante
      
  }
  analogWrite(pwm1,speedR);
  analogWrite(pwm2,speedL);
}
