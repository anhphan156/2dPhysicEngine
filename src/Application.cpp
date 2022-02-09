#include "Application.h"

#include <iostream>
#include <memory>

#include "Constants.h"
#include "Physics/Force.h"

#include "Physics/Contact.h"
#include "Physics/CollisionDetection.h"

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    // TODO: setup objects in the scene
	bodies.push_back(std::make_shared<Body>(800.f, 500.f, 0.f, std::make_shared<Circle>(250.f)));
	bodies.push_back(std::make_shared<Body>(90.f, 50.f, 1.f, std::make_shared<Circle>(10.f)));
	bodies.push_back(std::make_shared<Body>(200.f, 50.f, 2.f, std::make_shared<Box>(100.f, 70.f)));

	//springBody = new Body(280.f, 50.f, 5.5f, 15.f);

	//for(const auto& body : bodies){
		//body->AddForce(Vec2(1000.f, 0.f) * PIXEL_PER_METER); // wind
	//}

	liquid = Vec2(0.f, Graphics::Height() * 30 / 100);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT){
					bodies.push_back(std::make_shared<Body>(event.button.x, event.button.y, 1.f, std::make_shared<Circle>(10.f)));
				}
				break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {
	float timeToWait = MIL_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
	if(timeToWait > 0)
		SDL_Delay(timeToWait);


	float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.f;
	if(deltaTime > .016f){
		deltaTime = .016f;
	}

	timePreviousFrame = SDL_GetTicks();

	//for(const auto& body : bodies){
	for(auto it = bodies.begin(); it != bodies.end(); ++it){
		const auto& body = *it;
		if(body->shape->GetShape() == CIRCLE){

			const auto circle = std::static_pointer_cast<Circle>(body->shape);

			// Adding force
			body->AddForce(Vec2(0.f, 9.8f * body->mass) * PIXEL_PER_METER); // weight

			if(body->position.y >= liquid.y)
				body->AddForce(Force::GenerateDragForce(*body, .02f));
			//else
				//body->AddForce(Vec2(10.f, 0.f) * PIXEL_PER_METER);

			// Adding torque
			body->AddTorque(200.f);

			// Integration
			body->BodyUpdate(deltaTime);

			for(auto itt = it + 1; itt != bodies.end(); ++itt){
				if((*itt)->shape->GetShape() != CIRCLE) continue;
				Contact contact;		
				if(CollisionDetection::CollisionDetectionCircleCircle(body, *itt, contact)){
					contact.ResolveCollision();
				}
			}

			// Window bounding
			if(body->position.y + circle->radius > Graphics::Height() - 30.f){
				body->position.y = Graphics::Height() - circle->radius - 30.1f;
				body->velocity.y *= -.8f;
			}else if(body->position.y - circle->radius < 0.f){
				body->position.y = 0 + circle->radius;
				body->velocity.y *= -.8f;
			}else if(body->position.x + circle->radius > Graphics::Width()){
				body->position.x = Graphics::Width() - circle->radius;
				body->velocity.x *= -.8f;
			}else if(body->position.x - circle->radius < 0.f){
				body->position.x = 0 + circle->radius;
				body->velocity.x *= -.8f;
			}
		}else {
			body->AddTorque(300.f);
			body->BodyUpdate(deltaTime);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

	for(const auto& body : bodies){
		if(body->shape->GetShape() == CIRCLE){
			const auto circle = std::static_pointer_cast<Circle>(body->shape);
			Graphics::DrawCircle(body->position.x, body->position.y, circle->radius, body->rotation, 0xFFFFFFFF);
		}else if(body->shape->GetShape() == BOX){
			const auto box = std::static_pointer_cast<Box>(body->shape);
			Graphics::DrawPolygon(body->position.x, body->position.y, box->worldVertices, 0xFFFFFFFF);
		}
	}
	Graphics::DrawFillRect(liquid.x + Graphics::Width() / 2, liquid.y + Graphics::Height() * 35 / 100, Graphics::Width(),  Graphics::Height() * 70/100, 0x6A78FDFF);


    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    // TODO: destroy all objects in the scene

    Graphics::CloseWindow();
}
