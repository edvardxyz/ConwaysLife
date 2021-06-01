#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main (void){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int WIDTH = w.ws_col;
    int HEIGHT = w.ws_row-1;
    int (*world)[WIDTH] = calloc(HEIGHT, sizeof(int[WIDTH]));
    int (*worldTmp)[WIDTH] = calloc(HEIGHT, sizeof(int[WIDTH]));
    srand(time(0));

    // initialize random world 50 %
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int n = rand() % 2;
            if(n == 1) {
                world[i][j] = 1;
            }
            // border value
            if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                world[i][j] = 2;
                worldTmp[i][j] = 2;
            }
        }
    }
    do{
        // print world
        system("clear");
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if(world[i][j] == 0) {
                    printf("%c", ' ');
                } else {
                    printf("%c", '#');
                }
            }
            printf("%c", '\n');
        }
        // change worldTmp state
        for (int i = 1; i < HEIGHT-1; ++i) {
            for (int j = 1; j < WIDTH-1; ++j) {
                // get number of neighbors around
                int nb = 0;
                for (int x = -1; x < 2 ; ++x) {
                    for (int y = -1; y < 2 ; ++y) {
                        if(y == 0 && x == 0) {// skip self
                            continue;
                        }
                        if(world[i+x][j+y] == 1){
                            nb++;
                        }
                    }
                }
                // conway's rules:
                if(world[i][j] == 1) {
                    if(nb < 2 || nb > 3) {
                        worldTmp[i][j] = 0;
                    } else {
                        worldTmp[i][j] = 1;
                    }
                }else if (nb == 3) {
                    worldTmp[i][j] = 1;
                }
            }
        }
        // change world state
        for (int i = 1; i < HEIGHT-1; ++i) {
            for (int j = 1; j < WIDTH-1; ++j) {
                world[i][j] = worldTmp[i][j];
            }
        }
        usleep(100000);
    }while(1);
    free(world);
    free(worldTmp);
    return 0;
}

