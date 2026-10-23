#include "HudGauge.hpp"
#include "EclDiagnostic.hpp"

namespace th20 {

HudGauge::HudGauge() : fraction(0.0f), value_04(0) {}

FrontBossPanel::FrontBossPanel() noexcept
    : field_00(0.0f), field_04(0.0f), field_08(0), field_0c(0),
      field_4c(0), field_50(0) {}

FrontFlags::FrontFlags() noexcept {
    fields.bit_0 = 0;
    fields.field_1 = 0;
    fields.bit_3 = 0;
    fields.bit_4 = 0;
    fields.field_5 = 0;
    fields.bit_8 = 0;
    fields.field_9 = 0;
    fields.field_11 = 0;
    fields.bit_13 = 0;
}

FrontInf* current_front;

FrontInf::FrontInf()
    : field_50(0), fields_54{}, field_6c(0), fields_70{}, field_88(0), fields_8c{},
      field_11c(0), field_120(0.0f), field_124(0.0f), field_128(0), field_12c(0),
      field_130(0), field_134(0), field_138(0), field_150(nullptr),
      field_158(0), field_160(0), field_168(0), message_file(nullptr),
      field_174(0.0f), field_178(0.0f), field_17c(0), field_180(0), field_1b8(0),
      dialogue(nullptr), message_bytes(nullptr), field_1c4(0), field_1c8(0),
      field_1cc(0), field_2d0(0) {
    ecl_diagnostic_hint("initialize FrontInf\n");
    current_front = this;
}

std::int32_t FrontInf::has_dialogue() { return dialogue ? 1 : 0; }

void FrontInf::set_field_180(std::int32_t value) { field_180 = value; }

void FrontInf::set_boss_gauge(std::int32_t boss, std::int32_t marker,
                             float fraction, std::int32_t value) {
    boss_panels[boss].gauges[marker].fraction = fraction;
    boss_panels[boss].gauges[marker].value_04 = static_cast<std::uint32_t>(value);
}

} // namespace th20
