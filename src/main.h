#pragma once

#include <hook.h>
#include <base/base.h>
#include <base/log.h>
#include <yaml.h>
#include <Actor/Actor.h>
#include <Actor/ActorType.h>
#include <Actor/ActorDefinitionIdentifier.h>
#include <Actor/Player.h>
#include <Math/Vec2.h>
#include <Math/Vec3.h>

struct Settings {
	float ProjectileYOffset = 0.0;
	float ProjectileZOffset = 0.0;
	bool FishingRodOffsetEnabled = false;
	float FishingRodYOffset = 0.0;
	float FishingRodZOffset = 0.0;
	bool SplashPotionOffsetEnabled = false;
	float SplashPotionYOffset = 0.0;
	float SplashPotionZOffset = 0.0;

	template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) { 
		
		return f(settings.ProjectileYOffset, node["ProjectileYOffset"]) &&
			f(settings.ProjectileZOffset, node["ProjectileZOffset"]) &&
			f(settings.FishingRodOffsetEnabled, node["FishingRodOffsetEnabled"]) &&
			f(settings.FishingRodYOffset, node["FishingRodYOffset"]) &&
			f(settings.FishingRodZOffset, node["FishingRodZOffset"]) &&
			f(settings.SplashPotionOffsetEnabled, node["SplashPotionOffsetEnabled"]) &&
			f(settings.SplashPotionYOffset, node["SplashPotionYOffset"]) &&
			f(settings.SplashPotionZOffset, node["SplashPotionZOffset"]);
	}
} settings;

DEF_LOGGER("RelativeProjectileOffset");