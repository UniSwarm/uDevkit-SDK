
// ################################# Master configuration #################################
// FSEC
#pragma config BWRP = OFF            // Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED        // Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF            // Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF            // General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED        // General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF            // Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED        // Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF         // Alternate Interrupt Vector Table bit->Disabled AIVT

// FBSLIM
#pragma config BSLIM = 8191          // Boot Segment Flash Page Address Limit bits->

// FOSCSEL
#pragma config FNOSC = FRC           // Oscillator Source Selection->Primary
#pragma config IESO = ON             // Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC
#pragma config POSCMD = EC           // Primary Oscillator Mode Select bits->EC
#pragma config OSCIOFNC = ON         // OSC2 Pin Function bit->OSC2 is GPIO
#pragma config FCKSM = CSECME        // Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are enabled
#pragma config PLLKEN = PLLKEN_ON    // PLLKEN->PLLKEN_ON
#pragma config XTCFG = G3            // XT Config->24-32 MHz crystals
#pragma config XTBST = ENABLE        // XT Boost->Boost the kick-start

// FWDT
#pragma config RWDTPS = PS1048576    // Run Mode Watchdog Timer Post Scaler select bits->1:1048576
#pragma config RCLKSEL = LPRC        // Watchdog Timer Clock Select bits->Always use LPRC
#pragma config WINDIS = OFF          // Watchdog Timer Window Enable bit->Watchdog Timer in Window mode
#pragma config WDTWIN = WIN25        // Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config SWDTPS = PS1048576    // Sleep Mode Watchdog Timer Post Scaler select bits->1:1048576
#pragma config FWDTEN = ON_SW        // Watchdog Timer Enable bit->WDT controlled via SW, use WDTCON.ON bit

// FICD
#pragma config ICS = PGD3       // ICD Communication Channel Select bits->Communicate on PGEC3 and PGED3
#pragma config JTAGEN = OFF     // JTAG Enable bit->JTAG is disabled

// FDMTIVTL
#pragma config DMTIVTL = 65535  // Dead Man Timer Interval low word->

// FDMTIVTH
#pragma config DMTIVTH = 65535  // Dead Man Timer Interval high word->

// FDMTCNTL
#pragma config DMTCNTL = 0      // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->

// FDMTCNTH
#pragma config DMTCNTH = 0      // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->

// FDMT
#pragma config DMTDIS = OFF     // Dead Man Timer Disable bit->Dead Man Timer is Disabled and can be enabled by software

// FDEVOPT
#pragma config ALTI2C1 = OFF    // Alternate I2C1 Pin bit->I2C1 mapped to SDA1/SCL1 pins
#pragma config ALTI2C2 = OFF    // Alternate I2C2 Pin bit->I2C2 mapped to SDA2/SCL2 pins
#pragma config SMBEN = SMBUS    // SM Bus Enable->SMBus input threshold is enabled
#pragma config SPI2PIN = PPS    // SPI2 Pin Select bit->SPI2 uses I/O remap (PPS) pins

// FALTRE  G
#pragma config CTXT1 = OFF      // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits->Not Assigned
#pragma config CTXT2 = OFF      // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits->Not Assigned
#pragma config CTXT3 = OFF      // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits->Not Assigned
#pragma config CTXT4 = OFF      // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits->Not Assigned

// ################################# Slave configuration #################################
// FS1OSCSEL
#pragma config S1FNOSC = PRI            // Oscillator Source Selection (primary (PRI))
#pragma config S1IESO = OFF             // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FS1OSC
#pragma config S1OSCIOFNC = ON          // Slave OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config S1FCKSM = CSECMD         // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)

// FS1WDT
#pragma config S1RWDTPS = PS1048576     // Run Mode Watchdog Timer Post Scaler select bits (1:1048576)
#pragma config S1RCLKSEL = LPRC         // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config S1WINDIS = OFF           // Watchdog Timer Window Enable bit (Watchdog Timer operates in Window mode)
#pragma config S1WDTWIN = WIN25         // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config S1SWDTPS = PS1048576     // Sleep Mode Watchdog Timer Post Scaler select bits (1:1048576)
#pragma config S1FWDTEN = ON_SW         // Watchdog Timer Enable bit (WDT controlled via WDTCON.ON bit)

