#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
  FILE *fp;
  fp = fopen("/home/user/github/Race_Manager/configs.txt", "r"); // read mode

  int time_units_per_second, lap_distance, number_of_laps, number_of_teams, T_Avaria, T_Box_Min, T_Box_Max, fuel_capacity;
  if (fp == NULL)
  {
     perror("Error while opening the file.\n");
     exit(EXIT_FAILURE);
  }
  printf("Ficheiro aberto com exito\n");

  fscanf(fp,"%d\n%d, %d\n%d\n%d\n%d, %d\n%d",&time_units_per_second, &lap_distance, &number_of_laps,&number_of_teams, &T_Avaria, &T_Box_Min, &T_Box_Max, &fuel_capacity);
  printf("Número de unidades de tempo por segundo: %d\n",time_units_per_second);
  printf("Distância de cada volta, Número de voltas da corrida: %d, %d\n",lap_distance,number_of_laps);
  printf("Número de equipas: %d\n",number_of_teams);
  printf("T_Avaria: %d\n",T_Avaria);
  printf("T_Box_Min, T_Box_Max: %d, %d\n",T_Box_Min,T_Box_Max);
  printf("Capacidade do depósito de combustível: %d\n",fuel_capacity);


  fclose(fp);
  return 0;
}