#include <SDL_image.h>

#include "Sprite.h"

Sprite::Sprite(const Transform& transform)
 : m_transform(transform)
{
    m_animator = nullptr;
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
}

Sprite::~Sprite()
{
    // Deallocate
    free();
}

ComponentType Sprite::get_component_type()
{
    return ComponentType::SPRITE;
}

bool Sprite::load_from_file(std::string path, SDL_Renderer* renderer)
{
    // get rid of pre-existing texture
    free();

    // the final texture
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // get image dimensions
            m_width = loadedSurface->w;
            m_height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    // return sucess
    m_texture = newTexture;
    return m_texture != NULL;
}

bool Sprite::load_from_rendered_text(std::string aTextureText, SDL_Color aTextColor, SDL_Renderer* aRenderer, TTF_Font* aFont)
{
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(aFont, aTextureText.c_str(), aTextColor);
    if (textSurface == NULL)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        m_texture = SDL_CreateTextureFromSurface(aRenderer, textSurface);
        if (m_texture == NULL)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            m_width = textSurface->w;
            m_height = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    return m_texture != NULL;
}

void Sprite::free()
{
    // free texture if it exists
    if (m_texture != NULL)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}

void Sprite::set_alpha(Uint8 newAlpha)
{
    SDL_SetTextureAlphaMod(m_texture, newAlpha);
}

void Sprite::set_blend_mode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(m_texture, blending);
}

int Sprite::get_width()
{
    return m_width;
}

int Sprite::get_height()
{
    return m_height;
}

void Sprite::update()
{ 
    if (m_animator != nullptr)
    {
        m_animator->update();
    }
}

SDL_Texture* Sprite::get_texture()
{
    return m_texture;
}

SDL_Rect* Sprite::get_clip()
{
    if (m_animator != nullptr)
    {
        m_clip = m_animator->get_current_clip();
    }
    return m_clip;
}

const SDL_Rect* Sprite::get_render_quad()
{
    int x;
    int y;
    std::tie(x, y) = m_transform.get_position();
    m_render_quad = {x, y, m_width, m_height};
    return &m_render_quad;
}

void Sprite::set_size(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Sprite::set_clip(SDL_Rect& new_clip)
{
    m_clip = new SDL_Rect(new_clip);
}

void Sprite::add_animator(SpriteAnimator* animator)
{
    m_animator = std::make_unique<SpriteAnimator>(animator);
}
