#include "scan.hpp"
#include <userver/server/handlers/http_handler_base.hpp>
namespace scan_namespace {
    namespace {
        class ScanHandler final : public userver::server::handlers::HttpHandlerBase {
            public: 
                static constexpr std::string_view kName = "scan";
                using HttpHandlerBase::HttpHandlerBase;

                std::string HandleRequestThrow(
                    const userver::server::http::HttpRequest&,
                    userver::server::request::RequestContext&
                ) const override {
                    return "Your ip bla bla";
                }
        };
    }

    void AppendScanHandler(userver::components::ComponentList &component_list) {
        component_list.Append<ScanHandler>();
    }
}