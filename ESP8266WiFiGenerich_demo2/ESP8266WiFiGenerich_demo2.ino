/*
	���ʾ��ͼչʾ�����ʹ��WiFi�¼��������
	�ڱ����У�ESP8266��STATIONģʽ�¹�����
	��ʾ�������¼��������:
	-վ���ӵ�AP
	-վ����AP�Ͽ�����
	- ��ȡվIP
*ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830071
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
	Serial.println("ģ�����ӵ�����");
}

void DisconnectedHandler(const WiFiEventStationModeDisconnected &event)
{
	Serial.println(WiFi.status());
	Serial.println("ģ�������Ͽ�");
}

void setup()
{
	Serial.begin(115200);
	Serial.println();

	STAConnected = WiFi.onStationModeConnected(ConnectedHandler);
	STADisconnected = WiFi.onStationModeDisconnected(DisconnectedHandler);
	STAGotIP = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event) {
		Serial.println(WiFi.status());
		Serial.println("ģ����IP");
	});

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	Serial.println(WiFi.status());
}

void loop()
{
	delay(5000); //�ȴ�5��
	WiFi.disconnect(); //�Ͽ���ǰ��������
}
