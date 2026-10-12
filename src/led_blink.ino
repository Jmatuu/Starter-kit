// Dos motores con puente H hecho con relés (2 relés por motor)
//
//   Motor 1: R1 (GPIO 25) + R2 (GPIO 26)
//   Motor 2: R3 (GPIO 27) + R4 (GPIO 14)
//
// Cada relé tiene NC -> GND, NO -> V+ y COM -> un terminal del motor (LED en la simulación).
//   R_a ON  / R_b OFF  = adelante
//   R_a OFF / R_b ON   = atrás
//   ambos OFF          = parado (los dos terminales a GND)
// Nunca se activan los dos relés de un mismo motor a la vez.

const int R1 = 25, R2 = 26;   // motor 1
const int R3 = 27, R4 = 14;   // motor 2

const bool ACTIVO_ALTO = true;  // pon false si tu módulo de relé se activa con LOW
const int PAUSA = 100;          // ms con todo apagado antes de cambiar de sentido

int estado1 = 0, estado2 = 0;   // último sentido de cada motor

void rele(int pin, bool encendido) {
  digitalWrite(pin, (encendido == ACTIVO_ALTO) ? HIGH : LOW);
}

// d1, d2: 1 = adelante, -1 = atrás, 0 = parar
void mover(int d1, int d2) {
  if (d1 == estado1 && d2 == estado2) return;   // nada que cambiar

  // 1) apagar los 4 relés (parada) y esperar
  rele(R1, false); rele(R2, false);
  rele(R3, false); rele(R4, false);
  delay(PAUSA);

  // 2) aplicar el nuevo sentido a los dos motores a la vez
  rele(R1, d1 == 1);  rele(R2, d1 == -1);
  rele(R3, d2 == 1);  rele(R4, d2 == -1);

  estado1 = d1;
  estado2 = d2;
}

void adelante()        { mover( 1,  1); }
void atras()           { mover(-1, -1); }
void derecha()         { mover( 1,  0); }   // gira a la derecha: motor 1 avanza, motor 2 parado
void izquierda()       { mover( 0,  1); }   // gira a la izquierda: motor 2 avanza, motor 1 parado
void giroDerecha()     { mover( 1, -1); }   // gira sobre su eje
void giroIzquierda()   { mover(-1,  1); }   // gira sobre su eje
void parar()           { mover( 0,  0); }

void setup() {
  Serial.begin(115200);
  int pines[] = {R1, R2, R3, R4};
  for (int p : pines) {
    pinMode(p, OUTPUT);
    rele(p, false);
  }
}

void loop() {
  Serial.println("Adelante");   adelante();  delay(2000);
  parar();                                   delay(1000);
  Serial.println("Atras");      atras();     delay(2000);
  parar();                                   delay(1000);
  Serial.println("Derecha");    derecha();   delay(2000);
  parar();                                   delay(1000);
  Serial.println("Izquierda");  izquierda(); delay(2000);
  parar();                                   delay(1000);
}
