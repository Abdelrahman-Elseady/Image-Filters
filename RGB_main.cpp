#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char shrinkage[SIZE][SIZE][RGB];
unsigned char image3[SIZE][SIZE][RGB];
void loadImage();
void loadImage2();
void Filters();
void BlackWhite();
void Invert();
void Merge();
void Flip();
void DarkenLighten();
void Rotate();
void DetectEdges();
void Enlarge();
void Shrink();
void saveImage();
void Mirror();
void Shuffle();
void Blur();
void Crop();
void Skew();

int main()
{
    loadImage();
    Filters();
    saveImage();

    return 0;
}

//_________
void saveImage() {
    char imageFileName[100];

    // Get RGB image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//_________
void loadImage() {
    char imageFileName[100];

    // Get RGB image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

//_________
void loadImage2() {
    char imageFileName[100];

    // Get RGB image file name
    cout << "Enter the source image2 file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);
}
void Filters()
{

    cout << "1-Black and White\n"
        "2-Invert \n"
        "3-Merge \n"
        "4-Flip \n"
        "5-Rotate \n"
        "6-Darken or Lighten\n"
        "7-Detect Edges\n"
        "8-Enlarge Image\n"
        "9-Shrink\n"
        "a-Mirror Half Image\n"
        "b-Shuffle Image\n"
        "c-Blur\n"
        "d-Crop\n"
        "e-Skew (H and V)" << endl;
    cout << "Hello! choose your filter : " << endl;
    char c;
    cin >> c;
    if (c == '1') {
        BlackWhite();
    }
    else if (c == '2') {
        Invert();
    }
    else if (c == '3') {
        loadImage2();
        Merge();
    }
    else if (c == '4') {
        Flip();
    }
    else if (c == '5') {
        Rotate();
    }
    else if (c == '6') {
        DarkenLighten();
    }
    else if (c == '7') {
        DetectEdges();
    }
    else if (c == '8') {
        Enlarge();
    }
    else if (c == '9') {
        Shrink();
    }
    else if (c == 'a') {
        Mirror();
    }
    else if (c == 'b') {
        Shuffle();
    }
    else if (c == 'c') {
        Blur();
        Blur();
        Blur();
        Blur();
        Blur();
        Blur();
        Blur();
        Blur();
        Blur();
    }
    else if (c == 'd') {
        Crop();
    }
    else if (c == 'e') {
        Skew();
    }

}

void BlackWhite() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int average = 0;
            for (int k = 0; k < 3; ++k) {
                average += image[i][j][k];
            }
            average /= 3;    // calculating the average value of red , green and blue for every pixel

            for (int k = 0; k < 3; ++k) {
                if (average > 127)
                    image[i][j][k] = 255;
                else
                    image[i][j][k] = 0;
            }
        }
    }
}
void Invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {


                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}
void Merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
}
void Flip() {
    string choice;
    cout << "do you want horizontal or vertical??";
    cin >> choice;
    if (choice == "horizontal") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {

                    swap(image[i][j][k], image[255 - i][j][k]);
                }
            }
        }
    }
    else if (choice == "vertical") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image[i][j][k], image[i][255 - j][k]);
                }
            }
        }
    }
    else {
        cout << "correct answer please!" << endl;
        Flip();
    }
}
void DarkenLighten() {
    cout << "choose darken or lighten: ";
    string choice;
    cin >> choice;
    if (choice == "darken") {


        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = image[i][j][k] / 2;
            }
        }
    }
    else if (choice == "lighten") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = (255 + image[j][i])[k] / 2;
            }
        }
    }
    else {
        cout << "choose correct filter please!" << endl;
        DarkenLighten();
    }
}
void Rotate() {
    cout << "choose your angle: ";
    string choice;
    cin >> choice;
    if (choice == "180") {


        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)

                    image2[i][j][k] = image[255 - i][255 - j][k];
            }
        }
    }
    else if (choice == "270") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)

                    image2[i][j][k] = image[j][i][k];
            }
        }
    }
    else if (choice == "90") {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image2[i][j][k] = image[255 - j][i][k];
            }
        }
    }
    else {
        cout << "choose correct angle please!" << endl;
        Rotate();
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = image2[i][j][k];
        }
    }
}
void DetectEdges() {
    unsigned char imageC[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {


                if ((image[i][j][k]) > 127) {
                    image[i][j][k] = 255;
                    imageC[i][j][k] = 255;
                }
                else {
                    image[i][j][k] = 0;
                    imageC[i][j][k] = 0;
                }
            }
        }
    }

    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            for (int k = 0; k < RGB; ++k) {
                if (image[i][j][k] == 0) {
                    if (image[i - 1][j - 1][k] == 0 && image[i - 1][j][k] == 0 && image[i - 1][j + 1][k] == 0 &&
                        image[i][j - 1][k] == 0 && image[i][j + 1][k] == 0 &&
                        image[i + 1][j - 1][k] == 0 && image[i + 1][j][k] == 0 && image[i + 1][j + 1][k] == 0) {

                        imageC[i][j][k] = 255;
                    }
                }

            }
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] += imageC[i][j][k];
        }
    }
}
void Enlarge() {
    unsigned char imageE[SIZE][SIZE][RGB];
    cout << "Which quarter to enlarge 1, 2, 3, or 4? ";
    char s;
    cin >> s;

    switch (s) {
    case '1':
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < RGB; ++k) {
                    imageE[i * 2][j * 2][k] = image[i][j][k];
                    imageE[i * 2][j * 2 + 1][k] = image[i][j][k];
                    imageE[i * 2 + 1][j * 2][k] = image[i][j][k];
                    imageE[i * 2 + 1][j * 2 + 1][k] = image[i][j][k];
                }

            }
        }
        break;
    case '2':
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    imageE[i * 2][j * 2 - SIZE][k] = image[i][j][k];
                    imageE[i * 2][j * 2 + 1 - SIZE][k] = image[i][j][k];
                    imageE[i * 2 + 1][j * 2 - SIZE][k] = image[i][j][k];
                    imageE[i * 2 + 1][j * 2 + 1 - SIZE][k] = image[i][j][k];
                }

            }
        }
        break;
    case '3':
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < RGB; ++k) {
                    imageE[i * 2 - SIZE][j * 2][k] = image[i][j][k];
                    imageE[i * 2 - SIZE][j * 2 + 1][k] = image[i][j][k];
                    imageE[i * 2 + 1 - SIZE][j * 2][k] = image[i][j][k];
                    imageE[i * 2 + 1 - SIZE][j * 2 + 1][k] = image[i][j][k];
                }
            }
        }
        break;
    case '4':
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    imageE[i * 2 - SIZE][j * 2 - SIZE][k] = image[i][j][k];
                    imageE[i * 2 - SIZE][j * 2 + 1 - SIZE][k] = image[i][j][k];
                    imageE[i * 2 + 1 - SIZE][j * 2 - SIZE][k] = image[i][j][k];
                    imageE[i * 2 + 1 - SIZE][j * 2 + 1 - SIZE][k] = image[i][j][k];
                }
            }
        }
        break;
    }
    // Copy the enlarged image to the original image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = imageE[i][j][k];
        }
    }
}
void Shrink() {
    cout << "Shrink to 1/(2), 1/(3) or 1/(4)? ";
    int si;
    cin >> si;
    switch (si) {
    case 2:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i / 2][j / 2][k] = image[i][j][k];
                    image[i][j][k] = 255; // make rest pixels white
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i / 3][j / 3][k] = image[i][j][k];
                    image[i][j][k] = 255; // make rest pixels white
                }
            }
        }
        break;
    case 4:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i / 4][j / 4][k] = image[i][j][k];
                    image[i][j][k] = 255; // make rest pixels white
                }

            }
        }
        break;
    }
}
void Mirror() {
    cout << "choose left or right or upper or lower\n";
    string choice;
    cin >> choice;
    if (choice == "left")
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = image[i][255 - j][k];
            }
        }
    }
    else if (choice == "right")
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = image[i][255 - j][k];
            }
        }

    }
    else if (choice == "upper")
    {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = image[255 - i][j][k];
            }
        }

    }

    else
    {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = image[255 - i][j][k];
            }
        }

    }

}
void Shuffle() {
    unsigned char after[SIZE][SIZE][RGB];
    short Quarter1, Quarter2, Quarter3, Quarter4;
    cin >> Quarter1;

    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            for (int k = 0; k < RGB; ++k) {

                if (Quarter1 == 1)
                    after[i][j][k] = image[i][j][k];
                else if (Quarter1 == 2)
                    after[i][j][k] = image[i][j + (255 / 2)][k];
                else if (Quarter1 == 3)
                    after[i][j][k] = image[i + (255 / 2)][j][k];
                else
                    after[i][j][k] = image[i + (255 / 2)][j + (255 / 2)][k];
            }

        }
    }


    cin >> Quarter2;

    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = SIZE / 2; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                if (Quarter2 == 1)
                    after[i][j][k] = image[i][j - (255 / 2)][k];
                else if (Quarter2 == 2)
                    after[i][j][k] = image[i][j][k];
                else if (Quarter2 == 3)
                    after[i][j][k] = image[i + (255 / 2)][j + (255 / 2)][k];
                else
                    after[i][j][k] = image[i + (255 / 2)][j][k];
            }

        }
    }


    cin >> Quarter3;

    for (int i = SIZE / 2; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {

            for (int k = 0; k < RGB; ++k) {
                if (Quarter3 == 1)
                    after[i][j][k] = image[i - (255 / 2)][j][k];
                else if (Quarter3 == 2)
                    after[i][j][k] = image[i - (255 / 2)][j + (255 / 2)][k];
                else if (Quarter3 == 3)
                    after[i][j][k] = image[i][j][k];
                else
                    after[i][j][k] = image[i][j + (255 / 2)][k];
            }

        }
    }


    cin >> Quarter4;

    for (int i = SIZE / 2; i < SIZE; ++i) {
        for (int j = SIZE / 2; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {

                if (Quarter4 == 1)
                    after[i][j][k] = image[i - (255 / 2)][j - (255 / 2)][k];
                else if (Quarter4 == 2)
                    after[i][j][k] = image[i - (255 / 2)][j][k];
                else if (Quarter4 == 3)
                    after[i][j][k] = image[i][j - (255 / 2)][k];
                else
                    after[i][j][k] = image[i][j][k];
            }

        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = after[i][j][k];

        }

    }
}
void Blur() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = (image[i][j][k] + image[i][j + 1][k] + image[i][j - 1][k] + image[i + 1][j][k] + image[i - 1][j][k]) / 5;
        }
    }

}
void Crop() {
    short x, y, l, w;
    cin >> x >> y >> l >> w;


    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = 255;
        }
    }


    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = 255;
        }
    }

    for (int i = x + w; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = 255;
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = y + l; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k)
                image[i][j][k] = 255;
        }
    }
}
void Skew() {

    cout << " to skew right press 1 , to skew up press 0 : ";
    int direction;
    cin >> direction;
    double rad;
    cout << "what degree of skew ? ";
    cin >> rad;
    rad = 30;
    rad = (rad * 22) / (180 * 7);
    double left = 256 * (1 - tan(rad));
    double high = 256 * tan(rad);
    double moving = high / 256;
    if (direction) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < 127; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image2[i][j][k] = image[i][(int)(j * 255) / 127][k];
            }
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image3[i][j][k] = 255;
            }
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = high; j < high + left; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image3[i][j][k] = image2[i][j - (int)high][k];

            }
            high -= moving;
        }
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image1[i][j][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = image1[i][SIZE - 1 - j][k];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    shrinkage[i][j][k] = image[i][j][k];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = shrinkage[SIZE - j - 1][i][k];
            }
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image3[i][j][k] = 255;
            }
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < 127; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image2[i][j][k] = image[i][(int)(j * 255) / 127][k];
            }
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = high; j < high + left; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image3[j][i][k] = image2[i][j - (int)high][k];
            }
            high -= moving;
        }
    }
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k <RGB ; ++k) {
                image[i][j][k]=image3[i][j][k];
            }
        }
    }
}