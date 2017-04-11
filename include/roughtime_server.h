// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <protocol.h>
#include <stdint.h>
#include <string.h>

#include <string>
#include <utility>

namespace timeservice {

class RoughTimeServer {
 public:
  bool IsValid() const;
  bool GetTimeFromServer(roughtime::rough_time_t* timestamp) const;
  RoughTimeServer(std::string name,
                  std::string address,
                  uint8_t public_key[],
                  int public_key_len)
      : name_(std::move(name)), address_(std::move(address)) {
    if (public_key_len != ED25519_PUBLIC_KEY_LEN) {
      valid_ = false;
      return;
    }
    valid_ = true;
    memcpy(public_key_, public_key, ED25519_PUBLIC_KEY_LEN);
  }
  ~RoughTimeServer() = default;

 private:
  bool valid_;
  std::string name_;
  std::string address_;
  uint8_t public_key_[ED25519_PUBLIC_KEY_LEN];
};

}  // namespace timeservice
