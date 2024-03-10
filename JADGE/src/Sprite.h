#pragma once
#include "Component.h"
#include "Renderable.h"
#include "Transform.h"

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class Sprite : public Component, public Renderable
{
    public:
        Sprite();
        ~Sprite();
        ComponentType getComponentType();
        bool loadFromFile(std::string aPath, SDL_Renderer* aRenderer);
        bool loadFromRenderedText(std::string aTextureText, SDL_Color aTextColor, SDL_Renderer* aRenderer, TTF_Font* aFont);
        void free();
        // void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode aBlending);
        void setAlpha(Uint8 aNewAlpha);
        // void render(std::tuple<int, int> aPosition, SDL_Rect* aClip = NULL);
        int getWidth();
        int getHeight();
        void update();
        void set_parent(GameObject& parent);
        SDL_Texture* get_texture();
        SDL_Rect* get_clip();
        GameObject* get_gameobject();
        const SDL_Rect* get_render_quad();
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
        SDL_Rect* m_clip;
        Transform* m_transform;
};