// FS1ICD
#pragma config S1ICS = PGD1             // ICD Communication Channel Select bits (Communicate on PGEC3 and PGED3)
#pragma config S1ISOLAT = OFF           // Isolate the Slave core subsystem from the master subsystem during Debug (The slave can operate (in debug mode) even if the SLVEN bit in the MSI is zero.)
#pragma config S1NOBTSWP = OFF          // BOOTSWP Instruction Enable/Disable bit (BOOTSWP instruction is disabled)

// FS1DEVOPT
#pragma config S1ALTI2C1 = OFF          // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config S1SPI1PIN = PPS          // S1 SPI1 Pin Select bit (Slave SPI1 uses I/O remap (PPS) pins)
#pragma config S1SSRE = ON              // Slave Slave Reset Enable (Slave generated resets will reset the Slave Enable Bit in the MSI module)
#pragma config S1MSRE = ON              // Master Slave Reset Enable (The master software oriented RESET events (RESET Op-Code, Watchdog timeout, TRAP reset, illegalInstruction) will also cause the slave subsystem to reset.)

// FS1ALTREG
#pragma config S1CTXT1 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config S1CTXT2 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config S1CTXT3 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config S1CTXT4 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// ################################# PINS Ownership #################################
// FCFGPRA0
#pragma config CPRA0 = MSTR     // Pin RA0 Ownership Bits->Master core owns pin
#pragma config CPRA1 = MSTR     // Pin RA1 Ownership Bits->Master core owns pin
#pragma config CPRA2 = MSTR     // Pin RA2 Ownership Bits->Master core owns pin
#pragma config CPRA3 = MSTR     // Pin RA3 Ownership Bits->Master core owns pin
#pragma config CPRA4 = MSTR     // Pin RA4 Ownership Bits->Master core owns pin

// FCFGPRB0
#pragma config CPRB0 = MSTR     // Pin RB0 Ownership Bits->Master core owns pin
#pragma config CPRB1 = MSTR     // Pin RB1 Ownership Bits->Master core owns pin
#pragma config CPRB2 = MSTR     // Pin RB2 Ownership Bits->Master core owns pin
#pragma config CPRB3 = MSTR     // Pin RB3 Ownership Bits->Master core owns pin
#pragma config CPRB4 = MSTR     // Pin RB4 Ownership Bits->Master core owns pin
#pragma config CPRB5 = MSTR     // Pin RB5 Ownership Bits->Master core owns pin
#pragma config CPRB6 = MSTR     // Pin RB6 Ownership Bits->Master core owns pin
#pragma config CPRB7 = MSTR     // Pin RB7 Ownership Bits->Master core owns pin
#pragma config CPRB8 = MSTR     // Pin RB8 Ownership Bits->Master core owns pin
#pragma config CPRB9 = MSTR     // Pin RB9 Ownership Bits->Master core owns pin
#pragma config CPRB10 = MSTR    // Pin RB10 Ownership Bits->Master core owns pin
#pragma config CPRB11 = MSTR    // Pin RB11 Ownership Bits->Master core owns pin
#pragma config CPRB12 = MSTR    // Pin RB12 Ownership Bits->Master core owns pin
#pragma config CPRB13 = MSTR    // Pin RB13 Ownership Bits->Master core owns pin
#pragma config CPRB14 = MSTR    // Pin RB14 Ownership Bits->Master core owns pin
#pragma config CPRB15 = MSTR    // Pin RB15 Ownership Bits->Master core owns pin

// FCFGPRC0
#pragma config CPRC0 = MSTR     // Pin RC0 Ownership Bits->Master core owns pin
#pragma config CPRC1 = MSTR     // Pin RC1 Ownership Bits->Master core owns pin
#pragma config CPRC2 = MSTR     // Pin RC2 Ownership Bits->Master core owns pin
#pragma config CPRC3 = MSTR     // Pin RC3 Ownership Bits->Master core owns pin
#pragma config CPRC4 = SLV1     // Pin RC4 Ownership Bits->Slave core owns pin
#pragma config CPRC5 = SLV1     // Pin RC5 Ownership Bits->Slave core owns pin
#pragma config CPRC6 = MSTR     // Pin RC6 Ownership Bits->Master core owns pin
#pragma config CPRC7 = MSTR     // Pin RC7 Ownership Bits->Master core owns pin
#pragma config CPRC8 = MSTR     // Pin RC8 Ownership Bits->Master core owns pin
#pragma config CPRC9 = MSTR     // Pin RC9 Ownership Bits->Master core owns pin
#pragma config CPRC10 = SLV1    // Pin RC10 Ownership Bits->Slave core owns pin
#pragma config CPRC11 = SLV1    // Pin RC11 Ownership Bits->Slave core owns pin
#pragma config CPRC12 = MSTR    // Pin RC12 Ownership Bits->Master core owns pin
#pragma config CPRC13 = SLV1    // Pin RC13 Ownership Bits->Slave core owns pin
#pragma config CPRC14 = MSTR    // Pin RC14 Ownership Bits->Master core owns pin
#pragma config CPRC15 = MSTR    // Pin RC15 Ownership Bits->Master core owns pin

