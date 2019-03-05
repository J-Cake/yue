// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "nativeui/gfx/geometry/point_f.h"

#if defined(OS_MACOSX)
#include <ApplicationServices/ApplicationServices.h>
#elif defined(OS_WIN)
#include <d2d1.h>
#endif

#include "base/strings/stringprintf.h"

namespace nu {

#if defined(OS_MACOSX)
PointF::PointF(const CGPoint& r) : x_(r.x), y_(r.y) {
}

CGPoint PointF::ToCGPoint() const {
  return CGPointMake(x(), y());
}

#elif defined(OS_WIN)
D2D1_POINT_2F PointF::ToD2D1() const {
  return {x(), y()};
}
#endif

void PointF::SetToMin(const PointF& other) {
  x_ = x_ <= other.x_ ? x_ : other.x_;
  y_ = y_ <= other.y_ ? y_ : other.y_;
}

void PointF::SetToMax(const PointF& other) {
  x_ = x_ >= other.x_ ? x_ : other.x_;
  y_ = y_ >= other.y_ ? y_ : other.y_;
}

std::string PointF::ToString() const {
  return base::StringPrintf("%f,%f", x(), y());
}

PointF ScalePoint(const PointF& p, float x_scale, float y_scale) {
  PointF scaled_p(p);
  scaled_p.Scale(x_scale, y_scale);
  return scaled_p;
}


}  // namespace nu
