/**
 * Demo��
 *    STAģʽ�£���ʾͬ��ɨ��Scan wifi����
 * @author ��Ƭ������
 * @date 2019/09/03
 ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830044
 */
#include <ESP8266WiFi.h>

 //������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

void setup() {
	//���ô��ڲ����ʣ��Ա��ӡ��Ϣ
	DebugBegin(115200);
	//��ʱ5s Ϊ����ʾЧ��
	delay(5000);
	// �Ҳ�����������ң�ֻ������վ��
	WiFi.mode(WIFI_STA);
	//�Ͽ�����
	WiFi.disconnect();
	delay(100);
	DebugPrintln("Setup done");
}

void loop() {
	DebugPrintln("scan start");
	// ͬ��ɨ�裬�ȴ����ؽ��
	int n = WiFi.scanNetworks();
	DebugPrintln("scan done");
	if (n == 0) {
		DebugPrintln("no networks found");
	}
	else {
		DebugPrint(n);
		DebugPrintln(" networks found");
		for (int i = 0; i < n; ++i) {
			DebugPrint(i + 1);
			DebugPrint(": ");
			//��ӡwifi�˺�
			DebugPrint(WiFi.SSID(i));
			DebugPrint(",");
			DebugPrint(String("Ch:") + WiFi.channel(i));
			DebugPrint(",");
			DebugPrint(WiFi.isHidden(i) ? "hide" : "show");
			DebugPrint(" (");
			//��ӡwifi�ź�ǿ��
			DebugPrint(WiFi.RSSI(i));
			DebugPrint("dBm");
			DebugPrint(")");
			//��ӡwifi���ܷ�ʽ
			DebugPrintln((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "open" : "*");
			delay(10);
		}
	}
	DebugPrintln("");
	// ��ʱ5s֮���ٴ�ɨ��
	delay(5000);
}
