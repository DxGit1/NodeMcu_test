/**
 * Demo��
 *    STAģʽ�£���ʾWiFiClient��TCP server֮���ͨ�Ź���
 *    ��ʵ����Ҫ��TCP��������һ��ʹ�á�
 * @author ��Ƭ������
 * @date 2019/1/25
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830087
 */
#include <ESP8266WiFi.h>

 //������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

#define AP_SSID "space" //����ĳ����wifi����
#define AP_PSW  "12345678"//����ĳ����wifi����

const uint16_t port = 8001;
const char * host = "192.168.3.70"; // ip or dns
WiFiClient client;//����һ��tcp client����

void setup() {
	//���ô��ڲ����ʣ��Ա��ӡ��Ϣ
	DebugBegin(115200);
	//��ʱ5s Ϊ����ʾЧ��
	delay(5000);
	// �Ҳ�����������ң�ֻ������վ��
	WiFi.mode(WIFI_STA);
	WiFi.begin(AP_SSID, AP_PSW);

	DebugPrint("Wait for WiFi... ");
	//�ȴ�wifi���ӳɹ�
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}

	DebugPrintln("");
	DebugPrintln("WiFi connected");
	DebugPrint("IP address: ");
	DebugPrintln(WiFi.localIP());

	delay(500);
}

void loop() {

	DebugPrint("connecting to ");
	DebugPrintln(host);

	if (!client.connect(host, port)) {
		DebugPrintln("connection failed");
		DebugPrintln("wait 5 sec...");
		delay(5000);
		return;
	}

	// �������ݵ�Tcp server
	DebugPrintln("Send this data to server");
	client.println(String("Send this data to server"));
	delay(1000);
	// �������ݵ�Tcp server
	DebugPrintln("Send this data to server");
	client.println(String("Send this data to server"));
	delay(1000);
	// �������ݵ�Tcp server
	DebugPrintln("Send this data to server");
	client.println(String("Send this data to server"));
	delay(1000);
	// �������ݵ�Tcp server
	DebugPrintln("Send this data to server");
	client.println(String("Send this data to server"));
	// �������ݵ�Tcp server
	DebugPrintln("Send this data to server");
	client.println(String("Send this data to server"));
	delay(1000);

	//��ȡ��server���ص���Ӧ����
	String line = client.readStringUntil('\r');
	DebugPrintln(line);

	DebugPrintln("closing connection");

	delay(5000);
	client.stop();

	DebugPrintln("wait 5 sec...");
	
}
