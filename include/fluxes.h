#ifndef FLUXES_H
#define FLUXES_H

#define GHZ 1e9
#define keV 2.42e17
#define JANSKY 1e-23
#define mJY 1e-26
#define nJY 1e-32

typedef struct {

  double frequency;
  double flux;
  double flux_err;
  
} flux;

typedef struct  {

  double frequency;
  double lum;
  double lum_err;
  
} luminosity;

double flux_to_lum(flux *input, cosmology *params, double z);
double flux_to_lum_err(flux *input, cosmology *params, double z);
void convert_from_flux(flux *input, luminosity *output, cosmology *params, double z);

#endif // !FLUXES_H
