/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

#define LED_ON()    do { DDRC |= (1<<5); PORTC |= (1<<5); } while (0)
#define LED_OFF()   do { DDRC &= ~(1<<5); PORTC &= ~(1<<5); } while (0)
#define LED_TGL()   do { DDRC |= (1<<5); PINC |= (1<<5); } while (0)

void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    //debug
    debug_matrix = true;
    LED_ON();
    _delay_ms(500);
    LED_OFF();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Row pin configuration
 * row: 0   1   2   3   4   5
 * pin: B5  B4  B3  B2  B1  B0
 */
static void init_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRB  &= ~0b00111111;
    PORTB |= 0b00111111;
}

static uint8_t read_rows(void)
{
    return (PINB&(1<<5) ? 0 : (1<<0)) |
           (PINB&(1<<4) ? 0 : (1<<1)) |
           (PINB&(1<<3) ? 0 : (1<<2)) |
           (PINB&(1<<2) ? 0 : (1<<3)) |
           (PINB&(1<<1) ? 0 : (1<<4)) |
           (PINB&(1<<0) ? 0 : (1<<5));
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
 * pin: D5  C7  C6  D4  D0  E6  F0  F1  F4  F5  F6  F7  D7  D6
 */
static void unselect_cols(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRC  |= 0b11000000; // PC: 7 6
    PORTC |= 0b11000000;
    DDRD  |= 0b11111111; // PD: 7 6 5 4 3 2 1 0
    PORTD |= 0b11111111;
    DDRE  |= 0b01000000; // PE: 6
    PORTE |= 0b01000000;
    DDRF  |= 0b11110011; // PF: 7 6 5 4 1 0
    PORTF |= 0b11110011;
}

static void select_col(uint8_t col)
{
    // Output low(DDR:1, PORT:0) to select
    switch (col) {
        case 0:
            DDRD  |= (1<<5);
            PORTD &= ~(1<<5);
            break;
        case 1:
            DDRC  |= (1<<7);
            PORTC &= ~(1<<7);
            break;
        case 2:
            DDRC  |= (1<<6);
            PORTC &= ~(1<<6);
            break;
        case 3:
            DDRD  |= (1<<4);
            PORTD &= ~(1<<4);
            break;
        case 4:
            DDRD  |= (1<<0);
            PORTD &= ~(1<<0);
            break;
        case 5:
            DDRE  |= (1<<6);
            PORTE &= ~(1<<6);
            break;
        case 6:
            DDRF  |= (1<<0);
            PORTF &= ~(1<<0);
            break;
        case 7:
            DDRF  |= (1<<1);
            PORTF &= ~(1<<1);
            break;
        case 8:
            DDRF  |= (1<<4);
            PORTF &= ~(1<<4);
            break;
        case 9:
            DDRF  |= (1<<5);
            PORTF &= ~(1<<5);
            break;
        case 10:
            DDRF  |= (1<<6);
            PORTF &= ~(1<<6);
            break;
        case 11:
            DDRF  |= (1<<7);
            PORTF &= ~(1<<7);
            break;
        case 12:
            DDRD  |= (1<<7);
            PORTD &= ~(1<<7);
            break;
        case 13:
            DDRD  |= (1<<6);
            PORTD &= ~(1<<6);
            break;
        case 14:
            DDRD  |= (1<<1);
            PORTD &= ~(1<<1);
            break;
        case 15:
            DDRD  |= (1<<2);
            PORTD &= ~(1<<2);
            break;
        case 16:
            DDRD  |= (1<<3);
            PORTD &= ~(1<<3);
            break;
    }
}
