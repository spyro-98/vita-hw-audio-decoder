#ifndef VMD_AUDIO_FORMATS_H
#define VMD_AUDIO_FORMATS_H
#include <libavcodec/codec_par.h>
/* The ordinal contract is shared by discovery, playback and track changes.
 * A zero channel/rate is probed later; known incompatible shapes stay hidden. */
static inline int vmd_audio_parameters_playable(const AVCodecParameters *p){
 if(!p||p->codec_type!=AVMEDIA_TYPE_AUDIO||p->sample_rate<0||p->sample_rate>48000)return 0;
 int channels=p->ch_layout.nb_channels;
 if(channels<0)return 0;
 if(p->codec_id==AV_CODEC_ID_AAC||p->codec_id==AV_CODEC_ID_MP3)return channels<=2;
 return p->codec_id==AV_CODEC_ID_AC3&&channels<=6;
}
#endif
