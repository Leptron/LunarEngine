#include "../../public/LunarUltralight/UltralightManager.h"

namespace LunarGUI {
    using namespace ultralight;

    //static variables
    int UltralightManager::windowWidth = 1280;
    int UltralightManager::windowHeight = 720;
    bool UltralightManager::dimsChanged = false;

    UltralightManager::UltralightManager() {

    }

    UltralightManager::~UltralightManager() {
        ultralight::Config config;
        config.device_scale = 2.0;
        config.font_family_standard = "Arial";
        config.resource_path = "./resources/";

        config.use_gpu_renderer = false;

        ultralight::Platform::instance().set_config(config);
        ultralight::Platform::instance().set_font_loader(ultralight::GetPlatformFontLoader());
        ultralight::Platform::instance().set_file_system(ultralight::GetPlatformFileSystem("."));
        ultralight::Platform::instance().set_logger(this);

        renderer = ultralight::Renderer::Create();
    }

    void UltralightManager::ConstructView(std::string contents, std::string tagName, int width, int height) {
        int rWidth, rHeight;

        if(width != 0 && height != 0) {
            rWidth = width;
            rHeight = height;
        } else {
            rWidth = windowWidth;
            rHeight = windowHeight;
        }

        ultralight::RefPtr<ultralight::View> _tmpView;
        _tmpView = renderer->CreateView(rWidth, rHeight, false, nullptr);
        _tmpView->set_load_listener(this);
        _tmpView->LoadHTML(contents.c_str());

        _views[tagName] = &_tmpView;
    }

    void UltralightManager::SetFrame(std::vector<std::string> frames) {
        for(auto frameID : frames) {
            _viewDone[currFrame] = false;
            _views[currFrame]->get()->set_needs_paint(false);
            this->currFrame = frameID;
            _viewDone[currFrame] = true;

            //set frame to needs painting
            _views[currFrame]->get()->set_needs_paint(true);
        }
    }

    void UltralightManager::PassResources(LunarRenderer::LunarLayerConstruction *construction) {
        this->device = construction->device;
        this->swapChainExtent = construction->swapChainExtent;
        this->renderPass = construction->renderPass;
        this->swapChainImages = construction->swapChainImages;
        this->physicalDevice = construction->physicalDevice;
        this->commandPool = construction->commandPool;
        this->graphicsQueue = construction->graphicsQueue;
        this->swapChainFrameBuffers = construction->swapChainFrameBuffers;
    }

    void UltralightManager::PrepareGeometry() {
        std::vector<ULVertex> verts = {
            {{-0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f},  {1.0f, 1.0f}},
            {{-0.5f, 0.5f}, {0.0f, 1.0f}}
        };
    }

    //virtuals
    void UltralightManager::LogMessage(LogLevel log_level, const String16& message) {

    }

    void UltralightManager::OnFinishLoading(ultralight::View* caller) {
        std::cout << "done" << std::endl;
    }
}