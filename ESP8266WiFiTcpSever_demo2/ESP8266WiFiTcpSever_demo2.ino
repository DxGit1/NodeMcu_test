/**
 * Demo��
 *    ��ʾweb Server����
 *    ��PC����� ����IP��ַ������web server
 * @author ��Ƭ������
 * @date 2019/09/05
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830087
 */
#include <ESP8266WiFi.h>

const char* ssid = "space";//wifi�˺� ������Ҫ�޸�
const char* password = "12345678";//wifi���� ������Ҫ�޸�

//���� tcp server �˿ں���80
WiFiServer server(80);

void setup() {
	Serial.begin(115200);
	Serial.println();

	Serial.printf("Connecting to %s ", ssid);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println(" connected");
	//����TCP ����
	server.begin();
	//��ӡTCP server IP��ַ
	Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}

/**
 * ģ��web server ����http web��Ӧ����
 * �������ֶ�ƴ��HTTP��Ӧ����
 * ����¥�������������������ר����http����Ŀ�
 */
String prepareHtmlPage() {
	String htmlPage =
		String("HTTP/1.1 200 OK\r\n") +
		"Content-Type: text/html\r\n" +
		"Connection: close\r\n" +  // the connection will be closed after completion of the response
		"Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
		"\r\n" +
		"<!DOCTYPE HTML>" +
		"<html>" +
		"Analog input:  " + String(analogRead(A0)) +
		"</html>" +
		"\r\n";
	return htmlPage;
}


void loop() {
	WiFiClient client = server.available();
	// wait for a client (web browser) to connect
	if (client) {
		Serial.println("\n[Client connected]");
		while (client.connected()) {
			// ���϶�ȡ��������
			if (client.available()) {
				String line = client.readStringUntil('\r');
				Serial.print(line);
				// wait for end of client's request, that is marked with an empty line
				if (line.length() == 1 && line[0] == '\n') {
					//������Ӧ����
					client.println(prepareHtmlPage());
					break;
				}
			}
			//�������������� Connection: close  ��������Ӧ����֮��ͻ��Զ��Ͽ�����
		}
		delay(100); // give the web browser time to receive the data

		// close the connection:
		client.stop();
		Serial.println("[Client disonnected]");
	}
}
