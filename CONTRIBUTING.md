# Contributing to RTprog

:+1: We are happy to learn that you want to contribute !

Thank you for making the embedded world a more attractive domain. Each commits make it simpler.

This little guide goals to help you to contribute to this project.

Before contributing, never forget the following points:

* Keep the modularity of the project
* Keep the compatibility with a large set of microcontrollers
* Keep in mind RAM memory is expensive, use only that you really needs

## How Can I Contribute?

* Reporting bugs in [Issues](https://github.com/Robotips/rtprog/issues)

* Pull requests in [Pull requests](https://github.com/Robotips/rtprog/pulls)

## Styleguides

### Git commit messages

* Use past tense: `Updated funtion getSensor`

* Include the name of modified driver or module between square brackets.

  * `[uart] msg` For a global modification to the uart driver, not device dependent

  * `[uart:pic32mx] msg` For a specific modification to uart driver for PIC32MX family

### C code styleguide

* no tab, only space, 4 spaces
* no int, exept for error return value, only use sized type (uint8_t, int32_t...)

```C
int module_superFunction(uint8_t arg1)
{
    uint8_t val;

    if (arg1 == 0)
    {
        return -1;
    }

    switch (arg1)
    {
    case 1:
        val = 3;
        break;
    default:
        val = 8;
        break;
    }

    return val;
}

```
