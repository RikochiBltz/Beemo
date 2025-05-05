sbit PRA0 at RA0_bit;
sbit PRA1 at RA1_bit;
sbit PRA2 at RA2_bit;
sbit PRA3 at RA3_bit;
sbit borne at RA4_bit;
sbit PRA5 at RA5_bit;

sbit RESERVER at RB0_bit;
sbit MOTOR1 at RB1_bit;
sbit MOTOR2 at RB2_bit;
sbit displayRecharged at RB3_bit;
sbit ENTRER at RB4_bit;
sbit SORTIR at RB5_bit;
sbit PRB6 at RB6_bit;
sbit PRB7 at RB7_bit;

sbit LCD_RS at RC0_bit;
sbit BUZZER at RC1_bit;
sbit LCD_EN at RC2_bit;
sbit YELLOW_LED at RC3_bit;
sbit RED_LED at RC4_bit;
sbit GREEN_LED at RC5_bit;
sbit BLUE_LED at RC6_bit;
sbit PRC7 at RC7_bit;

sbit LCD_D0 at RD0_bit;
sbit LCD_D1 at RD1_bit;
sbit LCD_D2 at RD2_bit;
sbit LCD_D3 at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC2_bit;
sbit LCD_D0_Direction at TRISD0_bit;
sbit LCD_D1_Direction at TRISD1_bit;
sbit LCD_D2_Direction at TRISD2_bit;
sbit LCD_D3_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


unsigned int adc_result = 0;
unsigned int borne_disponibles = 1;
unsigned int nbVoiture = 0;
unsigned int nbReservation=0;
unsigned int dispoVerifier = 0;

unsigned int INTB0 = 0;
unsigned int INTB4 = 0;
unsigned int INTB5 = 0;
unsigned int INTA4 = 0;

unsigned int eepromAddress;
unsigned int totalVehiculesRecharged = 0;

unsigned int readFromEEPROM(unsigned int address) {
         return EEPROM_Read(address);
}

void writeToEEPROM(unsigned int address, unsigned int value) {
     EEPROM_Write(address, value);
     delay_ms(20);
}

void displayTotalVehiculesRecharged() {
     char buffer[16];
     LCD_cmd(_LCD_CLEAR);
     LCD_out(1, 1, "Total Recharges:");
     IntToStr(totalVehiculesRecharged, buffer);
     LCD_out(2, 1, buffer);

}

void displayBorneDispo() {
     LCD_cmd(_LCD_CLEAR);
     LCD_out(1, 1, "Borne:");
     LCD_Chr(2, 14, borne_disponibles + '0');

}

void displayNonDispo() {
     LCD_cmd(_LCD_CLEAR);
     LCD_out(1, 1, "Non dispo");
}

void displayEntrer() {
     LCD_cmd(_LCD_CLEAR);
     LCD_out(1, 1, "Entrez");
}

void displayChargement() {
     LCD_cmd(_LCD_CLEAR);
     LCD_Out(2,6,"En cours ");
     LCD_Out(1,1,"Chargement");
}

void displayChargee() {
     LCD_cmd(_LCD_CLEAR);
     LCD_Out(2,6,"Chargee");
}

void displayPasRes() {
     LCD_cmd(_LCD_CLEAR);
     LCD_out(1, 1, "Pas de");
     LCD_out(2, 1, "res");
}

void displayAuRevoir() {
     LCD_cmd(_LCD_CLEAR);
     LCD_out(1, 1, "Bye");
}

void displayBienvenue() {
     LCD_cmd(_LCD_CLEAR);
     LCD_Out(1,1,"Bienvenue Au");
     LCD_Out(2,6,"Kiosque");
}

void displayConfirmerRes() {
     LCD_cmd(_LCD_CLEAR);
     LCD_Out(1,1,"Confirmer");
}

void displayResConfirme() {
     LCD_cmd(_LCD_CLEAR);
     LCD_Out(1,1,"Reservation");
     LCD_Out(2,6,"Confirme");
}

void REDclignote() {
     RED_LED = 1;
     delay_ms(400);
     RED_LED = 0;
     delay_ms(400);
}

void GREENclignote() {
     GREEN_LED = 1;
     delay_ms(400);
     GREEN_LED = 0;
     delay_ms(400);
}

