#include <WiFi.h>
#include <HTTPClient.h>

void enviarDados(int ran){

  // Cria variavel para conex~]ao http
  HTTPClient http;

  // Define URL e BODY para fazer o post
  String url = "https://alarmeiot.up.railway.app/postdistancia";
  String body = "dado=" + String(ran);
  Serial.printf("Numero sorteado: %d\n", ran);

  // Inicia a conexão com a URL da API e adiciona o header (essa ultima parte eu n entendi direito)
  http.begin(url);
  
  http.addHeader("Content-Type", "application/json");

  // Faz o post e recebe a resposta HTTP
  int httpCode = http.POST(body);

  // Verifica se o post foi um sucesso
  if (httpCode == 200){
    Serial.println("Dados enviados");
  }else{
    Serial.println("Erro ao enviar os dados-Erro:" + String(httpCode));
  }

}

void setup(){

  Serial.begin(9600);
  randomSeed(millis());

  // Conecta à rede WiFi
  WiFi.begin("CLARO_2GLUCAS", "08052002");

  // Aguarda a conexão ser estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Verifica se a conexão foi estabelecida
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado à internet!");
  } else {
    Serial.println("Falha na conexão!");
  }

}

void loop(){

  int ran = random(100);

  enviarDados(ran);
  delay(10000);

}
