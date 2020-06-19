#pragma once

#include "../LunarPrimitives/SpriteManager.h"
#include "../LunarLogger.h"

#include <vector>
#include <string>
#include <thread>
#include <unordered_map>
#include <tuple>

namespace LunarAnimation {
	struct LunarAnimation {
		std::string spriteID;
		std::string animationID;

		std::vector<int> frames;
		int maxFrame;
		int currFrame;

		int playbackSpeed;
		int index;
		bool playing;
	};

	class LunarSpriteAnimationManager {
	public:
		LunarSpriteAnimationManager();
		~LunarSpriteAnimationManager();

		void PassManager(Lunar2D::SpriteManager* _manager);

		void CreateAnimation(std::string animationName, std::string targetSprite, std::vector<int> frames, int playbackSpeed); 
		void DeleteAnimation(std::string animationName);
		
		void PlayAnimation(std::string animationName);
		void StopAnimation(std::string animationName);

		void Update(float deltaTime);
	private:
		Lunar2D::SpriteManager* _manager;
		std::vector<LunarAnimation> animationQueue;
		std::unordered_map<std::string, std::tuple<float, float>> accumulators;
	};
}