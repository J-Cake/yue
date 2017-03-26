// Copyright 2017 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include <node.h>

#include "nativeui/nativeui.h"
#include "node_yue/node_bindings.h"
#include "node_yue/signal.h"

namespace vb {

template<>
struct Type<nu::Size> {
  static constexpr const char* name = "yue.Size";
  static v8::Local<v8::Value> ToV8(v8::Local<v8::Context> context,
                                   const nu::Size& value) {
    auto obj = v8::Object::New(context->GetIsolate());
    Set(context, obj, "width", value.width(), "height", value.height());
    return obj;
  }
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Size* out) {
    if (!value->IsObject())
      return false;
    int width, height;
    if (!Get(context, value.As<v8::Object>(),
             "width", &width, "height", &height))
      return false;
    *out = nu::Size(width, height);
    return true;
  }
};

template<>
struct Type<nu::SizeF> {
  static constexpr const char* name = "yue.Size";
  static v8::Local<v8::Value> ToV8(v8::Local<v8::Context> context,
                                   const nu::SizeF& value) {
    auto obj = v8::Object::New(context->GetIsolate());
    Set(context, obj, "width", value.width(), "height", value.height());
    return obj;
  }
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::SizeF* out) {
    if (!value->IsObject())
      return false;
    float width, height;
    if (!Get(context, value.As<v8::Object>(),
             "width", &width, "height", &height))
      return false;
    *out = nu::SizeF(width, height);
    return true;
  }
};

template<>
struct Type<nu::RectF> {
  static constexpr const char* name = "yue.Rect";
  static v8::Local<v8::Value> ToV8(v8::Local<v8::Context> context,
                                   const nu::RectF& value) {
    auto obj = v8::Object::New(context->GetIsolate());
    Set(context, obj, "x", value.x(), "y", value.y(),
        "width", value.width(), "height", value.height());
    return obj;
  }
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::RectF* out) {
    if (!value->IsObject())
      return false;
    float x, y, width, height;
    if (!Get(context, value.As<v8::Object>(),
             "x", &x, "y", &y, "width", &width, "height", &height))
      return false;
    *out = nu::RectF(x, y, width, height);
    return true;
  }
};

template<>
struct Type<nu::Vector2dF> {
  static constexpr const char* name = "yue.Vector2d";
  static v8::Local<v8::Value> ToV8(v8::Local<v8::Context> context,
                                   const nu::Vector2dF& value) {
    auto obj = v8::Object::New(context->GetIsolate());
    Set(context, obj, "x", value.x(), "y", value.y());
    return obj;
  }
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Vector2dF* out) {
    if (!value->IsObject())
      return false;
    float x, y;
    if (!Get(context, value.As<v8::Object>(), "x", &x, "y", &y))
      return false;
    *out = nu::Vector2dF(x, y);
    return true;
  }
};

template<>
struct Type<nu::Color> {
  static constexpr const char* name = "yue.Color";
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Color* out) {
    std::string hex;
    if (!vb::FromV8(context, value, &hex))
      return false;
    *out = nu::Color(hex);
    return true;
  }
};

template<>
struct Type<nu::Accelerator> {
  static constexpr const char* name = "yue.Accelerator";
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Accelerator* out) {
    std::string description;
    if (!vb::FromV8(context, value, &description))
      return false;
    *out = nu::Accelerator(description);
    return true;
  }
};

#ifndef ELECTRON_BUILD
template<>
struct Type<nu::Lifetime> {
  static constexpr const char* name = "yue.Lifetime";
  static void BuildConstructor(v8::Local<v8::Context>, v8::Local<v8::Object>) {
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "run", &nu::Lifetime::Run,
        "quit", &nu::Lifetime::Quit,
        "postTask", &nu::Lifetime::PostTask,
        "postDelayedTask", &nu::Lifetime::PostDelayedTask);
    SetProperty(context, templ,
                "onReady", &nu::Lifetime::on_ready);
  }
};
#endif

template<>
struct Type<nu::App> {
  static constexpr const char* name = "yue.App";
  static void BuildConstructor(v8::Local<v8::Context>, v8::Local<v8::Object>) {
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
  }
};

