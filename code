#include <WiFi.h>  
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Configurações do hardware
#define SENSOR_UMIDADE 35
#define RELE_IRRIGADOR 5

// Configurações Wi-Fi
const char* ssid = "guivos";
const char* password = "guibas1212";

// Parâmetros do sistema
float LIMIAR_LIGAR = 30.0;    // Limiar para ligar irrigador (%)
float LIMIAR_DESLIGAR = 40.0; // Limiar para desligar irrigador (%)
int seco = 4095;              // Valor ADC para solo seco
int molhado = 1400;           // Valor ADC para solo molhado

// Variáveis de estado
float umidade = 0;
bool irrigador = false;

// Criação do servidor web
AsyncWebServer server(80);

// Função para calcular a umidade em porcentagem
String readSoilHumidity() {
  int leitura = analogRead(SENSOR_UMIDADE);
  umidade = map(leitura, seco, molhado, 0, 100);
  umidade = constrain(umidade, 0, 100);
  return String(umidade, 1); 
}

// Função para obter status do irrigador
String readIrrigatorStatus() {
  return irrigador ? "LIGADO" : "DESLIGADO";
}

// Página HTML completa
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css">
  <style>
    html {
      font-family: Arial, sans-serif;
      display: inline-block;
      margin: 0 auto;
      text-align: center;
      padding: 20px;
      background-color: #f5f5f5;
    }
    h2 { color: #2c3e50; margin-bottom: 30px; }
    .card {
      background: white;
      border-radius: 10px;
      padding: 20px;
      margin: 15px auto;
      max-width: 400px;
      box-shadow: 0 4px 8px rgba(0,0,0,0.1);
    }
    .value {
      font-size: 2.5rem;
      font-weight: bold;
      margin: 10px 0;
    }
    .unit {
      font-size: 1rem;
      color: #7f8c8d;
    }
    .irrigator-on { color: #e74c3c; }
    .irrigator-off { color: #2ecc71; }
    .label {
      font-size: 1.1rem;
      color: #34495e;
      margin-bottom: 5px;
    }
    .progress-container {
      width: 100%;
      background-color: #ecf0f1;
      border-radius: 5px;
      margin: 15px 0;
    }
    .progress-bar {
      height: 20px;
      border-radius: 5px;
      background-color: #3498db;
      width: 0%;
      transition: width 0.5s;
    }
  </style>
</head>
<body>
  <h2><i class="fas fa-tint"></i> Sistema de Irrigacao</h2>
  
  <div class="card">
    <div class="label"><i class="fas fa-water"></i> Umidade do Solo</div>
    <div class="value" id="humidity">--</div>
    <div class="unit">Porcentagem</div>
    <div class="progress-container">
      <div class="progress-bar" id="humidity-bar"></div>
    </div>
  </div>
  
  <div class="card">
    <div class="label"><i class="fas fa-plug"></i> Estado do Irrigador</div>
    <div class="value" id="irrigator">--</div>
  </div>
  
  <div class="card">
    <div class="label"><i class="fas fa-microchip"></i> Leitura do Sensor</div>
    <div class="value" id="rawValue">--</div>
    <div class="unit">Valor ADC (0-4095)</div>
  </div>

  <div class="card" style="max-width: 450px;">
    <div class="label"><i class="fas fa-info-circle"></i> Limiares</div>
    <div style="display: flex; justify-content: space-between;">
      <div>Ligar: %LIMIAR_LIGAR% %</div>
      <div>Desligar: %LIMIAR_DESLIGAR% %</div>
    </div>
  </div>
</body>
<script>
function updateData() {
  fetch("/humidity")
    .then(r => r.text())
    .then(t => {
      document.getElementById("humidity").textContent = t;
      document.getElementById("humidity-bar").style.width = t + "%";
    });
  
  fetch("/irrigator")
    .then(r => r.text())
    .then(t => {
      document.getElementById("irrigator").textContent = t;
      document.getElementById("irrigator").className = t === "LIGADO" ? "irrigator-on" : "irrigator-off";
    });
  
  fetch("/raw")
    .then(r => r.text())
    .then(t => document.getElementById("rawValue").textContent = t);
}

// Atualiza a cada 2 segundos
setInterval(updateData, 2000);
// Executa imediatamente ao carregar
updateData();
</script>
</html>)rawliteral";

// Processador para substituir placeholders
String processor(const String& var) {
  if(var == "UMIDADE") return readSoilHumidity();
  if(var == "IRRIGADOR") return readIrrigatorStatus();
  if(var == "RAW_VALUE") return String(analogRead(SENSOR_UMIDADE));
  if(var == "LIMIAR_LIGAR") return String(LIMIAR_LIGAR, 1);
  if(var == "LIMIAR_DESLIGAR") return String(LIMIAR_DESLIGAR, 1);
  return String();
}

void setup() {
  Serial.begin(115200);
  pinMode(RELE_IRRIGADOR, OUTPUT);
  digitalWrite(RELE_IRRIGADOR, LOW);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.print("Conectado! IP: ");
  Serial.println(WiFi.localIP());

  // Rotas do servidor web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", readSoilHumidity());
  });
  
  server.on("/irrigator", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", readIrrigatorStatus());
  });
  
  server.on("/raw", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(analogRead(SENSOR_UMIDADE)));
  });

  server.begin();
}

void loop() {
  // Controle do irrigador
  int leitura = analogRead(SENSOR_UMIDADE);
  umidade = map(leitura, seco, molhado, 0, 100);
  umidade = constrain(umidade, 0, 100);

  if(!irrigador && umidade < LIMIAR_LIGAR) {
    irrigador = true;
    digitalWrite(RELE_IRRIGADOR, HIGH);
    Serial.println("Irrigador LIGADO");
  } 
  else if(irrigador && umidade > LIMIAR_DESLIGAR) {
    irrigador = false;
    digitalWrite(RELE_IRRIGADOR, LOW);
    Serial.println("Irrigador DESLIGADO");
  }

  delay(1000);
}
