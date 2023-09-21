---
icon: material/tools
---

## Basic USB Assembly

Basic assembly of the Qwiic Pocket Development Board only requires a USB-C cable connecting the board to a computer. Just plug the cable into the USB-C connector like the photo below shows and move on to the Software Setup section. 

**Photo showing USB connection - Mark L**

!!! note
    Your computer may not recognize the board as a known USB device if you have not installed the espressif boards package in Arduino and/or installed the espressif IDF.

## Battery Assembly

If you prefer a battery-powered application, plug a single-cell LiPo battery into the 2-pin JST connector on the underside of the board like the photo below. Remember, the MCP73831 only charges the battery when V_USB has voltage present either from the USB-C connector or through the V_USB PTH pin.

**Photo showing battery connection - Mark L**

For tips on the proper use of a LiPo battery and the 2-pin JST connector, please read through our [Single Cell LiPo Battery Care](https://learn.sparkfun.com/tutorials/single-cell-lipo-battery-care) tutorial.

## Smart Watch Example Assembly

Lastly, building the "smart watch" with the Pocket Development Board and the three Qwiic breakouts requires a bit more assembly using standoffs, screws, and Qwiic cables to build a stack of boards. The order of the boards does not really matter so long as the Qwiic Micro OLED is on top. 

**Photo showing all boards before assembling the stack - Mark L**

With the boards stacked up, connect them all together with Qwiic cables and the final assembly should look something like the photo below:

**Photo showing completed smart watch assembly - Mark L**