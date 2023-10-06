// Inlcude libraries needed
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
#include <SparkFun_Qwiic_OLED.h>
#include <SparkFun_RV1805.h>
#include <WiFi.h>
#include "time.h"

// WiFi SSID and password, change these for your WiFi network!
const char* ssid = "your-ssid";
const char* password = "your-password";

// Create RTC object
RV1805 rtc;

// Create OLED object
QwiicMicroOLED oled;

// Create sensor object
BMA400 accelerometer;

// Pin used for button input
int buttonPin = 9;

// Pin used for measuring battery voltage
int batteryPin = 1;

// Pin used for interrupt detection
int interruptPin = 4;

// Flag to know when interrupts occur
volatile bool interruptOccurred = false;

// Flag to know when user input is requested
bool userInput = true;

// Screen index
uint8_t screenIndex = 0;

// Enum to define various screen indices
typedef enum
{
    SCREEN_CLOCK,
    SCREEN_STEP_COUNTER,
    SCREEN_BATTERY_VOLTAGE,
    SCREEN_SYNC_RTC,
    SCREEN_MAX
} screen_index_t;

// Screen size properties
uint8_t midX = 0;
uint8_t midY = 0;
uint8_t clockRadius = 0;
uint8_t rowHeight = 0;

// Screen display flags
volatile bool updateScreen = true;
volatile bool screenOn = true;

// Screen update timer
uint32_t lastUpdateTime = 0;
uint32_t updateInterval = 1000/25;

// Sleep timer to automatically enter deep sleep after inactivity
uint32_t sleepTimerStart = 0;
uint32_t sleepTimerPeriod = 60000;

// Standard time zone relative to GMT (not daylight savings!)
int8_t timeZone = -7;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("Watch demo begin!");

    // Configure button pin as input with pullup
    pinMode(buttonPin, INPUT_PULLUP);

    // Configure battery pin as input
    pinMode(batteryPin, INPUT);

    // The ESP32-C6 has an attenuator on the ADC, which defaults to 11dB. This causes the resolution to be reduced
    analogSetAttenuation(ADC_0db);

    // Begin I2C driver
    Wire.begin(6, 7);

    // Begin RTC
    while(!rtc.begin())
    {
        Serial.println("Error: RTC not connected, check wiring and I2C address!");
        delay(1000);
    }
    Serial.println("RTC connected!");

    // Manually set time (uncomment if needed, set current time and upload, then comment out and upload again)
    // rtc.setTime(0,second,minute,hour,day,month,year,weekday);

    // Begin OLED
    while(!oled.begin())
    {
        Serial.println("Error: OLED not connected, check wiring and I2C address!");
        delay(1000);
    }
    Serial.println("OLED connected!");
    
    // Set screen size parameters
    midX = oled.getWidth() / 2;
    midY = oled.getHeight() / 2;
    clockRadius = min(midX, midY) - 2;
    rowHeight = oled.getHeight() / 3;
    
    // Begin accelerometer
    while(accelerometer.beginI2C() != BMA400_OK)
    {
        Serial.println("Error: BMA400 not connected, check wiring and I2C address!");
        delay(1000);
    }
    Serial.println("BMA400 connected!");

    // Set up tap detection
    bma400_tap_conf tapConfig =
    {
        .axes_sel = BMA400_TAP_Z_AXIS_EN, // Which axes to evaluate for interrupts (X/Y/Z in any combination)
        .sensitivity = BMA400_TAP_SENSITIVITY_7, // Sensitivity threshold, up to 7 (lower is more sensitive)
        .tics_th = BMA400_TICS_TH_6_DATA_SAMPLES, // Max time between top/bottom peaks of a single tap
        .quiet = BMA400_QUIET_60_DATA_SAMPLES, // Minimum time between taps to trigger interrupt
        .quiet_dt = BMA400_QUIET_DT_4_DATA_SAMPLES, // Minimum time between 2 taps to trigger double tap interrupt
        .int_chan = BMA400_INT_CHANNEL_1 // Which pin to use for interrupts
    };
    accelerometer.setTapInterrupt(&tapConfig);

    // Set up generic 1 interrupt, used to detect when device is rotated away from user
    bma400_gen_int_conf genConfig =
    {
        .gen_int_thres = 125, // 8mg resolution (eg. gen_int_thres=5 results in 40mg)
        .gen_int_dur = 100, // 10ms resolution (eg. gen_int_dur=5 results in 50ms)
        .axes_sel = BMA400_AXIS_XYZ_EN, // Which axes to evaluate for interrupts (X/Y/Z in any combination)
        .data_src = BMA400_DATA_SRC_ACCEL_FILT_LP, // Which filter to use (must be 100Hz, datasheet recommends filter 2)
        .criterion_sel = BMA400_ACTIVITY_INT, // Trigger interrupts when active or inactive
        .evaluate_axes = BMA400_ANY_AXES_INT, // Logical combining of axes for interrupt condition (OR/AND)
        .ref_update = BMA400_UPDATE_MANUAL, // Whether to automatically update reference values
        .hysteresis = BMA400_HYST_96_MG, // Hysteresis acceleration for noise rejection
        .int_thres_ref_x = (uint16_t) -360, // Raw 12-bit acceleration value
        .int_thres_ref_y = 0, // Raw 12-bit acceleration value
        .int_thres_ref_z = 360, // Raw 12-bit acceleration value (at 4g range (default), 512 = 1g)
        .int_chan = BMA400_INT_CHANNEL_1 // Which pin to use for interrupts
    };
    accelerometer.setGeneric1Interrupt(&genConfig);
    
    // Set up generic 2 interrupt, used to detect when device is rotated towards user
    genConfig.gen_int_thres = 50;
    genConfig.gen_int_dur = 50;
    genConfig.criterion_sel = BMA400_INACTIVITY_INT;
    genConfig.evaluate_axes = BMA400_ALL_AXES_INT;
    accelerometer.setGeneric2Interrupt(&genConfig);

    // Enable step counting
    bma400_step_int_conf stepConfig = {.int_chan = BMA400_INT_CHANNEL_1};
    accelerometer.setStepCounterInterrupt(&stepConfig);

    // Set INT 1 pin as push pull active high
    accelerometer.setInterruptPinMode(BMA400_INT_CHANNEL_1, BMA400_INT_PUSH_PULL_ACTIVE_1);

    // Enable interrupts from accelerometer
    accelerometer.enableInterrupt(BMA400_STEP_COUNTER_INT_EN, true);
    accelerometer.enableInterrupt(BMA400_SINGLE_TAP_INT_EN, true);
    accelerometer.enableInterrupt(BMA400_DOUBLE_TAP_INT_EN, true);
    accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, true);
    accelerometer.enableInterrupt(BMA400_GEN2_INT_EN, true);
    accelerometer.enableInterrupt(BMA400_LATCH_INT_EN, true);

    // Attach interrupt handler
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), bma400InterruptHandler, RISING);

    // Reset sleep timer
    sleepTimerStart = millis();
}

