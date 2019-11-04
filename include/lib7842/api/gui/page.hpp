#pragma once
#include "main.h"

namespace lib7842 {

class Page {

public:
  explicit Page(lv_obj_t* iparent, const std::shared_ptr<Logger>& ilogger = Logger::getDefaultLogger());
  explicit Page(
    lv_obj_t* iparent,
    lv_color_t icolor,
    const std::shared_ptr<Logger>& ilogger = Logger::getDefaultLogger());

  Page(const Page& ipage) = delete;
  virtual ~Page();

  virtual void initialize() = 0;
  virtual void render() = 0;

protected:
  lv_obj_t* container;
  lv_style_t cStyle;
  const lv_color_t themeColor;

  std::shared_ptr<Logger> logger {nullptr};
};

} // namespace lib7842
