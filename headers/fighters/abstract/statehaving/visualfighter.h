#pragma once

class VisualFighter: public virtual Fighter
{
private:
	SDL::Texture& img;
public:
	VisualFighter(SDL::Texture& img):img(img){}
	virtual SDL::Texture& GetImage()const noexcept
	{
		return img;
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
    {
    	SDL::Rect dst(dst_pos, Fighter::size);
    	rend.Draw(img, nullptr, &dst, 0, IsReversed()?SDL::Renderer::Flip::Horizontal:SDL::Renderer::Flip::None);
    }
};