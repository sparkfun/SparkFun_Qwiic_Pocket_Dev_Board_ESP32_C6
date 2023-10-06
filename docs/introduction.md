---
icon: material/book-open-page-variant
---

<div class="grid cards desc" markdown>

<!-- **SparkFun Qwiic Pocket Development Board - ESP32-C6** (DEV-22925)> -->
-   **SKU:** DEV-22925

    ---

    <figure markdown>
    [![SparkFun Qwiic Pocket Development Board - ESP32-C6](https://cdn.sparkfun.com//assets/parts/2/3/0/8/6/22925-_DEV_SparkFun_Qwiic_Pocket_Development_Board-_01.jpg)](https://www.sparkfun.com/products/22925)
    </figure>

-   The [SparkFun Qwiic Pocket Development Board - ESP32-C6](https://www.sparkfun.com/products/22925) features the ESP32-C6 Mini-1 module from espressif<sup>&trade;</sup>. The ESP32-C6 SoC is built around a RISC-V single-core processor with 4 MB flash memory and supports 2.4 GHz WiFi 6, Bluetooth<sup>&reg;</sup> 5 (with Low Energy), Zigbee and Thread 802.15.4 wireless protocols. The module uses an integrated PCB antenna. <br>
    The ESP32-C6 includes on-chip serial-to-UART conversion which helps reduce the number of components on the development board so we designed this Qwiic Dev Board to cram as much as we could into the Qwiic system's 1"x1" form factor so it does not break out as many GPIO pins as the [Thing Plus](https://www.sparkfun.com/products/22924) variant but it does include a USB-C connector, 2-pin JST connector for a single-cell LiPo battery along with a charging circuit for a connected battery, a Qwiic connector, and it also breaks out eight GPIO pins (including one UART). 

    <center>
    [Purchase from SparkFun :fontawesome-solid-cart-plus:](https://www.sparkfun.com/products/22925){ .md-button .md-button--primary }
    </center>

</div>

## Required Materials

To follow along with this guide you will need a USB-C cable to connect the dev board to your computer: 

<div class="grid cards" markdown>

-   <a href="https://www.sparkfun.com/products/14743">

    <figure markdown>
    ![USB 3.1 Cable A to C - 3 Foot](https://cdn.sparkfun.com//assets/parts/1/2/9/7/2/14743-USB_3.1_Cable_A_to_C_-_3_Foot-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/14743">
    **USB 3.1 Cable A to C - 3 Foot**<br>
    CAB-14743
    </a>

-   <a href="https://www.sparkfun.com/products/15424">
    
    <figure markdown>
    ![Reversible USB A to C Cable - 2m](https://cdn.sparkfun.com//assets/parts/1/7/4/8/7/18158-SparkFun_RedBoard_Plus-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/15424">
    **Reversible USB A to C Cable - 2m**<br>
    CAB-15424
    </a>
</div>

You may also want to get a Qwiic cable or kit to connect the Qwiic Dev Board - ESP32-C6 to other Qwiic devices:

<div class="grid cards" markdown>

-   <a href="https://www.sparkfun.com/products/17259">

    <figure markdown>
    ![Flexible Qwiic Cable - 100mm](https://cdn.sparkfun.com//assets/parts/1/6/2/4/6/17259-Flexible_Qwiic_Cable_-_100mm-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/17259">
    **Flexible Qwiic Cable - 100mm**<br>
    PRT-17259
    </a>

-   <a href="https://www.sparkfun.com/products/17260">
    
    <figure markdown>
    ![Qwiic Cable - 50mm](https://cdn.sparkfun.com//assets/parts/1/6/2/4/7/17260-Flexible_Qwiic_Cable_-_50mm-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/17260">
    **Flexible Qwiic Cable - 50mm**<br>
    PRT-17260
    </a>

-   <a href="https://www.sparkfun.com/products/17257">
    
    <figure markdown>
    ![Flexible Qwiic Cable - 500mm](https://cdn.sparkfun.com//assets/parts/1/6/2/4/4/17257-Flexible_Qwiic_Cable_-_500mm-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/17257">
    **Flexible Qwiic Cable - 500mm**<br>
    PRT-17257
    </a>

-   <a href="https://www.sparkfun.com/products/17261">

    <figure markdown>
    ![Flexible Qwiic Cable - Female Jumper (4-pin)](https://cdn.sparkfun.com//assets/parts/1/6/2/4/8/17261-Flexible_Qwiic_Cable_-_Female_Jumper__4-pin_-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/17261">**Flexible Qwiic Cable - Female Jumper (4-pin)**<br>
    CAB-17261
    </a>
</div>

## Optional Materials

The Qwiic Dev Board - ESP32-C6 includes a 2-pin JST connector and integrated charging circuit for an attached single-cell LiPo battery. Below are a few options for batteries we recommend for battery-powered applications:

<div class="grid cards" markdown align="center">

-   <a href="https://www.sparkfun.com/products/18286">

    <figure markdown>
    ![Lithium Ion Battery - 1250mAh (IEC62133 Certified)](https://cdn.sparkfun.com/r/140-140/assets/parts/1/7/6/0/6/17748-Lithium_Ion_Battery_-_1250_mAh__IEC62133_certified_-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/18286">
    **Lithium Ion Battery - 1250mAh (IEC62133 Certified)**<br>
    PRT-18286
    </a>

-   <a href="https://www.sparkfun.com/products/13855">

    <figure markdown>
    ![Lithium Ion Battery - 2Ah](https://cdn.sparkfun.com/r/140-140/assets/parts/1/1/4/6/2/13855-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/13855">
    **Lithium Ion Battery - 2Ah**<br>
    PRT-13855
    </a>

-   <a href="https://www.sparkfun.com/products/13851">

    <figure markdown>
    ![Lithium Ion Battery - 400mAh](https://cdn.sparkfun.com/r/140-140/assets/parts/1/7/6/0/6/17748-Lithium_Ion_Battery_-_1250_mAh__IEC62133_certified_-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/13851">
    **Lithium Ion Battery - 400mAh**<br>
    PRT-13851
    </a>

-   <a href="https://www.sparkfun.com/products/13854">

    <figure markdown>
    ![Lithium Ion Battery - 850mAh](https://cdn.sparkfun.com/r/140-140/assets/parts/1/1/4/6/1/13854-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/13854">
    **Lithium Ion Battery - 850mAh**<br>
    PRT-13854
    </a>
</div>

If you prefer a soldered connection or want to modify the solder jumpers on this board, you may need some of the products listed below:

<div class="grid cards" markdown align="center">

-   <a href="https://www.sparkfun.com/products/116">

    <figure markdown>
    ![Break Away Headers - Straight](https://cdn.sparkfun.com//assets/parts/1/0/6/00116-02-L.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/116">
    **Break Away Headers - Straight**<br>
    PRT-00116
    </a>

-   <a href="https://www.sparkfun.com/products/9507">
    
    <figure markdown>
    ![Soldering Iron - 30W (USE, 110V)](https://cdn.sparkfun.com//assets/parts/3/2/4/3/09507-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/9507">
    **Soldering Iron - 30W (USE, 110V)**<br>
    TOL-09507
    </a>

-   <a href="https://www.sparkfun.com/products/9200">
    
    <figure markdown>
    ![Hobby Knife](https://cdn.sparkfun.com//assets/parts/2/6/4/6/09200-Hobby_Knife-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/9200">
    **Hobby Knife**<br>
    TOL-09200
    </a>

-   <a href="https://www.sparkfun.com/products/14579">

    <figure markdown>
    ![Chip Quik No-Clean Flux Pen - 10mL](https://cdn.sparkfun.com//assets/parts/1/2/7/2/5/14579-Chip_Quik_No-Clean_Flux_Pen_-_10mL-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/14579">**Chip Quik No-Clean Flux Pen - 10mL**<br>
    CAB-14579
    </a>
</div>

## Smart Watch Example Materials

This guide also includes a demo using the Qwiic Pocket Development Board - ESP32-C6 with three Qwiic breakouts to create a DIY "smart watch" (sans the wristband) complete with display, pedometer, and motion controls. If you'd like to follow along and build this example, you'll need the following Qwiic breakouts:

<div class="grid cards" markdown align="center">
-  <a href="https://www.sparkfun.com/products/14532">
    <figure markdown>
    ![SparkFun Micro OLED Breakout (Qwiic)](https://cdn.sparkfun.com//assets/parts/1/2/6/2/1/14532-SparkFun_Micro_OLED_Breakout__Qwiic_-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/14532">**SparkFun Micro OLED Breakout (Qwiic)**<br>
    LCD-14532
    </a>
- <a href="https://www.sparkfun.com/products/14558">
    <figure markdown>
    ![SparkFun Real Time Clock Module - RV-1805 (Qwiic)](https://cdn.sparkfun.com//assets/parts/1/2/6/9/1/14558-SparkFun_Real_Time_Clock_Module_-_RV-1805__Qwiic_-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/14558">**SparkFun Real Time Clock Module - RV-1805 (Qwiic)**<br>
    BOB-14558
    </a>
- <a href="https://www.sparkfun.com/products/22397">
    <figure markdown>
    ![SparkFun 6DoF IMU Breakout - BMI270 (Qwiic)](https://cdn.sparkfun.com//assets/parts/2/2/4/2/9/22397_1_1.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/22397">**SparkFun 6DoF IMU Breakout - BMI270 (Qwiic)**<br>
    SEN-22397
    </a>
</div>

You'll also need three Qwiic cables of your choice of length and a set of standoffs to assemble the smart watch. We recommend either the 50mm or 100mm flexible cables as shown below:

<div class="grid cards" markdown align="center">
-   <a href="https://www.sparkfun.com/products/17260">
    <figure markdown>
    ![Flexible Qwiic Cable - 50mm](https://cdn.sparkfun.com//assets/parts/1/6/2/4/7/17260-Flexible_Qwiic_Cable_-_50mm-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/17260">**Flexible Qwiic Cable - 50mm**<br>
    PRT-17260
    </a>
-   <a href="https://www.sparkfun.com/products/17259">
    <figure markdown>
    ![Flexible Qwiic Cable - 100mm](https://cdn.sparkfun.com//assets/parts/1/6/2/4/6/17259-Flexible_Qwiic_Cable_-_100mm-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/17259">**Flexible Qwiic Cable - 100mm**<br>
    PRT-17259
    </a>
-   <a href="https://www.sparkfun.com/products/10463">
    <figure markdown>
    ![Standoff - Metal Hex (4-40; 3/8"; 10 pack)](https://cdn.sparkfun.com//assets/parts/4/9/5/4/10463-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/10463">**Standoff - Metal Hex (4-40; 3/8"; 10 pack)**<br>
    PRT-10463
    </a>
-   <a href="https://www.sparkfun.com/products/10453">
    <figure markdown>
    ![Screw - Phillips Head (1/4", 4-40, 10 pack)](https://cdn.sparkfun.com//assets/parts/4/9/4/7/10453-01.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/10453">**Screw - Phillips Head (1/4", 4-40, 10 pack)**<br>
    PRT-10453
    </a>
-   <a href="https://www.sparkfun.com/products/10454">
    <figure markdown>
    ![Nut - Metal (4-40, 10 pack)](https://cdn.sparkfun.com//assets/parts/4/9/4/6/10454-02b.jpg)
    </figure>
    </a>
    ---
    <a href="https://www.sparkfun.com/products/10454">**Nut - Metal (4-40, 10 pack)**<br>
    PRT-10453
    </a>   
</div>

## Suggested Reading

We designed this board for integration into SparkFun's Qwiic connect system.  Click on the banner below to learn more about the [SparkFun Qwiic Connect System](https://www.sparkfun.com/qwiic).

<div style="text-align: center">
<table>
  <tr>
   <td>
   <div style="text-align: center"><a href="https://www.sparkfun.com/qwiic"><img src="../assets/images/Qwiic-registered-updated.png" alt="Qwiic Connect System" title="Click to learn more about the Qwiic Connect System!"></a></div>
   </td>
  </tr>
  <tr>
    <td><div style="text-align: center"><i><a href="https://www.sparkfun.com/qwiic">Qwiic Connect System</a></i></div></td>
  </tr>
</table>
</div>

Before getting started with this Hookup Guide, you may want to read through the tutorials below if you are not familiar with the concepts covered in them or want a refresher. If you are using either of the Qwiic Shields linked above, we recommend reading through their respective Hookup Guides before continuing with this tutorial:

<div class="grid cards hide col-4" markdown align="center">

-   <a href="https://learn.sparkfun.com/tutorials/8">
    <figure markdown>
    ![Serial Communication](https://cdn.sparkfun.com/c/264-148/assets/7/d/f/9/9/50d24be7ce395f1f6c000000.jpg)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/8">**Serial Communication**
    </a>

-   <a href="https://learn.sparkfun.com/tutorials/82">
    <figure markdown>
    ![I2C](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/8/2/I2C-Block-Diagram.jpg)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/82">**I2C**
    </a>

-   <a href="https://learn.sparkfun.com/tutorials/62">
    <figure markdown>
    ![Logic Levels](https://cdn.sparkfun.com/c/264-148/assets/learn_tutorials/6/2/Input_Output_Logic_Level_Tolerances_tutorial_tile.png)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/62">**Logic Levels**
    </a>

-   <a href="https://learn.sparkfun.com/tutorials/61">
    <figure markdown>
    ![Installing Arduino IDE](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/6/1/arduinoThumb.jpg)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/61">**Installing Arduino IDE**
    </a>

-   <a href="https://learn.sparkfun.com/tutorials/15">
    <figure markdown>
    ![Installing an Arduino Library](https://cdn.sparkfun.com/c/178-100/assets/b/e/4/b/2/50f04b99ce395fd95e000001.jpg)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/15">**Installing an Arduino Library**
    </a>

-   <a href="https://learn.sparkfun.com/tutorials/112">
    <figure markdown>
    ![Serial Terminal Basics](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/1/1/2/terminalThumb.jpg)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/112">**Serial Terminal Basics**
    </a>

-   <a href="https://learn.sparkfun.com/tutorials/664">
    <figure markdown>
    ![How to Work with Jumper Pads and PCB Traces](https://cdn.sparkfun.com/c/264-148/assets/learn_tutorials/6/6/4/PCB_TraceCutLumenati.jpg)
    </figure>
    </a>
    <a href="https://learn.sparkfun.com/tutorials/664">**How to Work with Jumper Pads and PCB Traces**
    </a>
</div>