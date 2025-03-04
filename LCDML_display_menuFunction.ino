/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    //LCDML_UNUSED(param);
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);

    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
    //LCDML.FUNC_setGBA() 

    //
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change

    // uncomment this line when the screensaver should not be called when this function is running
    // reset screensaver timer
    //LCDML.SCREEN_resetTimer();

    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions ends.
    // this means when you are calling a jumpTo ore a goRoot function
    // that this part is called before a function is closed
  }
}


 * ===================================================================== *
 */
uint8_t value;

void mFunc_moisture(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    value = minLevel;
    // setup function
    // print LCD content
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("Min Level(10-90)"));
    lcd.setCursor(6, 1);
    lcd.print(value);
    lcd.print("%");
    // Reset Button Value
    LCDML.FUNC_setLoopInterval(100);

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        if(value < 90) value++;
      }
      if (LCDML.BT_checkRight())
      {
        LCDML.BT_resetLeft(); // reset the left button
        if (value > 10) value--;
      }
      if(LCDML.BT_checkEnter()) {minLevel = value; LCDML.FUNC_goBackToMenu();}
      // update LCD content
      // update LCD content
      lcd.setCursor(6, 1); // set cursor
      lcd.print(value); // print change content   
      lcd.print("%");   
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

void mFunc_w_time(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    value = wateringTime/1000;
    // setup function
    // print LCD content
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("Time,s (10-60)"));
    lcd.setCursor(6, 1);
    lcd.print(value);
    lcd.print("s");
    // Reset Button Value
    LCDML.FUNC_setLoopInterval(100);

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        if(value < 60) value++;
      }
      if (LCDML.BT_checkRight())
      {
        LCDML.BT_resetLeft(); // reset the left button
        if (value > 10) value--;
      }
      if(LCDML.BT_checkEnter()) {wateringTime = value * 1000; LCDML.FUNC_goBackToMenu();}
      // update LCD content
      // update LCD content
      lcd.setCursor(6, 1); // set cursor
      lcd.print(value); // print change content   
      lcd.print("s");   
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

void mFunc_w_pressure(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    value = map(waterPressure, 0, 255, 0, 90);
    // setup function
    // print LCD content
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("Pressure (10-90)"));
    lcd.setCursor(6, 1);
    lcd.print(value);
    lcd.print("%");
    // Reset Button Value
    LCDML.FUNC_setLoopInterval(100);

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        if(value < 90) value++;
      }
      if (LCDML.BT_checkRight())
      {
        LCDML.BT_resetLeft(); // reset the left button
        if (value > 10) value--;
      }
      if(LCDML.BT_checkEnter()) {waterPressure = map(value, 0, 90, 0, 255) ; LCDML.FUNC_goBackToMenu();}
      // update LCD content
      // update LCD content
      lcd.setCursor(6, 1); // set cursor
      lcd.print(value); // print change content   
      lcd.print("%");   
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    lcd.setCursor(0, 0);
    lcd.print(F("To close this"));
    lcd.setCursor(0, 1);
    lcd.print(F("function press"));
    lcd.setCursor(0, 2);
    lcd.print(F("any button or use"));
    lcd.setCursor(0, 3);
    lcd.print(F("back button"));
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if(LCDML.BT_checkAny()) { // check if any button is pressed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (global variable)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    lcd.print(F("20 sec wait")); // print some content on first row
    g_func_timer_info = 20;       // reset and set timer
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(g_timer_1);
  }


  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

    // this function is called every 100 milliseconds

    // this method checks every 1000 milliseconds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000)) {
      g_func_timer_info--;                // increment the value every second
      lcd.setCursor(0, 0);                // set cursor pos
      lcd.print(F("  "));
      lcd.setCursor(0, 0);                // set cursor pos
      lcd.print(g_func_timer_info);       // print the time counter value
    }

    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normally
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    // print LCD content
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("press left or up"));
    lcd.setCursor(0, 1);
    lcd.print(F("count: 0 of 3"));
    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;

        // update LCD content
        // update LCD content
        lcd.setCursor(7, 1); // set cursor
        lcd.print(g_button_value); // print change content
      }
    }

    // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

unsigned long timer_1 = 0, timer_2 = 0, counter;    // timer variable (global variable)

// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{

  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // update LCD content
    lcd.setCursor(3, 0); // set cursor
    lcd.print(F("Moisture:")); // print change content
    // set cursor
    lcd.setCursor(6, 1);
    lcd.print(moisture);
    lcd.print("%");
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(timer_1);
    counter = 0;
  
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

    // this function is called every 100 milliseconds

    // this method checks every 1000 milliseconds if it is called
    if(LCDML.TIMER_ms(timer_1, 2000)) {
      lcd.setCursor(0, 1);                // set cursor pos
      lcd.print(F("                "));
      lcd.setCursor(6, 1);                // set cursor pos
      lcd.print(moisture); 
      Serial.println(moisture);      // print the time counter value
      lcd.print("%");
      if (++counter > 15){
        lcd.noBacklight();
        counter = 0;
      }
    }
    
    if (LCDML.BT_checkAny()){
      lcd.backlight();
      counter = 0;
      if (LCDML.BT_checkEnter()) // check if any button is pressed (enter, up, down, left, right)
      {
        // remmove compiler warnings when the param variable is not used:
        LCDML_UNUSED(param);

        LCDML.FUNC_goBackToMenu();  // leave this function
      }
    }
  }

  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

// *********************************************************************
void mFunc_jumpTo_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    
    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}


// *********************************************************************
void mFunc_para(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {

    char buf[20];
    sprintf (buf, "parameter: %d", param);

    lcd.setCursor(0, 0);
    lcd.print(buf);
    lcd.setCursor(0, 1);
    lcd.print(F("press any key"));
    lcd.setCursor(0, 2);
    lcd.print(F("to leave it"));

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // For example
    switch(param)
    {
      case 10:
        // do something
        break;

      case 20:
        // do something
        break;

      case 30:
        // do something
        break;

      default:
        // do nothing
        break;
    }


    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())        // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
