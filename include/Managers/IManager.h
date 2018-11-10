#pragma once
namespace CodeNamePaste {
class IManager {
public:
    virtual ~IManager() = default;
    
    void DoInit() = 0;  // Throws on fatal failure
    void DoTick() = 0;
    bool DoShutdown() = 0;
};
}
