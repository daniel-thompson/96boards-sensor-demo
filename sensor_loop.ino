#include "DHT.h"
#include "Servo.h"

const int temp_sensor = A0;
const int light_sensor = A1;
const int rotary_sensor = A2;
const int touch_sensor = 3;
const int button_sensor = 4;

const int buzzer = 6;
const int led = 5;
const int servo = 7;

DHT dht(temp_sensor, DHT11);
unsigned long alarm;

Servo myservo;
unsigned long servo_alarm;

void setup() {
	Serial.begin(9600);

	pinMode(light_sensor, INPUT);
	pinMode(rotary_sensor, INPUT);
	pinMode(touch_sensor, INPUT);
	pinMode(button_sensor, INPUT);

	dht.begin();
	alarm = millis() + 1000;

	myservo.attach(7);
	servo_alarm = millis() + 2000;
}

void update() {
	int button_val = 1 - digitalRead(button_sensor);
	analogWrite(led, (analogRead(rotary_sensor) * button_val) / 4);
	digitalWrite(buzzer, digitalRead(touch_sensor));
	
}

void  loop() {
	update();


	if (millis() > alarm) {
		const int friendly = 0;
		float h = dht.readHumidity();
		float t = dht.readTemperature();

		if (isnan(h) || isnan(t)) {
			Serial.println("Failed to read from DHT");
		} else {
			Serial.print(friendly ? "Humidity: " : "H");
			update();
			Serial.println(h);
			update();

			Serial.print(friendly ? "Temperature: " : "T");
			update();
			Serial.println(t);
			update();
		}

		int light_val = analogRead(light_sensor);
		Serial.print(friendly ? "Light level: " : "L");
		update();
		Serial.println(light_val);
		update();

		int rotary_val = analogRead(rotary_sensor);
		Serial.print(friendly ? "Rotary position: " : "R");
		update();
		Serial.println(rotary_val);
		update();

		int touch_val = digitalRead(touch_sensor);
		Serial.print(friendly ? "Touch: " : "C");
		update();
		Serial.println(touch_val);
		update();

		int button_val = digitalRead(button_sensor);
		Serial.print(friendly ? "Button: " : "B");
		update();
		Serial.println(button_val);
		update();

		alarm += 1000;
	}

	if (millis() > servo_alarm) {
		int light_val = analogRead(light_sensor);
		light_val -= 200;
		if (light_val < 15)
			light_val = 15;
		light_val /= 3;
		myservo.write(light_val);

		servo_alarm += 15;
	}

}
