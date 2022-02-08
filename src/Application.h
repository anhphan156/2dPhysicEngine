#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>
#include "./Graphics.h"

class Application {
    private:
        bool running = false;

		float timePreviousFrame;

		std::vector<std::shared_ptr<class Body>> bodies;

		Vec2 liquid;

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
};

#endif
