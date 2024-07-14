#include"philo.c"

int cycle_of_life(void *input)
{
    t_in *in ;
    in = (t_in *)input;
    think();
    eat(in->t_eat);
    sleeep(in->t_sleep);
    return 0;
}

int    think(void){
    
}

int    eat(int time){

}

int    sleeep(int time){

}