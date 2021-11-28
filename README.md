# Projeto de prototipagem com um Sensor ultrassônico para ler distancia

>Este exemplo mostra como prototipar com ThingSpeak usando uma placa esp32 conectada por Wi-Fi. Você lê e grava dados de canal com a Biblioteca de comunicação ThingSpeak. A leitura do limite é ajustável, e lido no ThingSpeak para criar um detector de proximidade. O hardware consiste em um NodeMCU Amica CP2102 com ESP8266 Esp12 com um sensor ultrassônico hc-sr04 e um LED indicador para mostrar quando um objeto está presente. 
>A prototipagem de um projeto de sensor pode exigir reflashing de múltiplos códigos para ajustar os parâmetros de calibração, como os de um sensor de temperatura. Um ajuste de hardware adiciona complexidade, reduz a confiabilidade e pode ser difícil de alcançar quando seu projeto é implantado. Em vez disso, você pode ler os parâmetros de calibração do ThingSpeak e alterar os parâmetros em tempo real. Você pode melhorar a qualidade de suas medições ao ajustar um parâmetro de ajuste armazenado no ThingSpeak.

![Exemplo original do hardware](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/95f794fa-16f7-4ff4-b5ba-4736435b7c6b/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T194350Z&X-Amz-Expires=86400&X-Amz-Signature=c79f6ac450bc1a32cddd41d10b04af87ef7f95b86197494d568deaf06b08872c&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22&x-id=GetObject)
Exemplo original do hardware

### Hardware Suportado

* Arduino MKR1000
* Arduino Uno, Mega, Due ou Leonardo com uma rede sem fio ou conexão Ethernet
* NodeMCU ESP8266

>O sensor de sensor ultrassônico funciona enviando um pulso de som e medindo o tempo que leva para o pulso retornar de um objeto. O sistema usa o limite de distância lido no ThingSpeak e compara o limite com a distância medida. O LED fica aceso quando o Objeto está presente.

#### você verá os dados de proximidade no canal de status.
* O limite é definido para 15 cm
*  Dez medições são feitas para cada média
*  O sinalizador de leitura é definido para forçar a leitura dos parâmetros de calibração
*  O sinalizador de leitura é definido para forçar a leitura dos parâmetros de calibração

![Exemplo original em tempo real](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/1aa1f073-20d8-4b12-b491-c08f95b39869/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T194109Z&X-Amz-Expires=86400&X-Amz-Signature=223099cfe70c619cd40de9994da9a6ea029fad13045c3f9163eded154396874c&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22&x-id=GetObject)
Exemplo original em tempo real

### Hardware Utilizado
* NodeMCU Amica CP2102 com ESP8266 Esp12E 
* Sensor de sonar HC-SR04
* Fios de ligação (pelo menos 9)
* LED
* Resistência pequena (200 Ω - 1 kΩ)
* cabo USB

1. >Crie um canal ThingSpeak, conforme mostrado em Coletar dados em um novo canal . Armazene os dados no primeiro campo e armazene as configurações do dispositivo em campos sucessivos. As configurações do dispositivo incluem o limite de distância, número de medições para calcular a média e um sinalizador para controlar se o dispositivo atualiza as configurações em cada loop.
2. >Ative os campos 1, 2, 3 e 4 na visualização Configurações do canal . Para distinguir entre os campos, forneça um nome descritivo para cada campo. Esta imagem mostra um único canal configurado para coletar dados no primeiro campo e armazenar os parâmetros de calibração nos campos 2, 3 e 4.

![No começo de tudo](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/1e298c3a-6845-4e5b-bfc1-b53ace02a06b/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T194644Z&X-Amz-Expires=86400&X-Amz-Signature=d54728961befee4ee5a46e5787320861cc72ea87a0579e6455eb94e41e5fc137&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22&x-id=GetObject)
No começo de tudo

3. >Observe as chaves API de leitura e gravação apropriadas na guia Chaves API na visualização Configurações do canal (circulada na imagem).
4. >Preencha seus campos de calibração usando uma janela do navegador. Você pode copiar o texto da guia Chaves de API ou modificar este texto com sua chave de API de gravação. Insira cada URL diretamente na barra de endereço de seu navegador, alterando SUA CHAVE DE API DE ESCRITA (YOUR-WRITING-API-KEY) para a chave de API de gravação para seu canal.

###### Defina o limite para detectar um objeto (10 cm é um bom ponto de partida)

