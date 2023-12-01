# servicos-final

## Informações

### Servidor 

Foi utilizado o mesmo servidor do [trabalho de web services](https://github.com/HomeroKemmerich/servicos)

### Cliente

- Com base no projeto [FreeRTOS-ESP-IDF-HTTP-Client](https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-HTTP-Client) foram desenvolvidos os seguintes métodos:
    - `GET`
    - `POST`
- O firmware executa um loop infinito passando pelos métodos HTTP desenvolvidos, realizando as seguintes operações
    - Acessa o recurso raiz
    - Cria um recurso
    - Lê todos os recursos


## Utilização

- Execute o script [serve.sh](./serve.sh), substituindo o campo `[seu.endereço.ip]` pelo seu endereço IP.
- Carregue o código na ESP32