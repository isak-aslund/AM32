#include "main.h"

#pragma once

#ifndef EEPROM_H_
#define EEPROM_H_

typedef union EEprom_u {
    struct {
        uint8_t reserved_0; //0
        uint8_t eeprom_version; //1
        uint8_t reserved_1; //2
        struct {        
            uint8_t major; //3
            uint8_t minor; //4
        } version;
        uint8_t max_ramp;    //5 0.1% per ms to 25% per ms 
        uint8_t minimum_duty_cycle; //6  0.2% to 51 percent
        uint8_t disable_stick_calibration; //7 
        uint8_t absolute_voltage_cutoff;  //8  voltage level 1 to 100 in 0.5v increments
        uint8_t current_P; //9  0-255
        uint8_t current_I; //10 0-255
        uint8_t current_D; //11 0-255
        uint8_t active_brake_power; //12  1-5 percent duty cycle
        uint8_t brake_on_zero_throttle; // brake behavior when throttle is 0 but motor is still rotating
        char reserved_eeprom_3[3]; //13-16  
        uint8_t dir_reversed; // 17
        uint8_t bi_direction; // 18
        uint8_t use_sine_start; // 19
        uint8_t comp_pwm; // 20
        uint8_t variable_pwm; // 21
        uint8_t stuck_rotor_protection; // 22
        uint8_t advance_level; // 23
        uint8_t pwm_frequency; // 24
        uint8_t startup_power; // 25
        uint8_t motor_kv; // 26
        uint8_t motor_poles; // 27
        uint8_t brake_on_stop; // 28  // brake behavior after rotation has stopped
        uint8_t stall_protection; // 29
        uint8_t beep_volume; // 30
        uint8_t telemetry_on_interval; // 31
        struct {
            uint8_t low_threshold; // 32
            uint8_t high_threshold; // 33
            uint8_t neutral; // 34
            uint8_t dead_band; // 35
        } servo;
        uint8_t low_voltage_cut_off; // 36
        uint8_t low_cell_volt_cutoff; // 37
        uint8_t rc_car_reverse; // 38
        uint8_t use_hall_sensors; // 39
        uint8_t sine_mode_changeover_thottle_level; // 40
        uint8_t drag_brake_strength; // 41
        uint8_t driving_brake_strength; // 42
        struct {
            uint8_t temperature; // 43
            uint8_t current; // 44
        } limits;
        uint8_t sine_mode_power; // 45
        uint8_t input_type; // 46
        uint8_t auto_advance; // 47
        uint8_t tune[128]; // 48-175
        struct {
            uint8_t can_node; // 176
            uint8_t esc_index; // 177
            uint8_t require_arming; // 178
            uint8_t telem_rate; // 179
            uint8_t require_zero_throttle; // 180
            uint8_t filter_hz; // 181
            uint8_t debug_rate; // 182
            uint8_t term_enable; // 183
        } can;
        struct {
            uint8_t demag_blank; // 184  0=off, 1-4 post-commutation zero cross blanking strength
            uint8_t comm_filter; // 185  0=legacy 50% IIR, 1-4 low gain interval filter with outlier clamp
            uint8_t soft_comm; // 186  0=off, 1-4 soft commutation ramp length (needs HAVE_PHASE_BLEND target)
            uint8_t soft_start; // 187  0=off, 1-50 folding prop sine soft start, ramp time in 0.1s units (5=0.5s, 10=1s)
            uint8_t soft_start_erpm; // 188  soft start handover speed in hundreds of erpm, 5-100
        } quiet;
        uint8_t reserved_2[3]; // 189-191
        struct {
            uint8_t mode; // 192  0=off, 1=closed-loop eRPM governor
            uint8_t max_erpm_lo; // 193  eRPM at 100% throttle, uint16 LE in units of 100 eRPM
            uint8_t max_erpm_hi; // 194
            uint8_t kp; // 195  proportional gain (normalised, 0-255)
            uint8_t ki; // 196  integral gain
            uint8_t kd; // 197  derivative gain (acts on the slow speed estimate)
            uint8_t spd_filter; // 198  speed-estimate filter time constant (ms) for the P/I path, 1-100
            uint8_t d_filter; // 199  extra low-pass time constant (ms) for the derivative, 1-100
            uint8_t ff_kv; // 200  linear back-emf feedforward trim, percent of the Kv-derived value (100=1.0x)
            uint8_t ff_load; // 201  quadratic propeller-load feedforward gain (0=off)
        } rpm;
        uint8_t reserved_3[54]; // 202-255
    };
    uint8_t buffer[256];
} EEprom_t;

extern EEprom_t eepromBuffer;

// void save_to_flash(uint8_t *data);
// void read_flash(uint8_t* data, uint32_t address);
// void save_to_flash_bin(uint8_t *data, int length, uint32_t add);
void read_flash_bin(uint8_t* data, uint32_t add, int out_buff_len);
void save_flash_nolib(uint8_t* data, int length, uint32_t add);

#endif /* EEPROM_H_ */
