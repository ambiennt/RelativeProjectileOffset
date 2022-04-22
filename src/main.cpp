#include "main.h"
#include <dllentry.h>

DEFAULT_SETTINGS(settings);

void dllenter() {}
void dllexit() {}

TClasslessInstanceHook(Actor*,
	"?spawnProjectile@Spawner@@QEAAPEAVActor@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAV2@AEBVVec3@@3@Z",
	BlockSource &region, ActorDefinitionIdentifier const &id, Actor *spawner, Vec3 const &pos, Vec3 const &direction) {

	if(spawner && spawner->isInstanceOfPlayer()) {

		Vec3 newPos(pos);
		Vec2 rotation(spawner->mRot);

		rotation.y = (float)((rotation.y + 90.0) * INV_RADIAN_DEGREES);
		rotation.x = (float)((rotation.x * -INV_RADIAN_DEGREES));

		double verticalMovement = (double)std::cos(rotation.x);
		
		double rx = (double)(std::cos(rotation.y) * verticalMovement);
		double ry = (double)std::sin(rotation.x);
		double rz = (double)(std::sin(rotation.y) * verticalMovement);

		if (settings.FishingRodOffsetEnabled && (id.mIdentifier == "fishing_hook")) {
			newPos.x += rx * settings.FishingRodZOffset;
			newPos.y += (ry * settings.FishingRodZOffset) + settings.FishingRodYOffset;
			newPos.z += rz * settings.FishingRodZOffset;
		}
		else if (settings.SplashPotionOffsetEnabled && (id.mIdentifier == "splash_potion")) {
			newPos.x += rx * settings.SplashPotionZOffset;
			newPos.y += (ry * settings.SplashPotionZOffset) + settings.SplashPotionYOffset;
			newPos.z += rz * settings.SplashPotionZOffset;
		}
		else {
			newPos.x += rx * settings.ProjectileZOffset;
			newPos.y += (ry * settings.ProjectileZOffset) + settings.ProjectileYOffset;
			newPos.z += rz * settings.ProjectileZOffset;
		}

		auto* projectile = original(this, region, id, spawner, newPos, direction);
		projectile->setPos(newPos);
		return projectile;
	}
	return original(this, region, id, spawner, pos, direction);
}