#ifndef VITA_HW_AUDIO_DECODER_H
#define VITA_HW_AUDIO_DECODER_H

#include <stddef.h>
#include "vita_audio_types.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct VitaHwAudioDecoder VitaHwAudioDecoder;
typedef struct VitaHwAudioDecoderConfig {
 VitaAudioCodec codec; /* Native AAC or MP3; AC-3 is a software codec. */
 uint32_t channels, sample_rate;
 int input_is_adts;
} VitaHwAudioDecoderConfig;

VitaHwAudioDecoder *vita_hw_audio_decoder_create(void);
/* Reinitializes an existing object. Negative result: no decoder remains open. */
int vita_hw_audio_decoder_open(VitaHwAudioDecoder *, const VitaHwAudioDecoderConfig *);
/* 1: borrowed interleaved PCM16; 0: no output yet; negative: decode error.
 * One worker per object; copy PCM before the next decode/close call. */
int vita_hw_audio_decoder_decode(VitaHwAudioDecoder *, const uint8_t *, size_t, VitaDecodedAudio *);
void vita_hw_audio_decoder_close(VitaHwAudioDecoder *);
void vita_hw_audio_decoder_destroy(VitaHwAudioDecoder *);

#ifdef __cplusplus
}
#endif
#endif