// FCFGPRD0
#pragma config CPRD0 = SLV1     // Pin RD0 Ownership Bits->Slave core owns pin
#pragma config CPRD1 = SLV1     // Pin RD1 Ownership Bits->Slave core owns pin
#pragma config CPRD2 = MSTR     // Pin RD2 Ownership Bits->Master core owns pin
#pragma config CPRD3 = SLV1     // Pin RD3 Ownership Bits->Slave core owns pin
#pragma config CPRD4 = SLV1     // Pin RD4 Ownership Bits->Slave core owns pin
#pragma config CPRD5 = MSTR     // Pin RD5 Ownership Bits->Master core owns pin
#pragma config CPRD6 = MSTR     // Pin RD6 Ownership Bits->Master core owns pin
#pragma config CPRD7 = MSTR     // Pin RD7 Ownership Bits->Master core owns pin
#pragma config CPRD8 = MSTR     // Pin RD8 Ownership Bits->Master core owns pin
#pragma config CPRD9 = MSTR     // Pin RD9 Ownership Bits->Master core owns pin
#pragma config CPRD10 = MSTR    // Pin RD10 Ownership Bits->Master core owns pin
#pragma config CPRD11 = MSTR    // Pin RD11 Ownership Bits->Master core owns pin
#pragma config CPRD12 = MSTR    // Pin RD12 Ownership Bits->Master core owns pin
#pragma config CPRD13 = MSTR    // Pin RD13 Ownership Bits->Master core owns pin
#pragma config CPRD14 = MSTR    // Pin RD14 Ownership Bits->Master core owns pin
#pragma config CPRD15 = MSTR    // Pin RD15 Ownership Bits->Master core owns pin

// ################################# MSI configuration #################################
// FMBXM
#pragma config MBXM0 = M2S              // Mailbox 0 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM1 = M2S              // Mailbox 1 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM2 = M2S              // Mailbox 2 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM3 = M2S              // Mailbox 3 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM4 = M2S              // Mailbox 4 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM5 = S2M              // Mailbox 5 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM6 = S2M              // Mailbox 6 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM7 = S2M              // Mailbox 7 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM8 = S2M              // Mailbox 8 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM9 = S2M              // Mailbox 9 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM10 = S2M             // Mailbox 10 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM11 = S2M             // Mailbox 11 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM12 = S2M             // Mailbox 12 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM13 = S2M             // Mailbox 13 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM14 = S2M             // Mailbox 14 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM15 = S2M             // Mailbox 15 data direction (Mailbox register configured for Master data read (Slave to Master data transfer)

// FMBXHS1
#pragma config MBXHSA = MBX4            // Mailbox handshake protocol block A register assignment (MSIxMBXD4 assigned to mailbox handshake protocol block A)
#pragma config MBXHSB = MBX9            // Mailbox handshake protocol block B register assignment (MSIxMBXD9 assigned to mailbox handshake protocol block B)
#pragma config MBXHSC = MBX15           // Mailbox handshake protocol block C register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block C)
#pragma config MBXHSD = MBX15           // Mailbox handshake protocol block D register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block D)

// FMBXHS2
#pragma config MBXHSE = MBX15           // Mailbox handshake protocol block E register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block E)
#pragma config MBXHSF = MBX15           // Mailbox handshake protocol block F register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block F)
#pragma config MBXHSG = MBX15           // Mailbox handshake protocol block G register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block G)
#pragma config MBXHSH = MBX15           // Mailbox handshake protocol block H register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block H)

// FMBXHSEN
#pragma config HSAEN = ON               // Mailbox A data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSBEN = ON               // Mailbox B data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSCEN = OFF              // Mailbox C data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled)
#pragma config HSDEN = OFF              // Mailbox D data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled)
#pragma config HSEEN = OFF              // Mailbox E data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled)
#pragma config HSFEN = OFF              // Mailbox F data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled)
#pragma config HSGEN = OFF              // Mailbox G data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled)
#pragma config HSHEN = OFF              // Mailbox H data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled)
