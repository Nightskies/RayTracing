#pragma once
#include "Lambertian.h"
#include "Metal.h"

using Materials = std::variant<Lambertian, Metal>;