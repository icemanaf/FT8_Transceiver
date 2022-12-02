/* 
 * File:   controller.h
 * Author: Ashith
 *
 * Created on 03 October 2022, 19:53
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

//types
typedef enum 
{
  BAND_80,
  BAND_40,
  BAND_30,
  BAND_20,
  BAND_17,
  BAND_15,
  BAND_10          
          
} band;


typedef enum 
{
  FREQ,
  BAND,
  STEP
} selection;


typedef enum
{
  STEP_10,
  STEP_100,
  STEP_1000,
  STEP_10000,
  STEP_100000
} step_size;

typedef struct 
{
  long freq_80m;
  long freq_40m;
  long freq_30m;
  long freq_20m;
  long freq_17m;
  long freq_15m;
  long freq_10m;
  band current_band;
  selection current_selection;
  step_size current_step;
} state;

void ResetState( state*);
void ToggleSelection( state*);

long GetFrequency(state*);
void DecFreq( state*);
void IncFreq( state*);

void IncBand( state*);
void DecBand( state*);
int GetBandValue(state*);

long GetStepValue(state*);
void IncStep( state*);
void DecStep( state*);




#endif	/* CONTROLLER_H */

