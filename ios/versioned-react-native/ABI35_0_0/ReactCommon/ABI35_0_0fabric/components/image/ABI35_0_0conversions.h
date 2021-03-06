/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <folly/dynamic.h>
#include <ReactABI35_0_0/graphics/conversions.h>
#include <ReactABI35_0_0/imagemanager/primitives.h>

namespace facebook {
namespace ReactABI35_0_0 {

inline void fromRawValue(const RawValue &value, ImageSource &result) {
  if (value.hasType<std::string>()) {
    result = {.type = ImageSource::Type::Remote, .uri = (std::string)value};
    return;
  }

  if (value.hasType<std::unordered_map<std::string, RawValue>>()) {
    auto items = (std::unordered_map<std::string, RawValue>)value;
    result = {};

    result.type = ImageSource::Type::Remote;

    if (items.find("__packager_asset") != items.end()) {
      result.type = ImageSource::Type::Local;
    }

    if (items.find("width") != items.end() &&
        items.find("height") != items.end()) {
      result.size = {(Float)items.at("width"), (Float)items.at("height")};
    }

    if (items.find("scale") != items.end()) {
      result.scale = (Float)items.at("scale");
    } else {
      result.scale = items.find("deprecated") != items.end() ? 0.0 : 1.0;
    }

    if (items.find("url") != items.end()) {
      result.uri = (std::string)items.at("url");
    }

    if (items.find("uri") != items.end()) {
      result.uri = (std::string)items.at("uri");
    }

    if (items.find("bundle") != items.end()) {
      result.bundle = (std::string)items.at("bundle");
      result.type = ImageSource::Type::Local;
    }

    return;
  }

  abort();
}

inline std::string toString(const ImageSource &value) {
  return "{uri: " + value.uri + "}";
}

inline void fromRawValue(const RawValue &value, ImageResizeMode &result) {
  assert(value.hasType<std::string>());
  auto stringValue = (std::string)value;
  if (stringValue == "cover") {
    result = ImageResizeMode::Cover;
    return;
  }
  if (stringValue == "contain") {
    result = ImageResizeMode::Contain;
    return;
  }
  if (stringValue == "stretch") {
    result = ImageResizeMode::Stretch;
    return;
  }
  if (stringValue == "center") {
    result = ImageResizeMode::Center;
    return;
  }
  if (stringValue == "repeat") {
    result = ImageResizeMode::Repeat;
    return;
  }
  abort();
}

inline std::string toString(const ImageResizeMode &value) {
  switch (value) {
    case ImageResizeMode::Cover:
      return "cover";
    case ImageResizeMode::Contain:
      return "contain";
    case ImageResizeMode::Stretch:
      return "stretch";
    case ImageResizeMode::Center:
      return "center";
    case ImageResizeMode::Repeat:
      return "repeat";
  }
}

} // namespace ReactABI35_0_0
} // namespace facebook
