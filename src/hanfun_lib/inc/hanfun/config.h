#ifndef HF_CONFIG_H
#define HF_CONFIG_H

// =============================================================================
// Common
// =============================================================================

#define OFF     0
#define ON      1

// =============================================================================
// SimplePowerMeter Configuration
// =============================================================================

// In testing mode support all attributes.

#define HF_ITF_SPM_ENERGY_ATTR                  1
#define HF_ITF_SPM_POWER_ATTR                   1
#define HF_ITF_SPM_ENERGY_AT_RESET_ATTR         1
#define HF_ITF_SPM_TIME_AT_RESET_ATTR           1
#define HF_ITF_SPM_AVG_POWER_ATTR               1
#define HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR      1
#define HF_ITF_SPM_VOLTAGE_ATTR                 1
#define HF_ITF_SPM_CURRENT_ATTR                 1
#define HF_ITF_SPM_FREQUENCY_ATTR               1
#define HF_ITF_SPM_POWER_FACTOR_ATTR            1
#define HF_ITF_SPM_REPORT_INTERVAL_ATTR         1

// In testing mode support all commands.

#define HF_ITF_SPM_REPORT_CMD                   1
#define HF_ITF_SPM_RESET_CMD                    1

// =============================================================================

#define HF_PROTOCOL_FILTER_REPEATED_MAX_SIZE   10

#endif  /* HF_CONFIG_H */
