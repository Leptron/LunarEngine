#include "../../public/LunarLayerManager.h"

namespace LunarRenderer {
    LayerManager::LayerManager() {

    }

    LayerManager::LayerManager(LunarLayerConstruction *construction) {
        this->device = construction->device;
        this->swapChainExtent = construction->swapChainExtent;
        this->renderPass = construction->renderPass;
        this->swapChainImages = construction->swapChainImages;
        this->physicalDevice = construction->physicalDevice;
        this->commandPool = construction->commandPool;
        this->graphicsQueue = construction->graphicsQueue;
        this->swapChainFrameBuffers = construction->swapChainFrameBuffers;

        //create the descriptor set layout
        createDescriptorSetLayout();

        cameraView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
                                    glm::vec3(0.0f, 0.0f, 0.0f), 
                                    glm::vec3(0.0f, 1.0f, 0.0f));
    }

    LayerManager::~LayerManager() {

    }

    void LayerManager::CreateObject(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::string requestedMaterial, bool singular, std::string id) {
        ThreeDObject obj = {};
        obj.vertices = vertices;
        obj.indices = indices;
        obj.indexCount = static_cast<uint32_t>(indices.size());
        obj.singular = singular;
        obj.matID = requestedMaterial;
        obj.ID = id;

        //check if material was created
        LayerMaterial query = {};
        query.matID = requestedMaterial;

        bool materialFound = false;
        for(int i = 0; i < materials.size(); i++) {
            auto material = materials[i];
            if(material.matID == query.matID)
                materialFound = true;

            obj.materialIndex = i;
        }

        if(!materialFound) {
            //create material
            createRequestedMaterial(requestedMaterial);
            obj.materialIndex = materials.size() - 1;
        }

        objectProjectionID[obj.ID] = ProjectionMatricies{};

        //create the uniforms
        createUniformBuffers(obj);
        objects.push_back(obj);
    }

    void LayerManager::AllocateObjects() {
        BufferLayer m_buf = {};
        int blocks_found = 0;
        int index_base = 0;

        for(auto& object : objects) {
            if(blocks_found != BLOCK_COUNT) {
                object.indexBase = index_base;
                m_buf.objects.push_back(object);
                index_base += object.indexCount;
            }

            blocks_found++;
            if(blocks_found == BLOCK_COUNT) {
                createDescriptorPool();
                m_buf.poolIndex = descriptorPools.size() - 1;
                
                allocateBufferMemory(m_buf);
                createDescirptorSets(m_buf);

                buffers.push_back(m_buf);
                
                m_buf = {};
                blocks_found = 0;
                index_base = 0;
            }
        }

        if(blocks_found > 0) {
            createDescriptorPool();
            m_buf.poolIndex = descriptorPools.size() - 1;

            allocateBufferMemory(m_buf);
            createDescirptorSets(m_buf);

            buffers.push_back(m_buf);
                
            m_buf = {};
            blocks_found = 0;
            index_base = 0;
        }
    }

    void LayerManager::CleanAllUBO() {
        for(auto layer : buffers) {
            for(auto object : layer.objects) {
                for(size_t i = 0; i < 1; i++) {
                    vkDestroyBuffer(device, object.uniformBuffers[i], nullptr);
                    vkFreeMemory(device, object.uniformBuffersMemory[i], nullptr);
                }
            }
        }

        for(auto pool : descriptorPools) {
            vkDestroyDescriptorPool(device, pool, nullptr);
        }

        descriptorPools.clear();
    }

    void LayerManager:VkDevice device;:ReAttachComponents(LunarLayerConstruction *construction) {
        this->device = construction->device;
        this->swapChainExtent = construction->swapChainExtent;
        this->renderPass = construction->renderPass;
        this->swapChainImages = construction->swapChainImages;
        this->physicalDevice = construction->physicalDevice;
        this->commandPool = construction->commandPool;
        this->graphicsQueue = construction->graphicsQueue;
        this->swapChainFrameBuffers = construction->swapChainFrameBuffers;
    }

    void LayerManager::RecreateUBO() {
        for(auto& m_buf : buffers) {
            createDescriptorPool();
            m_buf.poolIndex = descriptorPools.size() - 1;

            for(auto& obj : m_buf.objects)
                createUniformBuffers(obj);
            createDescirptorSets(m_buf);
        }
    }

    void LayerManager::CleanAllStorageBuffers() {
        for(auto layer : buffers) {
            vkDestroyBuffer(device, layer.indexBuffer, nullptr);
            vkFreeMemory(device, layer.indexBufferMemory, nullptr);

            vkDestroyBuffer(device, layer.vertexBuffer, nullptr);
            vkFreeMemory(device, layer.vertexBufferMemory, nullptr);
        }
    }

    void LayerManager::UpdateObjectUniform(ProjectionMatricies newMatricies, std::string id) {
        objectProjectionID[id] = newMatricies;
    }
}