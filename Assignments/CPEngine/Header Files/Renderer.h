#pragma once
#include"GLib.h"
#include"SmartPointer.h"
#include"WeakPointer.h"
class GameObjects;
namespace Engine {
	namespace Renderer {
		GLib::Sprites::Sprite* CreateSprite(const char*);
		void* LoadFile(const char*, size_t&);
	}

	class Renderable {
	public:
		Renderable() = delete;
		Renderable(SmartPointer<GameObjects>, GLib::Sprites::Sprite*);
		~Renderable();

		bool DrawSprite();
	private:
		WeakPointer<GameObjects> m_gameObject;
		GLib::Sprites::Sprite* m_sprite;
	};
}