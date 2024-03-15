#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator()
{ }

SpriteAnimator::SpriteAnimator(SpriteAnimator* other)
{ }

SpriteAnimator::~SpriteAnimator()
{ }

void SpriteAnimator::update()
{
    m_current_frame++;
    if (m_current_frame > m_duration)
    {
        // for now just auto-loop
        m_current_frame = 0;
    }
}

SDL_Rect& SpriteAnimator::get_current_clip()
{
    return m_frames[m_timeline[m_current_frame]];
}

void SpriteAnimator::set_keyframes(std::vector<AnimationKeyFrame> key_frames)
{
    m_key_frames = key_frames;
    for(auto key_frame : m_key_frames)
    {
        for(int i = 0; i < key_frame.duration; i++)
        {
            m_timeline.insert(m_timeline.end(), key_frame.frame);
            m_duration++;
        }
    }
}

void SpriteAnimator::set_frames(std::vector<SDL_Rect> frames)
{
    m_frames = frames;
}