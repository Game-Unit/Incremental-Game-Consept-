#pragma once

class Animation {
    int frameCount;
    int currentFrame = 0;
    float frameTime;
    float timer = 0.0f;
public:
    Animation(int frames, float frameDuration)
        : frameCount(frames), frameTime(frameDuration) {}

    void Update(float dt) {
        timer += dt;
        if (timer >= frameTime) {
            currentFrame = (currentFrame + 1) % frameCount;
            timer = 0.0f;
        }
    }

    int GetFrame() const { return currentFrame; }
};