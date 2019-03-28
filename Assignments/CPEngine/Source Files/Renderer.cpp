#include"Renderer.h"
#include"GLib.h"
#include"GameObject.h"
#include"Point2D.h"
#include<iostream>
#include<assert.h>
#include "SmartPointer.h"
#include"WeakPointer.h"

namespace Engine {
#pragma region Sprite Rendering Functions
	namespace Renderer {
		GLib::Sprites::Sprite* CreateSprite(const char* i_spriteFileName) {
			assert(i_spriteFileName);

			size_t textureFileSize = 0;

			void * textureFile = LoadFile(i_spriteFileName, textureFileSize);

			GLib::Texture* texture = textureFile ? GLib::CreateTexture(textureFile, textureFileSize) : nullptr;

			//Dereferencing the Texture files after they are used
			assert(textureFile);
			delete[] textureFile;

			if (texture == nullptr) {
				return nullptr;
			}

			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int breath = 0;

			bool result = GLib::GetDimensions(texture, width, height, breath);

			assert(result);
			assert((height > 0) && (width > 0));

			GLib::Sprites::SpriteEdges edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
			GLib::Sprites::SpriteUVs uv = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
			GLib::RGBA color = { 255, 255, 255, 255 };

			GLib::Sprites::Sprite* sprite = GLib::Sprites::CreateSprite(edges, 0.1f, color, uv);

			if (sprite == nullptr) {
				GLib::Release(texture);
				return nullptr;
			}

			GLib::Sprites::SetTexture(*sprite, *texture);

			return sprite;
		}

		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile) {
			assert(i_pFilename != NULL);

			FILE * pFile = NULL;
			errno_t fopenError = NULL;
			fopenError = fopen_s(&pFile, i_pFilename, "rb");
			if (fopenError != 0)
				return NULL;

			assert(pFile != NULL);

			int FileIOError = fseek(pFile, 0, SEEK_END);
			assert(FileIOError == 0);

			long FileSize = ftell(pFile);
			assert(FileSize >= 0);

			FileIOError = fseek(pFile, 0, SEEK_SET);
			assert(FileIOError == 0);

			uint8_t * pBuffer = new uint8_t[FileSize];
			assert(pBuffer);

			size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
			assert(FileRead == FileSize);

			fclose(pFile);

			o_sizeFile = FileSize;

			return pBuffer;
		}
	}
#pragma endregion

#pragma region Overload Methods

	Renderable::Renderable(SmartPointer<GameObjects> i_object, GLib::Sprites::Sprite* i_sprite): m_gameObject(i_object), m_sprite(i_sprite) 
	{}
	
	Renderable::~Renderable() {
		/*if (m_gameObject) {
			delete m_gameObject;
		}*/
		if (m_sprite) {
			GLib::Sprites::Release(m_sprite);
		}
	}

#pragma endregion

#pragma region Draw Function
	/**
	Draws the sprites into the scene
	@returns true if drawing is successfull else return false
	*/
	bool Renderable::DrawSprite() {
		
		GLib::BeginRendering();
		GLib::Sprites::BeginRendering();

		if (m_gameObject != nullptr) {
			//starts Rendering of Sprites 
			SmartPointer<GameObjects> tempObject = m_gameObject.AquireOwnership();

			GLib::Point2D temp = { tempObject->Location().X(), tempObject->Location().Y() };
			GLib::Sprites::RenderSprite(*m_sprite, temp, 0.0f);
		} else {
			return false;
		}

		//End Rendering of Sprites
		GLib::Sprites::EndRendering();
		GLib::EndRendering();
		
		return true;
	}
#pragma endregion

}