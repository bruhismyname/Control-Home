#include "CTBot.h"
CTBot myBot;
CTBotReplyKeyboard Tbl;
CTBotInlineKeyboard TbLp1on, TbLp1off;

#define LampuLuar D1

#define LAMPU_LUAR_ON  "Lampu_Luar_ON"
#define LAMPU_LUAR_OFF  "Lampu_Luar_OFF"
#define TIDAK  "Tidak"

 String Status_Lampu_Luar;

 int Lampu_Luar = HIGH;

 bool TampilkanTombol;

 String ssid = "";
 String pass = "";
 String token = "";

void setup() {
  
Serial.begin(115200);                           
Serial.println("Memulai Koneksi...");

myBot.wifiConnect(ssid, pass);       
myBot.setTelegramToken(token);      

if (myBot.testConnection())   
    Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
else 
    Serial.println("\nTidak Terkoneksi Ke Telegram BOT"); 

pinMode(LampuLuar, OUTPUT);  

digitalWrite(LampuLuar, HIGH);      

Tbl.addButton("Lampu Luar");
Tbl.addRow();
Tbl.addButton("Cek Status");
Tbl.enableResize();
TampilkanTombol = false;

TbLp1on.addButton("✅ Ya", LAMPU_LUAR_ON, CTBotKeyboardButtonQuery);
TbLp1on.addButton("❌ Tidak", TIDAK, CTBotKeyboardButtonQuery);

TbLp1off.addButton("✅ Ya", LAMPU_LUAR_OFF, CTBotKeyboardButtonQuery);
TbLp1off.addButton("❌ Tidak", TIDAK, CTBotKeyboardButtonQuery);
}

void loop() {
TBMessage msg;

if (myBot.getNewMessage(msg)) {                                                           
  if (msg.text.equalsIgnoreCase("/start")) {                                         
        myBot.sendMessage(msg.sender.id, "Pembuat Program Rajwaa Muflihul Aufaa\nSelamat Datang Di Bot Kontrol Lampu.\n\nGunakan tombol dibawah untuk mengontrol lampu 👇", Tbl);
        Serial.println("\nUser memulai Bot \n");
        TampilkanTombol = true;
  } else if (msg.text.equalsIgnoreCase("Lampu Luar")) {
      if (Lampu_Luar == LOW) {
          myBot.sendMessage(msg.sender.id, "Saat ini Lampu Luar dalam keadaan ON\nApakah anda ingin mematikan Lampu Luar?", TbLp1off);
          Serial.println("\nUser mengirim perintah 'Lampu Luar' \nSaat ini Lampu Luar dalam keadaan ON \n");
      } else {
          myBot.sendMessage(msg.sender.id, "Saat ini Lampu Luar dalam keadaan OFF\nApakah anda ingin menyalakan Lampu Luar?", TbLp1on);
          Serial.println("\nUser mengirim perintah 'Lampu Luar' \nSaat ini Lampu Luar dalam keadaan OFF \n");            
      }
    } else if (msg.text.equalsIgnoreCase("Cek Status")) {
      if (Lampu_Luar == LOW) {
        Status_Lampu_Luar = "Lampu Luar ON";
      } else {
        Status_Lampu_Luar = "Lampu Luar OFF";
      }
      Serial.println("\nUser mengirim perintah 'Cek Status'\n");
      myBot.sendMessage(msg.sender.id, "Status saat ini : \n\n👉 " + Status_Lampu_Luar + "\n\nGunakan tombol dibawah untuk mengontrol lampu 👇", Tbl);
      Serial.println("\nStatus saat ini : \n\n👉 " + Status_Lampu_Luar + "\n");
    } else if (msg.messageType == CTBotMessageQuery) {
        if (msg.callbackQueryData.equals(LAMPU_LUAR_ON)) {
            digitalWrite(LampuLuar, LOW);
            Lampu_Luar = LOW;
            myBot.sendMessage(msg.sender.id, "💡 Lampu Luar Telah Dinyalakan");
            Serial.println("\nUser menyalakan Lampu Luar\n");
        } else if (msg.callbackQueryData.equals(LAMPU_LUAR_OFF)) {
            digitalWrite(LampuLuar, HIGH);
            Lampu_Luar = HIGH;
            myBot.sendMessage(msg.sender.id, "🚫 Lampu Luar Telah Dimatikan");
            Serial.println("\nUser mematikan Lampu Luar\n");
        } else if (msg.callbackQueryData.equals(TIDAK)) {
            myBot.sendMessage(msg.sender.id, "❌ Perintah Telah Dibatalkan!!!");
            Serial.println("\nUser telah membatalkan perintah\n");
        }
      } else {   
          myBot.sendMessage(msg.sender.id, "⛔️ ERROR: Perintah tidak dikenal?!\n\nGunakan tombol dibawah untuk mengontrol lampu 👇", Tbl);
          Serial.println("\nUser mengirim perintah yang tidak dikenal\n");
      }
  }
delay(500);
}