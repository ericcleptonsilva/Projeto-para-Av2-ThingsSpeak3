# Projeto de prototipagem com um Sensor ultrassônico para ler distancia

Este exemplo mostra como prototipar com ThingSpeak usando uma placa esp32 conectada por Wi-Fi. Você lê e grava dados de canal com a Biblioteca de comunicação ThingSpeak. A leitura do limite é ajustável, e lido no ThingSpeak para criar um detector de proximidade. O hardware consiste em um NodeMCU Amica CP2102 com ESP8266 Esp12 com um sensor ultrassônico hc-sr04 e um LED indicador para mostrar quando um objeto está presente.
 A prototipagem de um projeto de sensor pode exigir reflashing de múltiplos códigos para ajustar os parâmetros de calibração, como os de um sensor de temperatura. Um ajuste de hardware adiciona complexidade, reduz a confiabilidade e pode ser difícil de alcançar quando seu projeto é implantado. Em vez disso, você pode ler os parâmetros de calibração do ThingSpeak e alterar os parâmetros em tempo real. Você pode melhorar a qualidade de suas medições ao ajustar um parâmetro de ajuste armazenado no ThingSpeak


<img align="left" src="https://s3.us-west-2.amazonaws.com/secure.notion-static.com/95f794fa-16f7-4ff4-b5ba-4736435b7c6b/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211126%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211126T125145Z&X-Amz-Expires=86400&X-Amz-Signature=c329c6a6bb1a1d2391afebfc473c39bd93d5956a3b918787845a707077f1030d&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22&x-id=GetObject"  widght="350"/>
<br>
<h6>Exemplo original do hardware</h6>



### Hardware Suportado

1. Arduino MKR1000
2. Arduino Uno, Mega, Due ou Leonardo com uma rede sem fio ou conexão Ethernet
3. NodeMCU ESP8266

O sensor de sensor ultrassônico funciona enviando um pulso de som e medindo o tempo que leva para o pulso retornar de um objeto. O sistema usa o limite de distância lido no ThingSpeak e compara o limite com a distância medida. O LED fica aceso quando o Objeto está presente.

você verá os dados de proximidade no canal de estatus