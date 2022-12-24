#include "stc.h"
#include "usb.h"
#include "usb_req_vendor.h"

void usb_req_vendor()
{
    usb_setup_stall();
}
