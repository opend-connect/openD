#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iColourControl.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iColourControl.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_ICOLOURCONTROL openD HAN-FUN iColourControl
 *             This module specifies the HAN-FUN colour control interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ICOLOURCONTROL_H__
#define __OPEND_HANFUN_ICOLOURCONTROL_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iColourControl client services.
 */
typedef enum openD_hanfun_iColourControlClient_service {
  /**
   * Send a MOVE_TO_HUE message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOHUE_ADDR,
  /**
   * Send a MOVE_TO_HUE message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOHUE,
  /**
   * Send a MOVE_HUE message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVEHUE_ADDR,
  /**
   * Send a MOVE_HUE message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVEHUE,
  /**
   * Send a STEP_HUE message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STEPHUE_ADDR,
  /**
   * Send a STEP_HUE message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STEPHUE,
  /**
   * Send a MOVE_TO_SATURATION message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOSATURATION_ADDR,
  /**
   * Send a MOVE_TO_SATURATION message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOSATURATION,
  /**
   * Send a MOVE_SATURATION message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVESATURATION_ADDR,
  /**
   * Send a MOVE_SATURATION message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVESATURATION,
  /**
   * Send a STEP_SATURATION message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STEPSATURATION_ADDR,
  /**
   * Send a STEP_SATURATION message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STEPSATURATION,
  /**
   * Send a MOVE_TO_HUE_AND_SATURATION message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOHUEANDSATURATION_ADDR,
  /**
   * Send a MOVE_TO_HUE_AND_SATURATION message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOHUEANDSATURATION,
  /**
   * Send a MOVE_TO_XY message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOXY_ADDR,
  /**
   * Send a MOVE_TO_XY message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOXY,
  /**
   * Send a MOVE_XY message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVEXY_ADDR,
  /**
   * Send a MOVE_XY message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVEXY,
  /**
   * Send a MOVE_XY message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STEPXY_ADDR,
  /**
   * Send a MOVE_XY message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STEPXY,
  /**
   * Send a MOVE_TO_COLOUR_TEMPERATURE message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOCOLOURTEMPERATURE_ADDR,
  /**
   * Send a MOVE_TO_COLOUR_TEMPERATURE message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_MOVETOCOLOURTEMPERATURE,
  /**
   * Send a STOP message to the given address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STOP_ADDR,
  /**
   * Send a STOP message to the broadcast address.
   */
  OPEND_HANFUN_ICOLOURCONTROL_CLIENT_STOP,

} openD_hanfun_iColourControlClient_service_t;

/**
 * openD Hanfun iColourControl server services.
 */
typedef enum openD_hanfun_iColourControlServer_service {
  /**
   * Check if there are transitions to run.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_HASTRANSITIONS,
  /**
   * This updates the time remaining until a transition needs to be ran.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_TRANSITION,
  /**
   * Inform the APP that a new transition was added.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_CHANGED,
  /**
   * MOVE_TO_HUE message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVETOHUE,
  /**
   * MOVE_HUE message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVEHUE,
  /**
   * STEP_HUE message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_STEPHUE,
  /**
   * MOVE_TO_SATURATION message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVETOSATURATION,
  /**
   * MOVE_SATURATION message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVESATURATION,
  /**
   * STEP_SATURATION message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_STEPSATURATION,
  /**
   * MOVE_TO_HUE_AND_SATURATION message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVETOHUEANDSATURATION,
  /**
   * MOVE_TO_XY message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVETOXY,
  /**
   * MOVE_XY message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVEXY,
  /**
   * STEP_XY message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_STEPXY,
  /**
   * MOVE_TO_COLOUR_TEMPERATURE message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_MOVETOCOLOURTEMPERATURE,
  /**
   * STOP message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ICOLOURCONTROL_SERVER_STOP,

} openD_hanfun_iColourControlServer_service_t;

/**
 * openD Hanfun iColourControl direction structure.
 */
typedef enum openD_hanfun_iColourControl_direction {
  OPEND_HANFUN_ICOLOURCONTROL_DIRECTION_UP,
  OPEND_HANFUN_ICOLOURCONTROL_DIRECTION_DOWN,
  OPEND_HANFUN_ICOLOURCONTROL_DIRECTION_SHORTEST,
  OPEND_HANFUN_ICOLOURCONTROL_DIRECTION_LONGEST,
} openD_hanfun_iColourControl_direction_t;

/**
 * openD Hanfun iColourControl xyColour structure.
 */
typedef struct openD_hanfun_iColourControl_xyColour {
  /**
   * X colour value.
   */
  uint16_t x;
  /**
   * Y colour value.
   */
  uint16_t y;
} openD_hanfun_iColourControl_xyColour_t;

/**
 * openD Hanfun iColourControl hsColour structure.
 */
typedef struct openD_hanfun_iColourControl_hsColour {
  /**
   * Hue.
   */
  uint16_t hue;
  /**
   * Saturation.
   */
  uint8_t saturation;
} openD_hanfun_iColourControl_hsColour_t;

/**
 * openD Hanfun iColourControl moveToHueMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveToHueMessage {
  /**
   * Value of the new Hue.
   */
  uint16_t hue;
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of transition in units of 100 msec.
   */
  uint16_t time;
} openD_hanfun_iColourControl_moveToHueMessage_t;

