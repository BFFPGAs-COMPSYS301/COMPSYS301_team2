void LED_1_Write();
void LED_2_Write();
void LED_3_Write();

static void MoveForwardOneCell(void) {
    LED_1_Write(1);
    CyDelay(1000);
    LED_1_Write(0);
    CyDelay(1000);
}

static void TurnLeft(void) {
    LED_2_Write(1);
    CyDelay(1000);
    LED_2_Write(0);
    CyDelay(1000);
}

static void TurnRight(void) {
    LED_3_Write(1);
    CyDelay(1000);
    LED_3_Write(0);
    CyDelay(1000);
}