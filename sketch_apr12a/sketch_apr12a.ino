#include <Servo.h>// servo motor kütüphanesi
#include <NewPing.h>//ultrasonik sensör kütüphanesi
String voice;
//motor pinleri
#define SolMotorileri 6
#define SolMotorGeri 5
#define SagMotorileri 8
#define SagMotorGeri 9
#define led 53
#define ledmavi 51
#define ledyesil 49
#define ledkirmizi 45
#define ledvcc 47
  
//sensör pinleri
#define USTrigger 3
#define USEcho 2
#define Maksimum_uzaklik 100
  
Servo servo; //servo motor tanımlama
NewPing sonar(USTrigger, USEcho, Maksimum_uzaklik);//ultrasonik sensör tanımlama
//kullanılacak eleman tanımı
unsigned int uzaklik;
unsigned int on_uzaklik;
unsigned int sol_uzaklik;
unsigned int sag_uzaklik;
unsigned int zaman;
// program ilk çalıştığında sadece bir kez çalışacak programlar
void setup()
{
Serial.begin(9600); //iletişim ayarı
//motor çıkışları
pinMode(SolMotorileri, OUTPUT);
pinMode(SolMotorGeri, OUTPUT);
pinMode(SagMotorileri, OUTPUT);
pinMode(SagMotorGeri, OUTPUT);
pinMode(led, OUTPUT);
pinMode(ledkirmizi, OUTPUT);
pinMode(ledmavi, OUTPUT);
pinMode(ledyesil, OUTPUT);
pinMode(ledvcc, OUTPUT);
  
servo.attach(4); //servo pin tanımı
}
// sonsuz döngü
void loop() {
while (Serial.available()){ //Okumak için kullanılabilir bayt olup olmadığını kontrol et
delay(10); //10 milisaniye bekle
char c = Serial.read(); //Seri okuma
if (c == '#') {break;} // # tespit edildiğinde döngüden çık
voice += c; //Ses = ses + c Steno
}
if (voice.length() > 0) {
Serial.println(voice);
  
if(voice == "*ileri"||voice == "*ileri git") {ileri();}
else if(voice == "*geri"||voice == "*geri gel"){geri();}
else if(voice == "*sağa dön"||voice == "*sağ") {sag();}
else if(voice == "*sola dön"||voice == "*sol") {sol();}
else if(voice == "*dur"||voice == "*arabayı durdur") {dur();}
else if(voice == "*sol ileri"){sol(); delay(100); ileri();}
else if(voice == "*sağ ileri"){sag(); delay(100); ileri();}
else if(voice == "*sol geri"){sol(); delay(100); geri();}
else if(voice == "*sag geri"){sag(); delay(100); geri();}
else if(voice == "*ileri git dur"||voice == "*biraz ileri git") {ileri(); delay(500); dur();}
else if(voice == "*geri gel dur"||voice == "*biraz geri gel") {geri(); delay(500); dur();}
else if(voice == "*sola dön dur"||voice == "*biraz sola dön") {sol(); delay(500); dur();}
else if(voice == "*sağa dön dur"||voice == "*biraz sağa dön") {sag(); delay(500); dur();}
else if(voice == "*sola bak"||voice == "*soluna bak") {solabak();}
else if(voice == "*sağa bak"||voice == "*sağına bak") {sagabak();}
else if(voice == "*önüne bak"||voice == "*öne bak") {onunebak();}
else if(voice == "*ışığı aç"||voice == "*ledi yak") {ledyak();}
else if(voice == "*ışığı kapat"||voice == "*ledi söndür") {digitalWrite(51,HIGH); digitalWrite(49,HIGH); digitalWrite(45,HIGH); digitalWrite(47,LOW);}
else if(voice == "*kırmızı") {digitalWrite(45,LOW); digitalWrite(49,HIGH); digitalWrite(51,HIGH); digitalWrite(47,HIGH);}
else if(voice == "*yeşil") {digitalWrite(49,LOW); digitalWrite(45,HIGH); digitalWrite(51,HIGH); digitalWrite(47,HIGH); }
else if(voice == "*mavi") {digitalWrite(51,LOW); digitalWrite(49,HIGH); digitalWrite(45,HIGH); digitalWrite(47,HIGH);}
else if(voice == "*mor") {digitalWrite(51,LOW); digitalWrite(49,HIGH); digitalWrite(45,LOW); digitalWrite(47,HIGH);}
else if(voice == "*beyaz") {digitalWrite(51,LOW); digitalWrite(49,LOW); digitalWrite(45,LOW); digitalWrite(47,HIGH);}
else if(voice == "*engel"||voice == "*engel algıla"){engel();}
  
voice="";}}
  
// robotun yön komutları
void ileri()
{
digitalWrite(SolMotorGeri, LOW);
digitalWrite(SolMotorileri, HIGH);
digitalWrite(SagMotorGeri, LOW);
digitalWrite(SagMotorileri, HIGH);
}
  
void geri()
{
digitalWrite(SolMotorileri, LOW);
digitalWrite(SolMotorGeri, HIGH);
digitalWrite(SagMotorileri, LOW);
digitalWrite(SagMotorGeri, HIGH);
}
  
void sag()
{
digitalWrite(SolMotorileri, LOW);
digitalWrite(SolMotorGeri, HIGH);
digitalWrite(SagMotorGeri, LOW);
digitalWrite(SagMotorileri, HIGH);
}
  
void sol()
{
digitalWrite(SolMotorGeri, LOW);
digitalWrite(SolMotorileri, HIGH);
digitalWrite(SagMotorileri, LOW);
digitalWrite(SagMotorGeri, HIGH);
}
  
void dur()
{
digitalWrite(SolMotorGeri, LOW);
digitalWrite(SolMotorileri, LOW);
digitalWrite(SagMotorileri, LOW);
digitalWrite(SagMotorGeri, LOW);
}
void sagabak()
{
servo.write(0);
delay(100);
}
void solabak()
{
servo.write(180);
delay(100);
}
void onunebak()
{
servo.write(90);
delay(100);
}
void ledyak()
{
digitalWrite(53,HIGH);
}
void ledkapat()
{
digitalWrite(53,LOW);
}
// sensörün mesafe ölçümü
void sensor_olcum()
{
delay(50);
zaman = sonar.ping();
uzaklik = zaman / US_ROUNDTRIP_CM;
}
void engel()
{
delay(500);
servo.write(90);
sensor_olcum();
on_uzaklik = uzaklik;
if(on_uzaklik > 35 || on_uzaklik == 0)
{
ileri();
}
else
{
dur();
servo.write(180);
delay(500);
sensor_olcum();
sol_uzaklik = uzaklik;
servo.write(0);
delay(500);
sensor_olcum();
sag_uzaklik = uzaklik;
servo.write(90);
delay(500);
if(sag_uzaklik < sol_uzaklik)
{
sol();
delay(500);
ileri();
}
else if(sol_uzaklik < sag_uzaklik)
{
sag();
delay(500);
ileri();
}
else
{
geri();
}
}
}
