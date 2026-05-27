include <Wire.h> #include <Adafruit_GFX.h> #include <Adafruit_SSD1306.h> #include <DHT.h>

#define SCREEN_WIDTH 128 #define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 2 #define DHTTYPE DHT22 DHT dht(DHTPIN, DHTTYPE);

#define BUTTON_PIN 7

int tela = 0; int ultimoEstado = HIGH;

void setup() { pinMode(BUTTON_PIN, INPUT_PULLUP);

dht.begin();

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { while(true); }

display.clearDisplay(); display.setTextColor(SSD1306_WHITE); }

void loop() {

int leitura = digitalRead(BUTTON_PIN);

if(leitura == LOW && ultimoEstado == HIGH) { tela++;

if(tela > 1) {
  tela = 0;
}

delay(200);
}

ultimoEstado = leitura;

float temperatura = dht.readTemperature(); float umidade = dht.readHumidity();

display.clearDisplay();

if(tela == 0) {

display.setTextSize(2);
display.setCursor(10, 5);
display.println("CLIMA");

display.setTextSize(1);
display.setCursor(0, 30);
display.print("Temp: ");
display.print(temperatura);
display.println(" C");

display.setCursor(0, 45);
display.print("Umidade: ");
display.print(umidade);
display.println(" %");
} else {

display.setTextSize(2);
display.setCursor(15, 10);
display.println("RELOGIO");

display.setTextSize(2);
display.setCursor(25, 40);
display.println("12:45");
}

display.display();

delay(1000); }

