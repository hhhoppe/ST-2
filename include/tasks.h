// Copyright 2022 UNN-CS

#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

struct PoolCost {
    double concrete;
    double fence;
};

double calculateEarthRopeGap();
PoolCost calculatePoolCosts();

#endif  // INCLUDE_TASKS_H_
