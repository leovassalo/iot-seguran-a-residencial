A porção de software do sistema é dividida em duas: o flow do Node-red e o código do ESP32. Os códigos associados podem ser encontrados em seus respectivos 
folders. <br /><br />

O ESP só precisa ter seu código carregado uma única vez, podendo operar, inclusive sem a conexão de um computador em usos futuros (para mobilidade).
Neste projeto, foi utilizada a extensão PlatformIO no VScode. A plataforma é de uso simples e permite que o código seja gravado no microcontrolador com facilidade.

Para a configuração do dispositivo central de gerenciamento - Raspberry -, foi utilizado o software Node-Red (configurações e nodes disponíveis na pasta correspondente), no qual se faz necessária apenas sua ativação, contando com blocos de comando que permitem que sempre que uma ação é executada pelo assistente Jarvis (desde dizer a temperatura, ligar um led ou a simplesmente pedir para que o usuário repita), ele ativa a espera por uma nova Wake Word.
<br /><br />
