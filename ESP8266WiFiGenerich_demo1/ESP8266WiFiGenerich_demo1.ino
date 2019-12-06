/*
	���ʾ��ͼչʾ�����ʹ��WiFi�¼��������
	�ڱ����У�ESP8266��APģʽ�¹�����
	��ʾ�������¼��������:
	-վ���ӵ�ESP8266 AP
	-վ��ESP8266 AP�Ͽ�����
	- ESP8266 AP�������Թ���վ��̽������
	ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830071
*/

#include <ESP8266WiFi.h>
#include <stdio.h>

const char* ssid = "ESP8266";
const char* password = "12345678";

WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;
WiFiEventHandler probeRequestPrintHandler;
WiFiEventHandler probeRequestBlinkHandler;

bool blinkFlag;

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	// �������κ�wifi���õ�flash
	WiFi.persistent(false);

	// ����һ��AP
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid, password);

	// ע���¼�������
	// �ص����������¼�����ʱ������
	// onStationConnected��������ÿһ����station����ʱ����
	stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
	// onStationDisconnected��������ÿһ����station�Ͽ�ʱ����
	stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
	// onProbeRequestPrint��onProbeRequestBlink��������ÿһ���յ�̽������ʱ����
	// onProbeRequestPrint���ӡstation��mac��ַ���ź�ǿ�ȵ����ڼ�����
	// onProbeRequestBlink����˸LED
	probeRequestPrintHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestPrint);
	probeRequestBlinkHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestBlink);
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt) {
	Serial.print("Station connected: ");
	Serial.println(macToString(evt.mac));
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt) {
	Serial.print("Station disconnected: ");
	Serial.println(macToString(evt.mac));
}

void onProbeRequestPrint(const WiFiEventSoftAPModeProbeRequestReceived& evt) {
	Serial.print("Probe request from: ");
	Serial.print(macToString(evt.mac));
	Serial.print(" RSSI: ");
	Serial.println(evt.rssi);
}

void onProbeRequestBlink(const WiFiEventSoftAPModeProbeRequestReceived&) {
	// ���ǲ������¼��������е�����ʱ��������������������
	// �����������һ����־λ
	blinkFlag = true;
}

void loop() {
	if (millis() > 10000 && probeRequestPrintHandler) {
		// 10s֮�󣬽�ֹ onProbeRequestPrint
		Serial.println("Not printing probe requests any more (LED should still blink)");
		probeRequestPrintHandler = WiFiEventHandler();
	}
	if (blinkFlag) {
		blinkFlag = false;
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
		digitalWrite(LED_BUILTIN, HIGH);
	}
	delay(10);
}

String macToString(const unsigned char* mac) {
	char buf[20];
	snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	return String(buf);
}

