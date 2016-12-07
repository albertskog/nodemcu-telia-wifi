#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <TeliaWifiClient.h>

#define USE_SERIAL Serial

const char teliaWifiSsid[] = "Telia wifi";
const char teliaWifiUser[] = "Your phone number or email";
const char teliaWifiPassword[] = "Your password";


void setup() {
    USE_SERIAL.begin(115200);
}

void loop(){

    if (WiFi.status() != WL_CONNECTED) {
        connectWifi();
        TeliaWifi.connect(teliaWifiUser, teliaWifiPassword);
        return;
    }

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin("http://example.com/"); //HTTP
    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            USE_SERIAL.println(payload);
        }
    } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    
	delay(10000);

}

static void connectWifi(void) {

        USE_SERIAL.println("Connecting to " + String(teliaWifiSsid) + "...");

        WiFi.begin(teliaWifiSsid);

        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
           USE_SERIAL.println("Could not connect to wifi.");
           return;
        }

        USE_SERIAL.println("WiFi connected");
}

