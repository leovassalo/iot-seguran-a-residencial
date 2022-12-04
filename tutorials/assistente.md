Comandos disponíveis:
Ao se iniciar o sistema (vide tutoriais->setup físico), o microfone fica em espera da wake-word "Jarvis". Ao entendê-la com sucesso, a assistente responderá
uma frase de confirmação. Logo após tal interação, é possível dizer o que se deseja com o seguinte formato: acesso-ação, um par de palavras ditas idealmente
em sequência, onde as palavras de acesso:
* "Qual a":
    Para esse acesso temos as opções "Temperatura" e "Umidade", que retornam a leitura atual do DHT, respectivo ao que foi solicitado, devolvendo então ao
    usuário o valor lido.
* "Luzes":
    Aqui, "Acender" e "Desligar" mandam um sinal mqtt de ON ou OFF, respectivamente, que ativa o led interno localizado na placa ESP.
* e "Trava":
    Do qual é possível requisitar "Trancar", "Destrancar" e "Estado". Os dois primeiros o executam na trava localizada no ESP,
    enquanto o último lê o estado atual da mesma.
* Demais:
    O Jarvis responde - no caso de nenhuma das duplas de intenção ser detectada por ele - que necessita de que o usuário repita o comando.
    
Exemplo de uso ("U" corresponde a "usuário" e "J" ao assistente Jarvis): <br />
U: Jarvis! <br />
J: Já pode falar <br />
U: Diga a temperatura!
J: Desculpa, não entendi
U: Jarvis!
J: Ja pode falar
U: Qual a temperatura?
J: A temperatura é 25.50 graus
U: Jarvis!
J: Já pode falar
U: Acender luzes
* led nativo do ESP32 são acionado por MQTT *
U: Desligar
U: Jarvis!
J: Já pode falar
U: Desligar
J: Desculpa, não entendi
U: Jarvis!
J: Ja pode falar
U: Desligar luzes
* led interno do ESP32 é desligado por MQTT *
