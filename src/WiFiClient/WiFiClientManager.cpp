#include "WiFiClient/WiFiClientManager.h"

WiFiClientManagerDHCP::WiFiClientManagerDHCP() {
  loopback = IPAddress(127, 0, 0, 1);
}

void WiFiClientManagerDHCP::setSSID(const String& ssid) {
  this->ssid = ssid;
}

String WiFiClientManagerDHCP::getSSID() const {
  return ssid;
}

void WiFiClientManagerDHCP::setPassword(const String& password) {
  this->password = password;
}

String WiFiClientManagerDHCP::getPassword() const {
  return password;
}

void WiFiClientManagerDHCP::setIP(const IPAddress& ip) {
  this->ip = ip;
}

String WiFiClientManagerDHCP::getIP() const {
  return ip.toString();
}

void WiFiClientManagerDHCP::setSubnet(const IPAddress& subnet) {
  this->subnet = subnet;
}

String WiFiClientManagerDHCP::getSubnet() const {
  return subnet.toString();
}

void WiFiClientManagerDHCP::setGateway(const IPAddress& gateway) {
  this->gateway = gateway;
}

String WiFiClientManagerDHCP::getGateway() const {
  return gateway.toString();
}

void WiFiClientManagerDHCP::configureWiFi(const String& ssid, const String& password) {
  setSSID(ssid);
  setPassword(password);
}

void WiFiClientManagerDHCP::showDetails() {
  Serial.println("SSID: " + ssid);
  Serial.println("IP: " + getIP());
  Serial.println("Subnet: " + getSubnet());
  Serial.println("Gateway: " + getGateway());
  Serial.println("Loopback: " + loopback.toString());
  Serial.println("MAC Address: " + getMacAddress());
}

bool WiFiClientManagerDHCP::connect() {
  WiFi.begin(getSSID().c_str(), getPassword().c_str());
  int retryCount = 0;

  Serial.printf("Connecting");

  while (WiFi.status() != WL_CONNECTED && retryCount < 150) {

    Serial.printf(".");

    delay(500);
    retryCount++;
  }

  Serial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    setIP(WiFi.localIP());
    setSubnet(WiFi.subnetMask());
    setGateway(WiFi.gatewayIP());
    macAddress = WiFi.macAddress();
    Serial.println("Connected!");
    return true;
  }

  Serial.println("Connection Failed");
  return false;
}

void WiFiClientManagerDHCP::disconnect() {
  WiFi.disconnect();
  setIP(IPAddress(0, 0, 0, 0));
  setSubnet(IPAddress(0, 0, 0, 0));
  setGateway(IPAddress(0, 0, 0, 0));
}

bool WiFiClientManagerDHCP::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

String WiFiClientManagerDHCP::getMacAddress() const {
  String formattedMAC = "";
  for (int i = 0; i < 17; i += 3) {
    formattedMAC += macAddress.substring(i, i+2) + (i < 15 ? ":" : "");
  }
  return formattedMAC;
}
