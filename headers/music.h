#pragma once

class Music: public NonCopyable
{
private:
    SDL::Audio format;
    SDL::AudioDevice music_player;
    struct Data
    {
    	SDL::Audio::WAVBuffer buf;
        uint32 pos;
    };
public:
	Music(const string& file):format(48000, SDL::Audio::Format::U8, 1,0)
	{
		SDL::Audio::WAVBuffer music_buf;
		tie(format,music_buf)=format.LoadWAV(file);
		format.SetUserdata(new Data{func::Move(music_buf), 0});
		format.SetCallback([](void* userdata, uint8* stream, int len){
			Data* data=(Data*)userdata;
			const uint32 size=min<uint32>(data->buf.size()-data->pos, len);
			memcpy(stream, data->buf.data()+data->pos, size);
			data->pos+=size;
			if(size!=uint32(len))
			{
				data->pos=0;
				memcpy(stream+size, data->buf.data(), len-size);
			}
		});
		music_player.Open(format);
		music_player.Play();
	}
	~Music()
	{
        music_player.Close();
		delete format.GetUserdata<Data>();
	}
	void Start()
	{
		music_player.Play();
	}
	void Stop()
	{
		music_player.Pause();
	}
};