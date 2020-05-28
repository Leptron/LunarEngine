#include "../public/LunarEngineBase.h"

namespace LunarEngine {
	LunarEngineRenderer::LunarEngineRenderer() : VulkanExampleBase(ENABLE_VALIDATION) {
		title = "Leptron engine";
		//setup camera
		camera.type = Camera::CameraType::lookat;
		camera.setPosition(glm::vec3(0.0f, 0.0f, -2.5f));
		camera.setRotation(glm::vec3(0.0f));
		camera.setPerspective(60.0f, (float)width / (float)height, 1.0f, 256.0f);
	}

	LunarEngineRenderer::~LunarEngineRenderer() {
		//cleanup
		vkDestroyPipeline(device, pipeline, nullptr);

		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

		vkDestroyBuffer(device, vertices.buffer, nullptr);
		vkFreeMemory(device, vertices.memory, nullptr);

		vkDestroyBuffer(device, indices.buffer, nullptr);
		vkFreeMemory(device, indices.memory, nullptr);

		vkDestroyBuffer(device, uniformBufferVS.buffer, nullptr);
		vkFreeMemory(device, uniformBufferVS.memory, nullptr);

		vkDestroySemaphore(device, presentCompleteSemaphore, nullptr);
		vkDestroySemaphore(device, renderCompleteSemaphore, nullptr);

		for (auto& fence : waitFences)
			vkDestroyFence(device, fence, nullptr);
	}

