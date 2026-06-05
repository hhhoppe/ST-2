// Copyright 2022 UNN-CS

#include "tasks.h"
#include "circle.h"

double calculateEarthRopeGap() {
    const double earthRadiusMeters = 6378100.0;
    const double addedLength = 1.0;
    
    Circle oldEarth(earthRadiusMeters);
    double oldFerence = oldEarth.getFerence();
    
    double newFerence = oldFerence + addedLength;
    
    Circle newEarth(0.0);
    newEarth.setFerence(newFerence);
    double newRadius = newEarth.getRadius();
    
    return newRadius - earthRadiusMeters;
}

PoolCost calculatePoolCosts() {
    const double poolRadius = 3.0;
    const double pathWidth = 1.0;
    const double concretePrice = 1000.0;
    const double fencePrice = 2000.0;
    
    Circle pool(poolRadius);
    
    Circle outer(poolRadius + pathWidth);
    
    double pathArea = outer.getArea() - pool.getArea();
    
    double fenceLength = outer.getFerence();
    
    PoolCost costs;
    costs.concrete = pathArea * concretePrice;
    costs.fence = fenceLength * fencePrice;
    
    return costs;
}
