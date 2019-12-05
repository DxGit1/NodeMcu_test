/**
 * Demo��
 *    ����ESP8266 demo
 *    ��ӡESP8266ģ����Ϣ
 *    1.��ӡArduino Core For ESP8266 �汾,������2.4.2�汾
 *    2.��ӡFlash��Ψһ��оƬid�����߿���˼��һ���Ƿ������������ʲôΨһ�Բο���
 *    3.��ӡFlashʵ�ʴ�С
 *    4.��ӡIDE���õ�ʹ��Flash��С
 *    5.��ӡIDE���õ�Flash����ͨ�ŵ�Ƶ��
 *    6.��ӡFlash����ģʽ��QIO QOUT DIO DOUT���������ΪFlash��������
 * @author ��Ƭ������
 * @date 2018/10/22
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92829836
 */
void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	//ʹ��������Ź��Ĵ������
	ESP.wdtEnable(5000);
}

void loop() {
	//ι��
	ESP.wdtFeed();
	FlashMode_t ideMode = ESP.getFlashChipMode();
	String coreVersion = ESP.getCoreVersion();
	Serial.print(F("Arduino Core For ESP8266 Version: "));
	Serial.println(coreVersion);
	Serial.printf("Flash real id��Ψһ��ʶ����:   %08X\n", ESP.getFlashChipId());
	Serial.printf("Flash ʵ�ʴ�С: %u KBytes\n", ESP.getFlashChipRealSize() / 1024);
	Serial.printf("IDE����Flash��С: %u KBytes,����С��ʵ�ʴ�С\n", ESP.getFlashChipSize() / 1024);
	Serial.printf("IDE����FlashƵ�� : %u MHz\n", ESP.getFlashChipSpeed() / 1000000);
	Serial.printf("Flash ide mode:  %s\n\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));

	delay(1000);
}

