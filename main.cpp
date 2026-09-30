#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Struktur Pixel (BGR)
struct Pixel {
    unsigned char b = 0;   // Background MERAH (B=0, G=0, R=255)
    unsigned char g = 0;
    unsigned char r = 255;
};

// Fungsi menggambar garis menggunakan algoritma Bresenham / DDA
void drawLine(std::vector<Pixel>& canvas, int width, int height, float x1_norm, float y1_norm, float x2_norm, float y2_norm, int thickness = 3) {
    // Konversi koordinat OpenGL (-1.0 s/d 1.0) ke koordinat piksel layar
    int x1 = static_cast<int>((x1_norm + 1.0f) * 0.5f * (width - 1));
    int y1 = static_cast<int>((y1_norm + 1.0f) * 0.5f * (height - 1));
    int x2 = static_cast<int>((x2_norm + 1.0f) * 0.5f * (width - 1));
    int y2 = static_cast<int>((y2_norm + 1.0f) * 0.5f * (height - 1));

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int halfT = thickness / 2;

    while (true) {
        // Gambarkan titik tebal garis warna PUTIH (B=255, G=255, R=255)
        for (int offset_y = -halfT; offset_y <= halfT; ++offset_y) {
            for (int offset_x = -halfT; offset_x <= halfT; ++offset_x) {
                int px = x1 + offset_x;
                int py = y1 + offset_y;
                if (px >= 0 && px < width && py >= 0 && py < height) {
                    int index = py * width + px;
                    canvas[index].r = 255; // Putih
                    canvas[index].g = 255;
                    canvas[index].b = 255;
                }
            }
        }

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void generateBMP(int width, int height, const std::string& filename) {
    std::vector<Pixel> canvas(width * height);

    // --- MENGGAMBAR 2 GARIS DIAGONAL (X) ---
    // Garis 1: dari pojok kiri-bawah (-1, -1) ke pojok kanan-atas (1, 1)
    drawLine(canvas, width, height, -1.0f, -1.0f, 1.0f, 1.0f, 3);

    // Garis 2: dari pojok kiri-atas (-1, 1) ke pojok kanan-bawah (1, -1)
    drawLine(canvas, width, height, -1.0f, 1.0f, 1.0f, -1.0f, 3);

    // Header File BMP
    int rowSize = (width * 3 + 3) & (~3);
    int dataSize = rowSize * height;
    int fileSize = 54 + dataSize;

    unsigned char header[54] = {
        'B','M',
        static_cast<unsigned char>(fileSize), static_cast<unsigned char>(fileSize >> 8), static_cast<unsigned char>(fileSize >> 16), static_cast<unsigned char>(fileSize >> 24),
        0,0,0,0, 54,0,0,0, 40,0,0,0,
        static_cast<unsigned char>(width), static_cast<unsigned char>(width >> 8), static_cast<unsigned char>(width >> 16), static_cast<unsigned char>(width >> 24),
        static_cast<unsigned char>(height), static_cast<unsigned char>(height >> 8), static_cast<unsigned char>(height >> 16), static_cast<unsigned char>(height >> 24),
        1,0, 24,0, 0,0,0,0,
        static_cast<unsigned char>(dataSize), static_cast<unsigned char>(dataSize >> 8), static_cast<unsigned char>(dataSize >> 16), static_cast<unsigned char>(dataSize >> 24),
        0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };

    std::ofstream out(filename, std::ios::binary);
    out.write(reinterpret_cast<char*>(header), 54);

    std::vector<unsigned char> pad(rowSize - width * 3, 0);
    for (int y = 0; y < height; ++y) {
        out.write(reinterpret_cast<char*>(&canvas[y * width]), width * 3);
        if (!pad.empty()) out.write(reinterpret_cast<char*>(pad.data()), pad.size());
    }
    out.close();
    std::cout << "Berhasil membuat file Tugas 2: " << filename << std::endl;
}

int main() {
    // Langsung buat 4 ukuran window untuk poin a, b, c, d sekaligus
    generateBMP(300, 300, "tugas2_300x300.bmp");
    generateBMP(400, 400, "tugas2_400x400.bmp");
    generateBMP(500, 500, "tugas2_500x500.bmp");
    generateBMP(600, 600, "tugas2_600x600.bmp");
    return 0;
}