	uint32_t LunarEngineRenderer::getMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags properties) {
		//iterate over memory types available
		for (uint32_t i = 0; i < deviceMemoryProperties.memoryTypeCount; i++) {
			if((typeBits & 1) == 1) {
				if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
					return i;
			}

			typeBits >>= 1;
		}

		throw "could not find suitable memory type";
	}

	
	void LunarEngineRenderer::prepareSynchronizationPrimitives() {
		VkSemaphoreCreateInfo semaphoreCreateInfo = {};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreCreateInfo.pNext = nullptr;
		
		//image presentation sema
		VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &presentCompleteSemaphore));
		
		//command finished sema
		VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &renderCompleteSemaphore));

		//fences used to check draw command completion
		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		waitFences.resize(drawCmdBuffers.size());
		for(auto& fence : waitFences)
			VK_CHECK_RESULT(vkCreateFence(device, &fenceCreateInfo, nullptr, &fence));
	}

	//new buffer from command pool
	VkCommandBuffer LunarEngineRenderer::getCommandBuffer(bool begin) {
	
		VkCommandBuffer cmdBuffer;

		VkCommandBufferAllocateInfo cmdBufAllocateInfo = {};
		cmdBufAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		cmdBufAllocateInfo.commandPool = cmdPool;
		cmdBufAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		cmdBufAllocateInfo.commandBufferCount = 1;

		VK_CHECK_RESULT(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &cmdBuffer));

		if(begin) {
			VkCommandBufferBeginInfo cmdBufInfo = vks::initializers::commandBufferBeginInfo();
			VK_CHECK_RESULT(vkBeginCommandBuffer(cmdBuffer, &cmdBufInfo));
		}

		return cmdBuffer;
	}

	//end the command buffer and submit it
	//uses fence to ensure buffer is finished
	void LunarEngineRenderer::flushCommandBuffer(VkCommandBuffer commandBuffer) {
		assert(commandBuffer != VK_NULL_HANDLE);
		
		VK_CHECK_RESULT(vkEndCommandBuffer(commandBuffer));

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		//create fence to ensure it has finished executing
		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = 0;
		
		VkFence fence;
		VK_CHECK_RESULT(vkCreateFence(device, &fenceCreateInfo, nullptr, &fence));

		VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, fence));
		// Wait for the fence to signal that command buffer has finished executing
		VK_CHECK_RESULT(vkWaitForFences(device, 1, &fence, VK_TRUE, DEFAULT_FENCE_TIMEOUT));

		vkDestroyFence(device, fence, nullptr);
		vkFreeCommandBuffers(device, cmdPool, 1, &commandBuffer);		
	}

	//build seperate command buffers for every framebuffer
	//unlike in opengl, work is recoreded into buffers that is then resubmitted into the queue
	//allowing work to be generated upfront
	void LunarEngineRenderer::buildCommandBuffers() {
		VkCommandBufferBeginInfo cmdBufInfo = {};	
		cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmdBufInfo.pNext = nullptr;

		//set clear values for all f buffers
		VkClearValue clearValues[2];
		clearValues[0].color = { { 0.0f, 0.0f, 0.2f, 1.0f } };
		clearValues[1].depthStencil = {1.0f, 0};

		VkRenderPassBeginInfo renderPassBeginInfo = {};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.pNext = nullptr;
		renderPassBeginInfo.renderPass = renderPass;
		renderPassBeginInfo.renderArea.offset.x = 0;
		renderPassBeginInfo.renderArea.offset.y = 0;
		renderPassBeginInfo.renderArea.extent.width = width;
		renderPassBeginInfo.renderArea.extent.height = height;
		renderPassBeginInfo.clearValueCount = 2;
		renderPassBeginInfo.pClearValues = clearValues;

		for(int32_t i = 0; i < drawCmdBuffers.size(); ++i) {
			//set target frame buffer
			renderPassBeginInfo.framebuffer = frameBuffers[i];
			
			//start the first subpass specified
			//clearing the color and depth atachment
			VK_CHECK_RESULT(vkBeginCommandBuffer(drawCmdBuffers[i], &cmdBufInfo));

			//update dynamic viewport sate
			VkViewport viewport = {};
			viewport.height = (float)height;
			viewport.width = (float)width;
			viewport.minDepth = (float)0.0f;
			viewport.maxDepth = (float)1.0f;
			vkCmdSetViewport(drawCmdBuffers[i], 0, 1, &viewport);

			//update scissor
			VkRect2D scissor = {};
			scissor.extent.width = width;
			scissor.extent.height = height;
			scissor.offset.x = 0;
			scissor.offset.y = 0;
			vkCmdSetScissor(drawCmdBuffers[i], 0, 1, &scissor);

			//bind descriptor set
			vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
			//bind the rendering pipeline
			vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
			//bind the triangle vertex buffer
			VkDeviceSize offsets[1] = { 0 };
			
			vkCmdBindVertexBuffers(drawCmdBuffers[i], 0, 1, &vertices.buffer, offsets);
			
			//Bind the triangle index buffer
			vkCmdBindIndexBuffer(drawCmdBuffers[i], indices.buffer, 0, VK_INDEX_TYPE_UINT32);

			//draw the indexed triangle
			vkCmdDrawIndexed(drawCmdBuffers[i], indices.count, 1, 0, 0, 1);

			vkCmdEndRenderPass(drawCmdBuffers[i]);

			VK_CHECK_RESULT(vkEndCommandBuffer(drawCmdBuffers[i]));
		}
	}

	void LunarEngineRenderer::draw() {
		//get the next image in the swap chain
		VK_CHECK_RESULT(swapChain.acquireNextImage(presentCompleteSemaphore, &currentBuffer));

		//use a fence to wait until the command buffer has finshed execution before using it again
		VK_CHECK_RESULT(vkWaitForFences(device, 1, &waitFences[currentBuffer], VK_TRUE, UINT64_MAX));
		VK_CHECK_RESULT(vkResetFences(device, 1, &waitFences[currentBuffer]));

		//pipeline stage at which the queue submission will wait
		VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		//  The submit info structure specifices a command buffer queue submission batch
		VkSubmitInfo submitInfo  = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pWaitDstStageMask = &waitStageMask;
		submitInfo.pWaitSemaphores = &presentCompleteSemaphore;
		submitInfo.waitSemaphoreCount = 1;                           // One wait semaphore
		submitInfo.pSignalSemaphores = &renderCompleteSemaphore;     // Semaphore(s) to be signaled when command buffers have completed
		submitInfo.signalSemaphoreCount = 1;                         // One signal semaphore
		submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer]; // Command buffers(s) to execute in this batch (submission)
		submitInfo.commandBufferCount = 1; 

		//submit to the graphics queue
		VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, waitFences[currentBuffer]));

		// Present the current buffer to the swap chain
		// Pass the semaphore signaled by the command buffer submission from the submit info as the wait semaphore for swap chain presentation
		// This ensures that the image is not presented to the windowing system until all commands have been submitted
		VkResult present = swapChain.queuePresent(queue, currentBuffer, renderCompleteSemaphore);
		if (!((present == VK_SUCCESS) || (present == VK_SUBOPTIMAL_KHR))) {
			VK_CHECK_RESULT(present);
		}
	}

	// Prepare vertex and index buffers for an indexed triangle
	// Also uploads them to device local memory using staging and initializes vertex input and attribute binding to match the vertex shader
	void LunarEngineRenderer::prepareVertices(bool useStagingBuffers) {
		//setup verts
		std::vector<Vertex> vertexBuffer = 
		{
			{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
			{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
			{ {  0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
		};
		uint32_t vertexBufferSize = static_cast<uint32_t>(vertexBuffer.size()) * sizeof(Vertex);

		//setup indicies
		std::vector<uint32_t> indexBuffer = { 0, 1, 2 };
		indices.count = static_cast<uint32_t>(indexBuffer.size());
		uint32_t indexBufferSize = indices.count * sizeof(uint32_t);

		VkMemoryAllocateInfo memAlloc = {};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		VkMemoryRequirements memReqs;

		void *data;

		if(useStagingBuffers) {
			// Static data like vertex and index buffer should be stored on the device memory 
			// for optimal (and fastest) access by the GPU
			//
			// To achieve this we use so-called "staging buffers" :
			// - Create a buffer that's visible to the host (and can be mapped)
			// - Copy the data to this buffer
			// - Create another buffer that's local on the device (VRAM) with the same size
			// - Copy the data from the host to the device using a command buffer
			// - Delete the host visible (staging) buffer
			// - Use the device local buffers for rendering
			//

			struct StagingBuffer {
				VkDeviceMemory memory;
				VkBuffer buffer;
			};

			struct {
				StagingBuffer vertices;
				StagingBuffer indicies;
			} stagingBuffers;

			//vertex buffer
			VkBufferCreateInfo vertexBufferInfo = {};
			vertexBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			vertexBufferInfo.size = vertexBufferSize;
			//buffer is used as the copy source
			vertexBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			//create a host visible buffer to copy the data to (staging buffer)
			VK_CHECK_RESULT(vkCreateBuffer(device, &vertexBufferInfo, nullptr, &stagingBuffers.vertices.buffer));
			vkGetBufferMemoryRequirements(device, stagingBuffers.vertices.buffer, &memReqs);
			memAlloc.allocationSize = memReqs.size;

			// Request a host visible memory type that can be used to copy our data do
			// Also request it to be coherent, so that writes are visible to the GPU right after unmapping the buffer
			memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &stagingBuffers.vertices.memory));
			//map and copy
			VK_CHECK_RESULT(vkMapMemory(device, stagingBuffers.vertices.memory, 0, memAlloc.allocationSize, 0, &data));
			memcpy(data, vertexBuffer.data(), vertexBufferSize);
			vkUnmapMemory(device, stagingBuffers.vertices.memory);
			VK_CHECK_RESULT(vkBindBufferMemory(device, stagingBuffers.vertices.buffer, stagingBuffers.vertices.memory, 0));

			//create a device local buffer which the vertex data will be copied too
			vertexBufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			VK_CHECK_RESULT(vkCreateBuffer(device, &vertexBufferInfo, nullptr, &vertices.buffer));
			vkGetBufferMemoryRequirements(device, vertices.buffer, &memReqs);
			memAlloc.allocationSize = memReqs.size;
			memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &vertices.memory));
			VK_CHECK_RESULT(vkBindBufferMemory(device, vertices.buffer, vertices.memory, 0));

			//index buffers
			VkBufferCreateInfo indexBufferInfo = {};
			indexBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			indexBufferInfo.size = indexBufferSize;
			indexBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			// Copy index data to a buffer visible to the host (staging buffer)
			VK_CHECK_RESULT(vkCreateBuffer(device, &indexBufferInfo, nullptr, &stagingBuffers.indicies.buffer));
			vkGetBufferMemoryRequirements(device, stagingBuffers.indicies.buffer, &memReqs);
			memAlloc.allocationSize = memReqs.size;
			memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &stagingBuffers.indicies.memory));
			VK_CHECK_RESULT(vkMapMemory(device, stagingBuffers.indicies.memory, 0, indexBufferSize, 0, &data));
			memcpy(data, indexBuffer.data(), indexBufferSize);
			vkUnmapMemory(device, stagingBuffers.indicies.memory);
			VK_CHECK_RESULT(vkBindBufferMemory(device, stagingBuffers.indicies.buffer, stagingBuffers.indicies.memory, 0));

			//create destination buffer with device only visibility
			indexBufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			VK_CHECK_RESULT(vkCreateBuffer(device, &indexBufferInfo, nullptr, &indices.buffer));
			vkGetBufferMemoryRequirements(device, indices.buffer, &memReqs);
			memAlloc.allocationSize = memReqs.size;
			memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &indices.memory));
			VK_CHECK_RESULT(vkBindBufferMemory(device, indices.buffer, indices.memory, 0));

			// Buffer copies have to be submitted to a queue, so we need a command buffer for them
			// Note: Some devices offer a dedicated transfer queue (with only the transfer bit set) that may be faster when doing lots of copies
			VkCommandBuffer copyCmd = getCommandBuffer(true);

			//put buffer region copies into command buffer
			VkBufferCopy copyRegion = {};

			//Vertex buffer
			copyRegion.size = vertexBufferSize;
			vkCmdCopyBuffer(copyCmd, stagingBuffers.vertices.buffer, vertices.buffer, 1, &copyRegion);
            //Index buffer
            copyRegion.size = indexBufferSize;
            vkCmdCopyBuffer(copyCmd, stagingBuffers.indicies.buffer, indices.buffer, 1, &copyRegion);

            // Flushing the command buffer will also submit it to the queue and uses a fence to ensure that all commands have been executed before returning
            flushCommandBuffer(copyCmd);

            // Destroy staging buffers
			// Note: Staging buffer must not be deleted before the copies have been submitted and executed
            vkDestroyBuffer(device, stagingBuffers.vertices.buffer, nullptr);
            vkFreeMemory(device, stagingBuffers.vertices.memory, nullptr);
            vkDestroyBuffer(device, stagingBuffers.indicies.buffer, nullptr);
            vkFreeMemory(device, stagingBuffers.indicies.memory, nullptr);
		} else {
            // Don't use staging
			// Create host-visible buffers only and use these for rendering. This is not advised and will usually result in lower rendering performance

            //vertex buffer
            VkBufferCreateInfo vertexBufferInfo = {};
            vertexBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            vertexBufferInfo.size = vertexBufferSize;
            vertexBufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

            // Copy vertex data to a buffer visible to the host
            VK_CHECK_RESULT(vkCreateBuffer(device, &vertexBufferInfo, nullptr, &vertices.buffer));
            vkGetBufferMemoryRequirements(device, vertices.buffer, &memReqs);
            memAlloc.allocationSize = memReqs.size;
            // VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is host visible memory, and VK_MEMORY_PROPERTY_HOST_COHERENT_BIT makes sure writes are directly visible
            memAlloc.memoryTypeIndex = getMemoryTypeIndex(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            VK_CHECK_RESULT(vkAllocateMemory(device, &memAlloc, nullptr, &vertices.memory));
			VK_CHECK_RESULT(vkMapMemory(device, vertices.memory, 0, memAlloc.allocationSize, 0, &data));
            memcpy(data, vertexBuffer.data(), vertexBufferSize);
            vkUnmapMemory(device, vertices.memory);
            VK_CHECK_RESULT(vkBindBufferMemory(device, vertices.buffer, vertices.memory, 0));
        }
	}
}
