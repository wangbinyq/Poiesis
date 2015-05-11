// @file   Alien.h
// @author Matheus Vieira Portela
// @date   16/04/2015
//
// @brief Alien enemy game object

#include "Alien.h"

Alien::Alien(const Point& position, int numMinions)
{
    SetSprite(CFG_GETP("ALIEN_SPRITE"));
    SetCenter(position);
    hp = CFG_GETI("ALIEN_HP");
    angularSpeed = CFG_GETF("ALIEN_ANGULAR_SPEED");
    InitializeMinions(numMinions);
    explosionSoundEffect = std::unique_ptr<SoundEffect>(
        new SoundEffect(CFG_GETP("EXPLOSION_SOUND_EFFECT")));

    behaviorState = Moving;

    // Rotation vector is an unitary vector, since we only need it's direction
    rotationVector.Set(1, 0);
}

void Alien::InitializeMinions(int numMinions)
{
    float arcOffset = 2*M_PI/numMinions;

    for (int i = 0; i < numMinions; ++i)
    {
        std::weak_ptr<GameObject> minion =
            GameObjectFactory::CreateMinion(this, arcOffset*i);
        minionArray.push_back(minion);
    }
}

void Alien::RunBehavior()
{
    switch (behaviorState)
    {
        case Moving:
            MoveBehavior();
            break;
        case Shooting:
            ShootBehavior();
            break;
        case Resting:
            RestBehavior();
            break;
    }
}

void Alien::UpdateRotation(float dt)
{
    rotationVector.Rotate(angularSpeed * dt);
    SetRotation(rotationVector.GetDirection());
}

void Alien::UpdatePosition(float dt)
{
    Vector displacement = GetSpeed();
    displacement.Multiply(dt);
    
    Point position = GetCenter();
    position.Add(displacement);
    SetCenter(position);
}

void Alien::Update(float dt)
{
    RunBehavior();
    actionScheduler.Execute();
    shootCooldown.Update(dt);
    UpdatePosition(dt);
    UpdateRotation(dt);
}

void Alien::Render()
{
    RenderSprite();
}

void Alien::CreateExplosionAnimation()
{
    std::string sprite = CFG_GETP("ALIEN_EXPLOSION_SPRITE");
    int numFrames = CFG_GETI("ALIEN_EXPLOSION_NUM_FRAMES");
    float frameDuration = CFG_GETF("ALIEN_EXPLOSION_FRAME_TIME");
    GameObjectFactory::CreateStillAnimation(GetCenter(), sprite, numFrames,
        frameDuration, false);
}

void Alien::OnDeath()
{
    CreateExplosionAnimation();
    explosionSoundEffect->Play(CFG_GETI("EXPLOSION_SOUND_EFFECT_TIMES"));
}

bool Alien::IsDead()
{
    return (hp <= 0);
}

void Alien::NotifyCollision(std::shared_ptr<GameObject> other)
{
    if (other->Is("PenguinsBullet"))
        hp -= CFG_GETI("PENGUINS_BULLET_DAMAGE");

    if (IsDead())
    {
        for (unsigned int i = 0; i < minionArray.size(); ++i)
        {
            if (minionArray[i].expired())
                continue;

            auto minionPtr = minionArray[i].lock();
            auto minion = static_cast<Minion*>(minionPtr.get());
            minion->SetDead();
        }
    }
}

bool Alien::Is(std::string type)
{
    return (type == "Alien");
}

void Alien::MoveBehavior()
{
    if (actionScheduler.IsQueueEmpty())
    {
        LOG_D("[Alien] Move behavior");
        behaviorState = Shooting;

        std::shared_ptr<GameObject> playerObject =
            GameObjectManager::GetInstance().GetObject("player");

        if (playerObject)
        {
            Point point = playerObject->GetCenter();
            actionScheduler.Schedule(std::make_shared<MoveAction>(this, point,
                CFG_GETF("ALIEN_SPEED"), CFG_GETF("ALIEN_MOVE_ERROR_MARGIN")));
        }
    }
}

void Alien::ShootBehavior()
{
    if (actionScheduler.IsQueueEmpty())
    {
        LOG_D("[Alien] Shoot behavior");
        behaviorState = Resting;

        std::shared_ptr<GameObject> playerObject =
            GameObjectManager::GetInstance().GetObject("player");

        if (playerObject)
        {
            Point point = playerObject->GetCenter();
            actionScheduler.Schedule(std::make_shared<ShootAction>(this,
                minionArray, point));
        }

        shootCooldown.Set(CFG_GETF("ALIEN_REST_BEHAVIOR_TIME"));
    }
}

void Alien::RestBehavior()
{
    if (shootCooldown.IsFinished())
    {
        LOG_D("[Alien] Resting behavior");
        behaviorState = Moving;
    }
}