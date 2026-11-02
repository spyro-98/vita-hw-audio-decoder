# vita-hw-audio-decoder

Native AAC/MP3 decoding through the Vita `sceAudiodec` API. Audio API **1.0.0**, extracted for **VitaMediaDeck Beta 1.4.4**. The video backend remains independent.

## Use

Include `vita_hw_audio_decoder.h`, create an opaque decoder, open it with stream parameters, decode, then close or destroy it. Zero/designated-initialize configs. Returned PCM is borrowed until the next decode/receive or close; copy it before reuse. A decoder object is used by one worker at a time; join that worker before destruction. Closing twice and reopening the same object are safe.

The library does not own AudioOut, demux, volume, playback clocks or threads. VitaMediaDeck provides those once in `src/media/audio_playback.c`, including codec-specific grains (AAC 1024, MP3 576/1152, AC-3 1536), continuous PCM packing, EOF drain and cancellation.

## Build

Use VitaSDK and CMake. The CMake target is `VitaHwAudioDecoder::VitaHwAudioDecoder`.

This repository also owns the header-only `VitaAudioDecoder::Interface` contract. Video modules can import just its `interface/` subdirectory, without building or linking native audio. System AAC/MP3 initialization errors are returned to the caller, which decides whether a software audio fallback is appropriate.

Host regressions live in VitaMediaDeck `tests/multiaudio` and `tests/audio_volume`. Vita firmware calls are substituted on the host; physical audio output and A/V performance require console testing.

GPL-3.0-only. See [LICENSE](LICENSE). Development sources are published on the `main` branch; VitaMediaDeck pins an exact component commit in its dependency lock.
