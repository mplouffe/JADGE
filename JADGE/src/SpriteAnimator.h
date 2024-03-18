#pragma once

#include <SDL.h>
#include <vector>

struct AnimationKeyFrame
{
    int frame;
    int duration;
};

class SpriteAnimator
{
    public:
        SpriteAnimator();
        SpriteAnimator(SpriteAnimator*);
        void set_keyframes(std::vector<AnimationKeyFrame>);
        void set_frames(std::vector<SDL_Rect>);
        void update();
        SDL_Rect* get_current_clip();
    private:
        std::vector<AnimationKeyFrame> m_key_frames;
        std::vector<SDL_Rect> m_frames;
        std::vector<int> m_timeline;
        bool m_loop;
        int m_current_frame;
};

