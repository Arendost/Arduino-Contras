
/*
IMPORTANTE: A la hora de hacer las simulaciones en Proteus, siempre se debe
partir de tener un conocimiento de lo que se espera como resultado, si es
necesario de debe jugar con la funcion pausa del programa para que se compense el
tiempo de procesamiento que necesita su equipo informático. 
*/


int num;                                              // Variable que obtenemos del puerto serial
int ledV=13;                                          // Pin del led verde
int ledA=12;                                          // Pin del led Amarillo
int ledR=11;                                          // Pin del led Rojo
int password=1234;                                    // Password desde aqui puede ser cambiada la contraseña
int F=0;                                              // Variable que actua como indicador


void setup()
{
 Serial.begin(9600);                                  // Velocidad del puerto serial
pinMode(ledV,OUTPUT);                                 // Programado de salida del puerto donde se ubica el led verde
pinMode(ledA,OUTPUT);                                 // Programado de salida del puerto donde se ubica el led amarillo
pinMode(ledR,OUTPUT);                                 // Programado de salida del puerto donde se ubica el led rojo
Serial.println("Bienvenidos ");                       // Mensaje de bienvenida
pausa(100);                                           // Delay antes de aceptar numeros

}
void loop()
{
 if(Serial.available())                               // Si la comunicacion serial es utilizable, pregunta aqui.
 {
 pausa(500);                                          // Este delay debe ser modificado dependiendo de su equipo ya que como se indico arriba proteus no corre igual en todas la computadoras
 
 F=1;                                                 // Aqui usamos esta variable para indicar que se entro en el ciclo por lo que deja de parpadear el led amarillo
 String bufferString = "";                            // Variable usada para almacenar lo que recibe el puerto serial
 
 while (Serial.available()>0) {                       // Cosa que verifica que haya dados en el puerto
 bufferString += (char)Serial.read();                 // Almacenamiento de los caracteres recibidos por el puerto
 }

 num = bufferString.toInt();                          // Convercion de los caracteres a numeros
 Serial.println("------------------------");          // Mensaje diferenciador
 Serial.print("Ud digito: ");                         // Aviso de los numero que ingreso ya que en la pantalla no se ve
 Serial.println(num);                                 // Numero que ingresa
 Serial.println("------------------------");          // Mensaje diferenciador

 
 if(num==password)                                    // Bucle de verificacion de contraseña en este caso la contraseña es correcta
 {
 digitalWrite(ledV,HIGH);                             // Se activa el led verde
 digitalWrite(ledR,LOW);                              // Si el led rojo fue activado anteriormente se desactiva
 Serial.println("------------------------");          // Mensaje diferenciador
 Serial.println("Ud envio el codigo correcto ");      // Mensaje de verificacin de que el codigo recibido fue correcto
 Serial.println("------------------------");          // Mensaje diferenciador
 pausa(120000);                                         // Delay de encendido del led verde, debe er cambiado si en la simulacion el tiempo no corrsponde 
 digitalWrite(ledV,LOW);                              // Apagar el led verde ya que cumplio su funcion
 F=0;                                                 // Indicador de que ya puede volver a encerderse el amarillo
 }
 if(num!=password)                                    // Bucle de verificacion de contraseña en este caso la contraseña es incorrecta
 {
 digitalWrite(ledR,HIGH);                             // Se activa el led rojo
 digitalWrite(ledV,LOW);                              // Si el led verde fue activado anteriormente se desactiva
 Serial.println("------------------------");          // Mensaje diferenciador
 Serial.println("Ud envio un codigo erroneo ");       // Mensaje de verificacin de que el codigo recibido fue incorrecto
 Serial.println("------------------------");          // Mensaje diferenciador
 pausa(120000);                                         // Delay de encendido del led verde, debe er cambiado si en la simulacion el tiempo no corrsponde 
 digitalWrite(ledR,LOW);                              // Apagar el led rojo ya que cumplio su funcion
 F=0;                                                 // Indicador de que ya puede volver a encerderse el amarillo
 }
 
 }
else {                                                // Si no es usado el puerto serial se activa
  if(F==0){                                           // Verificacion de que no estan activo lo otre dos leds
 digitalWrite(ledA,HIGH);                             // Encendido del led amarillo intermitente
 pausa(60000);                                          // Encendido del led amarillo intermitente                                         
 digitalWrite(ledA,LOW);                              // Encendido del led amarillo intermitente
 pausa(60000); }                                        // Encendido del led amarillo intermitente
}
 } 

 
void pausa(unsigned int milisegundos)
{
  volatile unsigned long compara=0;
  volatile int contador =0;
  do
  {
    if (compara!=millis())
    {
      contador++;
      compara=millis();
    }
  }
  while(contador<=milisegundos);
  return;
}
