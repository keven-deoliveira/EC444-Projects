#include <stdio.h>
#include <string.h>
#include "esp_types.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#define TIMER_DIVIDER         16    //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // to seconds
#define TIMER_INTERVAL_SEC   (1)    // Sample test interval for the first timer
#define TEST_WITH_RELOAD      1     // Testing will be done with auto reload

#define BTN_GPIO 34

#define feeder_interval_seconds 120

// 14-Segment Display
#define SLAVE_ADDR                         0x70 // alphanumeric address
#define OSC                                0x21 // oscillator cmd
#define HT16K33_BLINK_DISPLAYON            0x01 // Display on cmd
#define HT16K33_BLINK_OFF                  0    // Blink off cmd
#define HT16K33_BLINK_CMD                  0x80 // Blink cmd
#define HT16K33_CMD_BRIGHTNESS             0xE0 // Brightness cmd

// Master I2C
#define I2C_EXAMPLE_MASTER_SCL_IO          22   // gpio number for i2c clk
#define I2C_EXAMPLE_MASTER_SDA_IO          23   // gpio number for i2c data
#define I2C_EXAMPLE_MASTER_NUM             I2C_NUM_0  // i2c port
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE  0    // i2c master no buffer needed
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE  0    // i2c master no buffer needed
#define I2C_EXAMPLE_MASTER_FREQ_HZ         100000     // i2c master clock freq
#define WRITE_BIT                          I2C_MASTER_WRITE // i2c master write
#define READ_BIT                           I2C_MASTER_READ  // i2c master read
#define ACK_CHECK_EN                       true // i2c master will check ack
#define ACK_CHECK_DIS                      false// i2c master will not check ack
#define ACK_VAL                            0x00 // i2c ack value
#define NACK_VAL                           0xFF // i2c nack value

static const uint16_t alphafonttable[] =  {
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000,
	0b0000000000000000, //  
	0b0100000000000110, // !
	0b0000001000100000, // "
	0b0001001011001110, // #
	0b0001001011101101, // $
	0b0010110111100100, // %
	0b0010001101011101, // &
	0b0000010000000000, // '
	0b0010010000000000, // (
	0b0000100100000000, // )
	0b0011111111000000, // *
	0b0001001011000000, // +
	0b0000100000000000, // ,
	0b0000000011000000, // -
	0b0100000000000000, // .
	0b0000110000000000, // /
	0b0000110000111111, // 0
	0b0000000000000110, // 1
	0b0000000011011011, // 2
	0b0000000010001111, // 3
	0b0000000011100110, // 4
	0b0010000001101001, // 5
	0b0000000011111101, // 6
	0b0000000000000111, // 7
	0b0000000011111111, // 8
	0b0000000011101111, // 9
	0b0001001000000000, // :
	0b0000101000000000, // ;
	0b0010010000000000, // <
	0b0000000011001000, // =
	0b0000100100000000, // >
	0b0001000010000011, // ?
	0b0010000010110111, // @
	0b0000000011110111, // A
	0b0001001010001111, // B
	0b0000000000111001, // C
	0b0001001000001111, // D
	0b0000000011111001, // E
	0b0000000001110001, // F
	0b0000000010111101, // G
	0b0000000011110110, // H
	0b0001001000000000, // I
	0b0000000000011110, // J
	0b0010010001110000, // K
	0b0000000000111000, // L
	0b0000010100110110, // M
	0b0010000100110110, // N
	0b0000000000111111, // O
	0b0000000011110011, // P
	0b0010000000111111, // Q
	0b0010000011110011, // R
	0b0000000011101101, // S
	0b0001001000000001, // T
	0b0000000000111110, // U
	0b0000110000110000, // V
	0b0010100000110110, // W
	0b0010110100000000, // X
	0b0001010100000000, // Y
	0b0000110000001001, // Z
	0b0000000000111001, // [
	0b0010000100000000, // 
	0b0000000000001111, // ]
	0b0000010000000010, // ^
	0b0000000000001000, // _
	0b0000000100000000, // `
	0b0010000001011000, // a
	0b0010000001111000, // b
	0b0000000011011000, // c
	0b0000100010001110, // d
	0b0000100001011000, // e
	0b0000000001110001, // f
	0b0000010010001110, // g
	0b0001000001110000, // h
	0b0001000000000000, // i
	0b0000000000001110, // j
	0b0011011000000000, // k
	0b0000000000110000, // l
	0b0001000011010100, // m
	0b0001000001010000, // n
	0b0000000011011100, // o
	0b0000000101110000, // p
	0b0000010010000110, // q
	0b0000000001010000, // r
	0b0010000010001000, // s
	0b0000000001111000, // t
	0b0000000000011100, // u
	0b0010000000000100, // v
	0b0010100000010100, // w
	0b0010100011000000, // x
	0b0010000000001100, // y
	0b0000100001001000, // z
	0b0000100101001001, // {
	0b0001001000000000, // |
	0b0010010010001001, // }
	0b0000010100100000, // ~
	0b0011111111111111,
};

