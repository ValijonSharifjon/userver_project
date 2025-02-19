#include "scan.hpp"
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/formats/json.hpp>
#include <userver/formats/json/value_builder.hpp>
#include "../network/scanner.hpp"

namespace scan_namespace {
    namespace {
        class ScanHandler final : public userver::server::handlers::HttpHandlerBase {
            public: 
                static constexpr std::string_view kName = "scan";
                using HttpHandlerBase::HttpHandlerBase;

                std::string HandleRequestThrow(
                    const userver::server::http::HttpRequest& request,
                    userver::server::request::RequestContext&
                ) const override {
                    auto network = request.GetArg("network");

                    if (network.empty()) {
                        throw userver::server::handlers::ClientError(
                            userver::server::handlers::ExternalBody{"Missing 'network' parameter"}
                        );
                    }

                    auto devices = network_scanner::ScanNetwork(network);

                    userver::formats::json::ValueBuilder json_builder;

                    for (const auto& device : devices) {
                        userver::formats::json::ValueBuilder device_json;
                        device_json["ip"] = device.ip;
                        device_json["name"] = device.name;
                        device_json["online"] = device.online;
                        json_builder.PushBack(std::move(device_json));
                    }

                    return userver::formats::json::ToString(json_builder.ExtractValue());
                }
        };
    }

    void AppendScanHandler(userver::components::ComponentList &component_list) {
        component_list.Append<ScanHandler>();
    }
}