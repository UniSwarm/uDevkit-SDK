/*uint8_t spi_read(uint8_t addr)
{
    uint16_t value, i, bit, dat;
    ACC_CS = 0;
    TRISDbits.TRISD2 = 0;
    for(i=0;i<500;i++) nop();

    dat = addr | 0x80;
    for(bit=0; bit<8; bit++)
    {
        ACC_SCK = 0;
        ACC_SD0 = (dat & 0x80) ? 1 : 0;
        for(i=0;i<500;i++) nop();
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
        dat <<= 1;
    }

    value = 0;
    TRISDbits.TRISD2 = 1;
    for(bit=0; bit<8; bit++)
    {
        value <<= 1;
        ACC_SCK = 0;
        for(i=0;i<500;i++) nop();
        if(ACC_SDI == 1)
            value |= 0x01;
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
    }

    for(i=0;i<500;i++) nop();
    ACC_CS = 1;
    TRISDbits.TRISD2 = 0;
    for(i=0;i<1000;i++) nop();

    return value;
}

void spi_write(uint8_t addr, uint8_t value)
{
    uint16_t i, bit, dat;
    ACC_CS = 0;
    TRISDbits.TRISD2 = 0;
    for(i=0;i<500;i++) nop();

    dat = addr;
    for(bit=0; bit<8; bit++)
    {
        ACC_SCK = 0;
        ACC_SD0 = (dat & 0x80) ? 1 : 0;
        for(i=0;i<500;i++) nop();
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
        dat <<= 1;
    }
    dat = value;
    for(bit=0; bit<8; bit++)
    {
        ACC_SCK = 0;
        ACC_SD0 = (dat & 0x80) ? 1 : 0;
        for(i=0;i<500;i++) nop();
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
        dat <<= 1;
    }

    for(i=0;i<500;i++) nop();
    ACC_CS = 1;
    for(i=0;i<1000;i++) nop();
}
*/
