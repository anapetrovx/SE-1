#include <xc.h>

void initADCmodule(void){
    // configurar puertos de entrada An0,An1 y An2
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    ANSELbits.ANS0 = 1;
    ANSELbits.ANS1 = 1;
    ANSELbits.ANS2 = 1;
    
    ADCON0bits.ADCS0 = 0; // TAD 1.6 us
    ADCON0bits.ADCS1 = 1; // TAD 1.6 us
    ADCON1bits.VCFG0 = 0; // Internal VREF+ == VDD
    ADCON1bits.VCFG1 = 0; // Internal VREF- == VSS
    ADCON0bits.CHS = 0b0000; // Initial channel is AN0
    ADCON1bits.ADFM = 1; // Right justify lecture
    ADCON0bits.ADON = 1; // Enable ADC chip
    PIE1bits.ADIE = 1; // Enable ADC interrupt
    
    // configurar timer 0 para contar el ADC_HOLD_TIME
    
    INTCONbits.T0IE = 0; // interrupciones desactivadas (polling)
    OPTION_REGbits.T0CS =0; //FOSC/4
    OPTION_REGbits.PSA =1; // No es necesario preescalado (contar hasta 4.67 uS) 
    
}

void initTIMER1module(void){
    T1CONbits.TMR1GE = 0;
    T1CONbits.TMR1ON = 0;
    T1CONbits.TMR1CS = 0; //internal clock 5 MHz
    T1CONbits.T1CKPS = 0b00; // prescale = 1;
    T1CONbits.T1INSYNC = 0;
    PIE1bits.TMR1IE = 1; // enable interrupt
    PIR1bits.TMR1IF = 0;
    //load timer 1 with 15536 = 3CB0
    TMR1L = 0xB0;
    TMR1H = 0x3C;
    T1CONbits.TMR1ON = 1;
}


void initHardware(void) {
    initADCmodule();
    initTIMER1module();
    //@TODO add initialization methods from other members of the group
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}