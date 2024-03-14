#pragma once

#include "Sprite.h"

struct AnimationKeyFrame
{
    int frame;
    int duration;
};

class SpriteAnimator : public Component
{
    public:
        SpriteAnimator();
        SpriteAnimator(SpriteAnimator*);
        ~SpriteAnimator();      
        void update();
    private:
        std::vector<AnimationKeyFrame> m_key_frames;
        std::unique_ptr<Sprite> m_sprite;
        bool m_loop;
};

