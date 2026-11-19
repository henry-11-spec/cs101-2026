#include <stdio.h>

typedef struct Books {
    int id;
    int price;
    char title[100];
} book_t;

void total_price(const book_t books[], int count)
{
    int total = 0;

    for (int i = 0; i < count; i++) {
        total += books[i].price;
    }

    printf("總價：%d\n", total);
}

void list_books(const book_t books[], int count)
{
    printf("Id  Price  Title\n");

    for (int i = 0; i < count; i++) {
        printf("%-3d %-6d %s\n",
               books[i].id, books[i].price, books[i].title);
    }
}

int main(void)
{
    book_t books[] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300,  "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550,  "Killers of the Flower Moon"},
        {5, 870,  "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    int count = sizeof(books) / sizeof(books[0]);

    list_books(books, count);
    total_price(books, count);

    FILE *file = fopen("Book.bin", "wb");
    if (file == NULL) {
        perror("Book.bin");
        return 1;
    }

    size_t written = fwrite(books, sizeof(books[0]), count, file);
    if (fclose(file) != 0 || written != (size_t)count) {
        printf("Book.bin 寫入失敗。\n");
        return 1;
    }

    printf("書籍資料已存入 Book.bin。\n");
    return 0;
}