/**
 * openD Hanfun iColourControl moveHueMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveHueMessage {
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of transition in units of 100 msec.
   */
  uint16_t rate;
} openD_hanfun_iColourControl_moveHueMessage_t;

/**
 * openD Hanfun iColourControl stepHueMessage structure.
 */
typedef struct openD_hanfun_iColourControl_stepHueMessage {
  /**
   * Step size in degrees.
   */
  uint8_t step_size;
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint8_t rate;
} openD_hanfun_iColourControl_stepHueMessage_t;

/**
 * openD Hanfun iColourControl moveToSaturationMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveToSaturationMessage {
  /**
   * Value of new saturation.
   */
  uint8_t saturation;
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint16_t time;
} openD_hanfun_iColourControl_moveToSaturationMessage_t;

/**
 * openD Hanfun iColourControl moveSaturationMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveSaturationMessage {
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint16_t time;
} openD_hanfun_iColourControl_moveSaturationMessage_t;

/**
 * openD Hanfun iColourControl stepSaturationMessage structure.
 */
typedef struct openD_hanfun_iColourControl_stepSaturationMessage {
  /**
   * Step size in degrees.
   */
  uint8_t step_size;
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint16_t time;
} openD_hanfun_iColourControl_stepSaturationMessage_t;

/**
 * openD Hanfun iColourControl moveToHueAndSaturationMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveToHueAndSaturationMessage {
  /**
   * New Hue and Saturation Colour.
   */
  openD_hanfun_iColourControl_hsColour_t colour;
  /**
   * Direction of movement.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint16_t time;
} openD_hanfun_iColourControl_moveToHueAndSaturationMessage_t;

/**
 * openD Hanfun iColourControl moveToXyMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveToXyMessage {
  /**
   * New XY Colour.
   */
  openD_hanfun_iColourControl_xyColour_t colour;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint16_t time;
} openD_hanfun_iColourControl_moveToXyMessage_t;

/**
 * openD Hanfun iColourControl moveXyMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveXyMessage {
  /**
   * The rate of change in units per seconds.
   */
  int16_t x_rate;
  /**
   * The rate of change in units per seconds.
   */
  int16_t y_rate;
} openD_hanfun_iColourControl_moveXyMessage_t;

/**
 * openD Hanfun iColourControl stepXyMessage structure.
 */
typedef struct openD_hanfun_iColourControl_stepXyMessage {
  /**
   * The rate of change in units per seconds.
   */
  int16_t x_rate;
  /**
   * The rate of change in units per seconds.
   */
  int16_t y_rate;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint8_t time;
} openD_hanfun_iColourControl_stepXyMessage_t;

/**
 * openD Hanfun iColourControl moveToColourTemperatureMessage structure.
 */
