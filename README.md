# servicos-final

## Sumário
- [Alunos](#alunos)
- [Informações](#informações)
- [Documentação](./doc/wiki.html)

## Alunos

- Bruno Helder
- Gabriel Tibola Castagnera
- Homero Kemmerich

## Informações

### Servidor 

Foi utilizado o mesmo servidor do [trabalho de web services](https://github.com/HomeroKemmerich/servicos), com algumas adaptações para o contexto.

### Cliente

- Com base no projeto [FreeRTOS-ESP-IDF-HTTP-Client](https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-HTTP-Client) foram desenvolvidos os seguintes métodos:
    - `GET`
    - `POST`
    - `PUT`
    - `DELETE`
- O firmware executa um loop infinito passando pelos métodos HTTP desenvolvidos, realizando a seguinte sequência de ações:
    - [x] Acessa o recurso raiz
    - [x] Cria um novo recurso
    - [x] Acessa o recurso criado
    - [x] Cria um novo recurso
    - [x] Lista todos os recursos
    - [x] Altera o segundo recurso
    - [x] Exclui o primeiro recurso
    - [x] Lista todos os recursos


## Utilização

- Execute o script [serve.sh](./serve.sh), substituindo o campo `[seu.endereço.ip]` pelo seu endereço IP.
- Altere as constantes de conexão no [arquivo de constantes do cliente](./client/src/constants/connection.h)
- Utilizando a ferramenta PlatformIO IDE, carregue o código na ESP32
    - Se necessário, realize o *reset* no botão