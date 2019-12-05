/**
 * Demo��
 *    STAģʽ�£���ʾ�첽ɨ��Scan wifi����
 * @author ��Ƭ������
 * @date 2019/09/03
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830044
 */
#include <ESP8266WiFi.h>

 //������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

/**
 * ��ӡɨ����
 * @param networksFound �������
 */
void prinScanResult(int networksFound) {
	Serial.printf("%d network(s) found\n", networksFound);
	for (int i = 0; i < networksFound; i++)
	{
		Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
	}
}

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
	Serial.print("\nScan start ... ");
	WiFi.scanNetworksAsync(prinScanResult);
}

void loop() {
}
