#include <sys/sdt.h>
#include "usdt_marker.h"

VALUE rb_mUsdtMarker;

#ifndef __APPLE__
static VALUE
rb_probe_i2 (VALUE mod, VALUE arg0, VALUE arg1) {
  DTRACE_PROBE2(rubygem, usdt_marker_i2, NUM2LONG(arg0), NUM2LONG(arg1));
  return Qtrue;
}

static VALUE
rb_probe_i1s1 (VALUE mod, VALUE arg0, VALUE arg1) {
  DTRACE_PROBE2(rubygem, usdt_marker_i1s1, NUM2LONG(arg0), StringValuePtr(arg1));
  return Qtrue;
}
#else
#include <err.h>
static VALUE
rb_probe_i2 (VALUE mod, VALUE arg0, VALUE arg1) {
  warn("MacOS is never supported, because they would not have DTRACE_PROBE*\n");
  return Qtrue;
}

static VALUE
rb_probe_i1s1 (VALUE mod, VALUE arg0, VALUE arg1) {
  warn("MacOS is never supported, because they would not have DTRACE_PROBE*\n");
  return Qtrue;
}
#endif

void
Init_usdt_marker(void)
{
  rb_mUsdtMarker = rb_define_module("UsdtMarker");
  rb_define_module_function(rb_mUsdtMarker, "probe_i2", rb_probe_i2, 2);
  rb_define_module_function(rb_mUsdtMarker, "probe_i1s1", rb_probe_i1s1, 2);
}
