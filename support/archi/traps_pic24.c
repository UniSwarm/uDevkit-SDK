void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void)
{
    INTCON1bits.OSCFAIL = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void)
{
    INTCON1bits.ADDRERR = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _StackError(void)
{
    INTCON1bits.STKERR = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void)
{
    INTCON1bits.MATHERR = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _DMACError(void)
{
    INTCON1bits.DMACERR = 0;
    while (1)
    {
        ;
    }
}

/* ****************************************************************
 * Alternate Exception Vector handlers if ALTIVT (INTCON2<15>) = 1 *
 *                                                                 *
 * Not required for labs but good to always include                *
 ******************************************************************/
void __attribute__((interrupt, no_auto_psv)) _AltOscillatorFail(void)
{
    INTCON1bits.OSCFAIL = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _AltAddressError(void)
{
    INTCON1bits.ADDRERR = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _AltStackError(void)
{
    INTCON1bits.STKERR = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _AltMathError(void)
{
    INTCON1bits.MATHERR = 0;
    while (1)
    {
        ;
    }
}

void __attribute__((interrupt, no_auto_psv)) _AltDMACError(void)
{
    INTCON1bits.DMACERR = 0;
    while (1)
    {
        ;
    }
}