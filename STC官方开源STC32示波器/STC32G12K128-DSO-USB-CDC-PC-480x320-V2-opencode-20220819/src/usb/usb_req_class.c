#include "stc.h"
#include "usb.h"
#include "usb_req_class.h"
#include "util.h"

LINECODING LineCoding;

void usb_req_class()
{
    switch (Setup.bRequest)
    {
    case SET_LINE_CODING:
        usb_set_line_coding();
        break;
    case GET_LINE_CODING:
        usb_get_line_coding();
        break;
    case SET_CONTROL_LINE_STATE:
        usb_set_ctrl_line_state();
        break;
    default:
        usb_setup_stall();
        return;
    }
}

void usb_set_line_coding()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = (BYTE *)&LineCoding;
    Ep0State.wSize = Setup.wLength;

    usb_setup_out();
}

void usb_get_line_coding()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = (BYTE *)&LineCoding;
    Ep0State.wSize = Setup.wLength;

    usb_setup_in();
}

void usb_set_ctrl_line_state()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    usb_setup_status();
}

void usb_uart_settings()
{
}