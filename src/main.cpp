#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>

// Cấu hình.
#define FIREBASE_HOST "fir-a8cb6-default-rtdb.firebaseio.com" //Đổi lại nhé
#define FIREBASE_AUTH "gHvTd9K7nLFvBOXBql5d5ybtAG3nJ4rSBbVZqGwP"
#define WIFI_SSID "OPPO A5 2020"
#define WIFI_PASSWORD "thuyen1524"

void setup()
{
  Serial.begin(115200);

  // Két nối wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop()
{
  // Set giá trị lưu vào db
  Firebase.setFloat("number", 42.0);
  // Kiểm tra lỗi
  if (Firebase.failed())
  {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);

  // Cập nhật giá trị
  Firebase.setFloat("number", 43.0);
  // Kiểm tra lỗi
  if (Firebase.failed())
  {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);

  // Lấy giá trị
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // Xóa giá trị
  Firebase.remove("number");
  delay(1000);

  // Thêm chuỗi
  Firebase.setString("message", "hello world");
  // Kiểm tra lỗi
  if (Firebase.failed())
  {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);

  // Thêm giá trị bool
  Firebase.setBool("truth", false);
  // Kiểm tra lỗi
  if (Firebase.failed())
  {
    Serial.print("setting /truth failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);

  // Lưu log
  String name = Firebase.pushInt("logs/temp", n++);
  // Kiểm tra lỗi
  if (Firebase.failed())
  {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
}