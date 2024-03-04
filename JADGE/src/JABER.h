#include <SDL.h>

class JABER
{
    public:
        JABER();
        JABER(JABER*);
        bool init(SDL_Window*);
        void close();
        void update();
    private:
        SDL_Renderer* renderer;
};