template<>
struct Type<nu::Window::Options> {
  static constexpr const char* name = "yue.Window.Options";
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Window::Options* out) {
    auto obj = value.As<v8::Object>();
    if (obj.IsEmpty())
      return false;
    Get(context, obj, "bounds", &out->bounds);
    return true;
  }
};

template<>
struct Type<nu::Window> {
  static constexpr const char* name = "yue.Window";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor,
        "create", &NewInstance<nu::Window, nu::Window::Options>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "close", &nu::Window::Close,
        "setContentBounds", &nu::Window::SetContentBounds,
        "getContentBounds", &nu::Window::GetContentBounds,
        "setBounds", &nu::Window::SetBounds,
        "getBounds", &nu::Window::GetBounds,
        "setContentView", &nu::Window::SetContentView,
        "getContentView", &nu::Window::GetContentView,
        "setVisible", &nu::Window::SetVisible,
        "isVisible", &nu::Window::IsVisible,
        "setBackgroundColor", &nu::Window::SetBackgroundColor);
    SetProperty(context, templ,
                "onClose", &nu::Window::on_close,
                "shouldClose", &nu::Window::should_close);
  }
};

template<>
struct Type<nu::View> {
  static constexpr const char* name = "yue.View";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setBackgroundColor", &nu::View::SetBackgroundColor,
        "setStyle", &nu::View::SetStyle,
        "printStyle", &nu::View::PrintStyle,
        "layout", &nu::View::Layout,
        "setBounds", &nu::View::SetBounds,
        "getBounds", &nu::View::GetBounds,
        "setVisible", &nu::View::SetVisible,
        "isVisible", &nu::View::IsVisible,
        "getParent", &nu::View::parent);
  }
};

template<>
struct Type<nu::Container> {
  using base = nu::View;
  static constexpr const char* name = "yue.Container";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor,
        "create", &NewInstance<nu::Container>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "getPreferredSize", &nu::Container::GetPreferredSize,
        "getPreferredWidthForHeight",
        &nu::Container::GetPreferredWidthForHeight,
        "getPreferredHeightForWidth",
        &nu::Container::GetPreferredHeightForWidth,
        "addChildView", &nu::Container::AddChildView,
        "addChildViewAt", &nu::Container::AddChildViewAt,
        "removeChildView", &nu::Container::RemoveChildView,
        "childCount", &nu::Container::child_count,
        "childAt", &nu::Container::child_at);
  }
};

template<>
struct Type<nu::Button::Type> {
  static constexpr const char* name = "yue.Button.Type";
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Button::Type* out) {
    std::string type;
    if (!vb::FromV8(context, value, &type))
      return false;
    if (type.empty() || type == "normal") {
      *out = nu::Button::Normal;
      return true;
    } else if (type == "checkbox") {
      *out = nu::Button::CheckBox;
      return true;
    } else if (type == "radio") {
      *out = nu::Button::Radio;
      return true;
    } else {
      return false;
    }
  }
};

template<>
struct Type<nu::Button> {
  using base = nu::View;
  static constexpr const char* name = "yue.Button";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setTitle", &nu::Button::SetTitle,
        "getTitle", &nu::Button::GetTitle,
        "setChecked", &nu::Button::SetChecked,
        "isChecked", &nu::Button::IsChecked);
    SetProperty(context, templ,
                "onClick", &nu::Button::on_click);
  }
};

template<>
struct Type<nu::Entry> {
  using base = nu::View;
  static constexpr const char* name = "yue.Entry";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor, "create", &NewInstance<nu::Entry>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setText", &nu::Entry::SetText,
        "getText", &nu::Entry::GetText);
    SetProperty(context, templ,
                "onActivate", &nu::Entry::on_activate,
                "onTextChange", &nu::Entry::on_text_change);
  }
};

template<>
struct Type<nu::Label> {
  using base = nu::View;
  static constexpr const char* name = "yue.Label";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor,
        "create", &NewInstance<nu::Label, const std::string&>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setText", &nu::Label::SetText,
        "getText", &nu::Label::GetText);
  }
};

