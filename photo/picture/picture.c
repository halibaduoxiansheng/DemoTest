#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp_in, *fp_out;
    char hex_str[1024];
    unsigned char binary_data[1024];
    int i, len, hex_value;

    // 打开输入文件（包含十六进制数据的文本文件）
    fp_in = fopen("hex_data.txt", "r");
    if (fp_in == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // 打开输出文件（将保存转换后的图片）
    fp_out = fopen("output.jpg", "wb");
    if (fp_out == NULL) {
        perror("Error opening output file");
        fclose(fp_in);
        return 1;
    }

    // 逐行读取十六进制字符串，并转换为二进制数据
    while (fgets(hex_str, sizeof(hex_str), fp_in) != NULL) {
        len = strlen(hex_str);
        // printf("len=%d\n", len);
        for (i = 0; i < len - 1; i += 2) {  // 每次处理两个十六进制字符
            sscanf(hex_str + i, "%2x", &hex_value);
            binary_data[i / 2] = (unsigned char)hex_value;
        }
        fwrite(binary_data, 1, len / 2, fp_out);
        //break;
    }

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}