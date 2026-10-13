
#include "project.h"
#include "robot_io.h"

int main(void)
{
    CyGlobalIntEnable;
    IO_Init();
    IO_Stop();

    CyDelay(2000);

    /* Short forward motor test */
    IO_Forward();
    CyDelay(200);

    IO_Stop();

    for (;;)
    {
        CyDelay(100);
    }
}
