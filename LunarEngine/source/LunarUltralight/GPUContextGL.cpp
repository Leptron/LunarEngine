#include "../../public/LunarUltralight/GPUContextGL.h"
#include "../../public/LunarUltralight/GPUDriverGL.h"

namespace ultralight {
    GPUContextGL::GPUContextGL(GLFWwindow* window, double scale) : window_(window) {
        driver_.reset(new ultralight::GPUDriverGL(scale));
    }

    GPUContextGL::~GPUContextGL() {}

    ultralight::GPUDriver* GPUContextGL::driver() const { return driver_.get(); }

    ultralight::FaceWinding GPUContextGL::face_winding() const { return ultralight::kFaceWinding_CounterClockwise; }

    void GPUContextGL::BeginDrawing() {}

    void GPUContextGL::EndDrawing() {}

    // Should only be called during drawing phase
    void GPUContextGL::PresentFrame() {
        glfwSwapBuffers(window_);
    }

    void GPUContextGL::Resize(int width, int height) {
        ultralight::GPUDriverGL* driver_gl = static_cast<ultralight::GPUDriverGL*>(driver_.get());
        driver_gl->SetViewport(width, height);
    }
}