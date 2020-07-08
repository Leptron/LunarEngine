#include "../../public/LunarUltralight/GPUDriverGL.h"

#include <ultralight/Ultralight/platform/FileSystem.h>
#include <ultralight/Ultralight/platform/Platform.h>
#include <fstream>
#include <iostream>
#include <sstream>

#define SHADER_PATH "shaders/"

#ifdef _DEBUG
#if _WIN32
#define INFO(x) \
  { std::cerr << "[INFO] " << __FUNCSIG__ << " @ Line " << __LINE__ << ":\n\t" << x << std::endl; }
#else
#define INFO(x) \
  { std::cerr << "[INFO] " << __PRETTY_FUNCTION__ << " @ Line " << __LINE__ << ":\n\t" << x << std::endl; }
#endif
#else
#define INFO(x)
#endif

#if _WIN32
#define FATAL(x)                                                                             \
  {                                                                                          \
    std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << " @ Line " << __LINE__ << ":\n\t" << x << std::endl; \
    std::cin.get();                                                                                        \
    exit(-1);                                                                                     \
  }
#else
#define FATAL(x)                                                                                           \
  {                                                                                                        \
    std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << " @ Line " << __LINE__ << ":\n\t" << x << std::endl; \
    std::cin.get();                                                                                        \
    exit(-1);                                                                                              \
  }
#endif

namespace ultralight {
    static void ReadFile(const char* filepath, std::string& result) {
        ultralight::FileSystem* fs = ultralight::Platform::instance().file_system();
        if (!fs)
            FATAL("No FileSystem defined.");

        auto handle = fs->OpenFile(filepath, false);
        if (handle == ultralight::invalidFileHandle)
            FATAL("Could not open file path: " << filepath);

        int64_t fileSize = 0;
        fs->GetFileSize(handle, fileSize);
        result.resize((size_t)fileSize);
        fs->ReadFromFile(handle, &result[0], fileSize);
        fs->CloseFile(handle);
    }

    inline char const* glErrorString(GLenum const err) noexcept {
        switch (err) {
            case GL_NO_ERROR:
                return "GL_NO_ERROR";
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION";
            case GL_STACK_OVERFLOW:
                return "GL_STACK_OVERFLOW";
            case GL_STACK_UNDERFLOW:
                return "GL_STACK_UNDERFLOW";
            case GL_OUT_OF_MEMORY:
                return "GL_OUT_OF_MEMORY";
            // OpenGL 3.0+ Errors
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL_INVALID_FRAMEBUFFER_OPERATION";
            default:
                return "UNKNOWN ERROR";
        }
    }

    inline std::string GetShaderLog(GLuint shader_id) {
        GLint length, result;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        std::string str(length, ' ');
        glGetShaderInfoLog(shader_id, (GLsizei)str.length(), &result, &str[0]);
        return str;
    }

    inline std::string GetProgramLog(GLuint program_id) {
        GLint length, result;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
        std::string str(length, ' ');
        glGetProgramInfoLog(program_id, (GLsizei)str.length(), &result, &str[0]);
        return str;
    }

    static GLuint LoadShaderFromFile(GLenum shader_type, const char* filename) {
        std::string shader_source;
        std::string path = std::string(SHADER_PATH) + filename;
        ReadFile(path.c_str(), shader_source);
        GLint compileStatus;
        const char* shader_source_str = shader_source.c_str();
        GLuint shader_id = glCreateShader(shader_type);
        glShaderSource(shader_id, 1, &shader_source_str, NULL);
        glCompileShader(shader_id);
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus == GL_FALSE)
            FATAL("Unable to compile shader. Filename: " << filename << "\n\tError:"
                                                        << glErrorString(glGetError()) << "\n\tLog: " << GetShaderLog(shader_id))
        return shader_id;
    }

    #ifdef _DEBUG
#define CHECK_GL()                 \
  {                                \
    if (GLenum err = glGetError()) \
      FATAL(glErrorString(err))    \
  }
#else
#define CHECK_GL()
#endif

    GPUDriverGL::GPUDriverGL(GLfloat scale) : scale_(scale) {
        // Render Buffer ID 0 is reserved for the screen
        frame_buffer_map[0] = 0;
    }

    void GPUDriverGL::CreateTexture(uint32_t texture_id,
    Ref<Bitmap> bitmap) {
        GLuint tex_id;
        glGenTextures(1, &tex_id);
        texture_map[texture_id] = tex_id;

        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, tex_id);

        CHECK_GL();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        CHECK_GL();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        CHECK_GL();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, bitmap->row_bytes() / bitmap->bpp());
        CHECK_GL();

        if (bitmap->format() == kBitmapFormat_A8_UNORM) {
            const void* pixels = bitmap->LockPixels();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, bitmap->width(), bitmap->height(), 0,
                GL_RED, GL_UNSIGNED_BYTE, pixels);
            bitmap->UnlockPixels();
        } else if (bitmap->format() == kBitmapFormat_BGRA8_UNORM_SRGB) {
            const void* pixels = bitmap->LockPixels();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->width(), bitmap->height(), 0,
                GL_BGRA, GL_UNSIGNED_BYTE, pixels);
            bitmap->UnlockPixels();
        } else {
            FATAL("Unhandled texture format: " << bitmap->format())
        }

        CHECK_GL();
        glGenerateMipmap(GL_TEXTURE_2D);
        CHECK_GL();
    }
}