```html 
Defina umm Limite
https://api.thingspeak.com/update?api_key=YOUR-WRITING-API-KEYfield2=10
``` 
###### Defina o número de medições para a média:
```html 
Média
https://api.thingspeak.com/update?api_key=YOUR-WRITING-API-KEYfield3=100
```
###### Defina o sinalizador de controle para que o dispositivo verifique se há novas configurações periodicamente
```html 
Média
Update de novas configurações
https://api.thingspeak.com/update?api_key=YOUR-WRITING-API-KEY&field4=1
```
>O navegador retorna o número de entradas no canal. Se você acabou de criar o canal, verá 1, 2 e 3 ao preencher os três campos de calibração obrigatórios.

### Esquemático da conexões

1. **NodeMCU** Amica **CP2102** com ESP8266 **Esp12E**

2. Conecte o **GND** do sensor ao **GND** do **NodeMCU**.

3. Conecte o pino **Trig** ao pino **D5** do **NodeMCU** .

4. Conecte o pino **Echo** ao pino **D6** do **NodeMCU** .

5. Conecte um **resistor 200Ω** ao pino **D2** do **NodeMCU** e conecte o **resistor** a um **LED** indicador. Conecte o **ânodo** do **LED** ao **GND**.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/123909bc-879b-426c-933f-8af26551706e/Sensor_de_Aproximiadade.jpg?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T195502Z&X-Amz-Expires=86400&X-Amz-Signature=8d21c55a537b0755f048c6ffdc0356950740caca307672a9321886e862bb5f1d&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Sensor%2520de%2520Aproximiadade.jpg%22&x-id=GetObject)

### Programe Seu Arduino

1. Baixe o IDE do Arduino mais recente.

