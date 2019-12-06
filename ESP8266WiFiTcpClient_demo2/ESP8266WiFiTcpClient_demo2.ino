/**
 * Demo��
 *    ��ʾHttp���������ӿ���Ϣ
 * @author ��Ƭ������
 * @date 2019/09/04
 *ԭ�����ӣ�https ://blog.csdn.net/dpjcn1990/article/details/92830087
 */
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


 //������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

const char* ssid = "space";         // XXXXXX -- ʹ��ʱ���޸�Ϊ��ǰ��� wifi ssid
const char* password = "12345678";         // XXXXXX -- ʹ��ʱ���޸�Ϊ��ǰ��� wifi ����
const char* host = "api.seniverse.com";
const char* APIKEY = "wcmquevztdy1jpca";        //API KEY
const char* city = "guangzhou";
const char* language = "zh-Hans";//zh-Hans ��������  ����ʾ����

const unsigned long BAUD_RATE = 115200;                   // serial connection speed
const unsigned long HTTP_TIMEOUT = 5000;               // max respone time from server
const size_t MAX_CONTENT_SIZE = 1000;                   // max size of the HTTP response

// ����Ҫ�Ӵ���ҳ����ȡ�����ݵ�����
struct WeatherData {
	char city[16];//��������
	char weather[32];//�������ܣ�����...��
	char temp[16];//�¶�
	char udate[32];//����ʱ��
};

WiFiClient client;
char response[MAX_CONTENT_SIZE];
char endOfHeaders[] = "\r\n\r\n";

void setup() {
	// put your setup code here, to run once:
	WiFi.mode(WIFI_STA);     //����esp8266 ����ģʽ
	DebugBegin(BAUD_RATE);
	DebugPrint("Connecting to ");//д������ʾ������
	DebugPrintln(ssid);
	WiFi.begin(ssid, password);   //����wifi
	WiFi.setAutoConnect(true);
	while (WiFi.status() != WL_CONNECTED) {
		//���������wifi����״̬������wifi����״̬
		delay(500);
		DebugPrint(".");
	}
	DebugPrintln("");
	DebugPrintln("WiFi connected");
	delay(500);
	DebugPrintln("IP address: ");
	DebugPrintln(WiFi.localIP());//WiFi.localIP()����8266��õ�ip��ַ
	client.setTimeout(HTTP_TIMEOUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	//�ж�tcp client�Ƿ�������״̬�����Ǿͽ�������
	while (!client.connected()) {
		if (!client.connect(host, 80)) {
			DebugPrintln("connection....");
			delay(500);
		}
	}
	//����http���� ����������Ӧͷ ֱ�ӻ�ȡ��Ӧbody
	if (sendRequest(host, city, APIKEY) && skipResponseHeaders()) {
		//�������
		clrEsp8266ResponseBuffer();
		//��ȡ��Ӧ����
		readReponseContent(response, sizeof(response));
		WeatherData weatherData;
		if (parseUserData(response, &weatherData)) {
			printUserData(&weatherData);
		}
	}
	delay(5000);//ÿ5s����һ��
}

/**
* @����http����ָ��
*/
bool sendRequest(const char* host, const char* cityid, const char* apiKey) {
	// We now create a URI for the request
	//��֪����  ����http����
	String GetUrl = "/v3/weather/now.json?key=";
	GetUrl += apiKey;
	GetUrl += "&location=";
	GetUrl += city;
	GetUrl += "&language=";
	GetUrl += language;
	// This will send the request to the server
	client.print(String("GET ") + GetUrl + " HTTP/1.1\r\n" +
		"Host: " + host + "\r\n" +
		"Connection: close\r\n\r\n");
	DebugPrintln("create a request:");
	DebugPrintln(String("GET ") + GetUrl + " HTTP/1.1\r\n" +
		"Host: " + host + "\r\n" +
		"Connection: close\r\n");
	delay(1000);
	return true;
}

/**
* @Desc ���� HTTP ͷ��ʹ��������Ӧ���ĵĿ�ͷ
*/
bool skipResponseHeaders() {
	// HTTP headers end with an empty line
	bool ok = client.find(endOfHeaders);
	if (!ok) {
		DebugPrintln("No response or invalid response!");
	}
	return ok;
}

/**
* @Desc ��HTTP��������Ӧ�ж�ȡ����
*/
void readReponseContent(char* content, size_t maxSize) {
	size_t length = client.peekBytes(content, maxSize);
	delay(100);
	DebugPrintln("Get the data from Internet!");
	content[length] = 0;
	DebugPrintln(content);
	DebugPrintln("Read data Over!");
	client.flush();//���һ�»���
}

/**
 * @Desc �������� Json����
 * ���ݸ�ʽ���£�
 * {
 *    "results": [
 *        {
 *            "location": {
 *                "id": "WX4FBXXFKE4F",
 *                "name": "����",
 *                "country": "CN",
 *                "path": "����,����,�й�",
 *                "timezone": "Asia/Shanghai",
 *                "timezone_offset": "+08:00"
 *            },
 *            "now": {
 *                "text": "����",
 *                "code": "4",
 *                "temperature": "23"
 *            },
 *            "last_update": "2017-09-13T09:51:00+08:00"
 *        }
 *    ]
 *}
 */
bool parseUserData(char* content, struct WeatherData* weatherData) {
	//    -- ����������Ҫ����������������JSON��������Ѵ�С
	//   �����ʹ��StaticJsonBufferʱ����Ҫ
	//    const size_t BUFFER_SIZE = 1024;
	//   �ڶ�ջ�Ϸ���һ����ʱ�ڴ��
	//    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
	//    -- �����ջ���ڴ��̫��ʹ�� DynamicJsonBuffer jsonBuffer ����
	DynamicJsonBuffer jsonBuffer;

	JsonObject& root = jsonBuffer.parseObject(content);

	if (!root.success()) {
		DebugPrintln("JSON parsing failed!");
		return false;
	}

	//�������Ǹ���Ȥ���ַ���
	strcpy(weatherData->city, root["results"][0]["location"]["name"]);
	strcpy(weatherData->weather, root["results"][0]["now"]["text"]);
	strcpy(weatherData->temp, root["results"][0]["now"]["temperature"]);
	strcpy(weatherData->udate, root["results"][0]["last_update"]);
	//  -- �ⲻ��ǿ�Ƹ��ƣ������ʹ��ָ�룬��Ϊ������ָ�����ݡ��������ڣ���������Ҫȷ��
	//   �����ȡ�ַ���ʱ�������ڴ���
	return true;
}

// ��ӡ��JSON����ȡ������
void printUserData(const struct WeatherData* weatherData) {
	DebugPrintln("Print parsed data :");
	DebugPrint("City : ");
	DebugPrint(weatherData->city);
	DebugPrint(", \t");
	DebugPrint("Weather : ");
	DebugPrint(weatherData->weather);
	DebugPrint(",\t");
	DebugPrint("Temp : ");
	DebugPrint(weatherData->temp);
	DebugPrint(" C");
	DebugPrint(",\t");
	DebugPrint("Last Updata : ");
	DebugPrint(weatherData->udate);
	DebugPrintln("\r\n");
}

// �ر���HTTP����������
void stopConnect() {
	DebugPrintln("Disconnect");
	client.stop();
}

void clrEsp8266ResponseBuffer(void) {
	memset(response, 0, MAX_CONTENT_SIZE);      //���
}
