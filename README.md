# Sistema de Irrigação Automatizada com ESP32

### Projeto Acadêmico — Automação Domótica  
**IFSP — Campus Bragança Paulista (BRA)**  
**5º Semestre de Engenharia de Controle e Automação**  

---

## Descrição

Este projeto consiste em um sistema de irrigação automática utilizando um microcontrolador **ESP32**, um **sensor de umidade do solo Resistivo** e um **relé** para o controle de  válvula Solenoide de irrigação.

O sistema mede continuamente a umidade do solo e, através de um controle baseado em **histerese**, aciona ou desliga o irrigador conforme os níveis de umidade definidos pelo software e usuario.

---

## Objetivo

Desenvolver um sistema inteligente de automação residencial, como parte da avaliação da disciplina de **Automação Domótica**, no **5º semestre** do curso de **Engenharia de Controle e Automação** no **Instituto Federal de São Paulo — IFSP (Campus BRA)**.

Este projeto compõe parte da **nota do semestre**.

---

## Funcionalidades

- Leitura de umidade do solo via sensor capacitivo.
- Acionamento automático de um relé (simulando bomba ou válvula de irrigação).
- Controle de histerese para evitar acionamentos constantes.
- Visualização dos dados no monitor serial (leitura analógica e porcentagem de umidade).

---

## Tecnologias Utilizadas

- **ESP32 DevKit V1**
- **Sensor resistivo de umidade do solo**
- **Módulo relé 5VDA 250VCA**
- **Arduino IDE**
- **Valvula Solenoide 127VAC**

---

## Conexões do Hardware

| Sensor de Umidade | ESP32        |
|-------------------|--------------|
| VCC               | 3.3V         |
| GND               | GND          |
| A0 (analógico)    | GPIO 35      |
| D0 (digital)      | (Não usado)  |

\* ⚠️ Atenção: Se o sensor for alimentado em 5V, verificar se a saída A0 não excede 3.3V. Usar divisor resistivo se necessário.

| Módulo Relé | ESP32    |
|--------------|---------|
| VCC          | 5V      |
| GND          | GND     |
| IN           | GPIO 5  |

---

| Válvula Sólenoide | Módulo Relé | ALIMENTAÇÃO |
--------------------|-------------|-------------|
|        VCC        |     --      |     FASE    |
|        GND        |     COM     |             |
|       --          |      NO     |    NEUTRO   |
---
## Código Fonte

O código está no arquivo `irrigacao_esp32.ino`.

Principais parâmetros configuráveis:

```cpp
// Limiares de controle (em porcentagem)
float LIMIAR_LIGAR = 30.0;
float LIMIAR_DESLIGAR = 40.0;

// Calibração ADC
int seco = 4095;    // Valor quando o solo está seco
int molhado = 1400; // Valor quando o solo está bem molhado
```

### Compatibilidade de Bibliotecas e Correção de Erros

Durante o desenvolvimento, foi identificado um problema de compatibilidade relacionado à biblioteca **`ESPAsyncWebServer`** ao utilizar o **core ESP32 versão 3.2.0** (ou superior). O erro reportado durante a compilação foi:

    error: call of overloaded 'IPAddress(unsigned int)' is ambiguous

 **Solução aplicada:**  
O problema ocorre devido à ambiguidade no construtor da classe `IPAddress` nas versões mais recentes do core ESP32. Para resolver, foi necessário editar o arquivo:

    /Arduino/libraries/ESP_Async_WebServer/src/AsyncWebSocket.cpp


Na linha correspondente (aproximadamente linha 844), a seguinte alteração foi feita:

```cpp
// Antes (com erro)
return IPAddress(0U);

// Depois (corrigido)
return IPAddress((uint32_t)0);
```
