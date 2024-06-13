# Velocímetro usando o HC-SR04 

Projeto simples que usa o sensor ultrassônico [HC-SR04](https://www.makerhero.com/produto/sensor-de-distancia-ultrassonico-hc-sr04/#:~:text=Como%20funciona%20o%20Sensor%20Ultrass%C3%B4nico,Echo%20permanecer%20em%20n%C3%ADvel%20alto.) para medir a velocidade média de um objeto que se aproxima/afasta do sensor ([existem sensores dedicados](https://www.robocore.net/sensor-robo/modulo-gps-gy-neo6mv2-com-antena) para isso, mas eu fiz com o ultrassônico por didática). 

A distância entre o sensor ultrassônico e o objeto é obtida medindo o tempo que leva para um pulso ultrassônico viajar até o objeto e retornar (trigger e echo). A velocidade média do objeto é calculada pela diferença na distância medida em dois intervalos de tempo distintos. 

Um [Arduino](https://pt.m.wikipedia.org/wiki/Arduino) vai ser utilizado para fazer a tarefa pesada. Usei dois métodos pra calcular a velocidade média: 

1. **Um único sensor:** Vai funcionar igual [um sensor de ré](https://seminovos.unidas.com.br/blog/sensor-de-re/#:~:text=O%20funcionamento%20do%20sensor%20de,emite%20alertas%20sonoros%20e%20visuais.). A velocidade média do objeto é calculada pela diferença nas distâncias medidas em dois intervalos de tempo distintos. 

2. **Dois sensores**: Vai funcionar como uma espécie de [radar doppler](https://pt.m.wikipedia.org/wiki/Radar_Doppler). Dois sensores são colocados a uma distância fixa um do outro. A velocidade do objeto é calculada pelo tempo que ele leva para se mover de um sensor para o outro. 

## Componentes utilizados
| Componente           |   Função 
| -------------------- | --------------
| Arduino (Uno, nano, etc)          | Atuar como o cérebro do projeto
| HC-SR04              | Medir distância usando o som
| Display LCD I2C      | Mostrar informações 
| Leds                  | Opicional, vai servir como referência de uso do ultrassônico
| Resistor de 220 ohms | Para limitar a corrente no led 
| Protoboard | Só pra deixar as coisas mais simples...
| Alguns jumpers | Conexão 

## Foto física e Circuito 

**Um sensor**
![foto_fisica](https://github.com/carlosnet85/velocimetro-ultrasonico/assets/54481508/c41de9e1-d1aa-41e1-9ba5-01f6356da25c) 

![circuito](https://github.com/carlosnet85/velocimetro-ultrasonico/assets/54481508/1aff3de0-55b5-4ea9-8c07-b6b117de5656)

**Dois sensores**
![20240613_151159](https://github.com/carlosnet85/arduino-velocimetro-hcsr04/assets/54481508/d869f09c-65c1-4aa6-b68d-d0e31edce7dc)
![2024-06-13-152313_1920x1080_scrot](https://github.com/carlosnet85/arduino-velocimetro-hcsr04/assets/54481508/acd4868d-1ecf-435e-9c88-15a9481c4333)