void loop()
{
    // Check if we need to enter deep sleep
    if((digitalRead(buttonPin) == LOW) || (millis() > (sleepTimerStart + sleepTimerPeriod)))
    {
        enterDeepSleep();
    }

    // Check whether interrupt triggered from accelerometer
    if(interruptOccurred)
    {
        // Reset interrupt flag
        interruptOccurred = false;
        
        // Reset sleep timer
        sleepTimerStart = millis();
        
        Serial.print("Interrupt occured: ");
        
        // Check what the interrupt source was
        uint16_t interruptStatus = 0;
        accelerometer.getInterruptStatus(&interruptStatus);
        if(interruptStatus & BMA400_ASSERTED_S_TAP_INT)
        {
            // Single tap, increment screen index if screen is on
            if(screenOn)
            {
                Serial.println("Single tap");
                screenIndex++;
                updateScreen = true;
            }
        }
        else if(interruptStatus & BMA400_ASSERTED_D_TAP_INT)
        {
            // Double tap used for input within a screen index, if applicable.
            // This always follows a single tap, so decrement screen index and
            // set input flag, if screen is on
            if(screenOn)
            {
                Serial.println("Double tap");
                screenIndex--;
                updateScreen = true;
                userInput = true;
            }
        }
        else if(interruptStatus & BMA400_ASSERTED_GEN1_INT)
        {
            // Generic 1 indicates the device was rotated away from the user, in
            // which case we'll turn the screen off
            Serial.println("Generic 1");
            screenOn = false;
            oled.erase();
            oled.display();
            
            // The generic interrupts trigger constantly. Disable generic 1, and
            // enable generic 2
            accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, false);
            accelerometer.enableInterrupt(BMA400_GEN2_INT_EN, true);
        }
        else if(interruptStatus & BMA400_ASSERTED_GEN2_INT)
        {
            // Generic 2 indicates the device was rotated towards the user, in
            // which case we'll turn the screen on
            Serial.println("Generic 2");
            screenOn = true;
            updateScreen = true;

            // The generic interrupts trigger constantly. Disable generic 2, and
            // enable generic 1
            accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, true);
            accelerometer.enableInterrupt(BMA400_GEN2_INT_EN, false);
        }
        else if(interruptStatus & BMA400_ASSERTED_STEP_INT)
        {
            // Step counter incremented, update the screen to give live count
            Serial.println("Step");
            updateScreen = true;
        }
        else
        {
            // Unknown source, just print and ignore it
            Serial.println("Unknown interrupt");
            Serial.println(interruptStatus, HEX);
        }
    }

    // Figure out what to display on the screen, if anything
    if(screenOn)
    {
        screenIndex %= SCREEN_MAX;
        switch(screenIndex)
        {
            case SCREEN_CLOCK:
                displayClock();
                break;
            case SCREEN_STEP_COUNTER:
                displayStepCounter();
                break;
            case SCREEN_BATTERY_VOLTAGE:
                displayBatteryVoltage();
                break;
            case SCREEN_SYNC_RTC:
                displaySyncRTC();
                break;
            default:
                // Shouldn't get here, but just in case
                screenIndex = 0;
                break;
        }
    }

    // Reset flags
    userInput = false;
}

