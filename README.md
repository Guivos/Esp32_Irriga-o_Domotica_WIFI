# 🌱 Sistema de Irrigação Automatizada com ESP32

### 💻 Projeto Acadêmico — Automação Domótica  
**IFSP — Campus Bragança Paulista (BRA)**  
**5º Semestre de Engenharia de Controle e Automação**  

---

## 📝 Descrição

Este projeto consiste em um sistema de irrigação automática utilizando um microcontrolador **ESP32**, um **sensor de umidade do solo capacitivo** e um **relé** para simular o controle de uma bomba d'água ou válvula de irrigação.

O sistema mede continuamente a umidade do solo e, através de um controle baseado em **histerese**, aciona ou desliga o irrigador conforme os níveis de umidade definidos.

---

## 🎯 Objetivo

Desenvolver um sistema inteligente de automação residencial, como parte da avaliação da disciplina de **Automação Domótica**, no **5º semestre** do curso de **Engenharia de Controle e Automação** no **Instituto Federal de São Paulo — IFSP (Campus BRA)**.

Este projeto compõe parte da **nota do semestre**.

---

## 🚀 Funcionalidades

- Leitura de umidade do solo via sensor capacitivo.
- Acionamento automático de um relé (simulando bomba ou válvula de irrigação).
- Controle de histerese para evitar acionamentos constantes.
- Visualização dos dados no monitor serial (leitura analógica e porcentagem de umidade).

---

## ⚙️ Tecnologias Utilizadas

- **ESP32 DevKit V1**
- **Sensor resistivo de umidade do solo**
- **Módulo relé 5VDA 250VCA**
- **Arduino IDE**
- **Valvula Solenoide 127VAC**

---

## 🔗 Conexões do Hardware

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
## 📜 Código Fonte

O código está no arquivo `irrigacao_esp32.ino`.

Principais parâmetros configuráveis:

```cpp
// Limiares de controle (em porcentagem)
float LIMIAR_LIGAR = 30.0;
float LIMIAR_DESLIGAR = 40.0;

// Calibração ADC
int seco = 4095;    // Valor quando o solo está seco
int molhado = 1400; // Valor quando o solo está bem molhado