typedef struct openD_hanfun_iColourControl_moveToColourTemperatureMessage {
  /**
   * Colour.
   */
  int16_t colour;
  /**
   * Time of a single step transition in units of 100 msec.
   */
  uint8_t time;
} openD_hanfun_iColourControl_moveToColourTemperatureMessage_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOHUE_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToHueAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Hue.
   */
  uint16_t hue;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Transition.
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToHueAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOHUE service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToHue {
  /**
   * Hue.
   */
  uint16_t hue;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Transition.
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToHue_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVEHUE_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveHueAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Rate of change.
   */
  uint16_t rate;
} openD_hanfun_iColourControlClientReq_moveHueAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVEHUE service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveHue {
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Rate of change.
   */
  uint16_t rate;
} openD_hanfun_iColourControlClientReq_moveHue_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STEPHUE_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stepHueAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Step size.
   */
  uint8_t step;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time to preform a single step.
   */
  uint8_t time;
} openD_hanfun_iColourControlClientReq_stepHueAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STEPHUE service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stepHue {
  /**
   * Step size.
   */
  uint8_t step;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time to preform a single step.
   */
  uint8_t time;
} openD_hanfun_iColourControlClientReq_stepHue_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOSATURATION_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToSaturationAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * New saturation value.
   */
  uint8_t saturation;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Transition time (in units of 100 ms).
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToSaturationAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOSATURATION service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToSaturation {
  /**
   * New saturation value.
   */
  uint8_t saturation;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Transition time (in units of 100 ms).
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToSaturation_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVESATURATION_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveSaturationAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Rate of change.
   */
  uint8_t rate;
} openD_hanfun_iColourControlClientReq_moveSaturationAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVESATURATION service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveSaturation {
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Rate of change.
   */
  uint8_t rate;
} openD_hanfun_iColourControlClientReq_moveSaturation_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STEPSATURATION_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stepSaturationAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Step size.
   */
  uint8_t step;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time to perform a single step.
   */
  uint8_t time;
} openD_hanfun_iColourControlClientReq_stepSaturationAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STEPSATURATION service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stepSaturation {
  /**
   * Step size.
   */
  uint8_t step;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Time to perform a single step.
   */
  uint8_t time;
} openD_hanfun_iColourControlClientReq_stepSaturation_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOHUEANDSATURATION_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToHueAndSaturationAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * New colour value.
   */
  openD_hanfun_iColourControl_hsColour_t hsColour;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Transition time (in units of 100 ms).
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToHueAndSaturationAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOHUEANDSATURATION service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToHueAndSaturation {
  /**
   * New colour value.
   */
  openD_hanfun_iColourControl_hsColour_t hsColour;
  /**
   * Direction of change.
   */
  openD_hanfun_iColourControl_direction_t direction;
  /**
   * Transition time (in units of 100 ms).
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToHueAndSaturation_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOXY_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToXyAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * New colour value.
   */
  openD_hanfun_iColourControl_xyColour_t colour;
  /**
   * Transition time (in units of 100 ms).
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToXyAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOXY service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToXy {
  /**
   * New colour value.
   */
  openD_hanfun_iColourControl_xyColour_t colour;
  /**
   * Transition time (in units of 100 ms).
   */
  uint16_t transition;
} openD_hanfun_iColourControlClientReq_moveToXy_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVEXY_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveXyAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * X rate of change (in units of sec).
   */
  uint16_t x_rate;
  /**
   * Y rate of change (in units of sec).
   */
  uint16_t y_rate;
} openD_hanfun_iColourControlClientReq_moveXyAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVEXY service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveXy {
  /**
   * X rate of change (in units of sec).
   */
  uint16_t x_rate;
  /**
   * Y rate of change (in units of sec).
   */
  uint16_t y_rate;
} openD_hanfun_iColourControlClientReq_moveXy_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STEPXY_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stepXyAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * X rate of change (in units of sec).
   */
  uint16_t x_rate;
  /**
   * Y rate of change (in units of sec).
   */
  uint16_t y_rate;
  /**
   * Time to perform a single step (in units of 100 msec).
   */
  uint8_t time;
} openD_hanfun_iColourControlClientReq_stepXyAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STEPXY service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stepXy {
  /**
   * X rate of change (in units of sec).
   */
  uint16_t x_rate;
  /**
   * Y rate of change (in units of sec).
   */
  uint16_t y_rate;
  /**
   * Time to perform a single step (in units of 100 msec).
   */
  uint8_t time;
} openD_hanfun_iColourControlClientReq_stepXy_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOCOLOURTEMPERATURE_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToColourTemperatureAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Colour.
   */
  uint16_t colour;
  /**
   * Time.
   */
  uint16_t time;
} openD_hanfun_iColourControlClientReq_moveToColourTemperatureAddr_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c MOVETOCOLOURTEMPERATURE service.
 */
