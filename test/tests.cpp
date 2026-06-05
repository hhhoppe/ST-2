// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "circle.h"
#include "tasks.h"

const double EPS = 1e-6;
const double PI = 3.14159265358979323846;

// ==================== ТЕСТЫ КОНСТРУКТОРА ====================

TEST(CircleConstructorTest, DefaultConstructor) {
    Circle c;
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleConstructorTest, ConstructorWithPositiveRadius) {
    Circle c(5.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(CircleConstructorTest, ConstructorWithZeroRadius) {
    Circle c(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleConstructorTest, ConstructorWithNegativeThrows) {
    EXPECT_THROW(Circle(-5.0), std::invalid_argument);
}

// ==================== ТЕСТЫ СЕТТЕРОВ ====================

TEST(CircleSettersTest, SetRadiusUpdatesAll) {
    Circle c(1.0);
    c.setRadius(3.0);
    EXPECT_NEAR(c.getRadius(), 3.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 3.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 9.0, EPS);
}

TEST(CircleSettersTest, SetFerenceUpdatesAll) {
    Circle c(1.0);
    c.setFerence(2.0 * PI * 4.0);
    EXPECT_NEAR(c.getRadius(), 4.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 4.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 16.0, EPS);
}

TEST(CircleSettersTest, SetAreaUpdatesAll) {
    Circle c(1.0);
    c.setArea(PI * 25.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(CircleSettersTest, SetRadiusNegativeThrows) {
    Circle c(1.0);
    EXPECT_THROW(c.setRadius(-1.0), std::invalid_argument);
    EXPECT_NEAR(c.getRadius(), 1.0, EPS);
}

TEST(CircleSettersTest, SetFerenceNegativeThrows) {
    Circle c(1.0);
    EXPECT_THROW(c.setFerence(-1.0), std::invalid_argument);
}

TEST(CircleSettersTest, SetAreaNegativeThrows) {
    Circle c(1.0);
    EXPECT_THROW(c.setArea(-1.0), std::invalid_argument);
}

TEST(CircleSettersTest, SetRadiusZero) {
    Circle c(5.0);
    c.setRadius(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleSettersTest, MultipleSetsConsistency) {
    Circle c(2.0);
    c.setRadius(3.0);
    c.setFerence(2.0 * PI * 4.0);
    c.setArea(PI * 25.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

// ==================== ТЕСТЫ ГЕТТЕРОВ ====================

TEST(CircleGettersTest, GetRadiusReturnsCorrectValue) {
    Circle c(7.5);
    EXPECT_NEAR(c.getRadius(), 7.5, EPS);
}

TEST(CircleGettersTest, GetFerenceReturnsCorrectValue) {
    Circle c(2.0);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 2.0, EPS);
}

TEST(CircleGettersTest, GetAreaReturnsCorrectValue) {
    Circle c(3.0);
    EXPECT_NEAR(c.getArea(), PI * 9.0, EPS);
}

// ==================== ТЕСТЫ МАТЕМАТИЧЕСКОЙ КОРРЕКТНОСТИ ====================

TEST(CircleMathTest, PiConsistency) {
    Circle c(2.0);
    EXPECT_NEAR(c.getFerence() / (2.0 * c.getRadius()), PI, EPS);
    EXPECT_NEAR(c.getArea() / (c.getRadius() * c.getRadius()), PI, EPS);
}

TEST(CircleMathTest, FerenceToAreaRelation) {
    Circle c(1.0);
    c.setFerence(10.0);
    double expectedArea = PI * std::pow(10.0 / (2.0 * PI), 2);
    EXPECT_NEAR(c.getArea(), expectedArea, EPS);
}

TEST(CircleMathTest, AreaToFerenceRelation) {
    Circle c(1.0);
    c.setArea(100.0);
    double expectedFerence = 2.0 * PI * std::sqrt(100.0 / PI);
    EXPECT_NEAR(c.getFerence(), expectedFerence, EPS);
}

// ==================== ТЕСТЫ ЗАДАЧИ "ЗЕМЛЯ И ВЕРЁВКА" ====================

TEST(EarthRopeTest, GapIsPositive) {
    double gap = calculateEarthRopeGap();
    EXPECT_GT(gap, 0.0);
}

TEST(EarthRopeTest, GapFormulaCheck) {
    double gap = calculateEarthRopeGap();
    double expected = 1.0 / (2.0 * PI);
    EXPECT_NEAR(gap, expected, EPS);
}

TEST(EarthRopeTest, GapApproximately16cm) {
    double gap = calculateEarthRopeGap();
    EXPECT_NEAR(gap, 0.1591549, 1e-5);
}

// ==================== ТЕСТЫ ЗАДАЧИ "БАССЕЙН" ====================

TEST(PoolTaskTest, PathAreaCorrect) {
    PoolCost costs = calculatePoolCosts();
    Circle pool(3.0);
    Circle outer(4.0);
    double expectedArea = outer.getArea() - pool.getArea();
    double actualArea = costs.concrete / 1000.0;
    EXPECT_NEAR(actualArea, expectedArea, EPS);
}

TEST(PoolTaskTest, FenceLengthCorrect) {
    PoolCost costs = calculatePoolCosts();
    Circle outer(4.0);
    double expectedLength = outer.getFerence();
    double actualLength = costs.fence / 2000.0;
    EXPECT_NEAR(actualLength, expectedLength, EPS);
}

TEST(PoolTaskTest, ConcreteCostPositive) {
    PoolCost costs = calculatePoolCosts();
    EXPECT_GT(costs.concrete, 0.0);
}

TEST(PoolTaskTest, FenceCostPositive) {
    PoolCost costs = calculatePoolCosts();
    EXPECT_GT(costs.fence, 0.0);
}

TEST(PoolTaskTest, ConcreteCostApproximate) {
    PoolCost costs = calculatePoolCosts();
    EXPECT_NEAR(costs.concrete, 21991.1, 10.0);
}

TEST(PoolTaskTest, FenceCostApproximate) {
    PoolCost costs = calculatePoolCosts();
    EXPECT_NEAR(costs.fence, 50265.5, 10.0);
}
