#include "wolf.h"

sfVector2f vector2f_new(double x, double y) {
  sfVector2f vec;
  vec.x = x;
  vec.y = y;
  return vec;
}

sfVector3f vector3f_new(double x, double y, double z) {
  sfVector3f vec;
  vec.x = x;
  vec.y = y;
  vec.z = z;
  return vec;
}

sfVector2i vector2i_new(int x, int y) {
  sfVector2i vec;
  vec.x = x;
  vec.y = y;
  return vec;
}

sfColor color_new(int a, int r, int g, int b) {
  sfColor color;
  color.a = a;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}
