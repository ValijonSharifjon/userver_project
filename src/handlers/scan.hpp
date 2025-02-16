#pragma once

#include <string>
#include <userver/components/component_list.hpp>

namespace scan_namespace {
    void AppendScanHandler(userver::components::ComponentList &component_list);
}