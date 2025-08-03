# Cosmic calculator

## Cosmological distances

Defined in `cosmology.h` allows for calculation of Hubble distance $d_H$, comoving distance $d_C$, transverse comoving distance $d_M$ and luminosity distance $d_L$, after [David W. Hogg](https://arxiv.org/abs/astro-ph/9905116). Integration is via Simpson's rule, number of steps is defined in header as `#define SIMSONSTEPS`. 

Cosmology is loaded from a JSON file in the `data` folder. User sets $H_0$, $\Omega_M$, $\Omega_{rad}$ and $\Omega_\Lambda$. From those, $\Omega_k$ is inferred via Friedmann equation.

## Luminosity calculation

User can also provide flux measurements in the form of a JSON file that has structure: `($\nu$, $\nu F_\nu$, $\Delta \nu F_\nu$)`: frequency, flux, flux error. Program can handle arbitrary number of measurements. It then recomputes them into $\nu L_\nu$ luminosities. Everything is computed in the CGS system of units, so input fluxes should be in $erg cm^{-2} s^{-1} Hz^{-1}$ and output luminosities are in $erg s^{-1}$.


## Dependencies 

* [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON)
* [Gnu Scientific Library](https://www.gnu.org/software/gsl/)
