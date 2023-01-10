#include <WiFi.h>
#include <HTTPClient.h>

const int microphonePin = 33;
const char* ssid = "mogwai-red";
const char* password = "790423Pa0221";
String server_host = "http://192.168.5.234:8080";

HTTPClient httpClient;
WiFiClient espClient;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("http://");
  Serial.print(WiFi.localIP());

  sendAliveDevice();
}

void httpCodeHandle(int httpCode) {
  if (httpCode > 0) {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      String payload = httpClient.getString();
      Serial.println(payload);
    }
  }
  else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
  }
}

void sendAliveDevice() {
  String url = server_host + "/alive";

  if (httpClient.begin(espClient, url))
  {
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.print("[HTTP] POST...\n");
    String postData = "uuid=12345";
    int httpCode = httpClient.POST(postData);
    httpCodeHandle(httpCode);
    httpClient.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}

void sendRing(String value) {
  String url = server_host + "/ring";

  if (httpClient.begin(espClient, url))
  {
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.print("[HTTP] POST...\n");
    String postData = "value=" + value;
    int httpCode = httpClient.POST(postData);
    httpCodeHandle(httpCode);
    httpClient.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}

void loop() {
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 1000; ++i) {
    int val = analogRead(microphonePin);
    //mn = min(mn, val);
    mx = max(mx, val);
  }

  //int delta = mx - mn;

  Serial.println(mx);

  if (mx >= 800) {
    sendRing(String(mx));    
  }
}
