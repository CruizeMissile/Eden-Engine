#ifndef H_GAME_WINDOW_H
#define H_GAME_WINDOW_H

#include "Precompiled.h"
#include "SDL2\SDL.h"

namespace edn
{
	// @Note: bitmased reference for brain dead moments http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/
	enum EDN_WINDOW_FLAGS
	{
		EDN_WINDOW_RUNNING       = 1,
		EDN_WINDOW_PAUSED        = 1 << 1,
		EDN_WINDOW_FULLSCREEN    = 1 << 2,
		EDN_WINDOW_BOARDERLESS   = 1 << 3,
		EDN_WINDOW_VSYNC         = 1 << 4,
		EDN_WINDOW_HIDE_CURSOR   = 1 << 5,
		EDN_WINDOW_CENTER_CURSOR = 1 << 6,
	};

	struct WindowConfiguration
	{
		String title;
		u32 width, height;
		u32 x, y;
		u32 flags;
	};

	class Window : public Singleton<Window>
	{
	public:
		// @Note: If I want to pass in configuration to the window I sould mek a structure that holds all of the information
		// and then pass it to an overloaded initialize function. The Non default constructor will never be called as this is
		// a Singleton and will not be able to be called.
		Window();
		~Window();

		bool Initialize();
		bool Initialize(WindowConfiguration & config);
		void Cleanup();

		void SetClearColor(f32 r, f32 g, f32 b);
		void SetClearColor(u32 hexcode);
		void Clear();
		void Update();
		void PollEvents();
		void SwapBuffers();

		inline bool IsRunning()      { return m_windowFlags & EDN_WINDOW_RUNNING;       }
		inline bool IsPaused()       { return m_windowFlags & EDN_WINDOW_PAUSED;        }
		inline bool IsFullscreen()   { return m_windowFlags & EDN_WINDOW_FULLSCREEN;    }
		inline bool IsBoarderless()  { return m_windowFlags & EDN_WINDOW_BOARDERLESS;   }
		inline bool IsVsync()        { return m_windowFlags & EDN_WINDOW_FULLSCREEN;    }
		inline bool IsHiddenCursor() { return m_windowFlags & EDN_WINDOW_HIDE_CURSOR;   }
		inline bool IsCenterCursor() { return m_windowFlags & EDN_WINDOW_CENTER_CURSOR; }

		inline String & GetTitle() { return m_title; }
		inline u32 Width()         { return m_resolution.width; }
		inline u32 Height()        { return m_resolution.height; }

		inline SDL_Window * GetWindowPtr()    { return m_windowHandle; }
		inline SDL_GLContext & GetGLContext() { return m_glContext; }

		void SetTitle(String & title);

	private:
		SDL_Window * m_windowHandle;
		SDL_GLContext m_glContext;

		String m_title;

		IRect m_resolution;
		IPoint m_position;
		IPoint m_center;
		
		u32 m_windowFlags;
	};
}

#endif
