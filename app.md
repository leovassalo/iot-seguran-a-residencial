<p style="text-align: justify"> A aplicação foi desenvolvida na plataforma Web MIT App Inventor (https://appinventor.mit.edu/), e serve, essencialmente, como dashboard e interface visual para o sistema. Trata-se de um app de uso intuitivo e não apresenta funções de alta complexidade.
Na imagem abaixo, é possível verificar alguns recursos do app: informações sobre a planta, acionamento de luzes, ar condicionado, umidificador e travas inteligentes; detecção de temperaturas altas e vazamento de gás; monitoramento de temperatura e umidade locais.  <br />
<br />
  
<img src="https://user-images.githubusercontent.com/82290945/204058163-77a13a5b-f52c-48a5-87d6-11840edd986e.png" width="200"/>


A comunicação com o mundo externo é feita com base em MQTT e, portanto, existe sempre uma tentativa de conexão com o servidor público da HiveMQ (http://www.hivemq.com/demos/websocket-client/).
Para que se utilize o MQTT, é necessária a instalação de uma extensão apropriada (disponível em https://ullisroboterseite.de/android-AI2-PahoMQTT.html).

![image](https://user-images.githubusercontent.com/82290945/204057967-4bc92fe9-f2ab-4f0b-a546-9d04ff5e82ea.png)

A seção de recepção de mensagens é feita em duas partes: a inscrição nos tópicos adequados e as ações sobre cada tipo de mensagem. Abaixo, vê-se a inscrição nos diferentes tópicos trabalhados no sistema:

![image](https://user-images.githubusercontent.com/82290945/204058361-5998391c-3c00-40ae-8468-1b78c5bd5df9.png)

O laço de ação é mais longo, envolvendo alguns ifs e elses:

![image](https://user-images.githubusercontent.com/82290945/204058574-1ed5e760-b758-4bf3-98a0-52e64b4e0a8f.png)

![image](https://user-images.githubusercontent.com/82290945/204058576-62e8f09f-d24c-4711-a545-0da5f751a317.png)

![image](https://user-images.githubusercontent.com/82290945/204058578-abe07e6a-14f7-4fc2-a200-98c878c34533.png)

![image](https://user-images.githubusercontent.com/82290945/204058582-8229a57b-9e79-4329-b3d4-8a00e654316a.png)





Do ponto de vista da lógica de ação, a aplicação é extremamente rudimentar: existem apenas condicionais associadas a cada botão e a cada mensagem MQTT recebida


![image](https://user-images.githubusercontent.com/82290945/204058620-986d8052-dac7-46bd-9ac1-6d339f0f5979.png)

  </p>

<br />Com esses recursos, é possível replicar o setup da aplicação.
