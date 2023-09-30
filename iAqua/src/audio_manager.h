#include <Arduino.h>
#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_

namespace iAqua{
    namespace audio{
        void setupDFPlayer();
        void playAudioTrack(int track_number);
        void fadeOutSound();
        void playAudioTrackLoop(int track_number);


    }
}

#endif