void YELLOWclignote() {
     YELLOW_LED = 1;
     delay_ms(400);
     YELLOW_LED = 0;
     delay_ms(400);
}

void BLUEclignote() {
     BLUE_LED = 1;
     delay_ms(400);
     BLUE_LED = 0;
     delay_ms(400);
}

void MOTOR1clignote() {
     MOTOR1 = 1;
     delay_ms(200);
     MOTOR1 = 0;
     delay_ms(200);
}

void MOTOR2clignote() {
     MOTOR2 = 1;
     delay_ms(200);
     MOTOR2 = 0;
     delay_ms(200);
}


void BLUEBUZZERclignote() {
     BLUE_LED = 1;
     BUZZER = 1;
     delay_ms(500);
     BLUE_LED = 0;
     BUZZER = 0;
     delay_ms(500);
}

void interrupt() {
    if (INTCON.INTF==1) {
        INTB0 = 1;
        INTCON.INTF = 0;
    }
    if (INTCON.RBIF==1){
       if (ENTRER == 1) {
          INTB4 = 1;
       }
       if (SORTIR == 1) {
          INTB5 = 1;
       }
       INTCON.RBIF= 0;
    }
    if (INTCON.T0IF == 1) {
       INTA4 = 1;
       TMR0 = 254;
       INTCON.T0IF = 0;
    }
    if (PIE2.EEIF == 1) {
       PIE2.EEIF = 0;
    }
}

void main(){
    TRISA = 0xFF;
    TRISC=0x00;
    TRISD=0x00;
    TRISB=0x39;      //0011 1001
    INTCON.GIE = 1;
    INTCON.INTE = 1;
    INTCON.RBIE = 1;
    INTCON.INTEDG = 1;
    INTCON.T0IE = 1;
    option_reg.T0CS = 1;
    PIE2.EEIE = 1;

    PORTD=0x00;
    PORTC=0x00;
    PORTB=0x00;
    ADCON1=0x80;
    TMR0 = 254;
    ADC_init();
    LCD_init();
    eepromAddress = 0x00;
    totalVehiculesRecharged = readFromEEPROM(eepromAddress);
    LCD_cmd(_LCD_CLEAR);
    LCD_cmd(_LCD_CURSOR_OFF);

    
    while(1){
             displayBienvenue();
             YELLOWclignote();
             if (INTB0 == 1) {
                INTB0 = 0;
                if (borne_disponibles <= 3) {
                    dispoVerifier = 1;
                    displayBorneDispo();
                    delay_ms(400);
                    INTCON.RBIF = 1;

                } else {
                    displayNonDispo();
                    delay_ms(400);
                }
             }
             
             if(INTB4 == 1) {
                 INTB4 = 0;

                 if (nbReservation) {
                     nbVoiture++;
                     displayEntrer();
                     MOTOR1clignote();
                     delay_ms(400);
                     nbReservation--;
                 } else {
                        displayPasRes();
                        delay_ms(400);
                 }
             }
             if(INTB5 == 1) {
                 INTB5 = 0;
                 
                 if (nbVoiture > 0) {
                     totalVehiculesRecharged++;
                     writeToEEPROM(eepromAddress, totalVehiculesRecharged);


                     nbVoiture--;
                     displayAuRevoir();
                     delay_ms(400);
                     borne_disponibles--;
                     MOTOR2clignote();
                     GREENclignote();


                 }

             }
             if (dispoVerifier) {
                 if (INTA4 == 1) {
                    INTA4 = 0;
                    displayResConfirme();
                    delay_ms(400);
                    borne_disponibles++;
                    nbReservation++;
                    dispoVerifier = 0;


                 }
                 if (TMR0 == 255) {
                    displayConfirmerRes();
                    delay_ms(400);

                 }
             } else if (INTA4 == 1) {
                 INTA4 = 0;
             }
             
             if (nbVoiture > 0) {
                 adc_result = ADC_read(0);
                 if (adc_result < 511) {
                     displayChargement();
                     REDclignote();
                 }
                 else if (adc_result >= 511) {
                     displayChargee();
                     BLUEBUZZERclignote();
                 }
             
             }
             
             if (displayRecharged == 1) {
                displayTotalVehiculesRecharged();
                delay_ms(400);
             }
    }
  }
