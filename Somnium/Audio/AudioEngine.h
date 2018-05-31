//AudioEngine.h
//LUMACAL 2018

#pragma once

namespace Somnium {
    namespace Audio {
        class AudioEngine {
        public:
            AudioEngine(void);
            
            void start(void);
            void stop(void);
            
            void playSound(char*); //Play single audio file
        };
    }
}