template<>
struct Type<nu::Progress> {
  using base = nu::View;
  static constexpr const char* name = "yue.Progress";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor, "create", &NewInstance<nu::Progress>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setValue", &nu::Progress::SetValue,
        "getValue", &nu::Progress::GetValue,
        "setIndeterminate", &nu::Progress::SetIndeterminate,
        "isIndeterminate", &nu::Progress::IsIndeterminate);
  }
};

template<>
struct Type<nu::Group> {
  using base = nu::View;
  static constexpr const char* name = "yue.Group";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor,
        "create", &NewInstance<nu::Group, const std::string&>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setContentView", &nu::Group::SetContentView,
        "getContentView", &nu::Group::GetContentView,
        "setTitle", &nu::Group::SetTitle,
        "getTitle", &nu::Group::GetTitle);
  }
};

template<>
struct Type<nu::Scroll::Policy> {
  static constexpr const char* name = "yue.Scroll.Policy";
  static v8::Local<v8::Value> ToV8(v8::Local<v8::Context> context,
                                   nu::Scroll::Policy policy) {
    if (policy == nu::Scroll::Policy::Always)
      return vb::ToV8(context, "always");
    else if (policy == nu::Scroll::Policy::Never)
      return vb::ToV8(context, "never");
    else
      return vb::ToV8(context, "automatic");
  }
  static bool FromV8(v8::Local<v8::Context> context,
                     v8::Local<v8::Value> value,
                     nu::Scroll::Policy* out) {
    std::string policy;
    if (!vb::FromV8(context, value, &policy))
      return false;
    if (policy == "automatic") {
      *out = nu::Scroll::Policy::Automatic;
      return true;
    } else if (policy == "always") {
      *out = nu::Scroll::Policy::Always;
      return true;
    } else if (policy == "never") {
      *out = nu::Scroll::Policy::Never;
      return true;
    } else {
      return false;
    }
  }
};

template<>
struct Type<nu::Scroll> {
  using base = nu::View;
  static constexpr const char* name = "yue.Scroll";
  static void BuildConstructor(v8::Local<v8::Context> context,
                               v8::Local<v8::Object> constructor) {
    Set(context, constructor, "create", &NewInstance<nu::Scroll>);
  }
  static void BuildPrototype(v8::Local<v8::Context> context,
                             v8::Local<v8::ObjectTemplate> templ) {
    Set(context, templ,
        "setScrollBarPolicy", &nu::Scroll::SetScrollBarPolicy,
        "setContentSize", &nu::Scroll::SetContentSize,
        "getContentSize", &nu::Scroll::GetContentSize,
        "setContentView", &nu::Scroll::SetContentView,
        "getContentView", &nu::Scroll::GetContentView);
  }
};

}  // namespace vb

namespace node_yue {

void Initialize(v8::Local<v8::Object> exports) {
  // Initialize the nativeui and leak it.
  new nu::State;
  new nu::Lifetime;
  // Initialize node integration and leak it.
  NodeBindings* node_bindings = NodeBindings::Create();
  node_bindings->PrepareMessageLoop();
  node_bindings->RunMessageLoop();

  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  vb::Set(context, exports,
          // GUI classes.
#ifndef ELECTRON_BUILD
          "Lifetime", vb::GetConstructor<nu::Lifetime>(context),
#endif
          "App", vb::GetConstructor<nu::App>(context),
          "Window", vb::GetConstructor<nu::Window>(context),
          "View", vb::GetConstructor<nu::View>(context),
          "Container", vb::GetConstructor<nu::Container>(context),
          "Button", vb::GetConstructor<nu::Button>(context),
          "Entry", vb::GetConstructor<nu::Entry>(context),
          "Label", vb::GetConstructor<nu::Label>(context),
          "Progress", vb::GetConstructor<nu::Progress>(context),
          "Group", vb::GetConstructor<nu::Group>(context),
          "Scroll", vb::GetConstructor<nu::Scroll>(context),
          // Methods.
#ifndef ELECTRON_BUILD
          "lifetime", nu::Lifetime::current(),
#endif
          "app", nu::State::current()->app());
}

}  // namespace node_yue

NODE_MODULE(yue, node_yue::Initialize)