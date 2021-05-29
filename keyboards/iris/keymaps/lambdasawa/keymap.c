#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
         , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,    ,
         , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,    ,
    LANG2, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,RSFT,LANG1,
         , Z  , X  , C  , V  , B  ,    ,         , N  , M  ,COMM,DOT ,RSFT,    ,
                       LOWR,LGUI,LCTL,         RALT,RSFT,RASE
  ),

  [_LOWER] = LAYOUT_kc(
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
         ,PLUS,MINS,ASTR,SLSH,PERC,               AT  ,COLN,SCLN,LBRC,RBRC,    ,
         ,HASH,AMPR,PIPE,EQL ,EXLM,               TILD,QUOT,DQUO,LPRN,RPRN,    ,
         ,DLR ,CIRC,BSLS,UNDS,QUES,    ,         ,GRV ,LT  ,GT  ,LCBR,RCBR,    ,
                           ,    ,    ,             ,    ,
  ),

  [_RAISE] = LAYOUT_kc(
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
         ,LEFT,DOWN,UP  ,RGHT,    ,                   ,ENT ,SPC ,TAB ,    ,    ,
         ,HOME,PGDN,PGUP,END ,    ,    ,         ,    ,BSPC,DEL ,ESC ,    ,    ,
                           ,    ,    ,             ,    ,
  ),

  [_ADJUST] = LAYOUT_kc(
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
         ,F1  ,F2  ,F3  ,F4  ,    ,                   ,7   ,8   ,9   ,    ,    ,
         ,F5  ,F6  ,F7  ,F8  ,RST ,                   ,4   ,5   ,6   ,    ,    ,
         ,F9  ,F10 ,F11 ,F12 ,PSCR,    ,         ,0   ,1   ,2   ,3   ,    ,    ,
                           ,    ,    ,             ,    ,
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
