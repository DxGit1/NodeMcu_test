/*
	这个示意图展示了如何使用WiFi事件处理程序。
	在本例中，ESP8266在STATION模式下工作。
	演示了三个事件处理程序:
	-站连接到AP
	-站与与AP断开连接
	- 获取站IP
*原文链接：https ://blog.csdn.net/dpjcn1990/article/details/92830071
*/

#include <ESP8266WiFi.h>

const char *ssid = "space";
const char *password = "12345678";

WiFiEventHandler STAConnected;
WiFiEventHandler STADisconnected;
WiFiEventHandler STAGotIP;

void ConnectedHandler(const WiFiEventStationModeConnected &event)
{
	Serial.println(WiFi.status());
	Serial.println("模块连接到网络");
}

void DisconnectedHandler(const WiFiEventStationModeDisconnected &event)
{
	Serial.println(WiFi.status());
	Serial.println("模块从网络断开");
}

void setup()
{
	Serial.begin(115200);
	Serial.println();

	STAConnected = WiFi.onStationModeConnected(ConnectedHandler);
	STADisconnected = WiFi.onStationModeDisconnected(DisconnectedHandler);
	STAGotIP = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event) {
		Serial.println(WiFi.status());
		Serial.println("模块获得IP");
	});

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	Serial.println(WiFi.status());
}

void loop()
{
	delay(5000); //等待5秒
	WiFi.disconnect(); //断开当前网络连接
}
