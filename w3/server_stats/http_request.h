#pragma once

#include <string_view>
#include <iostream>
using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;

  bool operator==(const HttpRequest &other) const {
      return ((method == other.method) && (uri == other.uri) && (protocol == other.protocol));
  }
};