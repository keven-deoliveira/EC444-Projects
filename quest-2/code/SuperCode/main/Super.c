/* ADC1 Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include <math.h>
#include "esp_adc_cal.h"
#include "sdkconfig.h"
#include "esp_vfs_dev.h"
#include "esp_adc_cal.h"

// which analog pin to connect
#define THERMISTORPIN A0
// resistance at 25 degrees C
#define R1 10000
// temp. for nominal resistance (almost always 25 C)
#define T0 294.15
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BETA 3950
// the value of the 'other' resistor
#define R0 10000

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

static esp_adc_cal_characteristics_t *adc_chars;
static esp_adc_cal_characteristics_t *adc_charsT;
static esp_adc_cal_characteristics_t *adc_charsIR;
static const adc_channel_t channel = ADC_CHANNEL_6;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_channel_t channelT = ADC_CHANNEL_0;    //GPIO36
static const adc_channel_t channelIR = ADC_CHANNEL_3;   //GPIO39
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_atten_t attenT = ADC_ATTEN_DB_11;
static const adc_atten_t attenIR = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

static void check_efuse(void)
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

void app_main(void)
{
    //Check if Two Point or Vref are burned into eFuse
    check_efuse();

    //Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(channel, atten);
        adc1_config_channel_atten(channelT, attenT);
        adc1_config_channel_atten(channelIR, attenIR);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
        adc2_config_channel_atten((adc2_channel_t)channelT, attenT);
        adc2_config_channel_atten((adc2_channel_t)channelIR, attenIR);
    }

    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    adc_charsT = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    adc_charsIR = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    esp_adc_cal_value_t val_typeT = esp_adc_cal_characterize(unit, attenT, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_charsT);
    esp_adc_cal_value_t val_typeIR = esp_adc_cal_characterize(unit, attenIR, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_charsIR);
    print_char_val_type(val_type);
    print_char_val_type(val_typeT);
    print_char_val_type(val_typeIR);

    float A = 0.0;

    //Continuously sample ADC1
    while (1) {
        uint32_t adc_reading = 0;
        uint32_t adc_readingT = 0;
        uint32_t adc_readingIR = 0;
        //Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            if (unit == ADC_UNIT_1) {
                adc_reading += adc1_get_raw((adc1_channel_t)channel);
                adc_readingT += adc1_get_raw((adc1_channel_t)channelT);
                adc_readingIR += adc1_get_raw((adc1_channel_t)channelIR);
            } else {       
                int raw, rawT, rawIR;
                adc2_get_raw((adc2_channel_t)channel, ADC_WIDTH_BIT_12, &raw);
                adc2_get_raw((adc2_channel_t)channelT, ADC_WIDTH_BIT_12, &rawT);
                adc2_get_raw((adc2_channel_t)channelIR, ADC_WIDTH_BIT_12, &rawIR);
                adc_reading += raw;
                adc_readingT += rawT;
                adc_readingIR += rawIR;
            }
        }
        adc_reading /= NO_OF_SAMPLES;
        adc_readingT /= NO_OF_SAMPLES;
        adc_readingIR /= NO_OF_SAMPLES;
        //Convert adc_reading to voltage in mV
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
        uint32_t voltageT = esp_adc_cal_raw_to_voltage(adc_readingT, adc_charsT);
        uint32_t voltageIR = esp_adc_cal_raw_to_voltage(adc_readingIR, adc_charsIR);

        // Thermistor Calculation
        float Rt, T, Tc, Tf, V0 = 0;
        V0 = voltage / 1000.00;
        Rt = R1 * V0 / (5 - V0);
        T = 1/(1/T0 + log(Rt/R0)/BETA);  // Temperature in Kelvin
        Tc = T - 273.15;                 // Celsius
        Tf = Tc * 9 / 5 + 32;            // Fahrenheit

        // IR range finder
        A = 48401.54 / (voltageT - 79.923);

        // Ultrasonic Sensor Calculations
        uint32_t vcm = 4.883;           //conversion to get volts per centimeter. This is found by 5V / 1024
        uint32_t range = voltageIR / vcm; //calculation to get range in centimeters.

        // Ultrasonic Sensor
        // printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
        printf("%f,", Tc);
        printf("%d,", range);
        printf("%f\n", A);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}