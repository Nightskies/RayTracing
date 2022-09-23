#pragma once
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

using Materials = std::variant<Lambertian, Metal, Dielectric>;