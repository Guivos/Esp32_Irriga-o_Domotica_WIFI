#define SENSOR_UMIDADE 35
#define RELE_IRRIGADOR 5

// Limiares de histerese (em %)
float LIMIAR_LIGAR = 30.0;
float LIMIAR_DESLIGAR = 40.0;

float umidade = 0;
bool irrigador = false;

// Calibração dos valores ADC
int seco = 4095;     // Valor lido quando o solo está completamente seco
int molhado = 1400;  // Valor lido quando o solo está completamente molhado

void setup() {
  Serial.begin(19200);
  pinMode(RELE_IRRIGADOR, OUTPUT);
  digitalWrite(RELE_IRRIGADOR, LOW);
  
  Serial.println("Sistema de Irrigação com Histerese e Calibração");
}

void loop() {
  int leitura = analogRead(SENSOR_UMIDADE);

  // Mapeia o valor lido para porcentagem correta
  umidade = map(leitura, seco, molhado, 0, 100);
  umidade = constrain(umidade, 0, 100); // Garante que fica entre 0 e 100

  Serial.print("Leitura ADC: ");
  Serial.print(leitura);
  Serial.print(" -> Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  // Controle com histerese
  if (!irrigador && umidade < LIMIAR_LIGAR) {
    irrigador = true;
    digitalWrite(RELE_IRRIGADOR, HIGH);
    Serial.println("Solo seco! Ligando irrigador.");
  }
  else if (irrigador && umidade > LIMIAR_DESLIGAR) {
    irrigador = false;
    digitalWrite(RELE_IRRIGADOR, LOW);
    Serial.println("Solo úmido. Desligando irrigador.");
  } 
  else {
    Serial.println(irrigador ? "Irrigador ligado." : "Irrigador desligado.");
  }

  delay(1000);
}
