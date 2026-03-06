// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "circle.h"
#include "tasks.h"

const double EPS = 1e-5;
const double PI = 3.14159265358979323846;

// ==================== ТЕСТЫ КОНСТРУКТОРА ====================

TEST(CircleTest, ConstructorDefault) {
    Circle c;
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ConstructorWithRadius) {
    Circle c(5.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(CircleTest, ConstructorZeroRadius) {
    Circle c(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ConstructorNegativeThrows) {
    EXPECT_THROW(Circle(-5.0), std::invalid_argument);
}

// ==================== ТЕСТЫ СЕТТЕРОВ ====================

TEST(CircleTest, SetRadiusUpdatesAll) {
    Circle c(1.0);
    c.setRadius(3.0);
    EXPECT_NEAR(c.getRadius(), 3.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 3.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 9.0, EPS);
}

TEST(CircleTest, SetFerenceUpdatesAll) {
    Circle c(1.0);
    c.setFerence(2.0 * PI * 4.0);
    EXPECT_NEAR(c.getRadius(), 4.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 4.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 16.0, EPS);
}

TEST(CircleTest, SetAreaUpdatesAll) {
    Circle c(1.0);
    c.setArea(PI * 25.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(CircleTest, SetRadiusNegativeThrows) {
    Circle c(1.0);
    EXPECT_THROW(c.setRadius(-1.0), std::invalid_argument);
    EXPECT_NEAR(c.getRadius(), 1.0, EPS);
}

TEST(CircleTest, SetFerenceNegativeThrows) {
    Circle c(1.0);
    EXPECT_THROW(c.setFerence(-1.0), std::invalid_argument);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI, EPS);
}

TEST(CircleTest, SetAreaNegativeThrows) {
    Circle c(1.0);
    EXPECT_THROW(c.setArea(-1.0), std::invalid_argument);
    EXPECT_NEAR(c.getArea(), PI, EPS);
}

TEST(CircleTest, SetRadiusZero) {
    Circle c(5.0);
    c.setRadius(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, SetFerenceZero) {
    Circle c(5.0);
    c.setFerence(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, SetAreaZero) {
    Circle c(5.0);
    c.setArea(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

// ==================== ТЕСТЫ КОРРЕКТНОСТИ ПЕРЕСЧЕТА ====================

TEST(CircleTest, MultipleSetsConsistency) {
    Circle c(2.0);
    c.setRadius(3.0);
    c.setFerence(2.0 * PI * 4.0);
    c.setArea(PI * 25.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(CircleTest, PiConsistency) {
    Circle c(2.0);
    EXPECT_NEAR(c.getFerence() / (2.0 * c.getRadius()), PI, EPS);
    EXPECT_NEAR(c.getArea() / (c.getRadius() * c.getRadius()), PI, EPS);
}

TEST(CircleTest, FerenceToArea) {
    Circle c(1.0);
    c.setFerence(10.0);
    double expectedArea = PI * std::pow(10.0 / (2.0 * PI), 2);
    EXPECT_NEAR(c.getArea(), expectedArea, EPS);
}

TEST(CircleTest, AreaToFerence) {
    Circle c(1.0);
    c.setArea(100.0);
    double expectedFerence = 2.0 * PI * std::sqrt(100.0 / PI);
    EXPECT_NEAR(c.getFerence(), expectedFerence, EPS);
}

// ==================== ТЕСТЫ ЗАДАЧИ "ВЕРЕВКА" ====================

TEST(EarthRopeTest, GapPositive) {
    double gap = solveEarthRopeTask();
    EXPECT_GT(gap, 0.0);
}

TEST(EarthRopeTest, GapFormula) {
    double gap = solveEarthRopeTask();
    double expected = 1.0 / (2.0 * PI);
    EXPECT_NEAR(gap, expected, EPS);
}

TEST(EarthRopeTest, GapInMeters) {
    double gap = solveEarthRopeTask();
    EXPECT_NEAR(gap, 0.1591549, 1e-6);
}

// ==================== ТЕСТЫ ЗАДАЧИ "БАССЕЙН" ====================

TEST(PoolTest, PathArea) {
    PoolCosts costs = solvePoolTask();
    Circle inner(3.0);
    Circle outer(4.0);
    double expectedArea = outer.getArea() - inner.getArea();
    double actualArea = costs.concrete_cost / 1000.0;
    EXPECT_NEAR(actualArea, expectedArea, EPS);
}

TEST(PoolTest, FenceLength) {
    PoolCosts costs = solvePoolTask();
    Circle outer(4.0);
    double expectedLength = outer.getFerence();
    double actualLength = costs.fence_cost / 2000.0;
    EXPECT_NEAR(actualLength, expectedLength, EPS);
}

TEST(PoolTest, ConcreteCostPositive) {
    PoolCosts costs = solvePoolTask();
    EXPECT_GT(costs.concrete_cost, 0.0);
}

TEST(PoolTest, FenceCostPositive) {
    PoolCosts costs = solvePoolTask();
    EXPECT_GT(costs.fence_cost, 0.0);
}

TEST(PoolTest, CostValues) {
    PoolCosts costs = solvePoolTask();
    EXPECT_NEAR(costs.concrete_cost, 21991.1, 10.0);
    EXPECT_NEAR(costs.fence_cost, 50265.5, 10.0);
}

// ==================== ИТОГО ТЕСТОВ ====================
// CircleTest: 15 тестов
// EarthRopeTest: 3 теста
// PoolTest: 5 тестов
// ВСЕГО: 23 теста