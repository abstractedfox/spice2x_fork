#pragma once

#include "games/game.h"
#include "external/linalg.h"
#include "touch/touch.h"

namespace games::drs {

    enum DRS_TOUCH_TYPE {
        DRS_DOWN = 0,
        DRS_UP   = 1,
        DRS_MOVE = 2,
    };

    typedef struct drs_touch {
        int type = DRS_UP;
        int id = 0;
        double x = 0.0;
        double y = 0.0;
        double width = 1;
        double height = 1;
    } drs_touch_t;

    struct VRFoot {
        uint32_t id;
        uint32_t index = ~0u;
        float length = 3.1f;
        float size_base = 0.05f;
        float size_scale = 0.1f;
        float height = 3.f;
        linalg::aliases::float4 rotation {0, 0, 0, 1};
        drs_touch_t event {};
        uint32_t get_index();
        linalg::aliases::float3 to_world(linalg::aliases::float3 pos);
    };

    extern char DRS_TAPELED[38 * 49][3];
    extern char DRS_MONITORLED[26 * 2][3];
    extern linalg::aliases::float3 VR_SCALE;
    extern linalg::aliases::float3 VR_OFFSET;
    extern float VR_ROTATION;
    extern VRFoot VR_FOOTS[2];
    extern std::vector<TouchEvent> TOUCH_EVENTS;
    extern bool DISABLE_TOUCH;
    extern bool TRANSPOSE_TOUCH;

    void fire_touches(drs_touch_t *events, size_t event_count);
    void start_vr();
    void start_touch();

    class DRSGame : public games::Game {
    public:
        DRSGame();
        virtual void attach() override;
        virtual void detach() override;
    };
}
