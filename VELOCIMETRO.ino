#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 3;
const int echoPin = 4;
const int led1 = 8;
const int led2 = 11;
const char* estado;

void led(int valor = 0) {
  if (valor == 1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else if (valor == 2) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
}

unsigned long calcularDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

float calcularVelocidade() {
  float distanciaIni = calcularDistancia();
  delay(500);
  float distanciaFin = calcularDistancia();

  float velocidade = (distanciaIni - distanciaFin) * 0.5;
  float velocidadePositiva = abs(velocidade);

  if (distanciaIni == distanciaFin) {
    led();
    estado = "Inerte";
    return velocidadePositiva;
  } else if (velocidade < 0) {
    led(2);
    estado = "Afast.";
    return velocidadePositiva;
  }
  led(1);
  estado = "Aprox.";
  return velocidadePositiva;
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(calcularDistancia());
  lcd.print(" CM     ");

  lcd.setCursor(10, 0);
  lcd.print(estado);

  lcd.setCursor(0, 1);
  lcd.print(calcularVelocidade());
  lcd.print(" CM/S           ");
}