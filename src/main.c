#include <stdio.h>
#include "include/portaudio.h"

int main()
{

    printf("Initializing portaudio...\n");
    if (Pa_Initialize() != paNoError)
    {
        printf("Failed to initialize portaudio\n");
        return -1;
    }
    printf("Portaudio successfully initialized!\n");
    return 0;
}