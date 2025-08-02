#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "cosmology.h"
#include "fluxes.h"
#include "fileIO.h"

int read_config(const char *filename, cosmology *params){

  // set defaults 

  params->H0 = 70;
  params->Omat = 0.3;
  params->Orad = 0;
  params->Olam = 0.7;
  params->Ok = 0;

  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Unable to open config file %s\n", filename);
    return 0;
  }

  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *json_data = (char *)malloc(file_size + 1);
  if (!json_data) {
    fclose(fp);
    fprintf(stderr, "Memory allocation error when reading the data!\n");
    return 0;
  }

  size_t read_size = fread(json_data, 1, file_size, fp);
  fclose(fp);
  json_data[read_size] = '\0';

  cJSON *json = cJSON_Parse(json_data);
  free(json_data);

  if (!json) {
    fprintf(stderr, "Error parsin JSON: %s\n", cJSON_GetErrorPtr());
  }

  cJSON *item;

  if ( (item = cJSON_GetObjectItem(json, "hubble_param") )  ) {
    params->H0 = item->valuedouble;
  }

  if ( (item = cJSON_GetObjectItem(json, "omega_matter") )  ) {
    params->Omat = item->valuedouble;
  }

  if ( (item = cJSON_GetObjectItem(json, "omega_rad") )  ) {
    params->Orad = item->valuedouble;
  }

  if ( (item = cJSON_GetObjectItem(json, "omega_lambda") )  ) {
    params->Olam = item->valuedouble;
  }

  params->Ok = (1. - params->Omat - params->Orad - params->Olam);

  cJSON_Delete(json);

  return 1;

}

flux* read_fluxes(const char* filename, int* count){

  FILE* file = fopen(filename, "r");
  if (!file) return NULL;

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* data = malloc(length + 1);
  fread(data, 1, length, file);
  data[length] = '\0';
  fclose(file);

  cJSON* json = cJSON_Parse(data);
  free(data);
  if (!json) return NULL;

  *count = cJSON_GetArraySize(json);
  flux* fluxes = malloc(*count * sizeof(flux));
  if (!fluxes){
    cJSON_Delete(json);
    return NULL;
  }

  for (int i = 0 ; i < *count ; i++) {
    cJSON* item = cJSON_GetArrayItem(json, i);
    fluxes[i].frequency = cJSON_GetObjectItem(item, "frequency")->valuedouble;
    fluxes[i].flux = cJSON_GetObjectItem(item, "flux")->valuedouble;
    fluxes[i].flux_err = cJSON_GetObjectItem(item, "flux_error")->valuedouble;
  }

  cJSON_Delete(json);
  return fluxes;

}
