#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#define THRESHOLD 50
void load_images(const char* background_file, const char* current_file) {
    int width1, height1, channels1;
    unsigned char* data1 = stbi_load(background_file, &width1, &height1, &channels1, 0);

    if (!data1) {
        fprintf(stderr, "Failed to load background image: %s\n", stbi_failure_reason());
        return ;
    }

    int width2, height2, channels2;
    unsigned char* data2 = stbi_load(current_file, &width2, &height2, &channels2, 0);

    if (!data2) {
        fprintf(stderr, "Failed to load current frame: %s\n", stbi_failure_reason());
        stbi_image_free(data1);
        return ;
    }

    if (width1 != width2 || height1 != height2 || channels1 != channels2) {
        printf("Error: Images must have the same dimensions and channels!\n");
        stbi_image_free(data1);
        stbi_image_free(data2);
        return ;
    }

    printf("Both images loaded successfully! Dimensions: %dx%d, Channels: %d\n", width1, height1, channels1);

    int image_size = width1 * height1 * channels1;
    unsigned char* op = (unsigned char*)malloc(image_size);
    for(int i = 0; i < image_size; i++) {
        int diff_r = abs(data1[i] - data2[i]);
        int diff_g = abs(data1[i + 1] - data2[i + 1]);
        int diff_b = abs(data1[i + 2] - data2[i + 2]);
        if(diff_r > THRESHOLD || diff_g > THRESHOLD || diff_b > THRESHOLD) {
          op[i] = data2[i];
          op[i + 1] = data2[i + 1];
            op[i + 2] = data2[i + 2];  
        }  else {
            op[i] = 0;
            op[i + 1] = 0;
            op[i + 2] = 0;
        }
    }
    const char* output_file = "data/output.jpg";
    stbi_write_jpg(output_file,width1,height1,channels1,op,width1*channels1);
    printf("Output image saved as output.png\n");
    stbi_image_free(data1);
    stbi_image_free(data2);
    free(op);
}
