// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/app.h"

#include "nativeui/gfx/font.h"
#include "nativeui/menu_bar.h"
#include "nativeui/state.h"

namespace nu {

// static
App* App::GetCurrent() {
  return State::GetCurrent()->GetApp();
}

App::App() : weak_factory_(this) {
}

App::~App() {
  // The GUI members must be destroyed before we shutdown GUI engine.
  default_font_ = nullptr;
}

Font* App::GetDefaultFont() {
  if (!default_font_)
    default_font_ = new Font;
  return default_font_.get();
}

Clipboard* App::GetClipboard(Clipboard::Type type) {
  int index = static_cast<int>(type);
  if (!clipboards_[index])
    clipboards_[index].reset(new Clipboard(type));
  return clipboards_[index].get();
}

}  // namespace nu
