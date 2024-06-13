#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // inicializa o lcd com endereco i2c 0x27 e define o lcd como 16 colunas e 2 linhas

const int trigPin1 = 3; // pino do trigger (o que dispara o pulso de som) do ultrassonico 1
const int echoPin1 = 2; // pino do echo (o que recebe o pulso refletido) do ultrassonico 1
const int led1 = 8;     // led de referencia do ultrassonico 1

const int trigPin2 = 5; // pino do trigger (o que dispara o pulso de som) do ultrassonico 2
const int echoPin2 = 4; // pino do echo (o que recebe o pulso refletido) do ultrassonico 2
const int led2 = 7;     // led de referencia do ultrassonico 2

const float distanciaEntreSensores = 3.0; // distancia fixa entre os sensores em cm
const float distanciaMinima = 25.0;       // distancia minima para considerar a deteccao de movimento

// funcao que mede a distancia com base nos pulsos do ultrassonico
unsigned long lerUltrasonico(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);  // intervalo para o proximo pulso
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // pulsa
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  // para o pulso

  // calcula a distancia com base no tempo entre o pulso do som pelo trigger e a chegada dele, por reflexao, no pino echo
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void setup() {
  pinMode(led1, OUTPUT);    // define o pino do led1 como saida
  pinMode(led2, OUTPUT);    // define o pino do led2 como saida
  pinMode(trigPin1, OUTPUT); // define o pino do trigger do sensor 1 como saida
  pinMode(echoPin1, INPUT);  // define o pino do echo do sensor 1 como entrada
  pinMode(trigPin2, OUTPUT); // define o pino do trigger do sensor 2 como saida
  pinMode(echoPin2, INPUT);  // define o pino do echo do sensor 2 como entrada

  lcd.init();              // ativa o display lcd
  lcd.backlight();         // liga a luz de fundo do display lcd
}

void loop() {
  unsigned long tempoInicio, tempoFim;  // variaveis para armazenar o tempo de inicio e fim do objeto passando de um sensor ao outro
  float velocidade;                     // variavel para armazenar a velocidade calculada

  // mensagem que aparece se nada passou na frente dos sensores
  lcd.setCursor(0, 0);
  lcd.print("Esperando...");
  lcd.setCursor(0, 1);
  lcd.print("0 CM/S          ");

  /* 
   *  verifica se o objeto esta acionando os dois sensores ao mesmo tempo
   *  pode dar falso-positivo se a distancia entre os sensores for muito curta ou o objeto for maior que a distancia entre os sensores 
   */
  while (lerUltrasonico(trigPin1, echoPin1) < distanciaMinima && (lerUltrasonico(trigPin2, echoPin2) < distanciaMinima)) {
    lcd.setCursor(0, 0);
    lcd.print("Objeto parado");

    delay(5000);

    lcd.clear();
    return; // sai da funcao pre-maturamente
  }
  
  /*
     verifica se o objeto passa do sensor 1 para o sensor 2
     apenas se a leitura do sensor for menor que a distancia minima
  */
  if (lerUltrasonico(trigPin1, echoPin1) < distanciaMinima) {
    digitalWrite(led1, HIGH); // acende o led do sensor 1
    tempoInicio = millis();   // registra o tempo de inicio

    lcd.setCursor(0, 0);
    lcd.print("Sentido 1-?  ");

    // aguarda o objeto passar pelo sensor 2
    while (lerUltrasonico(trigPin2, echoPin2) >= distanciaMinima) {
      delay(10);
    }

    digitalWrite(led2, HIGH); // acende o led do sensor 2
    tempoFim = millis();      // registra o tempo de fim

    float tempoTotal = (tempoFim - tempoInicio) / 1000.0; // calcula o tempo total em segundos
    velocidade = distanciaEntreSensores / tempoTotal;     // calcula a velocidade

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sentido 1-2:"); // exibe a direcao no display lcd
    lcd.setCursor(0, 1);
    lcd.print(velocidade);      // exibe a velocidade no display lcd
    lcd.print(" CM/S");

    delay(5000);
    digitalWrite(led1, LOW);    // apaga o led do sensor 1
    digitalWrite(led2, LOW);    // apaga o led do sensor 2
  }

  // verifica se o objeto passa do sensor 2 para o sensor 1
  if (lerUltrasonico(trigPin2, echoPin2) < distanciaMinima) {
    digitalWrite(led2, HIGH); // acende o led do sensor 2
    tempoInicio = millis();   // registra o tempo de inicio

    lcd.setCursor(0, 0);
    lcd.print("Sentido 2-?  ");

    // aguarda o objeto passar pelo sensor 1
    while (lerUltrasonico(trigPin1, echoPin1) >= distanciaMinima) {
      delay(10);
    }

    digitalWrite(led1, HIGH); // acende o led do sensor 1
    tempoFim = millis();      // registra o tempo de fim

    float tempoTotal = (tempoFim - tempoInicio) / 1000.0; // calcula o tempo total em segundos
    velocidade = distanciaEntreSensores / tempoTotal;     // calcula a velocidade

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sentido 2-1:"); // exibe a direcao no display lcd
    lcd.setCursor(0, 1);
    lcd.print(velocidade);      // exibe a velocidade no display lcd
    lcd.print(" CM/S");

    delay(5000);
    digitalWrite(led1, LOW);    // apaga o led do sensor 1
    digitalWrite(led2, LOW);    // apaga o led do sensor 2
  }
}
