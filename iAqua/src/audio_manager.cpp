#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

namespace iAqua {
namespace audio {
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini DFPlayer;

void setupDFPlayer() {
  mySoftwareSerial.begin(9600);
  if (!DFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Error inicializando modulo mp3:"));
    Serial.println(F("1.Porfavor revisa las conexiones!"));
    Serial.println(F("2.Porfavor inserta memoria microSD!"));
  }
  Serial.println(F("Inicialización correcta DFPlayer."));
  DFPlayer.volume(30); // volúmen de 0 a 30
}

void playAudioTrack(int track_number) { DFPlayer.play(track_number); }

void fadeOutSound() {
    const int fade_out_delay = 1;
    const int stop_delay = 150;

  for (int i = 30; i >= 0; i--) {
    DFPlayer.volume(i);
    delay(fade_out_delay);
  }
  delay(stop_delay);
  DFPlayer.stop();
  delay(stop_delay);
  DFPlayer.volume(30);
  delay(stop_delay);
}

} // namespace audio
} // namespace iAqua