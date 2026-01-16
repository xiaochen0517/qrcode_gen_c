#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <raylib.h>

void print_data(uint8_t *data_lists, int qrcode_width)
{
    for (int row = 0; row < qrcode_width; ++row)
    {
        for (int column = 0; column < qrcode_width; ++column)
        {
            int index = row * qrcode_width + column;
            uint8_t data = data_lists[index];
            printf("%03d: %03X, ", index, data);
        }
        printf("\n");
    }
}

void set_location_block(uint8_t *data_lists, int qrcode_width)
{
    for (int row = 0; row < qrcode_width; ++row)
    {
        for (int column = 0; column < qrcode_width; ++column)
        {
            int index = row * qrcode_width + column;
            if (
                (row == 0 || row == 6 || row == qrcode_width - 7 || row == qrcode_width - 1)
                && (column < 7 || column > qrcode_width - 8)
            )
            {
                data_lists[index] = 1;
            }

            if (
                (column == 0 || column == 6 || column == qrcode_width - 7 || column == qrcode_width - 1)
                && (row < 7 || row > qrcode_width - 8)
            )
            {
                data_lists[index] = 1;
            }

            if (
                ((row >= 2 && row <= 4) || (row >= qrcode_width - 5 && row <= qrcode_width - 3))
                && ((column >= 2 && column <= 4) || (column >= qrcode_width - 5 && column <= qrcode_width - 3))
            )
            {
                data_lists[index] = 1;
            }

            if (row == 6 && (column > 6 && column < qrcode_width - 7) && (column - 6) % 2 == 0)
            {
                data_lists[index] = 1;
            }
        }
    }
}

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 800;

    const int qrcode_width = 21;
    const int block_width = (screen_width - 20) / qrcode_width;
    printf("Block width: %d\n", block_width);

    // 分配内存空间并置为 0
    uint8_t *data_lists = calloc(qrcode_width * qrcode_width, sizeof(uint8_t));
    printf("Block size: %lu\n", sizeof(uint8_t) * (qrcode_width * qrcode_width));

    set_location_block(data_lists, qrcode_width);

    print_data(data_lists, qrcode_width);

    InitWindow(screen_width, screen_height, "qr-code generate");
    SetTargetFPS(10);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            for (int row = 0; row < qrcode_width; ++row)
            {
                for (int column = 0; column < qrcode_width; ++column)
                {
                    int index = row * qrcode_width + column;
                    uint8_t data = data_lists[index];

                    DrawCircle(
                        10 + (column * block_width) + block_width / 2,
                        10 + (row * block_width) + block_width / 2,
                        block_width / 3,
                        RED
                    );

                    if (data <= 0)
                    {
                        continue;
                    }
                    DrawRectangle(
                        10 + (column * block_width),
                        10 + (row * block_width),
                        block_width,
                        block_width,
                        BLACK
                    );
                    /*DrawCircle(
                        10 + (column * block_width) + block_width / 2,
                        10 + (row * block_width) + block_width / 2,
                        block_width / 3,
                        RED
                    );*/
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();
    free(data_lists);
    return 0;
}
