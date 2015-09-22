/*
 * main.h
 *
 *  Created on: 4 sept. 2015
 *      Author: lguillain
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_


#ifdef __cplusplus
extern "C" {
#endif

/* Bitmap */
#define EVENT_NOTHING_TO_DO               0x0000
#define EVENT_MSG_TO_FETCH                0x0001
#define EVENT_CMD_TO_PARSE                0x0002
#define EVENT_MSG_TO_SEND                 0x0004
#define EVENT_START_FINGER_ACQUISITION    0x0008


#define TAG_C0_MSG_FROM_WAD   0xC0
#define TAG_C8_RAPDU_FROM_WPD 0xC8

#define MAIN_SUCCESS             0
#define MAIN_ERROR_UNKNOWN_EVENT 1
#define MAIN_ERROR_UNKNOWN_MSG   2
#define MAIN_ERROR_SPI           3
#define MAIN_ERROR_NO_FINGERPRINT          4
#define MAIN_ERROR_FINGERPRINT_EXTRACT_KO          5
#define MAIN_ERROR_TRANSACTION_DONE          6

#define SLEEP_TIME 15

void set_event_interrupt(void);
void set_timer_interrupt(void);
void set_finger_is_present(bool is_present);
void Waitms(int ms);

#ifdef __cplusplus
}
#endif


#endif /* SOURCES_MAIN_H_ */
