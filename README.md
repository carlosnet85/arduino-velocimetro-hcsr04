# Velocímetro usando o HC-SR04

Projeto simples que usa o sensor ultrassônico HC-SR04 para medir a velocidade média de um objeto que se aproxima/afasta do sensor (existem sensores dedicados para isso, mas eu fiz com o ultrassônico por didática).

A distância entre o sensor ultrassônico e o objeto é obtida medindo o tempo que leva para um pulso ultrassônico viajar até o objeto e retornar (trigger e echo). A velocidade média do objeto é calculada pela diferença na distância medida em dois intervalos de tempo distintos.

Um arduino vai ser utilizado para fazer a tarefa pesada, que seria fazer todos esse trabalho.

## Componentes utilizados
| Componente           |   Função 
| -------------------- | --------------
| Arduino Uno          | Atuar como o cérebro do projeto
| HC-SR04              | Medir distância usando o som
| Display LCD i2c      | Mostrar informações 
| Led                  | Servir como referência de uso do ultrassônico
| Resistor de 220 ohms | Para limitar a corrente no led

## Foto física e Circuito
![foto_fisica](https://github.com/carlosnet85/velocimetro-ultrasonico/assets/54481508/c41de9e1-d1aa-41e1-9ba5-01f6356da25c)
![circuito](https://github.com/carlosnet85/velocimetro-ultrasonico/assets/54481508/1aff3de0-55b5-4ea9-8c07-b6b117de5656)

