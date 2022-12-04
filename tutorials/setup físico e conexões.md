Nesta seção, é possível conferir o setup físico associado aos diferentes dispositivos que compõem o sistema.
<br />
O ESP32, na condição de "dispositivo IoT" é o intermediário para duas funções do sistema: as luzes de conforto, associadas a seu led interno,
e as travas de segurança inteligentes, representadas por um relé conectado ao pino 23 do microcontrolador. Abaixo, é possível verificar a conexão do relé 
no pino adequado. Não se esqueça de utilizar os pinos GND e 3V3 para a alimentação do dispositivo.
<br /><br />
![image](https://user-images.githubusercontent.com/82290945/205467863-8f7d0ff8-4623-472e-ade3-366c0bc0ee88.png)

Em seguida, o Raspberry Pi 3 comporta todas as outras conexões: os dispositivos de IO (microfone/caixas de som, teclado/mouse/monitor) são conectados nas
entradas USB do microcomputador, enquanto o sensor DHT22 é conectado nos seguintes pinos do microcontrolador: 2 (entrada VCC),6 (ground) e 11 (saída de dados). Abaixo, é possível ver as conexões finais no dispositivo.
<br /><br />
![image](https://user-images.githubusercontent.com/82290945/205468058-a8d5f8b2-b056-415b-be2e-4e8803d75ace.png)
<br /><br />
<br /><br />

Além das conexões físicas é necessário o acionamento do software utilizado. Relacionado ao microcontrolador, a programação já está salva e disponível para uso no próprio dispositivo, se fazendo necessária apenas a instalação no lugar mais conveniente para os dispositivos periféricos: lâmpada, sensores e travas; Quanto o Raspberry necessita apenas do acionamento do software Node-Red (através do comando "Node-Red start" direto no cmd do mesmo), que então estará além de conectado na rede WiFi local (previamente configurada para ambos Raspiberry e ESP32) estará também usando a porta local 1883 para seu completo funcionamento. Enquanto permanecer ligado nenhuma interação com o software em si se faz necessária, já que o próprio assistente consegue se retro acionar.