2. Adicione a [Biblioteca ThingSpeak para Arduino e ESP8266](https://github.com/mathworks/thingspeak-arduino) ao gerenciador de biblioteca. Escolha `Sketch`> `Include Library`> `Manage Libraries`. Selecione `ThingSpeak`para adicioná-lo ao seu esboço.

3. Adicione a `ESP8266WiFi`biblioteca no gerenciador de biblioteca.  Escolha `Sketch`> `Include Library`> `Manage Libraries`. Selecione `ESP8266WiFi`biblioteca para adicioná-lo ao seu esboço.

4. Crie o aplicativo. Abra uma nova janela no IDE do Arduino e salve o arquivo. Adicione o código fornecido na seção Código. Certifique-se de editar as informações da rede sem fio, o ID do canal e as chaves API.

5. Depois de carregar seu programa com sucesso, você pode monitorar a saída usando o monitor serial. Se um objeto estiver presente a uma distância mais próxima do limite definido, seu dispositivo posta a distância para o seu canal. Experimente fazer experiências com o número de medições para calcular a média e veja como as flutuações medidas mudam. Depois de definir os parâmetros, você pode alterar o valor do sinalizador de leitura de `1`para `0`. Uma vez que seu dispositivo lê este sinalizador como 0, ele para de verificar os parâmetros do ThingSpeak, economizando energia e largura de banda.

```C+
#include <ThingSpeak.h>// always include thingspeak header file after other header files and custom macros
#include <ESP8266WiFi.h>

#define triggerPin D5
#define echoPin D6
#define LEDpin D2

#define WIFI_SSID "WiFi network name"    // replace MySSID with your WiFi network name
#define WIFI_PASSWORD "WiFi password"  // replace MyPassword with your WiFi password


char ssid[] = WIFI_SSID;   // your network SSID (name)
char pass[] = WIFI_PASSWORD;   // your network password


WiFiClient  client;


char* writeAPIKey = "YOUR-WRITING-API-KEY";
char* readAPIKey = "YOUR-READING-API-KEY";
const long channelID = 0000000;   // replace 0000000 with your channel number
const unsigned int firstReadFieldNumber = 2;
const unsigned int secondReadFieldNumber = 3;
const unsigned int switchField = 4; // Field number (1-8) to use to change status of device.  Determines if data is read from ThingSpeak.

// Other constants
const unsigned long postingInterval = 60L * 1000L;   // Post data every 60 seconds

// Global variables
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;
float distanceThreshold = 0;
bool getInfo = 0;  // Set this to zero if you don’t want to read data from ThingSpeak anymore (i.e. calibration complete)
int points = 7;




int writeTSData(long TSChannel, unsigned int TSField, float data, char* ReadAPIKey) {
  int  writeSuccess = ThingSpeak.writeField(TSChannel, TSField, data, writeAPIKey); //write the data to the channel
  return writeSuccess;
}

// Use this function if you want multiple fields simultaneously.
/*
  int writeTDData(long TSChannel,unsigned int TSField1,float data1,unsigned int TSField2,data2,char* ReadAPIKey){
  ThingSpeak.setField(TSField1,data1);
  ThingSpeak.setField(TSField1,data2);

  writeSuccess = ThingSpeak.writeFields(TSChannel, writeAPIKey);
  return writeSuccess;
  }
*/

float readTSData(long TSChannel, unsigned int TSField, char* ReadAPIKey) {

  float data = 0;

  data = ThingSpeak.readFloatField(TSChannel, TSField, ReadAPIKey);
  Serial.println(" Data read from ThingSpeak " + String(data));
  return data;
}

float getDistance(int tPin, int ePin) {

  long duration, distance;

  digitalWrite(tPin, LOW);  // Reinicialize o pino do gatilho.
  delayMicroseconds(2);
  digitalWrite(tPin, HIGH);  // Inicie uma medição.
  delayMicroseconds(10); //
  digitalWrite(tPin, LOW);   // Complete o pulso.
  duration = pulseIn(ePin, HIGH);  // Espere por um pulso de reflexão.
  distance = (duration/2) / 29.1;     // Calcule a distância apropriada usando a velocidade estimada do som..

  // Esta seção é útil ao depurar o sensor.
  /*
    if (distance >= 200 || distance <= 0){
      Serial.println("Out of range");
    }
    else {
     Serial.print(distance);
     Serial.println(" cm");
    }
  */
  return distance;
}
void setup()
{
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(LEDpin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Start");
  Serial.print("Connect Wifi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  Serial.println("Connected");
  ThingSpeak.begin(client);
  configTime(0, 0, "south-america.pool.ntp.org");

  WiFi.disconnect();
  delay(100);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".\n");
    delay(500);
  }

  Serial.print("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Check NTP/Time, usually it is instantaneous and you can delete the code below.
  Serial.print("Retrieving time: ");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".\n");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
  
  //  os Gets iniciais dos parâmetros  da ThingSpeak.
  distanceThreshold = readTSData(channelID,firstReadFieldNumber,readAPIKey);
  points = readTSData(channelID,secondReadFieldNumber,readAPIKey);




}

void loop() {
  float distance = 0;  
      for (uint16_t loops = 0; loops < points; loops++){
	      distance += getDistance(triggerPin,echoPin);  //faz uma medição, armazene a soma de todas as medições
      delay(5);  
     }  

  distance = distance / points;

  if (distance < distanceThreshold) {
    digitalWrite(LEDpin, HIGH);
  }

  else {
    digitalWrite(LEDpin, LOW);
  }


  Serial.println("Media: " + String(distance) + " cm");

  if (millis() - lastUpdateTime >=  postingInterval) {
    lastUpdateTime = millis();
    if (!(getInfo == 0)) {
      distanceThreshold = readTSData(channelID, firstReadFieldNumber, readAPIKey);
      points = readTSData(channelID, secondReadFieldNumber, readAPIKey);
      getInfo = (bool)readTSData(channelID, switchField, readAPIKey);
    }
    if (distance < distanceThreshold) {
      writeTSData(channelID, 1, distance, writeAPIKey);
    }

  }
  delay(500);    // Provide some delay between measurements.

}
```
### Resultado Final
> Image do site

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/934ff9c0-d87d-46fa-818e-7a93dd8ed98b/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T195802Z&X-Amz-Expires=86400&X-Amz-Signature=4c460b1488d8551732145ab8d4668d128b34e6e459116e08d92a2f6166ddae16&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22&x-id=GetObject)

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/a8501342-a323-46e3-8956-af050a9cd021/VID_20211105_2350512.mp4?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T195831Z&X-Amz-Expires=86400&X-Amz-Signature=97d2f1a4e4aa70c751ad24a324aeb06aececb602bebfc633d306f35e1bd10fae&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22VID_20211105_235051~2.mp4%22&x-id=GetObject)

<!-- blank line -->
<figure class="video_container">
  <iframe src="https://s3.us-west-2.amazonaws.com/secure.notion-static.com/a8501342-a323-46e3-8956-af050a9cd021/VID_20211105_2350512.mp4?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20211128%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211128T195831Z&X-Amz-Expires=86400&X-Amz-Signature=97d2f1a4e4aa70c751ad24a324aeb06aececb602bebfc633d306f35e1bd10fae&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22VID_20211105_235051~2.mp4%22&x-id=GetObject" frameborder="0" allowfullscreen="true"> </iframe>
</figure>
<!-- blank line -->