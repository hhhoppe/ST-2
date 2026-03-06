// Copyright 2022 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

struct PathCosts {
  double concrete;
  double fence;
};

double earthRopeGap();
PathCosts poolExpenses();

#endif  // INCLUDE_TASKS_H_