# Projeto Vision - Auxílio para Deficientes Visuais em Supermercados
**Objetivo:** Desenvolver um sistema que auxilia deficientes visuais em supermercados, proporcionando autonomia na hora de fazer compras.

## Funcionalidades:

* Leitor de etiquetas RFID acoplado à cesta de compras.
* Sistema narrador que descreve os produtos (nome, quantidade, preço, validade, etc.).
* Base de dados atualizável com informações dos produtos.
* Integração com servidor web para atualização e gerenciamento dos dados.

## Tecnologias:

* Arduino UNO R3
* Módulo sensor RFID - MFRC522 13,56MHz
* MP3 ARDUINO DFPLAYER MINI
* Ethernet Shield W5100
* Servidor Apache
* Banco de dados MySQL
* PHP

## Destaques:

* **Inovação:** Solução que visa melhorar a inclusão social de deficientes visuais.
* **Integração de Hardware e Software:** Combinação de Arduino com tecnologias web para um sistema completo.

## Funcionamento:

O código do Arduino (dataphp.ino) faz a leitura das tags RFID e se comunica com o servidor web pelo código php (mercado.php). Então, o servidor web processa as informações e retorna os dados do produto para o Arduino, que aciona o módulo MP3 para reproduzir as informações do produto.
