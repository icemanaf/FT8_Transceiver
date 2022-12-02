#include "../controller.h"


void ResetState( state *val)
{
  val->freq_80m=3500000;
  val->freq_40m=7000000;
  val->freq_30m=10000000;
  val->freq_20m=14074000;
  val->freq_17m=18068000;
  val->freq_15m=21000000;
  val->freq_10m=28074000;
  
  val->current_band=BAND_20;
  val->current_selection=FREQ;
  val->current_step=STEP_1000;
}

void ToggleSelection( state *val)
{
    switch(val->current_selection)
    {
        case FREQ:
            val->current_selection=BAND;
            break;
        case BAND:
            val->current_selection=STEP;
            break;
        case STEP:
            val->current_selection=FREQ;
            break;
        default:
             val->current_selection=FREQ;
            
    }
}

long GetStepValue(state *val)
{
    
    switch(val->current_step)
    {
        case STEP_10:
            return 10;
        case STEP_100:
            return 100;
        case STEP_1000:
            return 1000;
        case STEP_10000:
            return 10000;
        case STEP_100000:
            return 100000;
            
    }
    
    return 1000;
}

long GetFrequency(state* val)
{
    long ret=0;
    
    switch(val->current_band)
    {
      case BAND_80:
        ret=val->freq_80m;
        break;
      case BAND_40:
        ret=val->freq_40m;
        break;
      case BAND_30:
        ret=val->freq_30m;
        break;
      case BAND_20:
        ret=val->freq_20m;
        break;
      case BAND_17:
        ret=val->freq_17m;
        break;
      case BAND_15:
        ret=val->freq_15m;
        break;
      case BAND_10:
        ret=val->freq_10m;
        break;
        
    }

    return ret;
}

void IncFreq( state *val)
{
    int step=GetStepValue(val);
    switch(val->current_band)
    {
        case BAND_80:
            val->freq_80m=val->freq_80m+step;
            break;
        case BAND_40:
            val->freq_40m=val->freq_40m+step;
            break;
         case BAND_30:
            val->freq_30m=val->freq_30m+step;
            break;
        case BAND_20:
            val->freq_20m=val->freq_20m+step;
            break;
        case BAND_17:
            val->freq_17m=val->freq_17m+step;
            break;
        case BAND_15:
            val->freq_15m=val->freq_15m+step;
            break;
         case BAND_10:
            val->freq_10m=val->freq_10m+step;
            break; 
        
    }
}


void DecFreq( state *val)
{
    int step=GetStepValue(val);
    switch(val->current_band)
    {
        case BAND_80:
            val->freq_80m=val->freq_80m-step;
            break;
        case BAND_40:
            val->freq_40m=val->freq_40m-step;
            break;
         case BAND_30:
            val->freq_30m=val->freq_30m-step;
            break;
        case BAND_20:
            val->freq_20m=val->freq_20m-step;
            break;
        case BAND_17:
            val->freq_17m=val->freq_17m-step;
            break;
        case BAND_15:
            val->freq_15m=val->freq_15m-step;
            break; 
        case BAND_10:
            val->freq_10m=val->freq_10m-step;
            break;  
        
    }
}

int GetBandValue(state *val)
{
    switch(val->current_band)
    {
        case BAND_80:
            return 80;
        case BAND_40:
            return 40;
        case BAND_30:
            return 30;
        case BAND_20:
            return 20;
        case BAND_17:
            return 17;
        case BAND_15:
            return 15;
        case BAND_10:
            return 10;
        default:
            return 20;
    }
    
}

void IncBand( state *val)
{
    switch(val->current_band)
    {
        case BAND_80:
            val->current_band=BAND_40;
            break;
        case BAND_40:
            val->current_band=BAND_30;
            break;
        case BAND_30:
            val->current_band=BAND_20;
            break;
        case BAND_20:
            val->current_band=BAND_17;
            break;
        case BAND_17:
            val->current_band=BAND_15;
            break;
        case BAND_15:
            val->current_band=BAND_10;
            break;
        case BAND_10:
            val->current_band=BAND_80;
            break;
    
    }
}


void DecBand( state *val)
{
    switch(val->current_band)
    {
        case BAND_80:
            val->current_band=BAND_10;
            break;
        case BAND_40:
            val->current_band=BAND_80;
            break;
        case BAND_30:
            val->current_band=BAND_40;
            break;
        case BAND_20:
            val->current_band=BAND_30;
            break;
        case BAND_17:
            val->current_band=BAND_20;
            break;
        case BAND_15:
            val->current_band=BAND_17;
            break;
        case BAND_10:
            val->current_band=BAND_15;
            break;
    
    }
}

void IncStep( state *val)
{
    switch(val->current_step)
    {
        case STEP_10:
            val->current_step=STEP_100;
            break;
        case STEP_100:
            val->current_step=STEP_1000;
            break;
        case STEP_1000:
            val->current_step=STEP_10000;
            break;
        case STEP_10000:
            val->current_step=STEP_100000;
            break;
        case STEP_100000:
            val->current_step=STEP_10;
            break;
    }
}


void DecStep( state *val)
{
    switch(val->current_step)
    {
        case STEP_10:
            val->current_step=STEP_100000;
            break;
        case STEP_100:
            val->current_step=STEP_10;
            break;
        case STEP_1000:
            val->current_step=STEP_100;
            break;
        case STEP_10000:
            val->current_step=STEP_1000;
            break;
        case STEP_100000:
            val->current_step=STEP_10000;
            break;
       
    }
}