typedef struct openD_hanfun_iColourControlClientReq_moveToColourTemperature {
  /**
   * Colour.
   */
  uint16_t colour;
  /**
   * Time.
   */
  uint16_t time;
} openD_hanfun_iColourControlClientReq_moveToColourTemperature_t;

/**
 * openD Hanfun iColourControl client request parameter structure of the @c STOP_ADDR service.
 */
typedef struct openD_hanfun_iColourControlClientReq_stopAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iColourControlClientReq_stopAddr_t;

/**
 * openD Hanfun iColourControl server confirm parameter structure of the @c HASTRANSITIONS and @c TRANSITION service.
 */
typedef struct openD_hanfun_iColourControlServerCfm_transition {
  /**
   * Time left for the next transition.
   */
  uint16_t transition;
} openD_hanfun_iColourControlServerCfm_transition_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVETOHUE service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveToHue {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move to Hue Message.
   */
  openD_hanfun_iColourControl_moveToHueMessage_t message;
} openD_hanfun_iColourControlServerInd_moveToHue_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVEHUE service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveHue {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move Hue Message.
   */
  openD_hanfun_iColourControl_moveHueMessage_t message;
} openD_hanfun_iColourControlServerInd_moveHue_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c STEPHUE service.
 */
typedef struct openD_hanfun_iColourControlServerInd_stepHue {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Step Hue Message.
   */
  openD_hanfun_iColourControl_stepHueMessage_t message;
} openD_hanfun_iColourControlServerInd_stepHue_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVETOSATURATION service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveToSaturation {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move to Saturation Message.
   */
  openD_hanfun_iColourControl_moveToSaturationMessage_t message;
} openD_hanfun_iColourControlServerInd_moveToSaturation_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVESATURATION service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveSaturation {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move Saturation Message.
   */
  openD_hanfun_iColourControl_moveSaturationMessage_t message;
} openD_hanfun_iColourControlServerInd_moveSaturation_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c STEPSATURATION service.
 */
typedef struct openD_hanfun_iColourControlServerInd_stepSaturation {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Step Saturation Message.
   */
  openD_hanfun_iColourControl_stepSaturationMessage_t message;
} openD_hanfun_iColourControlServerInd_stepSaturation_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVETOHUEANDSATURATION service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveToHueAndSaturation {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move to Hue and Saturation Message.
   */
  openD_hanfun_iColourControl_moveToHueAndSaturationMessage_t message;
} openD_hanfun_iColourControlServerInd_moveToHueAndSaturation_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVETOXY service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveToXy {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move to XY Message.
   */
  openD_hanfun_iColourControl_moveToXyMessage_t message;
} openD_hanfun_iColourControlServerInd_moveToXy_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVEXY service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveXy {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move XY Message.
   */
  openD_hanfun_iColourControl_moveXyMessage_t message;
} openD_hanfun_iColourControlServerInd_moveXy_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c STEPXY service.
 */
typedef struct openD_hanfun_iColourControlServerInd_stepXy {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Step XY Message.
   */
  openD_hanfun_iColourControl_stepXyMessage_t message;
} openD_hanfun_iColourControlServerInd_stepXy_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c MOVETOCOLOURTEMPERATURE service.
 */
typedef struct openD_hanfun_iColourControlServerInd_moveToColourTemperature {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Move to colour temperature Message.
   */
  openD_hanfun_iColourControl_moveToColourTemperatureMessage_t message;
} openD_hanfun_iColourControlServerInd_moveToColourTemperature_t;

/**
 * openD Hanfun iColourControl server indication parameter structure of the @c STOP service.
 */
