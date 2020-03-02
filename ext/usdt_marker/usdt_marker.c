#include "usdt_marker.h"

VALUE rb_mUsdtMarker;

void
Init_usdt_marker(void)
{
  rb_mUsdtMarker = rb_define_module("UsdtMarker");
}
