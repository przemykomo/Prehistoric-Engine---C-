#ifndef GL_SWAP_CHAIN_H
#define GL_SWAP_CHAIN_H

#include "engine/prehistoric/common/framework/swapchain/SwapChain.h"

#include <glew.h>
#include <glfw3.h>

class GLSwapChain : public Swapchain
{
public:
	virtual void SetupSwapchain(void* physicalDevice) override;

	virtual void SwapBuffers(Window* window) override;

	virtual void SetVSync(bool vSync) const override;
	virtual void SetWindowSize(Window* window, uint32_t width, uint32_t height) override;

	virtual void SetClearColor(const float& red, const float& green, const float& blue, const float& alpha) override;
	virtual void ClearScreen() override;

	virtual void DeleteSwapchain(void* device) override;
};

#endif