Nesta seção, é possível conferir o setup físico associado aos diferentes dispositivos que compõem o sistema.
<br />
O ESP32, na condição de "dispositivo IoT" é o intermediário para duas funções do sistema: as luzes de conforto, associadas a seu led interno,
e as travas de segurança inteligentes, representadas por um relé conectado ao pino 23 do microcontrolador. Abaixo, é possível verificar a conexão do relé 
no pino adequado. Não se esqueça de utilizar os pinos GND e 3V3 para a alimentação do dispositivo.
<br /><br />
![image](https://user-images.githubusercontent.com/82290945/205467863-8f7d0ff8-4623-472e-ade3-366c0bc0ee88.png)

Em seguida, o Raspberry Pi 3 comporta todas as outras conexões: os dispositivos de IO (microfone/caixas de som, teclado/mouse/monitor) são conectados nas
entradas USB do microcomputador, enquanto o sensor DHT22 é conectado nos pinos (AJUDA). Abaixo, é possível ver as conexões finais no dispositivo
<br /><br />
![image](https://user-images.githubusercontent.com/82290945/205468058-a8d5f8b2-b056-415b-be2e-4e8803d75ace.png)
<br /><br />
<br /><br />
