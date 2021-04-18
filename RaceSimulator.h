//Edgar Filipe Ferreira Duarte 2019216077
//Pedro Guilherme da Cruz Ferreira 2018277677
#define SIZE 50
#define DEBUG

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct config_fich_struct{
  int time_units_per_second;
  int lap_distance;
  int number_of_laps;
  int number_of_teams;
  int number_of_cars;
  int T_Avaria;
  int T_Box_Min;
  int T_Box_Max;
  int fuel_capacity;
};

struct car{
  int car_number;
  int speed;
  float consumption;
  int reliability;
  int completed_laps;
  int amount_breakdown;
  int times_refull;
};



struct team{
  char team_name[SIZE];
  char box_state[SIZE];
  int number_of_cars;
  int number_readers;
  struct car *cars;
};


struct semaphoreStruct{
  sem_t *logMutex;
  sem_t *writingMutex;
  sem_t *readingMutex;
};
