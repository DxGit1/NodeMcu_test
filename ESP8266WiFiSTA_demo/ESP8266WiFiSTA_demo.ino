/**
 * Demo3��
 *    statinģʽ�£�����һ�����ӵ��ɽ���㣨wifi�ȵ㣩�����Ҵ�ӡstation��Ϣ
 * @author ��Ƭ������
 * @date 2019/09/02
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92829934
 */
#include <ESP8266WiFi.h>

#define AP_SSID "space" //����ĳ����wifi����
#define AP_PSW  "12345678" //����ĳ����wifi����
 //������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

void setup() {
	//���ô��ڲ����ʣ��Ա��ӡ��Ϣ
	DebugBegin(115200);
	//��ʱ2s Ϊ����ʾЧ��
	delay(2000);
	DebugPrintln("Setup start");
	//����STAģʽ�������ӵ�wifi����
	WiFi.begin(AP_SSID, AP_PSW);
	//�����Զ�����
	WiFi.setAutoConnect(true);
	//�����Զ�����
	WiFi.setAutoReconnect(true);
	DebugPrint(String("Connecting to ") + AP_SSID);
	//�ж�����״̬�Ƿ������ϣ�û�����Ͼ���ʱ500ms�����Ҵ��һ���㣬ģ�����ӹ���
	//������չ����������һֱ�������� �Ƿ���������жϣ��������Լ�ʵ��
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		DebugPrint(".");
	}
	DebugPrintln("");

	DebugPrintln("rint Network Info:");
	if (WiFi.status() == WL_CONNECTED) {
		//���mac��ַ
		DebugPrintln(String("Connected, mac address: ") + WiFi.macAddress().c_str());

		//���station IP��ַ�������IP��ַ��DHCP����
		DebugPrintln(String("Connected, IP address: ") + WiFi.localIP().toString());

		//������������ַ
		DebugPrintln(String("Subnet mask: ") + WiFi.subnetMask().toString());

		//������� IP��ַ
		DebugPrintln(String("Gataway IP: ") + WiFi.gatewayIP().toString());

		//���hostname
		DebugPrintln(String("Default hostname: ") + WiFi.hostname());
		//�����µ�hostname
		WiFi.hostname("Station_host_����");
		DebugPrintln(String("New hostname: ") + WiFi.hostname());

		//���SSID
		DebugPrintln(String("SSID: ") + WiFi.SSID());

		//���psk
		DebugPrintln(String("psk: ") + WiFi.psk());

		//���BSSID
		DebugPrintln(String("BSSID: ") + WiFi.BSSIDstr());

		//���RSSI
		DebugPrintln(String("RSSI: ") + WiFi.RSSI() + " dBm");
	}

	DebugPrintln("Setup End");
}

void loop() {
}

