#pragma once
#include <stdint.h>

/// @brief Feed filament to FINDA
///
/// Continuously feed filament until FINDA is not switched ON
/// and than retract to align filament 600 steps away from FINDA.

namespace logic {

struct FeedToFinda {
    enum {
        EngagingIdler,
        PushingFilament,
        UnloadBackToPTFE,
        DisengagingIdler,
        OK,
        Failed
    };

    inline FeedToFinda()
        : state(OK)
        , feedPhaseLimited(true) {}

    /// Restart the automaton
    /// @param feedPhaseLimited
    ///  * true feed phase is limited, doesn't react on button press
    ///  * false feed phase is unlimited, can be interrupted by any button press after blanking time
    void Reset(bool feedPhaseLimited);

    /// @returns true if the state machine finished its job, false otherwise
    bool Step();

    /// This method may be used to check the result of the automaton
    /// @returns OK if everything went OK and FINDA triggered (or the user pressed a button)
    /// @returns Failed if the FINDA didn't trigger
    inline uint8_t State() const { return state; }

private:
    uint8_t state;
    bool feedPhaseLimited;
};

} // namespace logic