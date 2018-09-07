# Rotador

Implementacion en Arduino del código para controlar activamente un rotador.

# Error de inicialización

Para poder bajar los codigos a la placa en Linux (en caso de que tire error al
intentar hacerlo: can't open device ... ) hay que correr las siguientes lineas
por linea de comandos:

sudo usermod -a -G dialout $USER
sudo chmod a+rw /dev/ttyUSB0

Luego se pueden bajar los códigos.

# Conexiones stepper motor

El motor que usamos es el 28byj-48

El stepper motor se inicializa/configura/controla con las lineas iniciales
de los codigos:

#include <Stepper.h> --> libreria
const int stepsPerRevolution = 2048; --> de la datasheet
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); --> configuracion de conexion

Las conexiones de la placa del motor se hacen de la siguiente forma:
IN1 -> 8
IN2 -> 10
IN3 -> 9
IN4 -> 11

Tal vez podrian conectarse IN2 e IN3 al reves cambiando la linea de configuracion?

# Velocidad del motor

Puede configurarse la velocidad de rotacion del motor:
myStepper.setSpeed(15); --> velocidad de rotacion en RPM

Probando encontramos que hasta 15 anda bien, con 20 ya no funciona. No encontramos
en la datasheet el valor exacto del limite.
En caso de no especificar el valor, cuando se le dice cuantos pasos moverse
lo hace a la velocidad maxima?

El motor puede girar para ambos lados. Para que gire se le da la instruccion:
myStepper.step(n);

n es la cantidad de pasos y su signo determina el sentido de giro.

# Sensor ultrasonico

El sensor mide el tiempo entre la emision de un pulso ultrasonico (trigger) y la 
deteccion (echo). Para emitir se le manda un pulso de 10us al pin trigger.
Luego se mide la duracion del pulso en echo y esto es proporcional a la distancia.

# Sensor de obstaculos

El sensor detecta si hay un obstaculo dentro de un rango determinado
El rango de deteccion puede controlarse con un potenciometro que ya 
viene incorporado.
