#pragma once
#include "Component.h"
#include "Renderable.h"
#include "Transform.h"
#include "SpriteAnimator.h"

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class Sprite : public Component, public Renderable
{
    public:
        Sprite(const Transform&);
        ~Sprite();
        ComponentType get_component_type();
        bool load_from_file(std::string, SDL_Renderer*);
        bool load_from_rendered_text(std::string, SDL_Color, SDL_Renderer*, TTF_Font*);
        void free();
        // void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void set_blend_mode(SDL_BlendMode);
        void set_alpha(Uint8);
        void set_clip(SDL_Rect&);
        int get_width();
        int get_height();
        void set_size(int, int);
        void update();
        void add_animator(SpriteAnimator*);
        SDL_Texture* get_texture();
        SDL_Rect* get_clip();
        const SDL_Rect* get_render_quad();
    private:
        const Transform& m_transform;
        std::unique_ptr<SpriteAnimator> m_animator;
        SDL_Texture* m_texture;
        int m_width;
        int m_height;
        SDL_Rect* m_clip;
        SDL_Rect m_render_quad;
};