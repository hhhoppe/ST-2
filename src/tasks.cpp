// Copyright 2022 UNN-CS

#include "tasks.h"
#include "circle.h"

namespace {
constexpr double kPoolRadius = 3.0;
constexpr double kPathWidth = 1.0;
constexpr double kConcreteCostPerSquareMeter = 1000.0;
constexpr double kFenceCostPerMeter = 2000.0;
}  // namespace

double solveEarthRopeTask() {
  return 1.0 / (2.0 * 3.14159265358979323846);
}

PoolCosts solvePoolTask() {
  Circle pool(kPoolRadius);
  Circle outer(pool.getRadius() + kPathWidth);

  const double path_area = outer.getArea() - pool.getArea();
  const double concrete_cost = path_area * kConcreteCostPerSquareMeter;
  const double fence_cost = outer.getFerence() * kFenceCostPerMeter;

  return {concrete_cost, fence_cost};
}
