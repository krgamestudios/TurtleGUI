/* Copyright: (c) Kayne Ruse 2013-2016
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "render_text_texture.hpp"

#include <stdexcept>

SDL_Texture* renderTextTexture(SDL_Renderer* const renderer, TTF_Font* font, SDL_Color color, std::string str) {
	//make the surface (from SDL_ttf)
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);
	if (!surface) {
		throw(std::runtime_error("Failed to create a TTF surface"));
	}

	//convert to texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	//cleanup
	SDL_FreeSurface(surface);

	//check
	if (!texture) {
		throw(std::runtime_error("Failed to create a TTF texture"));
	}

	//NOTE: free the texture yourself
	return texture;
}

void renderTextDirect(SDL_Renderer* const renderer, TTF_Font* font, SDL_Color color, std::string str, int x, int y) {
	int w = 0, h = 0;
	SDL_Texture* tmpTex = renderTextTexture(renderer, font, color, str);
	SDL_QueryTexture(tmpTex, nullptr, nullptr, &w, &h);
	SDL_Rect dclip = {x, y, w, h};
	SDL_RenderCopy(renderer, tmpTex, nullptr, &dclip);
	SDL_DestroyTexture(tmpTex);
}
