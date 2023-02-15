/*
PRÁCTICA 22. XANELA DUN COCHE CON INVERSIÓN DE XIRO E 2 FINAIS DE CARREIRA
Nesta práctica a xanela do coche activase e párase cun mesmo
pulsador, pero ó mesmo tempo o paro faise a través dun fin de 
carreira situado na parte posterior da xanela e outro fin de 
carreira situado na parte inferior da mesma, con 2 pulsadores 
que se activan a través dun pulso eléctrico.

A posición inicial da xanela está parada arriba no fin de carreira 
(estado 1), se premo o pulsador do pin 10, a xanela baixa (estado 2),
cando chega abaixo, actívase o fin de carreira (pasando ó estado 3).
Se volvo premer o pulsador, activo o motor de subida, a xanela 
e se pare no fin de carreira da parte inferior(estado 0).

Entradas: 3 Pulsadores (dixitais)
Saida: 2 Relés (2x dixital)

Autor: Jéssica Suárez Parada
Data:12/02/2023
*/

#define motorArriba 12
#define motorAbaixo 11
#define pulsador 10
#define fcArriba 9
#define fcAbaixo 8

int estado = 1;    //Toma valores 0,1,2,3. En 0 sube en 2 baixa, 
                   //en 1 párase arriba e 3 párase abaixo.
int contador = 0;  //Contador co numero de impulsos do motor

void setup(){
  pinMode(motorArriba, OUTPUT);
  pinMode(motorAbaixo,OUTPUT);
  pinMode(pulsador,INPUT);
  pinMode(fcArriba, INPUT);
  pinMode(fcAbaixo, INPUT);
  
  Serial.begin(9600);  //Velocidade de sincronismo das comunicacións
}

void loop() {   //executa a lectura do pulsador
  if(digitalRead(pulsador)) {  
    estado = (++estado) % 4; //carga o valor do resto da division /3. ex: 1/3, resto =1, este é o estado que toma como lectura o pulsador 
//   estado++ ;asigna e despois actualiza. ++estado; actualiza e logo designa.
//   if(estado > 3) {  //cando o estado é maior que 2,o orde da suma e da división.
//   estado = 0;     //volve ó estado 0
//   }

    contador = 100;
    while(digitalRead(pulsador)) {
      delay(20);
    }
  }
  
  if(digitalRead(fcArriba)) {   //Acciona o fin de Carreira arriba
    if(estado != 2 ) {  //Sube a xanela,estado 0(diferente ó estado 2) 
      estado = 1;       //Paro fin de carreira arriba               
    }
    delay(20);
  }
   
  if(digitalRead(fcAbaixo)) {   //Acciona o fin de Carreira abaixo
    if(estado != 0 ) {  //Baixa a xanela,estado 2(diferente ó estado 0)   
      estado = 3;       //Paro fin de carreira abaixo               
    }
    delay(20);
  }
  
  //Fin da lectura do pulsador
  
  Serial.print("Valor do contador: ");
  Serial.println(contador);
  Serial.print("  | Estado: ");
  Serial.println(estado);
  
  //Accionamento dos motores
  if(contador > 0) {         //Conta o número de impulsos do motor
    if(estado == 0){         //Sube a xanela
    digitalWrite(motorArriba, HIGH);
    digitalWrite(motorAbaixo, LOW);
    delay(70);
    contador--;
  }
  else if(estado== 2) {  //Baixa a xanela
    digitalWrite(motorArriba, LOW);
    digitalWrite(motorAbaixo, HIGH);
    delay(70);
    contador--;
  }
    else {
    digitalWrite(motorArriba, LOW);
    digitalWrite(motorAbaixo, LOW);
    delay(70);
    contador--;  
    }
  }
  else {      //Se o motor está parado , lee o pulsador 10 veces/seg.
    digitalWrite(motorArriba, LOW);
    digitalWrite(motorAbaixo, LOW);
    delay(100);
  }
}
  //Fin do accionamento dos motores
  //delay (100)
