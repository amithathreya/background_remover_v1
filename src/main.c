#include "background.h"
#include<stdio.h>

void load_images(const char* background_file , const char* current_file);
int main()
{
    load_images("data/background.jpg", "data/frame.jpg");
    printf("Image loaded successfully.\n");
    return 0;
}