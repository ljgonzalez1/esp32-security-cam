#ifndef ESPCAM_PROJECT_WIFICLIENTMANAGER_H
#define ESPCAM_PROJECT_WIFICLIENTMANAGER_H


#include <WiFi.h>
#include <cstring>

class WiFiClientManagerDHCP {
private:
  String ssid;
  String password;
  IPAddress ip;
  IPAddress subnet;
  IPAddress gateway;
  IPAddress loopback;
  String macAddress;

public:
  WiFiClientManagerDHCP();
  void setSSID(const String& ssid);
  String getSSID() const;
  void setPassword(const String& password);
  String getPassword() const;
  void setIP(const IPAddress& ip);
  String getIP() const;
  void setSubnet(const IPAddress& subnet);
  String getSubnet() const;
  void setGateway(const IPAddress& gateway);
  String getGateway() const;
  void configureWiFi(const String& ssid, const String& password);
  void showDetails();
  bool connect();
  void disconnect();
  bool isConnected();
  String getMacAddress() const;
};


#endif //ESPCAM_PROJECT_WIFICLIENTMANAGER_H
