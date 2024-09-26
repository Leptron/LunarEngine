#pragma once

#include <ultralight/Ultralight/platform/GPUDriver.h>
#include <ultralight/Ultralight/platform/Config.h>
#include "GPUDriverImpl.h"
#include <memory>

typedef struct GLFWwindow GLFWwindow;

#define ENABLE_OFFSCREEN_GL 0

namespace ultralight {
    class GPUContextGL {
        public:
            GPUContextGL(GLFWwindow* window, double scale);
            ~GPUContextGL();

            ultralight::GPUDriver* driver() const;
            ultralight::FaceWinding face_winding() const;

            void BeginDrawing();
            void EndDrawing();

            // Should only be called during drawing phase
            void PresentFrame();
            void Resize(int width, int height);

        private:
            std::unique_ptr<ultralight::GPUDriver> driver_;
            GLFWwindow* window_;
    };
}