#include "main.h"
#include <dllentry.h>

DEFAULT_SETTINGS(settings);

void dllenter() {}
void dllexit() {}

TClasslessInstanceHook(Actor*, "?spawnProjectile@Spawner@@QEAAPEAVActor@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAV2@AEBVVec3@@3@Z",
    BlockSource &region, ActorDefinitionIdentifier const &id, Actor *actor, Vec3 const &pos, Vec3 const &direction) {

    if(actor && actor->getEntityTypeId() == ActorType::Player_0) {
        
        auto newPos = pos;
        Vec2 rotation = actor->mRot;
        constexpr double rad = 0.01745329251;

        rotation.y = (rotation.y + 90.0) * rad;
        rotation.x = (rotation.x * -rad);
        double verticalMovement = cos(rotation.x);

        if (settings.FishingRodOffsetEnabled && id.identifier == "fishing_hook") {
            newPos.x += (cos(rotation.y) * verticalMovement) * settings.FishingRodZOffset;
            newPos.y += (sin(rotation.x) * settings.FishingRodZOffset) + settings.FishingRodYOffset;
            newPos.z += (sin(rotation.y) * verticalMovement) * settings.FishingRodZOffset;
        }
        else if (settings.SplashPotionOffsetEnabled && id.identifier == "splash_potion") {
            newPos.x += (cos(rotation.y) * verticalMovement) * settings.SplashPotionZOffset;
            newPos.y += (sin(rotation.x) * settings.SplashPotionZOffset) + settings.SplashPotionYOffset;
            newPos.z += (sin(rotation.y) * verticalMovement) * settings.SplashPotionZOffset;
        }
        else {
            newPos.x += (cos(rotation.y) * verticalMovement) * settings.ProjectileZOffset;
            newPos.y += (sin(rotation.x) * settings.ProjectileZOffset) + settings.ProjectileYOffset;
            newPos.z += (sin(rotation.y) * verticalMovement) * settings.ProjectileZOffset;
        }

        auto* projectile = original(this, region, id, actor, newPos, direction);
        projectile->setPos(newPos);
        return projectile;
    }
    return original(this, region, id, actor, pos, direction);
}