typedef struct openD_hanfun_iColourControlServerInd_stop {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iColourControlServerInd_stop_t;

/**
 * openD Hanfun iColourControl client request structure.
 */
typedef struct openD_hanfun_iColourControlClientReq {
  /**
   * Hanfun iColourControl client service.
   */
  openD_hanfun_iColourControlClient_service_t service;

  /**
   * Hanfun iColourControl parameters.
   */
  union {
    openD_hanfun_iColourControlClientReq_moveToHueAddr_t moveToHueAddr;
    openD_hanfun_iColourControlClientReq_moveToHue_t moveToHue;
    openD_hanfun_iColourControlClientReq_moveHueAddr_t moveHueAddr;
    openD_hanfun_iColourControlClientReq_moveHue_t moveHue;
    openD_hanfun_iColourControlClientReq_stepHueAddr_t stepHueAddr;
    openD_hanfun_iColourControlClientReq_stepHue_t stepHue;
    openD_hanfun_iColourControlClientReq_moveToSaturationAddr_t moveToSaturationAddr;
    openD_hanfun_iColourControlClientReq_moveToSaturation_t moveToSaturation;
    openD_hanfun_iColourControlClientReq_moveSaturationAddr_t moveSaturationAddr;
    openD_hanfun_iColourControlClientReq_moveSaturation_t moveSaturation;
    openD_hanfun_iColourControlClientReq_stepSaturationAddr_t stepSaturationAddr;
    openD_hanfun_iColourControlClientReq_stepSaturation_t stepSaturation;
    openD_hanfun_iColourControlClientReq_moveToHueAndSaturationAddr_t moveToHueAndSaturationAddr;
    openD_hanfun_iColourControlClientReq_moveToHueAndSaturation_t moveToHueAndSaturation;
    openD_hanfun_iColourControlClientReq_moveToXyAddr_t moveToXyAddr;
    openD_hanfun_iColourControlClientReq_moveToXy_t moveToXy;
    openD_hanfun_iColourControlClientReq_moveXyAddr_t moveXyAddr;
    openD_hanfun_iColourControlClientReq_moveXy_t moveXy;
    openD_hanfun_iColourControlClientReq_stepXyAddr_t setpXyAddr;
    openD_hanfun_iColourControlClientReq_stepXy_t setpXy;
    openD_hanfun_iColourControlClientReq_moveToColourTemperatureAddr_t moveToColourTemperatureAddr;
    openD_hanfun_iColourControlClientReq_moveToColourTemperature_t moveToColourTemperature;
    openD_hanfun_iColourControlClientReq_stopAddr_t stopAddr;
  } param;
} openD_hanfun_iColourControlClientReq_t;

/**
 * openD Hanfun iColourControl server request structure.
 */
typedef struct openD_hanfun_iColourControlServerReq {
  /**
   * Hanfun iColourControl server service.
   */
  openD_hanfun_iColourControlClient_service_t service;

} openD_hanfun_iColourControlServerReq_t;

/**
 * openD Hanfun iColourControl server confirm structure.
 */
typedef struct openD_hanfun_iColourControlServerCfm {
  /**
   * Hanfun iColourControl server service.
   */
  openD_hanfun_iColourControlClient_service_t service;

  /**
   * Hanfun iColourControl parameters.
   */
  union {
    openD_hanfun_iColourControlServerCfm_transition_t hasTransitions;
    openD_hanfun_iColourControlServerCfm_transition_t transition;

  } param;
} openD_hanfun_iColourControlServerCfm_t;

/**
 * openD Hanfun iColourControl server indication structure.
 */
typedef struct openD_hanfun_iColourControlServerInd {
  /**
   * Hanfun iColourControl server service.
   */
  openD_hanfun_iColourControlClient_service_t service;

  /**
   * Hanfun iColourControl parameters.
   */
  union {
    openD_hanfun_iColourControlServerInd_moveToHue_t moveToHue;
    openD_hanfun_iColourControlServerInd_moveHue_t moveHue;
    openD_hanfun_iColourControlServerInd_stepHue_t stepHue;
    openD_hanfun_iColourControlServerInd_moveToSaturation_t moveToSaturation;
    openD_hanfun_iColourControlServerInd_moveSaturation_t moveSaturation;
    openD_hanfun_iColourControlServerInd_stepSaturation_t stepSaturation;
    openD_hanfun_iColourControlServerInd_moveToHueAndSaturation_t moveToHueAndSaturation;
    openD_hanfun_iColourControlServerInd_moveToXy_t moveToXy;
    openD_hanfun_iColourControlServerInd_moveXy_t moveXy;
    openD_hanfun_iColourControlServerInd_stepXy_t stepXy;
    openD_hanfun_iColourControlServerInd_moveToColourTemperature_t moveToColourTemperature;
    openD_hanfun_iColourControlServerInd_stop_t stop;
  } param;
} openD_hanfun_iColourControlServerInd_t;


/*! @} defgroup OPEND_HANFUN_ICOLOURCONTROL */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ICOLOURCONTROL_H__ */
#ifdef __cplusplus
}
#endif
