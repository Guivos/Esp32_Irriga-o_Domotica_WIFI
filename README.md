
# Sistema de Irrigação Automatizada com ESP32

### Projeto Acadêmico — Automação Domótica  
IFSP — Campus Bragança Paulista (BRA)  
5º Semestre de Engenharia de Controle e Automação  

---

## Descrição

Este projeto consiste no desenvolvimento de um Sistema de Irrigação Inteligente utilizando o microcontrolador ESP32, um sensor de umidade do solo (resistivo) e um módulo relé para controle de uma válvula solenoide 127V.

O sistema realiza a leitura contínua da umidade do solo e, com base em um controle de histerese, aciona ou desliga automaticamente o irrigador. Além disso, implementa um servidor web local, permitindo ao usuário monitorar em tempo real os níveis de umidade e o status da irrigação por meio de qualquer dispositivo conectado à mesma rede Wi-Fi.

---

## Objetivo

Desenvolver um sistema inteligente de automação residencial como parte da avaliação da disciplina de Automação Domótica, no 5º semestre do curso de Engenharia de Controle e Automação do IFSP — Campus Bragança Paulista.

---

## Funcionalidades

- Leitura da umidade do solo (valor bruto e percentual)
- Acionamento automático do irrigador via módulo relé
- Controle por histerese, evitando acionamentos constantes
- Interface web local para monitoramento em tempo real
- Interface responsiva, acessível via computador, tablet ou smartphone
- Calibração manual via software dos limites de umidade
- Exibição de dados técnicos como valores ADC e limites configurados

---

## Arquitetura do Sistema

- Microcontrolador: ESP32 DevKit V1
- Sensor: Umidade do Solo Resistivo
- Atuador: Módulo Relé 5VDC
- Dispositivo Controlado: Válvula Solenoide 127V (Normalmente Fechada)
- Interface Web: HTML, CSS e JavaScript rodando no próprio ESP32
- Conectividade: Wi-Fi (rede local)

---

## Diagrama de Conexões

### Sensor de Umidade ↔️ ESP32

| Sensor            | ESP32  |
|-------------------|--------|
| VCC               | 3.3V   |
| GND               | GND    |
| A0 (Analógico)    | GPIO 35|

Observação: Se alimentado com 5V, utilizar divisor resistivo na saída A0.

---

### Módulo Relé ↔️ ESP32

| Relé  | ESP32  |
|-------|--------|
| VCC   | 5V     |
| GND   | GND    |
| IN    | GPIO 5 |

---

### Válvula Solenoide ↔️ Relé ↔️ Rede Elétrica

| Válvula        | Relé   | Alimentação AC |
|----------------|--------|-----------------|
| Terminal 1     | COM    | Fase            |
| Terminal 2     | NO     | Neutro          |

---

## Interface Web

- Mostra umidade atual em percentual com barra de progresso
- Mostra status do irrigador (ligado ou desligado)
- Exibe os valores brutos do sensor (ADC)
- Mostra os limites de controle configurados
- Atualização automática a cada 2 segundos
- Compatível com celular, tablet e computador

---

## Parâmetros do Código

```cpp
// Limiares de controle
float LIMIAR_LIGAR = 30.0;      // Em percentual
float LIMIAR_DESLIGAR = 40.0;   // Em percentual

// Calibração ADC do sensor
int seco = 4095;     // Valor ADC com solo seco
int molhado = 1400;  // Valor ADC com solo bem molhado
```

---

## Lógica de Controle — Histerese

- Liga irrigação quando a umidade for menor ou igual a LIMIAR_LIGAR
- Desliga irrigação quando a umidade for maior ou igual a LIMIAR_DESLIGAR

Essa lógica evita o acionamento constante da válvula em situações de pequena oscilação de umidade, protegendo os componentes e aumentando sua vida útil.

---

## Bibliotecas Necessárias

- WiFi.h — Conexão Wi-Fi
- AsyncTCP.h — Comunicação TCP assíncrona
- ESPAsyncWebServer.h — Servidor Web assíncrono

---

## Correção de Erros

Atenção ao utilizar ESPAsyncWebServer com ESP32 Core versão 3.2.0 ou superior.

Erro reportado:

```
error: call of overloaded 'IPAddress(unsigned int)' is ambiguous
```

Solução aplicada:

Editar o arquivo:

```
/Arduino/libraries/ESP_Async_WebServer/src/AsyncWebSocket.cpp
```

Modificar:

```cpp
// Original (com erro)
return IPAddress(0U);

// Corrigido
return IPAddress((uint32_t)0);
```

---

## Organização do Projeto

```
├── irrigacao_esp32.ino         # Código Sem WIFI
├── irrigacao_esp32.ino         # Código principal com WIFI
├── drivers
│   └──[...]                    # Drivers necessarios para funcionar a interface.
├── README.md                   # Este documento
```

---

## Acesso ao Projeto

Repositório: https://github.com/RMDomingos20/Esp32_Irriga-o_Domotica.git

---

## Autores

- Guilherme Gabriel Franco de Souza  
- Jonathan Alexandre de Moraes Cândido  
- Rafael Domingos Siqueira Magalhães  
- Vitor Wohlers de Godoy  
- Vinicius Henrique de Melo  

---

## Referências

- ESPRESSIF SYSTEMS. ESP32 Datasheet.  
- CASA DA ROBÓTICA — Documentação de componentes.  
- Mendes, G. H.; Silva, D. R.; Oliveira, A. P. IoT aplicada à automação residencial.  
- ONU — Relatório dos Objetivos de Desenvolvimento Sustentável 2023.  

---
