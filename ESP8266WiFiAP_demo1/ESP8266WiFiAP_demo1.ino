/**
 * Demo��
 *    APģʽ�£���ʾAP ����������ʹ��
 * @author ��Ƭ������
 * @date 2019/09/02
 *https://blog.csdn.net/dpjcn1990/article/details/92829923
 */
#include <ESP8266WiFi.h>

#define AP_SSID "AP_Test_����" //����ĳ����AP����
#define AP_PSW  "12345678" //����ĳ����AP���� 8λ����
 //������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

void setup() {
	//���ô��ڲ����ʣ��Ա��ӡ��Ϣ
	DebugBegin(115200);
	//��ʱ2s Ϊ����ʾЧ��
	delay(2000);
	DebugPrint("Setting soft-AP configuration ... ");
	//����AP��Ϣ
	WiFi.mode(WIFI_AP);
	DebugPrintln(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
	//����APģʽ���������˺ź�����
	DebugPrint("Setting soft-AP ... ");
	boolean result = WiFi.softAP(AP_SSID, AP_PSW);
	if (result) {
		DebugPrintln("Ready");
		//��� soft-ap ip��ַ
	//    DebugPrint(String("Soft-AP IP address = "));
	//    DebugPrintln(WiFi.softAPIP());
		DebugPrintln(String("Soft-AP IP address = ") + WiFi.softAPIP().toString());
		//��� soft-ap mac��ַ
		DebugPrintln(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
	}
	else {
		DebugPrintln("Failed!");
	}
	DebugPrintln("Setup End");
}

void loop() {
	//���ϴ�ӡ��ǰ��station����
	DebugPrintln(String("Stations connected =") + WiFi.softAPgetStationNum());
	delay(3000);
}