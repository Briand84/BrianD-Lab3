
#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address


float computeAngle(int x, int y, int z){
    float res = 0;
    float res_1 = 0;
    float sum_yz = 0;
    float atan_res = 0;
    float convert = 0;

    // using the formula from equation 6, (Ax1 / sqrt (Ay1)2 + (Az1)2 )

    y = y*y;  //squares the 'y' axis value
    z = z*z; // squares the 'z'axis value
    sum_yz = sqrt(y+z); //squareroot of value of (y+z)
    res_1 = float(x)/sum_yz; //calculates the angle by dividing x over sum_yz
    atan_res = atan(res_1); // returns arctangent of res_1
    convert = (atan_res*180)/PI; //converts gradians to angle
    res = convert; // result in degrees
    return res;
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {

        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res);


        thread_sleep_for(2000);

    }
}

