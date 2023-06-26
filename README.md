# Velocímetro com Sensor HC-SR04 e Arduino
Imagem do Velocímetro

Este projeto consiste em um **velocímetro simples** utilizando um sensor [ultrasonico](https://autocorerobotica.blog.br/aprenda-utilizar-o-sensor-de-distancia-ultrassonico-hc-sr04-com-arduino/) e uma placa [Arduino](https://blog.kalatec.com.br/arduino-o-que-e/#:~:text=A%20placa%20funciona%20atrav%C3%A9s%20de,e%20instalado%20em%20um%20computador.). <br>O sensor mede a distância entre ele e um objeto em movimento para calcular a velocidade aproximada. O resultado é exibido em um display, mostrando tanto a distância quanto a velocidade calculada.

Você pode fazer o download dos arquivos no codigo fonte deste repositorio.

# Circuito (Fritzing)
![circuito](https://github.com/carlosnet85/velocimetro-ultrasonico/assets/54481508/43a99a92-638d-4db3-8cea-64767baf8c6b)

# Explicação do codigo
A biblioteca **Wire** é utilizada para a comunicação I2C, enquanto a biblioteca **LiquidCrystal_I2C** é específica para displays LCD que utilizam comunicação I2C. Elas são incluídas no código para que possamos (no caso deste projeto) controlar o display LCD I2C.
```
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

<br>Aqui criamos o **objeto** lcd do tipo LiquidCrystal_I2C. No caso deste projeto, o endereço I2C do display LCD é 0x27, com 16 colunas e 2 linhas.
```
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

**Agora vamos definir os pinos digitais**
<br>Os pinos **trigPin** e **echoPin** são definidos como as conexões do sensor ultrassônico HC-SR04.
* O trig é usado para enviar o sinal de disparo ao sensor (ping).
* echo é usado para receber o sinal de retorno.
```
const int trigPin = 3;
const int echoPin = 4;
```

Os **leds** 1 e 2 serão usados para indicar diferentes estados do objeto em movimento.
```
const int led1 = 8;
const int led2 = 11;
```


<br>A variável **estado** é definida como um ponteiro para uma cadeia de caracteres (const char*) e será utilizada para armazenar o estado do objeto (parado, se mexendo ou se afastando).
```
const char* estado;
```

<br>A função **led()** é definida para controlar os dois LEDs. Ela possui um parâmetro valor que tem um valor padrão de 0.
```
void led(int valor = 0) {
  digitalWrite(led1, (valor == 1) ? HIGH : LOW);
  digitalWrite(led2, (valor == 2) ? HIGH : LOW);
}
```

<br>Dentro da função, utilizamos a função digitalWrite() para definir o estado dos LEDs com base no valor passado como argumento.
<br>O operador condicional ternário ```(valor == 1) ? HIGH : LOW``` é usado para determinar se o LED 1 deve ser ligado ou desligado. Se o valor for igual a 1, o LED 1 é definido como HIGH (ligado), caso contrário, é definido como LOW (desligado).
<br>Da mesma forma, o operador condicional ternário```(valor == 2) ? HIGH : LOW``` é usado para determinar o estado do LED 2.


**Também pode ser escrito assim:**
```
void led(int valor = 0) {
  if(valor == 1){
     digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
  } else if(valor == 2){
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
  }
}
```

<br> Aqui criamos uma função que controla o ultrassonico para assim medir a distancia
```\cpp
unsigned long calcularDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}
```

<br>```digitalWrite(trigPin, LOW); ``` Primeiro desativamos o pino trig para garantir que o pino esteja inicializado corretamente.
<br>```delayMicroseconds(2);``` Aguardamos um curto período de tempo de 2 microssegundos para estabilizar o pino antes de enviar o sinal de disparo.
<br>```digitalWrite(trigPin, HIGH);``` Depois ativamos o pino trig para enviar o sinal de disparo ao sensor.
<br>```delayMicroseconds(10);``` Mantém o pino trig ativo por 10 microssegundos para acionar o pulso ultrassônico.
<br>```digitalWrite(trigPin, LOW);``` Por fim desativamos o pino trig para finalizar o pulso ultrassônico.
<br>```return pulseIn(echoPin, HIGH) * 0.034 / 2;``` A função pulseIn() é utilizada para medir o tempo de resposta do pino echo (pingtime), que recebe o sinal de retorno do pulso ultrassônico refletido pelo objeto porque estamos interessados no tempo em que o pino echo permanece em estado HIGH. O valor retornado por pulseIn() é a duração desse tempo em microssegundos.

<br> Em seguida, esse valor é multiplicado por 0.034, que é o fator de conversão para converter a duração em microssegundos em distância em centímetros, com base na velocidade do som no ar (aproximadamente 343 metros por segundo). Por fim, o resultado (que é retornado pela função) é dividido por 2, porque o pulso ultrassônico percorre a distância de ida e volta. [Você pode ver isso aqui](https://www.researchgate.net/publication/362928227/figure/fig1/AS:11431281080984124@1661440740341/The-simplified-diagram-of-project-The-HC-SR04-ultrasonic-sensor-is-used-to-measure-the.jpg)

<br>Essa função permite medir a distância usando o sensor ultrassônico e os pulsos de disparo e retorno, fornecendo uma estimativa da distância entre o sensor e o objeto em movimento.

<br> Aqui criamos uma função que vai utilizar a função calcularVelocidade() para calcular a velocidade aproximada do objeto em movimento com base nas medições de distância.
```\cpp
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
```

<br>```float distanciaIni = calcularDistancia();```Chama a função calcularDistancia() para obter a distância inicial do objeto em movimento e armazena o valor na variável distanciaIni.
<br>```delay(500);``` Aguarda um período de 500 milissegundos para permitir a medição de uma segunda distância.
<br>```float distanciaFin = calcularDistancia();``` Chama novamente a função calcularDistancia() para obter a distância final do objeto após o atraso de 500 milissegundos e armazena o valor na variável distanciaFin.
<br>```float velocidade = (distanciaIni - distanciaFin) * 0.5;``` Calcula a velocidade aproximada subtraindo a distância final (distanciaFin) da distância inicial (distanciaIni) e multiplicando o resultado por 0.5 (por conta do delay de 500 milissegundos).
<br>```float velocidadePositiva = abs(velocidade);``` Calcula o valor absoluto da velocidade para garantir que seja sempre um valor positivo. A função abs() é usada para obter o valor absoluto.

```
if (distanciaIni == distanciaFin){
          led();
          estado = "Inerte";
          return velocidadePositiva;
}
``` 
Verifica se a distância inicial e a distância final são iguais. Se forem iguais, significa que o objeto está parado. Nesse caso, apaga os LEDs pela função led() sem argumentos, define o estado como "Inerte" (parado) e retorna a velocidade absoluta.

```
 else if (velocidade < 0) {
    led(2);
    estado = "Afast.";
    return velocidadePositiva;
  }
  ```
Verifica se a velocidade calculada é menor que zero (ou negativa). Se sim, significa que o objeto está se afastando. Nesse caso, acende os led2 chamando a função led(2), define o estado como "Afast." (afastando) e retorna a velocidade absoluta.
  
```
  led(1);
  estado = "Aprox.";
  return velocidadePositiva; 
```
Se nenhuma das condições anteriores for verdadeira, significa que o objeto está se aproximando. Portanto, acende os led1 chamando a função led(1), define o estado como "Aprox."(aproximando) e retorna a velocidade absoluta.

<br> Aqui definimos os pinos dos leds e do trig como OUTPUT, ou seja, estes pinos serão usados para enviar sinais de saída. já o pino echo será usado como pino de entrada de sinal. Também vamos inicializa o display LCD e ligar a luz de fundo dele. Esta função é usada para configurar o ambiente e inicializar as configurações iniciais antes do loop principal começar a ser executado. Executa apenas uma vez.
```
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
}
```

<br> Finalmente, vamos fazer todas as funções serem chamadas, que inclusive, as informações serão exibidas em um display LCD. É onde a lógica principal do programa é implementada e repetida até que o Arduino seja desligado.
```
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
```

<br>```lcd.setCursor();``` Essa função posiciona onde o texto deve aparecer na tela do display. O primeiro argumento é a coluna e o segundo a linha.
<br>```lcd.print();``` Essa função escreve o texto com base na função setCursor();
