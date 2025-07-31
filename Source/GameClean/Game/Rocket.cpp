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

    //// Emit multiple particles for visible spread
    //const int numParticles = 8; // Adjust for more/less particles
    //for (int i = 0; i < numParticles; ++i)
    //{
    //    float angle = transform.rotation + swaws::random::getReal(-90.0f, 90.0f);
    //    swaws::vec2 velocity = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(angle));
    //    velocity *= swaws::random::getReal(-180.0f, 180.0f);

    //    swaws::Particle particle;
    //    particle.position = transform.position;
    //    particle.velocity = velocity;
    //    particle.color = (tag == "enemy") ? swaws::vec3{ 0, 1, 1 } : swaws::vec3{ 1, 1, 1 };
    //    particle.lifespan = swaws::random::getReal(0.15f, 0.3f);

    //    swaws::GetEngine().GetPS().AddParticle(particle);
    //}

    swaws::Particle particle;
    particle.position = transform.position;
    particle.velocity = swaws::vec2{ swaws::random::getReal(-50.0f, 50.0f), swaws::random::getReal(-50.0f, 50.0f) };
    particle.color = swaws::vec3{ 1, 1, 1 };
    particle.lifespan = 0.25f;

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

