/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_mini, double output_lim_maxi) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
   this->Kpi = Kpi;
   this->Kii = Kii;
   this->Kdi = Kdi;
   this->output_lim_maxi = output_lim_maxi;
   this->output_lim_mini = output_lim_mini;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   d_error = (cte - prev_cte)/delta_time;
   p_error = cte;
   i_error += cte * delta_time;
   prev_cte = cte;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control = (Kpi * p_error) + (Kii * i_error) + (Kdi * d_error);
   if(initvalue == true && control > 0.3) {
     control = 0.3;
     initvalue = false;
   }
  
   if(control < output_lim_mini)
      control = output_lim_mini;
   if(control > output_lim_maxi)
      control = output_lim_maxi;
   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  delta_time = new_delta_time;
  if(delta_time < 1) delta_time = 1;
}