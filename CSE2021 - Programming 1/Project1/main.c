#include <stdio.h>
#include <stdib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}


unsigned char *edit_image(unsigned char *background, unsigned char *foreground, unsigned char *weather_forecast, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
             for (int k = 0; k < channel; k++)
             {
                 if(abs(foreground[i*width*channel + j*channel + 1] - background[i*width*channel + j*channel + 1]) < 55)
                 {
                     temp_array[i*width*channel + j*channel + k] = weather_forecast[i*width*channel + j*channel + k];
                 }

                 else
                     temp_array[i*width*channel + j*channel + k] = foreground[i*width*channel + j*channel + k];
            }
        }
    }

    return temp_array;
}


int main ()
{
    // declare variables
    char path_background[] = "./background.jpeg";
    char path_foreground[] = "./foreground.jpeg";
    char path_weather_forecast[] = "./new_background.jpeg";

    char save_path[] = "./New.jpeg";

    // read image data
    int width, height, channel;
    unsigned char *background = stbi_load(path_background, &width, &height, &channel, 0);

    unsigned char *foreground = stbi_load(path_foreground, &width, &height, &channel, 0);

    unsigned char *weather_forecast = stbi_load(path_weather_forecast, &width, &height, &channel, 0);

    if (background == NULL || foreground == NULL || weather_forecast == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }

    printf("Width: %d\nHeight: %d\nChannel: %d\n", width, height, channel);

    // save image
    unsigned char *cutimage = edit_image(background, foreground, weather_forecast, width, height, channel);
    stbi_write_png(save_path, width, height, channel, cutimage, width * channel);
    printf("New image saved to %s\n", save_path);

    return 0;
}