// Displays time an analog clock style
void displayClock()
{
    // Check if we need to update the screen. Uses a timer to limit refresh rate
    if(!updateScreen)
    {
        if(millis() >= (lastUpdateTime + updateInterval))
        {
            lastUpdateTime += updateInterval;
        }
        else
        {
            return;
        }
    }
    updateScreen = false;

    // Get current time from RTC
    rtc.updateTime();
    int timeMilli = millis() % 1000;
    int timeSecs = rtc.getSeconds();
    int timeMins = rtc.getMinutes();
    int timeHours = rtc.getHours() % 12;

    // Clear OLED
    oled.erase();

    // Draw circle to define clock face
    oled.circle(midX, midY, clockRadius);

    // Draw a solid circle to indicate 1 second intervals
    int x = (clockRadius+1) * sin(timeMilli * 2*PI/1000);
    int y = (clockRadius+1) *-cos(timeMilli * 2*PI/1000);
    oled.circleFill(midX + x, midY + y, 2);

    // Draw second hand
    x = clockRadius * sin(timeSecs * 2*PI/60);
    y = clockRadius *-cos(timeSecs * 2*PI/60);
    oled.line(midX, midY, midX + x, midY + y);

    // Draw minute hand
    x = clockRadius*.75 * sin(timeMins * 2*PI/60);
    y = clockRadius*.75 *-cos(timeMins * 2*PI/60);
    oled.line(midX, midY, midX + x, midY + y);

    // Draw hour hand
    x = clockRadius*.5 * sin(timeHours * 2*PI/12);
    y = clockRadius*.5 *-cos(timeHours * 2*PI/12);
    oled.line(midX, midY, midX + x, midY + y);

    // Display on the OLED
    oled.display();
}

// Displays step count
void displayStepCounter()
{
    // Check if screen needs to be updated
    if(!updateScreen)
        return;
    updateScreen = false;

    // Create text buffer
    char displayStr[10] = {0};
    uint8_t numChars = 0;

    // Get step count and activity type from accelerometer
    uint32_t stepCount = 0;
    uint8_t activityType = 0;
    accelerometer.getStepCount(&stepCount, &activityType);
    
    // Clear screen
    oled.erase();

    // Print header
    numChars = sprintf(displayStr, "Steps");
    printRow(0, displayStr, numChars);
    
    // Print number of steps
    numChars = sprintf(displayStr, "%li", stepCount);
    printRow(1, displayStr, numChars);

    // Print activity type
    switch(activityType)
    {
        case BMA400_RUN_ACT:
            numChars = sprintf(displayStr, "Running");
            break;
        case BMA400_WALK_ACT:
            numChars = sprintf(displayStr, "Walking");
            break;
        case BMA400_STILL_ACT:
            numChars = sprintf(displayStr, "Standing");
            break;
        default:
            numChars = sprintf(displayStr, "Unknown");
            break;
    }
    printRow(2, displayStr, numChars);

    // Display on OLED
    oled.display();
}

// Displays battery voltage
void displayBatteryVoltage()
{
    // Check if screen needs to be updated
    if(!updateScreen)
        return;
    updateScreen = false;

    // Create text buffer
    char displayStr[10] = {0};
    uint8_t numChars = 0;

    // Clear screen
    oled.erase();

    // Print header
    numChars = sprintf(displayStr, "Battery");
    printRow(0, displayStr, numChars);
    numChars = sprintf(displayStr, "Voltage");
    printRow(1, displayStr, numChars);
    
    // Measure battery voltage, averaged over several samples
    uint8_t numSamples = 100;
    uint32_t batteryRaw = 0;
    for(uint8_t i = 0; i < numSamples; i++)
    {
        batteryRaw += analogRead(batteryPin);
    }
    float voltage = 3.3 / 4095 * batteryRaw / numSamples;

    // Measured voltage is less than true battery voltage, partly because of the
    // voltage divider circuit, and partly because the ADC has a non-zero input
    // current. This scaler was experimentally found to correct these effects,
    // though the nominal value may differ between boards
    voltage *= 1.688;
    
    // Print battery voltage
    numChars = sprintf(displayStr, "%.3fV", voltage);
    printRow(2, displayStr, numChars);

    // Display on OLED
    oled.display();
}

