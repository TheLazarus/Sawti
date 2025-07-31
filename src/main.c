#include <stdio.h>
#include <math.h>
#include "include/portaudio.h"

#define NUM_SECONDS 5
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 64
#define TABLE_SIZE 200
#define MY_PI 3.14159265

typedef struct
{
    float sine[200];
    int left_phase;
    int right_phase;
    char message[20];
} paTestData;

void populate_sinTable(paTestData *data)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        data->sine[i] = (float)sin(((double)i / (double)TABLE_SIZE) * MY_PI * 2);
    }
    data->left_phase = data->right_phase = 0;
}

void paTestCallback()
{
}

int main()
{
    PaStreamParameters outputParams;
    PaStream *stream;
    PaError err;
    paTestData data;
    int i;

    printf("PortAudio Test: output sine wave. Sample Rate = %d, Buffer Size = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);
    populate_sinTable(&data);

    printf("Initializing portaudio...\n");
    if (Pa_Initialize() != paNoError)
    {
        printf("Failed to initialize portaudio\n");
        return -1;
    }
    printf("Portaudio successfully initialized!\n");
    outputParams.device = Pa_GetDefaultOutputDevice();

    if (outputParams.device == paNoDevice)
    {
        fprintf(stderr, "Failed to get the default output device\n");
        return -1;
    }

    printf("Found the default audio device\n");
    outputParams.channelCount = 2;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;

    if (Pa_OpenStream(&stream, NULL, &outputParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, paTestCallback, &data) != paNoError)
    {
        fprintf(stderr, "Failed to open portaudio stream\n");
        return -1;
    }

    printf("Successfully opened audio stream\n");
    return 0;
}