#include <iostream>
#include <SDL2/SDL.h>
#include <Kiwi/PhysicsWorld.h>
#include <Kiwi/Colliders/CircleCollider.h>
#include <Kiwi/Colliders/LineCollider.h>
#include <Kiwi/Solvers/PositionSolver.h>

// Stolen from https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void DrawCollider(SDL_Renderer* renderer, Kiwi::CircleCollider* collider, Kiwi::Transform* transform)
{
    SDL_RenderDrawCircle(renderer, (int)(transform->Position.x + collider->Center.x), (int)(-transform->Position.y + collider->Center.y + 600), (int)collider->Radius);
}
void DrawCollider(SDL_Renderer* renderer, Kiwi::LineCollider* collider, Kiwi::Transform* transform)
{
    glm::vec2 vec = collider->Vec * collider->Length;
    SDL_RenderDrawLine(renderer, (int)(transform->Position.x), (int)(-transform->Position.y + 600), (int)(vec.x + transform->Position.x), (int)(-vec.y - transform->Position.y + 600));
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Chinabelle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Kiwi::Transform transform1;
    transform1.Position = glm::vec2(300.0f, 380.0f);
    Kiwi::CircleCollider collider1;
    collider1.Center = glm::vec2(0.0f);
    collider1.Radius = 32.0f;
    Kiwi::Object obj1;
    obj1.MyTransform = &transform1;
    obj1.MyCollider = &collider1;
    obj1.Velocity = glm::vec2(25.0f);

    Kiwi::Transform transform2;
    transform2.Position = glm::vec2(100.0f, 100.0f);
    Kiwi::CircleCollider collider2;
    collider2.Center = glm::vec2(0.0f);
    collider2.Radius = 32.0f;
    Kiwi::Object obj2;
    obj2.MyTransform = &transform2;
    obj2.MyCollider = &collider2;
    obj2.AffectedByGravity = false;

    Kiwi::Transform transform3;
    transform3.Position = glm::vec2(0.0f, 10.0f);
    Kiwi::LineCollider collider3;
    collider3.Vec = glm::vec2(1.0f, 0.0f);
    collider3.Length = 800;
    Kiwi::Object obj3;
    obj3.MyTransform = &transform3;
    obj3.MyCollider = &collider3;
    obj3.AffectedByGravity = false;

    Kiwi::PhysicsWorld world; 
    world.SimulationSpeed = 5.0f;
    world.AddObject(&obj1);
    world.AddObject(&obj2);
    world.AddObject(&obj3);
    world.AddSolver(new Kiwi::PositionSolver);

    bool quit = false;
    float timestep = 0.0f;
    float lastFrame = 0.0f;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                        quit = true;
                    break;

                default:
                    break;
            }
        }

        world.Step(timestep);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DrawCollider(renderer, &collider1, obj1.MyTransform);
        DrawCollider(renderer, &collider2, obj2.MyTransform);
        DrawCollider(renderer, &collider3, obj3.MyTransform);

        SDL_RenderPresent(renderer);

        float newFrame = (float)SDL_GetTicks() * 0.001f;
        timestep = newFrame - lastFrame;
        lastFrame = newFrame;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();  
}
