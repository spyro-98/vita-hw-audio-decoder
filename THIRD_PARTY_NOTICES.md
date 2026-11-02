# Third-party notices

This module is extracted from VitaMediaDeck's former `vita-hw-decoder` package and retains GPL-3.0-only licensing. See LICENSE. The PlayStation Vita firmware API is called through VitaSDK; no Sony firmware binary is distributed here.

The implementation uses public SceAudiodec declarations. Shared optional FFmpeg format helpers use FFmpeg public headers; native audio decoding does not link FFmpeg or software codecs.
