/****************************************************************************
                                                Jose Jorge Jimenez-Olivas
                                                June 25, 2018

File Name:      Controller.ino
Description:    Button command functions. Button behavior is handled in this
                file, every function is mapped to a specific button from the 
                bluetooth controller. 
****************************************************************************/
#include "Controller.h"

/* Connected in: Controller Mode */

int button_up() {

  return 0;
}

int button_down() {

  return 0;
}

int button_left() {

  return 0;
}

int button_right() {

  return 0;
}

int button_select() {

  return 0;
}

int button_start() {

  return 0;
}

int button_triangle() {

  return 0;
}

int button_square() {
  
  return 0;
}

int button_o() {

  return 0;
}

int button_x() {

  return 0;
}

/* Connected in: Swicth Mode */

int powerButton() {

  digitalWrite( ledPin, !digitalRead( ledPin ) );
  
  return 0;
}

/* Connected in: Dimmer Mode */

int newCurrentDim( int, int); 

int slideButton() {
  int currentDim = atoi( buffer );    /* current dim value */
  static int previousDim = currentDim;/* prev value between 0 - 255 */

  if( previousDim < MIN_DIM || previousDim > MAX_DIM ) {
    /* enforce valid previous dim value */
    previousDim = currentDim;
    return 1;
  }

  if( abs( currentDim - previousDim ) > 50 ) {
    /* abnormal jump - calculate correct currentDim */
    currentDim = newCurrentDim( previousDim, 50 );
  }

  analogWrite( ledPin, currentDim );
  previousDim = currentDim;


  return 0;
}

int newCurrentDim( int previousDim, int jump ) {
  int prevLen = String( previousDim ).length(); /* number of digits in prevBuff */
  int currLen = strlen( buffer );          /* number of digits in currBuff */
  int numOffset = abs(currLen - prevLen);  /* new number offset in currBuff */
  int newDim;                              /* new current Dim */
  int initDim;                             /* initial dim value prediction */

  initDim = atoi( buffer + numOffset );
  newDim = initDim;

  if( newDim - previousDim < -jump && currLen > 1) {
    newDim = atoi( buffer + (currLen - prevLen) - 1 );
  }
  else if( newDim - previousDim > jump && currLen > 1) {
    newDim = atoi( buffer + (currLen - prevLen) + 1);
  }

  if( abs(newDim - previousDim) > abs(initDim - previousDim)  ) {
    /* incorrect newDim prediction. no change needed */
    Serial.println( initDim );
    newDim = initDim;
  }

  if( newDim - previousDim == 0 && currLen > 1) {
    newDim = atoi( buffer + (currLen - prevLen) - 1 );
  }

  return newDim;
}

