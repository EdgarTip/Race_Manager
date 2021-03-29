#define DEBUG



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include "RaceSimulator.h"

#include "RaceManager.h"
#include "ReadConfig.h"

/*Struct that retains the information given by the initial file
Not a shared memory struct but the values will be given to the
processes created in this script*/



/*Shared memory struct the will share memory about the current state of all
of the cars. Will be updated by the Race Manager
*/


struct config_fich_struct *inf_fich;

struct team *team_list;

sem_t *mutex;

int shmid;

//PARA TESTE PARA APAGAR MAIS TARDE
void teste(){
  for(int i = 0; i< inf_fich->number_of_teams; i++){
    if(strcmp(team_list[i].team_name, "") == 0){
      return;
    }
    for(int j = 0; j < inf_fich->number_of_cars; j++){
      if(team_list[i].cars[j].speed ==0){
        break;
      }
      printf("Team name:%s\n Box state:%s\n Car number: %d\n Car speed: %d\n Car consumption: %d\n Car reliability: %d\n", team_list[i].team_name
                                                                                                                       , team_list[i].box_state
                                                                                                                       , team_list[i].cars[j].car_number
                                                                                                                       , team_list[i].cars[j].speed
                                                                                                                       , team_list[i].cars[j].consumption
                                                                                                                       , team_list[i].cars[j].reliability);
    }
    printf("-----------\n");
  }

}


void writeLog(char * string){
  char buffer[200];

  sprintf(buffer, "date|cut -c17-24 >> logs.txt ; sed -i '$ s/$/ %s/' logs.txt; ",string);


  /* https://unix.stackexchange.com/questions/412835/append-text-with-echo-without-new-line
  sed -i '$ s/$/abc/' file.txt
      -i - modify the file inplace
      $ - indicate the last record/line
      s/$/abc/ - substitute the end of the line $ with substring abc (for the last record)

  */

  sem_wait(mutex);

  system(buffer);

  sem_post(mutex);

}


//Main function. Here the RaceManager and the MalfunctionManager processes will be created
int main(){
  system(">logs.txt");  //Limpa o ficheiro logs.txt
  //Initialize the inf_fich struct and populate it

   inf_fich=readConfigFile();

   sem_unlink("MUTEX");
   mutex = sem_open("MUTEX", O_CREAT|O_EXCL,0700,1);



  //Creates shared memory
  shmid = shmget(IPC_PRIVATE, (sizeof(struct team*) + sizeof(struct car*) * inf_fich->number_of_cars)* inf_fich->number_of_teams, IPC_CREAT|0700);
  if (shmid < 1) exit(0);
  team_list = (struct team*) shmat(shmid, NULL, 0);
  if (team_list < (struct team*) 1) exit(0);

  for(int i = 0; i < inf_fich->number_of_teams ; i++){
      team_list[i].cars = (struct car*)(team_list + inf_fich->number_of_teams + i +1);
  }



  writeLog("Ficheiro de entrada lido");



  //Apenas para teste
  /*
  strcpy(team_list[0].team_name,"Sporting");
  strcpy(team_list[0].box_state, "OPEN" ) ;
  team_list[0].cars[0].speed = 10;
  team_list[0].cars[0].consumption = 70;
  team_list[0].cars[0].reliability = 60;
  team_list[0].cars[0].car_number = 19;

  team_list[0].cars[1].speed = 50;
  team_list[0].cars[1].consumption = 80;
  team_list[0].cars[1].reliability = 90;
  team_list[0].cars[1].car_number = 29;


  strcpy(team_list[1].team_name,"Benfica");
  strcpy(team_list[1].box_state, "Reservado");
  team_list[1].cars[0].speed = 50;
  team_list[1].cars[0].consumption = 10;
  team_list[1].cars[0].reliability = 40;
  team_list[1].cars[0].car_number = 9;

  strcpy(team_list[2].team_name,"Porto");
  strcpy(team_list[2].box_state, "OPEN" );
  team_list[2].cars[0].speed = 90;
  team_list[2].cars[0].consumption = 100;
  team_list[2].cars[0].reliability = 70;
  team_list[2].cars[0].car_number = 8;
  */
  int pid=fork();

  if(pid!=0){
    sleep(4);
  }
  else{
    int pid2=fork();
    if(pid2==0){
      sleep(3);

      /*strcpy(team_list[4].team_name,"Boavista");
      strcpy(team_list[4].box_state, "OPEN" );
      team_list[4].cars[0].speed = 90;
      team_list[4].cars[0].consumption = 100;
      team_list[4].cars[0].reliability = 70;
      team_list[4].cars[0].car_number = 8;
      printf("---Gerador de Corrida.---\n");

      */
      //Race_Manager(inf_fich->number_of_teams, inf_fich->number_of_cars);

      printf("Gerador de Corrida is out!\n");

      exit(0);
    }
    else{
      printf("---Gerador de Avarias.---\n");
      /*strcpy(team_list[3].team_name,"Rio Ave");
      strcpy(team_list[3].box_state, "Reservado");
      team_list[3].cars[0].speed = 50;
      team_list[3].cars[0].consumption = 10;
      team_list[3].cars[0].reliability = 40;
      team_list[3].cars[0].car_number = 9;

      */



      exit(0);
    }
  }

  printf("---------MAIN-------\n");


  free(inf_fich);
  shmdt(team_list);
  shmctl(shmid, IPC_RMID, NULL);
  sem_close(mutex);
  sem_unlink("MUTEX");
  sleep(1);
  return 0;

}
