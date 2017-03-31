#pragma once

class Sound: public NonCopyable
{
private:
	struct Data
	{
		SDL::Audio::WAVBuffer buf;
		uint32 pos;
		bool play;
	};
	static constexpr Data* Cast(void* ptr)
	{
		return (Data*)ptr;
	}
	static void Callback(void* data, uint8* stream, int len)
	{
		if(Cast(data)->play)
		{
			if(Cast(data)->pos>=Cast(data)->buf.size())
			{
				memset(stream, 0, len);
				Cast(data)->pos=0;
				Cast(data)->play=false;
			}
			else
			{
				const uint32 size=min<uint32>(Cast(data)->buf.size()-Cast(data)->pos, len);
				memcpy(stream, Cast(data)->buf.data()+Cast(data)->pos, size);
				if(size<uint32(len))
				{
					memset(stream+size, 0, len-size);
					Cast(data)->pos=0;
					Cast(data)->play=false;
				}
				Cast(data)->pos+=size;
			}
		}
		else
		{
			memset(stream, 0, len);
		}
	}
	SDL::Audio format;
	SDL::AudioDevice player;
public:
	Sound(const string& file):format(48000, SDL::Audio::Format::U8, 1,0)
	{
		SDL::Audio::WAVBuffer buf;
		tie(format,buf)=format.LoadWAV(file);
		format.SetUserdata(new Data{func::Move(buf), 0, false});
		format.SetCallback(Callback);
		player.Open(format);
		player.Play();
	}
	void Play()
	{
		format.GetUserdata<Data>()->play=true;
		format.GetUserdata<Data>()->pos=0;
	}
	~Sound()
	{
		delete format.GetUserdata<Data>();
	}
};