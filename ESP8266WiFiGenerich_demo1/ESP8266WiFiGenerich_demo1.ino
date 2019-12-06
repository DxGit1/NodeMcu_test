/*
	这个示意图展示了如何使用WiFi事件处理程序。
	在本例中，ESP8266在AP模式下工作。
	演示了三个事件处理程序:
	-站连接到ESP8266 AP
	-站与ESP8266 AP断开连接
	- ESP8266 AP接收来自工作站的探测请求
	原文链接：https ://blog.csdn.net/dpjcn1990/article/details/92830071
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

	// 不保存任何wifi配置到flash
	WiFi.persistent(false);

	// 建立一个AP
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid, password);

	// 注册事件处理器
	// 回调函数会在事件发生时被调用
	// onStationConnected函数会在每一次有station连接时调用
	stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
	// onStationDisconnected函数会在每一次有station断开时调用
	stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
	// onProbeRequestPrint和onProbeRequestBlink函数会在每一次收到探针请求时调用
	// onProbeRequestPrint会打印station的mac地址和信号强度到串口监视器
	// onProbeRequestBlink会闪烁LED
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
	// 我们不能在事件处理函数中调用延时函数或者其他阻塞函数
	// 因此这里设置一个标志位
	blinkFlag = true;
}

void loop() {
	if (millis() > 10000 && probeRequestPrintHandler) {
		// 10s之后，禁止 onProbeRequestPrint
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

