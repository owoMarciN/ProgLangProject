#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
	: Texture(filename, x, y, w, h){

	mTimer = Timer::Instance();

	mStartX = x;
    mStartY = y;

	mFrameCount = frameCount;
	mAnimationSpeed = animationSpeed;
	mTimePerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationDir;

	mAnimationDone = false;

	mWrapMode = loop;
}

AnimatedTexture::~AnimatedTexture() {

}

void AnimatedTexture::WrapMode(WRAP_MODE mode) {
	mWrapMode = mode;
}

void AnimatedTexture::Update(){
	if(!mAnimationDone){
		mAnimationTimer += mTimer->DeltaTime();
		if(mAnimationTimer >= mAnimationSpeed) {
			//Only loop if the wrap mode is loop
			if(mWrapMode == loop) {
				mAnimationTimer -= mAnimationSpeed;
			}
            else{
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}

		if(mAnimationDirection == horizontal) {
			mClippedRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
    	}
        else{
			mClippedRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
    }
}

bool AnimatedTexture::Done(){
	return mAnimationDone;
}