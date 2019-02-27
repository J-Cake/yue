// Copyright 2019 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#ifndef NATIVEUI_GFX_ATTRIBUTED_TEXT_H_
#define NATIVEUI_GFX_ATTRIBUTED_TEXT_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "nativeui/gfx/color.h"
#include "nativeui/types.h"

namespace nu {

class Font;
class RectF;
class SizeF;
struct TextDrawOptions;

class NATIVEUI_EXPORT AttributedText : public base::RefCounted<AttributedText> {
 public:
  explicit AttributedText(const std::string& text);

  void SetFont(Font* font);
  void SetFontFor(Font* font, int start, int end);
  void SetColor(Color font);
  void SetColorFor(Color font, int start, int end);

  RectF GetBoundsFor(const SizeF& size, const TextDrawOptions& options);
  std::string GetText() const;

  NativeAttributedText GetNative() const { return text_; }

 protected:
  virtual ~AttributedText();

 private:
  friend class base::RefCounted<AttributedText>;

  void PlatformSetFontFor(Font* font, int start, int end);
  void PlatformSetColorFor(Color color, int start, int end);

  NativeAttributedText text_;

#if defined(OS_WIN)
  // IDWriteTextLayout does not provide a way to get text.
  base::string16 original_text_;
#endif
};

}  // namespace nu

#endif  // NATIVEUI_GFX_ATTRIBUTED_TEXT_H_
