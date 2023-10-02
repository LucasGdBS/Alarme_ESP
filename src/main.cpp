#include <WiFi.h>
#include <HTTPClient.h>

#define wifi "NOME"
#define senha "SENHA"

void enviarDados(float ran){

  // Cria variavel para conex~]ao http
  HTTPClient http;

  // Define URL e BODY para fazer o post
  String url = "https://alarmeiot.up.railway.app/postdistancia/?dado=" + String(ran);
  Serial.printf("Numero sorteado: %f\n", ran);

  // Inicia a conexão com a URL da API e adiciona o header (essa ultima parte eu n entendi direito)
  http.begin(url);
  
  http.addHeader("accept", "application/json");

  // Faz o post e recebe a resposta HTTP
  int httpCode = http.POST({});

  // Verifica se o post foi um sucesso
  if (httpCode > 0){
    Serial.printf("[HTTP] POST... código de status: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      String resposta = http.getString();
      Serial.println("Resposta da API: " + resposta);
    }
  } else {
    Serial.printf("[HTTP] Falha na conexão...\n");
  }

  http.end();
}

void setup(){

  Serial.begin(9600);
  randomSeed(millis());

  // Conecta à rede WiFi
  WiFi.begin(wifi, senha);

  // Aguarda a conexão ser estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Verifica se a conexão foi estabelecida
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado à internet!");
  }

}

void loop(){

  float ran = random(100)*1.0;

  enviarDados(ran);
  delay(5000);

}