void displaySyncRTC()
{
    // Check if screen needs to be updated
    if(!updateScreen)
        return;
    updateScreen = false;

    // Create text buffer
    char displayStr[10] = {0};
    uint8_t numChars = 0;

    // Clear screen
    oled.erase();

    // Print RTC sync message
    numChars = sprintf(displayStr, "Sync RTC");
    printRow(0, displayStr, numChars);
    numChars = sprintf(displayStr, "with NTP?");
    printRow(1, displayStr, numChars);

    // Display on OLED
    oled.display();

    // Check if user requested to synchronize RTC
    if(userInput)
    {
        // Clear screen
        oled.erase();

        // Print RTC sync message
        numChars = sprintf(displayStr, "Syncing");
        printRow(0, displayStr, numChars);
        numChars = sprintf(displayStr, "RTC...");
        printRow(1, displayStr, numChars);
        
        // Display on OLED
        oled.display();

        // Start connecting to WiFi network
        WiFi.begin(ssid, password);
        while(WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi...");
            delay(1000);
        }
        
        // Sync with an NTP server
        configTime(timeZone * 3600, 3600, "pool.ntp.org");
        
        // Disconnect WiFi
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);

        // Get updated time
        struct tm timeinfo;
        getLocalTime(&timeinfo);

        // Set RTC to current time
        uint8_t time[TIME_ARRAY_LENGTH];
        time[TIME_HUNDREDTHS] = rtc.DECtoBCD(millis());
        time[TIME_SECONDS] = rtc.DECtoBCD(timeinfo.tm_sec);
        time[TIME_MINUTES] = rtc.DECtoBCD(timeinfo.tm_min);
        time[TIME_HOURS] = rtc.DECtoBCD(timeinfo.tm_hour);
        time[TIME_DATE] = rtc.DECtoBCD(timeinfo.tm_mday);
        time[TIME_MONTH] = rtc.DECtoBCD(timeinfo.tm_mon);
        time[TIME_YEAR] = rtc.DECtoBCD(timeinfo.tm_year);
        time[TIME_DAY] = rtc.DECtoBCD(timeinfo.tm_wday);
        rtc.setTime(time, TIME_ARRAY_LENGTH);

        // Clear screen
        oled.erase();

        // Print RTC sync message
        numChars = sprintf(displayStr, "RTC");
        printRow(0, displayStr, numChars);
        numChars = sprintf(displayStr, "Synced!");
        printRow(1, displayStr, numChars);
        
        // Display on OLED
        oled.display();
    }
}

// Helper function to display text on rows 0-2
void printRow(uint8_t row, char* text, uint8_t numChars)
{
    // Set cursor location so text is centered
    oled.setCursor(midX - 5 * numChars / 2, rowHeight * row);

    // Print text at cursor location
    oled.print(text);
}

// Helper function to minimuze total current consumption and enter deep sleep
void enterDeepSleep()
{
    // Turn off display
    oled.erase();
    oled.display();
    oled.displayPower(false);

    // Minimize current consumption of RTC
    rtc.enableLowPower();
    rtc.enableSleep();
    rtc.writeRegister(RV1805_CTRL1, 0x77);

    // Disable accelerometer interrupts, except double tap
    accelerometer.enableInterrupt(BMA400_STEP_COUNTER_INT_EN, false);
    accelerometer.enableInterrupt(BMA400_SINGLE_TAP_INT_EN, false);
    // accelerometer.enableInterrupt(BMA400_DOUBLE_TAP_INT_EN, false);
    accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, false);
    accelerometer.enableInterrupt(BMA400_GEN2_INT_EN, false);

    // Could have had a new interrupt fire, read status to clear old interrupts
    uint16_t interruptStatus = 0;
    accelerometer.getInterruptStatus(&interruptStatus);
    
    // Set interrupt pin as wakeup source
    esp_deep_sleep_enable_gpio_wakeup(BIT(interruptPin), ESP_GPIO_WAKEUP_GPIO_HIGH);
    
    // Enter deep sleep. This never returns, instead the code restarts entirely
    esp_deep_sleep_start();
}

// ISR for accelerometer interrupts
void bma400InterruptHandler()
{
    // Set flag to be evaluated later
    interruptOccurred = true;
}