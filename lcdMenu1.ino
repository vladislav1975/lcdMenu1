// ============================================================
// Example:     LCDML_serialmonitor
// ============================================================
// Description:
// This example includes the complete functionality over some
// tabs. All Tabs which are started with "LCDML_display_.."
// generates an output on the display / console / ....
// This example is for the author to test the complete functionality
// ============================================================
// *********************************************************************
// special settings
// *********************************************************************
// enable this line when you are not usigng a standard arduino
// for example when your chip is an ESP or a STM or SAM or something else

//#define _LCDML_cfg_use_ram 

// *********************************************************************
// includes
// *********************************************************************
  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib2.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _I2C_ADDR 0x3f
  #define _LCDML_DISP_cols  16
  #define _LCDML_DISP_rows  2
  #define tmp 0

  // enable this line (set to 1) to show a header above the first menu element
  // this function can be changed in LCDML_display_menu tab
  #define _LCDML_DSIP_use_header 0

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar

  const uint8_t pompPin = 13;
  const uint8_t sensorPin = A0;
  const uint32_t interval = 1000;
  uint8_t minLevel = 30; //minimum moisture level
  uint16_t wateringTime = 10000; // Watering time (ms) 65 sec. maximum
  uint8_t waterPressure = 128; // 0 - 255
  int sensorValue, moisture;
  String mStr;
  bool isWatering = false;
  long int curr, prev;
  
  // LCD object
  // liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
  LiquidCrystal_I2C lcd(_I2C_ADDR, _LCDML_DISP_cols, _LCDML_DISP_rows);

  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  };

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

  bool isTimeToCheck();
  void checkSoil();
  void watering();

// *********************************************************************
// Global variables
// *********************************************************************


// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows-_LCDML_DSIP_use_header, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0
  // LCDML_0_X      => layer 1
  // LCDML_0_X_X    => layer 2
  // LCDML_0_X_X_X  => layer 3
  // LCDML_0_...      => layer ...

  // For beginners
  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
  LCDML_add         (0  , LCDML_0         , 1  , "Information"         , mFunc_screensaver);       // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (1,   LCDML_0         , 2  , "Set Level,%"         , mFunc_moisture)
  LCDML_add         (2,   LCDML_0         , 3  , "Watering, ms"        , mFunc_w_time)
  LCDML_add         (3,   LCDML_0         , 4  , "Pressure, %"         , mFunc_w_pressure)
  
  // LCDML_add         (1  , LCDML_0         , 2  , "Time info"        , mFunc_timer_info);        // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (2  , LCDML_0         , 3  , "Program"          , NULL);                    // NULL = no menu function
  // LCDML_add         (3  , LCDML_0_3       , 1  , "Program 1"        , NULL);                    // NULL = no menu function
  // LCDML_add         (4  , LCDML_0_3_1     , 1  , "P1 dummy"         , NULL);                    // NULL = no menu function
  // LCDML_add         (5  , LCDML_0_3_1     , 2  , "P1 Settings"      , NULL);                    // NULL = no menu function
  // LCDML_add         (6  , LCDML_0_3_1_2   , 1  , "Warm"             , NULL);                    // NULL = no menu function
  // LCDML_add         (7  , LCDML_0_3_1_2   , 2  , "Cold"             , NULL);                    // NULL = no menu function
  // LCDML_add         (8  , LCDML_0_3_1_2   , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (9  , LCDML_0_3_1     , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (10 , LCDML_0_3       , 2  , "Program 2"        , mFunc_p2);                // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (11 , LCDML_0_3       , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (12 , LCDML_0         , 4  , "Special"          , NULL);                    // NULL = no menu function
  // LCDML_add         (13 , LCDML_0_4       , 1  , "Go to Root"       , mFunc_goToRootMenu);      // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (14 , LCDML_0_4       , 2  , "Jump to Time info", mFunc_jumpTo_timer_info); // this menu function can be found on "LCDML_display_menuFunction" tab
  // LCDML_add         (15 , LCDML_0_4       , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab


  // Advanced menu (for profit) part with more settings
  // Example for one function and different parameters
  // It is recommend to use parameters for switching settings like, (small drink, medium drink, big drink) or (200ml, 400ml, 600ml, 800ml) ...
  // the parameter change can also be released with dynParams on the next example
  // LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  // LCDML_addAdvanced (16 , LCDML_0         , 5  , NULL,          "Parameter"      , NULL,                0,            _LCDML_TYPE_default);                    // NULL = no menu function
  // LCDML_addAdvanced (17 , LCDML_0_5       , 1  , NULL,          "Parameter 1"      , mFunc_para,       10,            _LCDML_TYPE_default);                    // NULL = no menu function
  // LCDML_addAdvanced (18 , LCDML_0_5       , 2  , NULL,          "Parameter 2"      , mFunc_para,       20,            _LCDML_TYPE_default);                    // NULL = no menu function
  // LCDML_addAdvanced (19 , LCDML_0_5       , 3  , NULL,          "Parameter 3"      , mFunc_para,       30,            _LCDML_TYPE_default);                    // NULL = no menu function
  // LCDML_add         (20 , LCDML_0_5       , 4  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab


  // Example for dynamic content
  // 1. set the string to ""
  // 2. use type  _LCDML_TYPE_dynParam   instead of    _LCDML_TYPE_default
  // this function type can not be used in combination with different parameters
  // LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  //LCDML_addAdvanced (21 , LCDML_0         , 6  , NULL,          ""                  , mDyn_para,                0,   _LCDML_TYPE_dynParam);                     // NULL = no menu function

  // Example for conditions (for example for a screensaver)
  // 1. define a condition as a function of a boolean type -> return false = not displayed, return true = displayed
  // 2. set the function name as callback (remove the braces '()' it gives bad errors)
  // LCDMenuLib_addAdvanced(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  LCDML_addAdvanced (4 , LCDML_0         , 7  , COND_hide,  "screensaver"        , mFunc_screensaver,        0,   _LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab

  // ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    4

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
    Serial.println(F(_LCDML_VERSION)); // only for examples

    // LCD Begin
    lcd.begin();
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
    //LCDML.SCREEN_disable();

    // Some needful methods

    // You can jump to a menu function from anywhere with
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  { 

    LCDML.loop();
    if (isTimeToCheck()) checkSoil();
    if (moisture < minLevel){
      isWatering = true;
      Serial.println(isWatering);
      prev = millis();
      analogWrite(pompPin, waterPressure);
    }
    if(isWatering & millis() - prev >= wateringTime){
      analogWrite(pompPin, 0);
      isWatering = false;
    }
  }

  bool isTimeToCheck(){
  static unsigned long previousMillis = 0;
  static unsigned long currentMillis;

  currentMillis = millis();
  if (currentMillis < previousMillis) previousMillis = 0;
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

void watering(){
  long int start;
  start = millis();
  analogWrite(pompPin, waterPressure);
  while (millis() - start < wateringTime)  

  analogWrite(pompPin, 0);
}

void checkSoil(){
  sensorValue = analogRead(sensorPin);
  moisture = map(sensorValue, 160, 489, 100, 0);
  Serial.println(sensorValue);
  mStr = String(moisture);
  if (mStr.length() == 1) mStr = "  " + mStr;
  else if (mStr.length() == 2) mStr = " " + mStr;
  mStr += "%";
  // lcd.setCursor(5, 1);
  // lcd.print(mStr);
  // Serial.println(sensorValue);
}