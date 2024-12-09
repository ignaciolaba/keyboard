#include QMK_KEYBOARD_H

// Variables globales
static bool delete_mode = false;  // Indica si está activo el modo de borrar
static uint16_t registered_delete;  // Código de la tecla en modo borrar
static bool accent_active = false;  // Indica si el acento está activo
static bool caps_word = false;  // Indica si está activo Caps Word

// Función para interrumpir modificadores (opcional)
void interrupt_mods(void) {
    // Lógica personalizada para manejar modificadores (si es necesario)
}

// Función para manejar modificadores
void mod_key_handler(uint16_t keycode, bool down, keyrecord_t *record) {
    // Implementa aquí cualquier lógica para manejar teclas modificadoras
}

// Función para manejar Caps Word
void set_caps(bool enable, bool word_mode, bool persistent) {
    caps_word = enable;
    if (enable) {
        register_code(KC_CAPS);
    } else {
        unregister_code(KC_CAPS);
    }
}

// Función principal para manejar acentos y caracteres especiales
bool process_accents(uint16_t keycode, bool down, keyrecord_t *record) {
    if (delete_mode) {
        if (down) {
            if (keycode == KC_GRV) {  // Tecla para activar borrar
                register_code(registered_delete);
            } else {
                unregister_code(registered_delete);
                delete_mode = false;
                return true;
            }
        } else {
            if (keycode == KC_GRV) {
                unregister_code(registered_delete);
            }
        }
        return false;  // Detiene el procesamiento de otras teclas
    }

    if (!down) return true;  // Ignora teclas liberadas

    switch (keycode) {
        case KC_QUOT:  // Tecla de tilde ´
            accent_active = true;
            return false;

        case KC_A: case KC_E: case KC_I: case KC_O: case KC_U:  // Vocales con acento
            if (accent_active) {
                tap_code16(ES_ACUT);  // Acento ´
                accent_active = false;
            }
            tap_code16(keycode);  // Envía la vocal
            return false;

        case KC_N:  // Manejo de la ñ
            if (accent_active) {
                tap_code16(ES_NTIL);  // Enviar ñ
                accent_active = false;
            } else {
                tap_code16(keycode);  // Enviar n normal
            }
            return false;

        case KC_GRV:  // Manejo de la tecla para borrar
            delete_mode = true;
            registered_delete = KC_BSPC;  // Borrar con Backspace
            register_code(registered_delete);
            return false;

        default:
            if (accent_active) {
                accent_active = false;  // Desactivar acento si no hay vocal
            }
            return true;  // Procesar otras teclas
    }

     // Verifica si está activa la combinación MO(1) + KC_SCLN
    if (IS_LAYER_ON(1) && keycode == KC_SCLN && record->event.pressed) {
        tap_code(KC_COMM);  // Envía KC_SCLN
        return false;       // Detiene el procesamiento adicional
    }

    // Llama al procesamiento de acentos
    if (!process_accents(keycode, record->event.pressed, record)) {
        return false;
    }

    // Debug de la tecla presionada
    if (record->event.pressed) {
        uprintf("Key pressed: %u\n", keycode);
    }

    return true;
}
