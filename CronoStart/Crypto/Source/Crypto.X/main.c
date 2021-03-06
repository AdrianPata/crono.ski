/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on May 3, 2016, 11:29 AM
 */


#include <xc.h>
#include <string.h>
#include "sha256.h"
#include "aes256.h"
#include "hmac.h"
#include "base64.h"
#include "crc8.h"

// CONFIG1H
#pragma config FOSC = INTIO67   // Internal oscillator block
#pragma config PLLCFG = OFF      // 4X PLL Enable (Oscillator multiplied by 4)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

#define _XTAL_FREQ 16000000

/*
 * http://www.fileformat.info/tool/hash.htm
 * http://www.freeformatter.com/hmac-generator.html#ad-output
 * http://www.xorbin.com/tools/sha256-hash-calculator 
 */

void main(void) {
    IRCF2=1;IRCF1=1;IRCF0=1; //HFINTOSC ? (16 MHz)
    
    
    char a=8;
    char r;
    
    r=a%3;
    TX1REG=r;
    
    //***************** CRC8
    //char msg[]={0x09,0x97,0xAD,0x02,0x00};
    //char r=CRCCalc(msg,5);
    
    //TX1REG=r;
    
    /*
    BYTE text1[] = "abc";
    BYTE buf1[SHA256_BLOCK_SIZE];
    BYTE mes[64];
    
    memset(mes,0x36,sizeof mes);
    mes[0]=0x55;
    mes[1]=0x59;
    mes[2]=0x42;
    mes[3]=0x59;
    mes[4]=0x5F;
    
    SHA256_CTX ctx1;
    sha256_init(&ctx1);
	sha256_update(&ctx1, mes, 55);
	sha256_final(&ctx1, buf1);
    */
    
    //***************** Base64
    /*
    char msg[]="YW55IGNhcm5hbCBwbGVhc3VyZQ==";
    char len=strlen(msg);
    char rez[200];
    
    base64_decode(msg,&len,rez);
    
    TX1REG=rez[0];
     */
    
    //*************** HMAC
    //BYTE msg[]="abc";
    //BYTE key[SHA256_BLOCK_SIZE]="cotoi";
    
    //hmac(key,msg);
    
    
    
    
    /*
    unsigned long long bitlen;
    char a;
    bitlen=0xAABBCCDD;
    a=bitlen>>8;
    TX1REG=a;
    return;
    */
    
    //******************** AES
    
    //aes256_context ctx; 
    //uint8_t key[32];
    //uint8_t buf[16], i;

    /* put a test vector */
    //for (i = 0; i < sizeof(buf);i++) buf[i] = i * 16 + i;
    //for (i = 0; i < sizeof(key);i++) key[i] = i;
    
    //aes256_init(&ctx, key);
    //aes256_encrypt_ecb(&ctx, buf);
}
