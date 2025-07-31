#include "Rocket.h"
#include "EngineInc.h"
#include "Enemy.h"
#include "Player.h"

void Rocket::Update(float dt)
{
    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;
    velocity = force;

    transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    float angle = transform.rotation + swaws::random::getReal(-60.0f, 60.0f);
    swaws::vec2 velocity = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(angle));
    velocity *= swaws::random::getReal(80.0f, 150.0f);

    swaws::Particle particle;
    particle.position = transform.position;
    particle.velocity = velocity;
    particle.color = (tag == "enemy") ? swaws::vec3{ 0, 1, 1 } : swaws::vec3{ 1, 1, 1 };
    particle.lifespan = swaws::random::getReal(50.f, 120.0f);

    swaws::GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other)
{
    if (other->tag != tag)
    {
        destroyed = true;
    }
    std::cout << other->tag << std::endl;
}

