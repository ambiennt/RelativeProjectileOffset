#pragma once

#include <yaml.h>
#include <string>
#include <map>
#include "dll.h"
#include <hook.h>
#include <base/log.h>
#include <Actor/Actor.h>
#include <Actor/ActorDefinitionIdentifier.h>
#include <Actor/Player.h>
#include <Math/Vec2.h>
#include <Math/Vec3.h>
#include <cmath>

struct Settings {
	float ProjectileYOffset = 0.0;
	float ProjectileZOffset = 0.0;
	float FishingRodYOffset = 0.0;
	float FishingRodZOffset = 0.0;

	template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) { 
		
		return f(settings.ProjectileYOffset, node["ProjectileYOffset"]) &&
			f(settings.ProjectileZOffset, node["ProjectileZOffset"]) &&
			f(settings.FishingRodYOffset, node["FishingRodYOffset"]) &&
			f(settings.FishingRodZOffset, node["FishingRodZOffset"]);
	}
};

DEF_LOGGER("RelativeProjectileOffset");

extern Settings settings;