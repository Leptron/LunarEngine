#include "../../public/LunarManager/LunarAnimationManager.h"

namespace LunarAnimation {
	LunarSpriteAnimationManager::LunarSpriteAnimationManager(): _manager(nullptr) {
		LunarLogger::Logger::getInstance()->log("Created Animation Manager", "Animation", "CYAN");
	}

	LunarSpriteAnimationManager::~LunarSpriteAnimationManager() {

	}

	void LunarSpriteAnimationManager::PassManager(Lunar2D::SpriteManager* _manager) {
		this->_manager = _manager;
	}

	void LunarSpriteAnimationManager::CreateAnimation(std::string animationName, std::string targetSprite, std::vector<int> frames, int playbackSpeed) {
		float mAccumulation = 1.0f / playbackSpeed;
		accumulators[animationName] = std::make_tuple(mAccumulation, 0.0f);

		LunarAnimation _anim = {};

		_anim.animationID = animationName;
		_anim.spriteID = targetSprite;
		_anim.frames = frames;
		_anim.maxFrame = frames.size() - 1;
		_anim.currFrame = 0;
		_anim.playbackSpeed = playbackSpeed;
		_anim.playing = false;
		_anim.index = animationQueue.size();

		animationQueue.push_back(_anim);
		LunarLogger::Logger::getInstance()->log("Created Animation with ID of " + _anim.animationID, "Animation", "CYAN");
	}

	void LunarSpriteAnimationManager::DeleteAnimation(std::string animationName) {
		//TODO : implement
	}

	void LunarSpriteAnimationManager::PlayAnimation(std::string animationName) {
		for (auto& _anim : animationQueue) {
			if (_anim.animationID == animationName)
				_anim.playing = true;
		}
	}

	void LunarSpriteAnimationManager::StopAnimation(std::string animationName) {
		for (auto& _anim : animationQueue) {
			if (_anim.animationID == animationName)
				_anim.playing = true;
		}
	}

	void LunarSpriteAnimationManager::Update(float deltaTime) {
		for (auto& _anim : animationQueue) {
			if (_anim.playing) {
				//currAccumulator
				auto _animTuple = accumulators[_anim.animationID];
				float currAccumulator = std::get<1>(_animTuple);
				float max_accum = std::get<0>(_animTuple);

				currAccumulator += deltaTime;
				if (currAccumulator >= max_accum) {
					int pCFrame = _anim.currFrame;
					//check if it is the max
					if (pCFrame == _anim.maxFrame)
						pCFrame = 0;
					else
						pCFrame += 1;

					currAccumulator = 0.0f;
					_anim.currFrame = pCFrame;
					_manager->UpdateTiledTile(_anim.spriteID, _anim.currFrame);
				}

				auto _nTuple = std::make_tuple(max_accum, currAccumulator);
				accumulators[_anim.animationID] = _nTuple;
			}
		}
	}
}