// 0 = never pushed, 1 = first push, 2 = any consecutive pushes
uint8_t btn_state = 0;

int timer_count = feeder_interval_seconds;

int time_arr[3];

// A simple structure to pass "events" to main task
typedef struct {
    int flag;     // flag for enabling stuff in main code
} timer_event_t;

// Initialize queue handler for timer-based events
xQueueHandle timer_queue;

// ISR handler
void IRAM_ATTR timer_group0_isr(void *para) {

    // Prepare basic event data, aka set flag
    timer_event_t evt;
    evt.flag = 1;

    // Clear the interrupt, Timer 0 in group 0
    TIMERG0.int_clr_timers.t0 = 1;

    // After the alarm triggers, we need to re-enable it to trigger it next time
    TIMERG0.hw_timer[TIMER_0].config.alarm_en = TIMER_ALARM_EN;

    // Send the event data back to the main program task
    xQueueSendFromISR(timer_queue, &evt, NULL);
}

// Initialize timer 0 in group 0 for 1 sec alarm interval and auto reload
static void alarm_init() {
    /* Select and initialize basic parameters of the timer */
    timer_config_t config;
    config.divider = TIMER_DIVIDER;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = TEST_WITH_RELOAD;
    timer_init(TIMER_GROUP_0, TIMER_0, &config);

    // Timer's counter will initially start from value below
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);

    // Configure the alarm value and the interrupt on alarm
    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, TIMER_INTERVAL_SEC * TIMER_SCALE);
    timer_enable_intr(TIMER_GROUP_0, TIMER_0);
    timer_isr_register(TIMER_GROUP_0, TIMER_0, timer_group0_isr,
        (void *) TIMER_0, ESP_INTR_FLAG_IRAM, NULL);

    // Start timer
    timer_start(TIMER_GROUP_0, TIMER_0);
}

void IRAM_ATTR button_intr(void* arg) {
    int i;
    for(i = 0; i < 100000; i++){
        //debounce
    }
    if (!btn_state) {
        btn_state = 1;
    }
    else if(btn_state == 1) {
        btn_state = 2;
    }
}

static void btn_init() {
    gpio_pad_select_gpio(BTN_GPIO);
    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_GPIO, GPIO_INTR_NEGEDGE);
    gpio_intr_enable(BTN_GPIO);
    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL2);
    gpio_isr_handler_add(BTN_GPIO, button_intr, NULL);
}

static void time_conversion(int sec, int time_arr[]) {
    int h, m, s;

    h = sec/3600;
    m = (sec -(3600*h))/60;
    s = (sec -(3600*h)-(m*60));

    time_arr[0] = h;
    time_arr[1] = m;
    time_arr[2] = s;
}

// The main task of this example program
static void timer_evt_task(void *arg) {
    while (1) {
        // Create dummy structure to store structure from queue
        timer_event_t evt;

        // Transfer from queue
        xQueueReceive(timer_queue, &evt, portMAX_DELAY);

        // Do something if triggered!
        if (evt.flag == 1) {
            time_conversion(timer_count, time_arr);
            //printf("%d\n", timer_count);
            printf("%02d:%02d:%02d\n", time_arr[0], time_arr[1], time_arr[2]);
            if (timer_count == 0) {
                // reset, send signal to servo
                timer_count = feeder_interval_seconds;
                printf("FISH FED\n");
            }
            else {
                if (btn_state == 1) {
                    timer_count--;
                }
                else if (btn_state == 2) {
                    printf("Reset!\n");
                    timer_count = feeder_interval_seconds;
                    btn_state = 1;
                }
            }
        }
    }
}

// Function to initiate i2c -- note the MSB declaration!
static void i2c_example_master_init(){
    // Debug
    printf("\n>> i2c Config\n");
    int err;

    // Port configuration
    int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;

    /// Define I2C configurations
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;                              // Master mode
    conf.sda_io_num = I2C_EXAMPLE_MASTER_SDA_IO;              // Default SDA pin
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;                  // Internal pullup
    conf.scl_io_num = I2C_EXAMPLE_MASTER_SCL_IO;              // Default SCL pin
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;                  // Internal pullup
    conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;       // CLK frequency
    err = i2c_param_config(i2c_master_port, &conf);           // Configure
    if (err == ESP_OK) {printf("- parameters: ok\n");}

    // Install I2C driver
    err = i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);
    // i2c_set_data_mode(i2c_master_port,I2C_DATA_MODE_LSB_FIRST,I2C_DATA_MODE_LSB_FIRST);
    if (err == ESP_OK) {printf("- initialized: yes\n\n");}

    // Dat in MSB mode
    i2c_set_data_mode(i2c_master_port, I2C_DATA_MODE_MSB_FIRST, I2C_DATA_MODE_MSB_FIRST);
}

