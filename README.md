# Locomotivas

## Pre-requisitos

Para utilizar o sistema de locomotivas é necessário instalar na IDE do arduino, uma biblioteca chamada WebSockets criada por Markus Sattler.

Para isso, siga os passos:

1. Abra a IDE do arduino.
2. Vá em sketch no menu superior.
3. Depois em Incluir Biblioteca.
4. Clique em Gerenciar Bibliotecas.

Uma nova janela vai se abrir.

5. No canto superior direito, busque por WebSockets.
6. Encontre a biblioteca "WebSockets by Markus Sattler".
7. instale a versão mais recente.

Depois de instalada a biblioteca, está tudo pronto para usar este código.

## Criando uma mesa de controle

Dentro da pasta server, abra o arquivo server.ino.  
Ao abrir o arquivo, na linha 4 será possível editar o nome do controle:

* const char *user = "controle1";

Para criar outro controle, edite o nome.  
por exemplo troque para controle2, controle3, etc...

Por padrão ficará algo no modelo:

* const char *user = "controleX";

Onde X é o número do controle.

## Criando um novo trem

Dentro da pasta client, abra o arquivo client.ino.  
Ao abrir o arquivo, na linha 4 será possivel editar o nome do controle ao qual o trem vai se conectar.

* const char *user = "controleX";

Onde X é o número do controle para conecção.

**É possível que mais de um trem se connecte ao mesmo controle, porém cada trem só se conecta a um controle**. Isso significa que com um mesmo controle, você pode controlar até 5 trens, estes vão receber o mesmo valor de velocidade, estados de farol e de controle automático.

## Enviando os códigos para os nodes

Com a IDE do arduino aberta, vá até:

1. Arquivo no menu superior.
2. Preferencias

Uma nova janela vai se abrir.

3. Na opção URLs Adicionais para Gerenciadores de Placas, copie e cole o seguinte link [http://arduino.esp8266.com/stable/package_esp8266com_index.json]().
4. Clique em OK.
5. Vá em Ferramentas.
6. Placas.
7. Gerenciador de Placas.
8. Busque por esp8266 (por ESP8266 Community)
9. Instale.

Também é necessário intalar um driver. Clique no link para ver o [Tutorial de instalação do Driver](https://www.drivereasy.com/knowledge/ch340g-driver-download-and-update-in-windows/)

10. Reinicie a IDE.

Para passar os códigos para os nodes, é necessário observar qual modelo está sendo usado.

### NodeMCU

![NodeMCU](https://images-na.ssl-images-amazon.com/images/I/81U4jvpGnYL._SL1500_.jpg)

Conecte um cabo USB nele e no computador.  
Na IDE do Arduino, vá em:

1. Ferramentas
2. Placas
3. Selecione a opção NodeMCU 1.0 (ESP-12E Module)
4. Novamente em ferramentas, clique em Porta.
5. Selecione a porta na qual o Node está conectado.

Pronto. Basta clicar na opção carregar.

### ESP8266

![ESP8266](https://cdn.itead.cc/media/catalog/product/cache/1/image/9df78eab33525d08d6e5fb8d27136e95/i/m/im151118007_4_.jpg)

Este modelo é mais complicado. É possivel programá-lo utilizando um arduino UNO, como mostra este [exemplo](https://www.hackster.io/pratikdesai/how-to-program-esp8266-esp-01-module-with-arduino-uno-598166). 

**OBS: O exemplo acima usa um modelo diferente, porém as ligações dos pinos são as mesmas. Bata seguir a tabela mostrada.**

Após fazer a ligação, vé em:

1. Ferramentas.
2. Placa.
3. Selecione Generic ESP8266 Module.
4. Novamente em Ferramentas.
5. Porta.
6. Selecione a porta que está o arduino.

Pronto. Basta carregar o código.

# Contato

Para mais informações, você pode me encontrar no [Facebook](https://www.facebook.com/dener.vieira.735) ou no [Instagram](https://www.instagram.com/dv_vieira/).