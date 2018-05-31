//AudioEngine.cpp
//LUMACAL 2018

#include <thread>
#include <iostream>
#include "AudioEngine.h"
#include <portsf.h>
#include <tinyAudioLib.h>

#define FRAME_BLOCK_LEN 512

namespace Somnium {
    namespace Audio {
        
        AudioEngine::AudioEngine() {
            
        }
        
        void AudioEngine::stop() {
            
        }
        
        void AudioEngine::start() {
            
        }
        
        void AudioEngine::playSound(char *file) {
            float buf[FRAME_BLOCK_LEN*2];
            int sfd; //descriptor
            PSF_PROPS props; //file info
            long nread; //Frames read
            
            if(file==0) { //Require input
                printf("No file supplied\n");
            } else {
                printf("%s\n", file);
                psf_init(); //Init portsf
                sfd = psf_sndOpen(file, &props, 0); //Open file
                
                if(sfd < 0) { //File not read?
                    printf("Error occured while opening: %d\n", sfd);
                } else {
                    if(props.chans > 2) { //2 channel max
                        printf("Invalid no. channels\n");
                    } else {
                        do {
                            nread = psf_sndReadFloatFrames(sfd, buf, FRAME_BLOCK_LEN);
                            if(props.chans == 2) //Stereo
                                outBlockInterleaved(buf, FRAME_BLOCK_LEN);
                            else //Mono
                                outBlockMono(buf, FRAME_BLOCK_LEN);
                        } while(nread == FRAME_BLOCK_LEN);
                    }
                }
                printf("finished");
                psf_sndClose(sfd);//Close file
                psf_finish();
            }
        }
    }
}
