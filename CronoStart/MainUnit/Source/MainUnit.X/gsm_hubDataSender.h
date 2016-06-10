/* 
 * File:   gsm_hubDataSender.h
 * Author: Adi
 *
 * Created on June 3, 2016, 7:23 PM
 */

#ifndef GSM_HUBDATASENDER_H
#define	GSM_HUBDATASENDER_H

void gsm_prepare_sendID();
void gsm_sendData();
void gsm_prepare_sendData(const char* b,char len);

#endif	/* GSM_HUBDATASENDER_H */

