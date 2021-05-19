#include <dllentry.h>
#include "global.h"

Settings settings;
DEFAULT_SETTINGS(settings);

void dllenter() {}
void dllexit() {}
void PreInit() {}
void PostInit() {}

TClasslessInstanceHook(Actor*, "?spawnProjectile@Spawner@@QEAAPEAVActor@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAV2@AEBVVec3@@3@Z",
    BlockSource &region, ActorDefinitionIdentifier const &id, Actor *actor, Vec3 const &pos, Vec3 const &direction) {

    if(auto* player = dynamic_cast<Player*>(actor)) {
    	//position vector
        Vec3 newPos(pos);
        //direction vector
        Vec2 rotation = direct_access<Vec2>(player, 256);

        float rad = 0.0174533f;//M_PI / 180.f

        rotation.y = (rotation.y + 90.f) * rad;
        rotation.x = (rotation.x * -rad);

        float verticalMovement = cos(rotation.x);
        newPos.x += (cos(rotation.y) * verticalMovement) * settings.ProjectileZOffset;

        if(id.identifier == "fishing_hook") {
            newPos.y += (sin(rotation.x) * settings.ProjectileZOffset) + settings.FishingRodYOffset;
            newPos.z += (sin(rotation.y) * verticalMovement) * settings.FishingRodZOffset;
        } else {
            newPos.y += (sin(rotation.x) * settings.ProjectileZOffset) + settings.ProjectileYOffset;
            newPos.z += (sin(rotation.y) * verticalMovement) * settings.ProjectileZOffset;
        }

        auto* projectile = original(this, region, id, actor, newPos, direction);
        projectile->setPos(newPos);
        return projectile;
    }
    return original(this, region, id, actor, pos, direction);
}