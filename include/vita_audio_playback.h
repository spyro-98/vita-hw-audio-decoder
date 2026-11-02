#ifndef VITA_AUDIO_PLAYBACK_H
#define VITA_AUDIO_PLAYBACK_H

#include <stddef.h>
#include <stdint.h>

struct AVFormatContext;
typedef struct VitaAudioPlayback VitaAudioPlayback;

/* Header-only session contract, shared by both video modules. The embedding
 * app owns workers, codec objects, PCM and AudioOut. Keep this driver alive
 * until the video session has closed. A missing driver means video-only. */
typedef struct VitaAudioPlaybackDriver {
 int (*start)(VitaAudioPlayback *, struct AVFormatContext *, int stream,
              uint64_t position_ms, volatile int *cancel, volatile int *gate);
 /* Join all workers and release implementation, including partial starts.
  * Safe on zeroed state and after a previous join. Never closes the demux. */
 void (*join)(VitaAudioPlayback *);
 void (*set_volume)(VitaAudioPlayback *, int percent);
} VitaAudioPlaybackDriver;

struct VitaAudioPlayback {
 const VitaAudioPlaybackDriver *driver;
 void *implementation;
 volatile int *cancel, *start_gate;
 volatile int had_error, eof, first_packet_ready;
 /* Readiness belongs to decoded PCM. EOF belongs to fully drained output. */
 volatile uint32_t first_packet_pts_ms, played_until_ms;
 volatile int first_packet_pts_valid, paused, stop, volume_percent, thread_done;
 int decoder_ready, port_open, started;
};

static inline int vita_audio_playback_start(
 VitaAudioPlayback *state, const VitaAudioPlaybackDriver *driver,
 struct AVFormatContext *demux, int stream, uint64_t position,
 volatile int *cancel, volatile int *gate) {
 if (!state || !driver || !driver->start || !driver->join || !driver->set_volume)
  return -1;
 state->driver = driver;
 return driver->start(state, demux, stream, position, cancel, gate);
}
static inline void vita_audio_playback_join(VitaAudioPlayback *state) {
 if (state && state->driver && state->driver->join) state->driver->join(state);
}
static inline void vita_audio_playback_set_volume(VitaAudioPlayback *state, int percent) {
 if (state && state->driver && state->driver->set_volume)
  state->driver->set_volume(state, percent);
}
static inline uint64_t vita_audio_playback_clock_us(const VitaAudioPlayback *state) {
 return state ? (uint64_t)__atomic_load_n(&state->played_until_ms, __ATOMIC_ACQUIRE) * 1000ULL : 0;
}
#endif
