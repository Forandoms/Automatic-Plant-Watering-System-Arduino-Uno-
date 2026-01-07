/*
 * Proje: Otomatik Sulama (Sürekli Geri Beslemeli) ve LDR Kontrolü
 * Bileşenler: HW-103 (Nem), LDR Modülü, SG90, LED
 * * MANTIK:
 * 1. SULAMA: Nem sensörü sürekli okunur. Toprak kuru olduğu sürece vana AÇIK (90°) kalır.
 * Nem algılandığı anda vana KAPALI (0°) pozisyonuna döner.
 * 2. AYDINLATMA: Ortamda ışık varsa LED söner, yoksa yanar (Sulama durumundan bağımsız).
 */

#include <Servo.h>

// --- Pin Atamaları ---
const int NEM_SENSOR_PIN = A0;  // Analog Nem Girişi
const int LDR_PIN = 8;          // Dijital Işık Girişi
const int SERVO_PIN = 9;        // Servo Sinyal
const int LED_PIN = 7;          // Aydınlatma LED'i

// --- Kalibrasyon Değerleri ---
// Nem sensörü havada (kuru) iken genelde 1023'e yakın, suda 300-400 civarıdır.
// 600 değeri, toprağın "kurumaya başladığı" eşik noktasıdır.
const int KURULUK_ESIK_DEGERI = 600; 

// --- Servo Açıları ---
const int POZISYON_KAPALI_X = 0;   // Vana kapalı (Başlangıç)
const int POZISYON_ACIK_Y = 180;    // Vana açık (Sulama)

Servo sulamaServosu;

void setup() {
  Serial.begin(9600);
  
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  sulamaServosu.attach(SERVO_PIN);
  sulamaServosu.write(POZISYON_KAPALI_X); // Başlangıçta sistemi kapalı tut.
  
  Serial.println("Sistem Devrede: Surekli nem ve isik kontrolu basladi.");
}

void loop() {
  // --- A. Sensör Verilerini Oku ---
  int nemDegeri = analogRead(NEM_SENSOR_PIN);
  int isikDurumu = digitalRead(LDR_PIN);

  // --- B. Işık ve LED Kontrolü (Bağımsız Döngü) ---
  // LDR Modül mantığı: Genellikle ışık varken 0 (LOW), yokken 1 (HIGH) verir.
  if (isikDurumu == HIGH) {
    // Işık YOK -> LED YANSIN
    digitalWrite(LED_PIN, HIGH);
  } else {
    // Işık VAR -> LED SÖNSÜN
    digitalWrite(LED_PIN, LOW);
  }

  // --- C. Nem ve Motor Kontrolü (Sürekli Geri Besleme) ---
  // Eşik değerinin üzeri "KURU" anlamına gelir.
  
  if (nemDegeri > KURULUK_ESIK_DEGERI) {
    // DURUM: Toprak Kuru (Nem Yok)
    // Eylem: Motor Y pozisyonuna (90 derece) gelsin ve orada kalsın.
    
    // Servo zaten 90'da değilse hareket ettir (Gereksiz titremeyi önler)
    if (sulamaServosu.read() != POZISYON_ACIK_Y) {
      sulamaServosu.write(POZISYON_ACIK_Y);
      Serial.println("Toprak Kuru -> Vana ACILDI (90 Derece)");
    }
    
  } else {
    // DURUM: Toprak Islak (Nem Var)
    // Eylem: Motor X pozisyonuna (0 derece) dönsün.
    
    if (sulamaServosu.read() != POZISYON_KAPALI_X) {
      sulamaServosu.write(POZISYON_KAPALI_X);
      Serial.println("Nem Algilandi -> Vana KAPATILDI (0 Derece)");
    }
  }

  // Çok hızlı döngüyü engellemek ve ADC kararlılığı için kısa bekleme
  delay(100);
}