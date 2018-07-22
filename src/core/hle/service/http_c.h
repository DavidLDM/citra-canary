// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <unordered_map>
#include "core/hle/kernel/shared_memory.h"
#include "core/hle/service/service.h"

namespace Service {
namespace HTTP {

struct Context;
struct ClientCertContext;

class HTTP_C final : public ServiceFramework<HTTP_C> {
public:
    HTTP_C();

private:
    /**
     * HTTP_C::Initialize service function
     *  Inputs:
     *      1 : POST buffer size
     *      2 : 0x20
     *      3 : 0x0 (Filled with process ID by ARM11 Kernel)
     *      4 : 0x0
     *      5 : POST buffer memory block handle
     *  Outputs:
     *      1 : Result of function, 0 on success, otherwise error code
     */
    void Initialize(Kernel::HLERequestContext& ctx);

    /**
     * HTTP_C::CreateContext service function
     *  Inputs:
     *      1 : URL buffer size, including null-terminator
     *      2 : RequestMethod
     *      3 : (URLSize << 4) | 10
     *      4 : URL data pointer
     *  Outputs:
     *      1 : Result of function, 0 on success, otherwise error code
     *      2 : HTTP context handle
     */
    void CreateContext(Kernel::HLERequestContext& ctx);

    /**
     * HTTP_C::CreateContext service function
     *  Inputs:
     *      1 : Context handle
     *  Outputs:
     *      1 : Result of function, 0 on success, otherwise error code
     */
    void CloseContext(Kernel::HLERequestContext& ctx);

    /**
     * HTTP_C::AddRequestHeader service function
     *  Inputs:
     * 1 : Context handle
     * 2 : Header name buffer size, including null-terminator.
     * 3 : Header value buffer size, including null-terminator.
     * 4 : (HeaderNameSize<<14) | 0xC02
     * 5 : Header name data pointer
     * 6 : (HeaderValueSize<<4) | 10
     * 7 : Header value data pointer
     *  Outputs:
     *      1 : Result of function, 0 on success, otherwise error code
     */
    void AddRequestHeader(Kernel::HLERequestContext& ctx);

    Kernel::SharedPtr<Kernel::SharedMemory> shared_memory = nullptr;

    std::unordered_map<u32, Context> contexts;
    u32 context_counter = 0;

    std::unordered_map<u32, ClientCertContext> client_certs;
    u32 client_certs_counter = 0;
};

void InstallInterfaces(SM::ServiceManager& service_manager);

} // namespace HTTP
} // namespace Service
