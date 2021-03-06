#ifndef WINDOW_H
#define WINDOW_H

#include "engine/prehistoric/core/util/Constants.h"

#include "engine/prehistoric/common/framework/swapchain/Swapchain.h"
#include "engine/prehistoric/common/framework/context/Context.h"

class Window
{
public:
	Window(const int& width, const int& height, const char* title, const bool& fullscreen);
	Window();
	
	virtual ~Window() = 0;

	void SetClearColor(const float& red, const float& green, const float& blue, const float& alpha) const { swapchain->SetClearColor(red, green, blue, alpha); }
	void ClearScreen() const { swapchain->ClearScreen(); }

	void SetVSync(bool vsync) const { swapchain->SetVSync(vsync); }

	void DeleteSwapChain(void* device) { swapchain->DeleteSwapchain(device); }

	virtual bool Create() = 0;
	virtual bool ShouldClose() const = 0; 
	virtual void Input() = 0;
	virtual void Render() const = 0;

	inline bool GetClosed() const { return closed; }
	inline void SetClosed(const bool& closed) { this->closed = closed; }

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void SetWidth(int width) { this->width = width; }
	void SetHeight(int height) { this->height = height; }

	inline Swapchain* GetSwapchain() const { return swapchain; }
	inline Context* GetContext() const { return context; }

	virtual void* GetWindowHandle() const = 0;

	bool& GetResized() { return resized; }
	void SetResized(bool resized) { this->resized = resized; }
protected:
	int width;
	int height;
	const char* title;
	bool fullscreen;
	bool closed;

	bool resized;

	Swapchain* swapchain;
	Context* context;
};

#endif