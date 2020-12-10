#include "stats.h"

HttpRequest ParseRequest(string_view line) {
    while (line[0] == ' ') line.remove_prefix(1);
    array<string_view, 3> result;
    size_t pos = 0;
    size_t i = 0;
    const size_t pos_end = std::string_view::npos;
    while(true) {
        size_t space = line.find(' ', pos);
        result[i++] = (space == pos_end ? line.substr(pos) : line.substr(pos, space - pos));
        if (space == pos_end) break;
        else pos = space + 1;
    }
    return {result[0], result[1], result[2]};
}

Stats::Stats() = default;

void Stats::AddMethod(string_view method) {
    ++method_stats[(method_stats.find(method) == method_stats.end() ? "UNKNOWN" : method)];
}
void Stats::AddUri(string_view uri) {
    ++uri_stats[(uri_stats.find(uri) == uri_stats.end() ? "unknown" : uri)];
}

const map<string_view, int>& Stats::GetMethodStats() const { return method_stats; }
const map<string_view, int>& Stats::GetUriStats() const { return uri_stats; }
