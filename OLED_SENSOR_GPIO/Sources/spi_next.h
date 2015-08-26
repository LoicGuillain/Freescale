/*
 * spi_next.h
 *
 *  Created on: 18 juin 2015
 *      Author: dusautois
 */

#ifndef SPI_NEXT_H_
#define SPI_NEXT_H_

void spi_next_init();
void spi_next_free();
uint8_t spi_next_transmit(uint8_t byte);
uint16_t spi_next_frame(uint8_t *send, uint16_t length_send, uint8_t *recv, uint16_t length_recv);
uint32_t spi_next_getversion();

#define NEXT_MAX_ROW    180
#define NEXT_MAX_COL    256
#define NEXT_DIAG_SIZE    9
#define NEXT_DIAG_DATA   "\x55\x55\x55\x55\x55\x55\x55\x55\x00"

byte Next_calibrate();
byte Next_isFinger();
byte Next_getFinger(byte* data);
byte Next_getHalfFinger(byte* data);

uint32_t Next_version();
byte Next_serial(byte* data);
byte Next_isConnected();
byte Next_diagnostic(byte out[NEXT_DIAG_SIZE]);
byte Next_stop(byte scanCount);



#endif