// Utility  Functions //////////////////////////////////////////////////////////

// Utility function to test for I2C device address -- not used in deploy
int testConnection(uint8_t devAddr, int32_t timeout) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    int err = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return err;
}

// Utility function to scan for i2c device
static void i2c_scanner() {
    int32_t scanTimeout = 1000;
    printf("\n>> I2C scanning ..."  "\n");
    uint8_t count = 0;
    for (uint8_t i = 1; i < 127; i++) {
        // printf("0x%X%s",i,"\n");
        if (testConnection(i, scanTimeout) == ESP_OK) {
            printf( "- Device found at address: 0x%X%s", i, "\n");
            count++;
        }
    }
    if (count == 0)
        printf("- No I2C devices found!" "\n");
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////

// Alphanumeric Functions //////////////////////////////////////////////////////

// Turn on oscillator for alpha display
int alpha_oscillator() {
  int ret;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, OSC, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

// Set blink rate to off
int no_blink() {
  int ret;
  i2c_cmd_handle_t cmd2 = i2c_cmd_link_create();
  i2c_master_start(cmd2);
  i2c_master_write_byte(cmd2, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd2, HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (HT16K33_BLINK_OFF << 1), ACK_CHECK_EN);
  i2c_master_stop(cmd2);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd2, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd2);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

// Set Brightness
int set_brightness_max(uint8_t val) {
  int ret;
  i2c_cmd_handle_t cmd3 = i2c_cmd_link_create();
  i2c_master_start(cmd3);
  i2c_master_write_byte(cmd3, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd3, HT16K33_CMD_BRIGHTNESS | val, ACK_CHECK_EN);
  i2c_master_stop(cmd3);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd3, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd3);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

////////////////////////////////////////////////////////////////////////////////

static void test_alpha_display() {

    char hour[5];
    char minute[5];
    char second[5];

    // Debug
    int ret;
    printf(">> Test Alphanumeric Display: \n");

    // Set up routines
    // Turn on alpha oscillator
    ret = alpha_oscillator();
    if(ret == ESP_OK) {printf("- oscillator: ok \n");}
    // Set display blink off
    ret = no_blink();
    if(ret == ESP_OK) {printf("- blink: off \n");}
    ret = set_brightness_max(0xF);
    if(ret == ESP_OK) {printf("- brightness: max \n");}

    while (1) {
      sprintf(hour, "%02d", time_arr[0]);
      sprintf(minute, "%02d", time_arr[1]);
      sprintf(second, "%02d", time_arr[2]);
      
      int i;  

      uint16_t displaybuffer_hr[8];
      uint16_t displaybuffer_min[8];

      for (i = 0; i < 4; i++) { // i think this is needed otherwise text wouldnt change
          displaybuffer_hr[i] = alphafonttable[' '];
      }

      for (i = 0; i < 4; i++) { // i think this is needed otherwise text wouldnt change
          displaybuffer_min[i] = alphafonttable[' '];
      }

      i = 0;
      while (i < 4 && hour[i] != '\0') { // go until 4 chars or end of string
        displaybuffer_hr[i] = alphafonttable[(int) hour[i]];
        displaybuffer_min[i] = alphafonttable[(int) minute[i]];
        i++;
      }


      // Send commands characters to display over I2C
      i2c_cmd_handle_t cmd4 = i2c_cmd_link_create();
      i2c_master_start(cmd4);
      i2c_master_write_byte(cmd4, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
      i2c_master_write_byte(cmd4, (uint8_t)0x00, ACK_CHECK_EN);
      for (uint8_t i=0; i<8; i++) {
        i2c_master_write_byte(cmd4, displaybuffer_min[i] & 0xFF, ACK_CHECK_EN);
        i2c_master_write_byte(cmd4, displaybuffer_min[i] >> 8, ACK_CHECK_EN);
      }
      i2c_master_stop(cmd4);
      ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd4, 1000 / portTICK_RATE_MS);
      i2c_cmd_link_delete(cmd4);

      // for (int i = 0; i < 8; i++) {
      //     printf("%04x\n", displaybuffer[i]);
      // }

      if(ret == ESP_OK) {
      }
    }
}

void app_main(void) {
    btn_init();
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
      256, 0, 0, NULL, 0) );

    // Need uart driver
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    i2c_example_master_init();
    i2c_scanner();

    // Create a FIFO queue for timer-based
    timer_queue = xQueueCreate(10, sizeof(timer_event_t));

    // Create task to handle timer-based events
    xTaskCreate(timer_evt_task, "timer_evt_task", 2048, configMAX_PRIORITIES, 5, NULL);
    xTaskCreate(test_alpha_display,"test_alpha_display", 4096, configMAX_PRIORITIES-1, 5, NULL);

    // Initiate alarm using timer API
    alarm_init();
}
