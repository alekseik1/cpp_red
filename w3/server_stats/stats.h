#pragma once

#include "http_request.h"

#include <string_view>
#include <istream>
#include <map>

using namespace std;

HttpRequest ParseRequest(string_view line);

class Stats {
public:
  Stats();

  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;

protected:
    map<string_view, int> method_stats = {
            {"GET", 0},
            {"PUT", 0},
            {"POST", 0},
            {"DELETE", 0},
            {"UNKNOWN", 0},
    };
    map<string_view, int> uri_stats = {
            {"/", 0},
            {"/order", 0},
            {"/product", 0},
            {"/basket", 0},
            {"/help", 0},
            {"unknown", 0},
    };
};

