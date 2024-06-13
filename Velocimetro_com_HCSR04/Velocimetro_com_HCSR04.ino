#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // inicializa o LCD com endereço I2C 0x27 e define o LCD como 16 colunas e 2 linhas

const int trigPin = 3; // pino do trigger (o que dispra o pulso de som) do ultrassonico
const int echoPin = 2; // pino do echo (o que recebe o pulso de refletido) do ultrassonico
const int led = 8;     // define o pino do LED

const char* estado;    // variavel que armazena o estado do movimento
float intervalo = 500; // intervalo de tempo entre as leituras do sensor (em milissegundos)

// funcao que mede a distancia com base nos pulsos do ultrassonico
unsigned long lerUltrasonico(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);  // intervalo para o proximo pulso
  delayMicroseconds(2);        
  digitalWrite(trigPin, HIGH); // pulsa
  delayMicroseconds(10);       
  digitalWrite(trigPin, LOW);  // para o pulso
  
  // calcula a distancia com base no tempo entre o pulso do som pelo trigger e a chegada dele, por reflecao, no pino echo
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

// funcao que calcula a velocidade media
float calcularVelocidade(long distInicial, long distFinal, float intervalo) {
  float velocidade = (distFinal - distInicial) / intervalo;

  if (distInicial == distFinal) {
    estado = "Inerte"; // se a distancia inicial e a final forem iguais, o objeto esta parado
  } else if (velocidade > 0) {
    estado = "Afast."; // se a velocidade for positiva, o objeto está se afastando
  } else {
    estado = "Aprox."; // se a velocidade for negativa, o objeto está se aproximando
  }

  // retorna o valor absoluto da velocidade (basicamente, o valor sempre vai ser retornado positivo, independetemente se na variavel esta negativo)
  return abs(velocidade);
}

void setup() {
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 

  lcd.init();              // ativa o display LCD
  lcd.backlight();         // liga a luz de fundo do display LCD
}

void loop() {
  // le a distancia medida pelo sensor ultrassônico
  unsigned long distInicial = lerUltrasonico(trigPin, echoPin);
  delay(intervalo); // aguarda antes de fazer a proxima medicao
 // le novamente a distancia medida pelo sensor ultrassônico
  unsigned long distFinal = lerUltrasonico(trigPin, echoPin);

  // registra a distancia inicial (a distancia entre o objeto e o ultrassonico) no display LCD
  lcd.setCursor(0, 0);
  lcd.print(distInicial);
  lcd.print(" CM     ");

  // calcula a velocidade com base nas distancias obtidas, e transforma o intervalo em segundos, pois a distancia esta em cm por segundo
  float velocidade = calcularVelocidade(distInicial, distFinal, (intervalo / 1000.0));

  // acende o LED se o objeto esta em movimento
  (velocidade > 0) ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);

  // registra o estado no display LCD
  lcd.setCursor(10, 0);
  lcd.print(estado);

  // registra a velocidade calculada (pode nao ser 100% preciso!)
  lcd.setCursor(0, 1);
  lcd.print(velocidade);
  lcd.print(" CM/S           "); 
}
