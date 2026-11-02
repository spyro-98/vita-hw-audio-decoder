#ifndef VITA_AUDIO_TYPES_H
#define VITA_AUDIO_TYPES_H
#include <stdint.h>
typedef enum VitaAudioCodec {VITA_AUDIO_CODEC_AAC=1,VITA_AUDIO_CODEC_MP3,VITA_AUDIO_CODEC_AC3} VitaAudioCodec;
typedef struct VitaDecodedAudio {
 const int16_t *pcm; /* interleaved signed PCM16, borrowed until next decode */
 uint32_t frames,channels,sample_rate;
} VitaDecodedAudio;
#endif
