#include "libgpio_gpio.h"
#include <gpiod.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//FIXME includes...

// Well well the power of globals
// FIMXE don't be evil :D
const char *chipname = "gpiochip0";
struct gpiod_chip *chip;

struct gpiod_line *rst; 
struct gpiod_line *dc;
struct gpiod_line *busy;

// Oh hell what a mess
#define EPD_RST_PIN      17
#define EPD_DC_PIN       25
#define EPD_BUSY_PIN     24

void LIBGPIO_GPIO_Init()
{
  chip = gpiod_chip_open_by_name(chipname);
  rst = gpiod_chip_get_line(chip, 2);
  dc = gpiod_chip_get_line(chip, 1);
  busy = gpiod_chip_get_line(chip, 6);
}

void LIBGPIO_GPIO_Exit()
{
  gpiod_line_release(busy);
  gpiod_line_release(dc);
  gpiod_line_release(rst);
  gpiod_chip_close(chip);
}

struct gpiod_line * pin_to_chip(int Pin)
{
  switch(Pin)
  {
    case EPD_RST_PIN:
      return rst;
	  case EPD_DC_PIN:
      return dc;
    case EPD_BUSY_PIN:
      return busy;
  }
  return 0;
}

int LIBGPIO_GPIO_Direction(int Pin, int Dir)
{
  if(Dir)
  {
    gpiod_line_request_output(pin_to_chip(Pin), "", 0);
  }
  else
  {
    gpiod_line_request_input(pin_to_chip(Pin), "");
  }
  return 0;
}

int LIBGPIO_GPIO_Read(int Pin)
{
  struct gpiod_line* pin = pin_to_chip(Pin);
  if(!pin)
    return 0;
  return gpiod_line_get_value(pin);
}

int LIBGPIO_GPIO_Write(int Pin, int value)
{
  struct gpiod_line* pin = pin_to_chip(Pin);
  if(!pin)
    return 0;
#if 0
  if(value == 0)
  gpiod_line_set_value(pin, 1);
  else
  gpiod_line_set_value(pin, 0);
#endif

  gpiod_line_set_value(pin, value);
  return 0;
}
