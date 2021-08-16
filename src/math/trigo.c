#include <math.h>
#include "wolf.h"

double cosd(double angle) {
  return (cos(angle * M_PI / 180));
}

double sind(double angle) {
  return (sin(angle * M_PI / 180));
}

double tand(double angle) {
  return (tan(angle * M_PI / 180));
}

double rad(double angle) {
  return angle * M_PI / 180;
}

double degree(double angle) {
  return angle * 180 / M_PI;
}
