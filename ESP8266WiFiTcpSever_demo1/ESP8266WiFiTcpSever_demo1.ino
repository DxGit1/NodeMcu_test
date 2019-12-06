/**
 * Demo��
 *    ��ʾWiFiServer����
 *    ��TCP�������� ģ��TCP client����
 * @author ��Ƭ������
 * @date 2019/09/04
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830087
 */
#include <ESP8266WiFi.h>

 //���������ٸ�client�������ӱ�server(һ�㲻Ҫ����4��)
#define MAX_SRV_CLIENTS 2
//������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

const char* ssid = "space";
const char* password = "12345678";

//����server �˿ں���23
WiFiServer server(23);
//����clients
WiFiClient serverClients[MAX_SRV_CLIENTS];

void setup() {
	DebugBegin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	DebugPrint("\nConnecting to ");
	DebugPrintln(ssid);
	uint8_t i = 0;
	while (WiFi.status() != WL_CONNECTED && i++ < 20) {
		delay(500);
	}
	if (i == 21) {
		DebugPrint("Could not connect to");
		DebugPrintln(ssid);
		while (1) {
			delay(500);
		}
	}
	//����server
	server.begin();
	//�ر�С���ϲ������ܣ�������ʱ��������
	server.setNoDelay(true);

	DebugPrint("Ready! Use 'telnet ");
	DebugPrint(WiFi.localIP());
	DebugPrintln(" 23' to connect");
}

void loop() {
	uint8_t i;
	//����Ƿ����µ�client�������
	if (server.hasClient()) {
		for (i = 0; i < MAX_SRV_CLIENTS; i++) {
			//�ͷž���Ч���߶Ͽ���client
			if (!serverClients[i] || !serverClients[i].connected()) {
				if (serverClients[i]) {
					serverClients[i].stop();
				}
				//�������µ�client
				serverClients[i] = server.available();
				DebugPrint("New client: ");
				DebugPrint(i);
				break;
			}
		}
		//���ﵽ��������� �޷��ͷ���Ч��client����Ҫ�ܾ�����
		if (i == MAX_SRV_CLIENTS) {
			WiFiClient serverClient = server.available();
			serverClient.stop();
			DebugPrintln("Connection rejected ");
		}
	}
	//���client������������
	for (i = 0; i < MAX_SRV_CLIENTS; i++) {
		if (serverClients[i] && serverClients[i].connected()) {
			if (serverClients[i].available()) {
				//get data from the telnet client and push it to the UART
				while (serverClients[i].available()) {
					//���͵����ڵ�����
					Serial.write(serverClients[i].read());
				}
			}
		}
	}

	if (Serial.available()) {
		//�Ѵ��ڵ����������������� ���͸�client
		size_t len = Serial.available();
		uint8_t sbuf[len];
		Serial.readBytes(sbuf, len);
		//push UART data to all connected telnet clients
		for (i = 0; i < MAX_SRV_CLIENTS; i++) {
			if (serverClients[i] && serverClients[i].connected()) {
				serverClients[i].write(sbuf, len);
				delay(1);
			}
		}
	}
}
