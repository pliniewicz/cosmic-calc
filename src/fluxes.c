#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_math.h>

#include "cosmology.h"
#include "fluxes.h"

double flux_to_lum(flux *input, cosmology *params, double z){
  double dl = distance_luminosity(z, params) * MEGA * PARSEC;

  return 4 * M_PI * dl * dl * input->frequency * input->flux;
}

double flux_to_lum_err(flux *input, cosmology *params, double z){
  double dl = distance_luminosity(z, params) * MEGA * PARSEC;

  return 4 * M_PI * dl * dl * input->frequency * input->flux_err;
}

void convert_from_flux(flux *input, luminosity *output, cosmology *params, double z){
  output->frequency = input->frequency;
  output->lum = flux_to_lum(input, params, z);
  output->lum_err = flux_to_lum_err(input, params, z);
}
