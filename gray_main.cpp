#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char shrinkage[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
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

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________
void loadImage2() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image2 file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}
void Filters()
{

    cout << "1-Black and White\n"
            "2-Invert \n"
            "3-Merge \n"
            "4-Flip \n"
            "5-Darken or Lighten\n"
            "6-Rotate \n"
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
        DarkenLighten();
    }
    else if (c == '6') {
        Rotate();
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
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
void Invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            image[i][j] = 255 - image[i][j];
        }
    }
}
void Merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            image[i][j] = (image[i][j] + image2[i][j]) / 2;

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


                swap(image[i][j], image[255 - i][j]);

            }
        }
    }
    else if (choice == "vertical") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {

                swap(image[i][j], image[i][255 - j]);

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

                image[i][j] = image[i][j] / 2;
            }
        }
    }
    else if (choice == "lighten") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = (255 + image[j][i]) / 2;
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


                image2[i][j] = image[255 - i][255 - j];
            }
        }
    }
    else if (choice == "270") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k)

                    image2[i][j] = image[j][i];
            }
        }
    }
    else if (choice == "90") {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image2[i][j] = image[255 - j][i];
            }
        }
    }
    else {
        cout << "choose correct angle please!" << endl;
        Rotate();
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}
void DetectEdges() {
    unsigned char imageC[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if ((image[i][j]) > 127) {
                image[i][j] = 255;
                imageC[i][j] = 255;
            }
            else {
                image[i][j] = 0;
                imageC[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            if (image[i][j] == 0) {
                if (image[i - 1][j - 1] == 0 && image[i - 1][j] == 0 && image[i - 1][j + 1] == 0 &&
                    image[i][j - 1] == 0 && image[i][j + 1] == 0 &&
                    image[i + 1][j - 1] == 0 && image[i + 1][j] == 0 && image[i + 1][j + 1] == 0) {

                    imageC[i][j] = 255;
                }
            }

        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] += imageC[i][j];
        }
    }
}
void Enlarge() {
    unsigned char imageE[SIZE][SIZE];
    cout << "Which quarter to enlarge 1, 2, 3, or 4? ";
    char s;
    cin >> s;

    switch (s) {
        case '1':
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    imageE[i * 2][j * 2] = image[i][j];
                    imageE[i * 2][j * 2 + 1] = image[i][j];
                    imageE[i * 2 + 1][j * 2] = image[i][j];
                    imageE[i * 2 + 1][j * 2 + 1] = image[i][j];
                }

            }
            break;
        case '2':
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = SIZE / 2; j < SIZE; j++) {
                    imageE[i * 2][j * 2 - SIZE] = image[i][j];
                    imageE[i * 2][j * 2 + 1 - SIZE] = image[i][j];
                    imageE[i * 2 + 1][j * 2 - SIZE] = image[i][j];
                    imageE[i * 2 + 1][j * 2 + 1 - SIZE] = image[i][j];
                }

            }

            break;
        case '3':
            for (int i = SIZE / 2; i < SIZE; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    imageE[i * 2 - SIZE][j * 2] = image[i][j];
                    imageE[i * 2 - SIZE][j * 2 + 1] = image[i][j];
                    imageE[i * 2 + 1 - SIZE][j * 2] = image[i][j];
                    imageE[i * 2 + 1 - SIZE][j * 2 + 1] = image[i][j];
                }
            }

            break;
        case '4':
            for (int i = SIZE / 2; i < SIZE; i++) {
                for (int j = SIZE / 2; j < SIZE; j++) {

                    imageE[i * 2 - SIZE][j * 2 - SIZE] = image[i][j];
                    imageE[i * 2 - SIZE][j * 2 + 1 - SIZE] = image[i][j];
                    imageE[i * 2 + 1 - SIZE][j * 2 - SIZE] = image[i][j];
                    imageE[i * 2 + 1 - SIZE][j * 2 + 1 - SIZE] = image[i][j];
                }
            }

            break;
    }
    // Copy the enlarged image to the original image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = imageE[i][j];
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
                    image[i / 2][j / 2] = image[i][j];
                    image[i][j] = 255; // make rest pixels white
                }
            }
            break;
        case 3:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[i / 3][j / 3] = image[i][j];
                    image[i][j] = 255; // make rest pixels white
                }
            }
            break;
        case 4:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[i / 4][j / 4] = image[i][j];
                    image[i][j] = 255; // make rest pixels white
                }
            }
            break;
    }
}
void Mirror()
{
    cout << "choose left or right or upper or lower\n";
    string choice;
    cin >> choice;
    if (choice == "left")
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {

                image[i][j] = image[i][255 - j];
            }
        }
    }
    else if (choice == "right")
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {

                image[i][j] = image[i][255 - j];
            }
        }

    }
    else if (choice == "upper")
    {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j] = image[255 - i][j];
            }
        }

    }

    else
    {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j] = image[255 - i][j];
            }
        }

    }
}
void Shuffle()
{
    unsigned char after[SIZE][SIZE];
    short Quarter1, Quarter2, Quarter3, Quarter4;
    cin >> Quarter1;

    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {

            if (Quarter1 == 1)
                after[i][j] = image[i][j];
            else if (Quarter1 == 2)
                after[i][j] = image[i][j + (255 / 2)];
            else if (Quarter1 == 3)
                after[i][j] = image[i + (255 / 2)][j];
            else
                after[i][j] = image[i + (255 / 2)][j + (255 / 2)];
        }
    }


    cin >> Quarter2;

    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = SIZE / 2; j < SIZE; ++j) {
            if (Quarter2 == 1)
                after[i][j] = image[i][j - (255 / 2)];
            else if (Quarter2 == 2)
                after[i][j] = image[i][j];
            else if (Quarter2 == 3)
                after[i][j] = image[i + (255 / 2)][j + (255 / 2)];
            else
                after[i][j] = image[i + (255 / 2)][j];
        }
    }


    cin >> Quarter3;

    for (int i = SIZE / 2; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {

            if (Quarter3 == 1)
                after[i][j] = image[i - (255 / 2)][j];
            else if (Quarter3 == 2)
                after[i][j] = image[i - (255 / 2)][j + (255 / 2)];
            else if (Quarter3 == 3)
                after[i][j] = image[i][j];
            else
                after[i][j] = image[i][j + (255 / 2)];
        }
    }


    cin >> Quarter4;

    for (int i = SIZE / 2; i < SIZE; ++i) {
        for (int j = SIZE / 2; j < SIZE; ++j) {

            if (Quarter4 == 1)
                after[i][j] = image[i - (255 / 2)][j - (255 / 2)];
            else if (Quarter4 == 2)
                after[i][j] = image[i - (255 / 2)][j];
            else if (Quarter4 == 3)
                after[i][j] = image[i][j - (255 / 2)];
            else
                after[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = after[i][j];

        }

    }

}
void Blur() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            image[i][j] = (image[i][j] + image[i][j + 1] + image[i][j - 1] + image[i + 1][j] + image[i - 1][j]) / 5;
        }
    }
}
void Crop()
{
    short x, y, l, w;
    cin >> x >> y >> l >> w;


    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < SIZE; ++j) {                                   //upp
            image[i][j] = 255;
        }
    }



    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < y; ++j) {                                   //left
            image[i][j] = 255;
        }
    }

    for (int i = x + w; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {                                   //low
            image[i][j] = 255;
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = y + l; j < SIZE; ++j) {                                   //right
            image[i][j] = 255;
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
                image2[i][j] = image[i][(int) (j * 255) / 127];
            }
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image3[i][j] = 255;
            }
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = high; j < high + left; ++j) {
                image3[i][j] = image2[i][j - (int) high];

            }
            high -= moving;
        }

    } else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image1[i][SIZE - 1 - j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                shrinkage[i][j] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = shrinkage[SIZE - j - 1][i];
            }
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image3[i][j] = 255;
            }
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < 127; ++j) {
                image2[i][j] = image[i][(int) (j * 255) / 127];
            }
        }


        for (int i = 0; i < SIZE; ++i) {
            for (int j = high; j < high + left; ++j) {
                image3[j][i] = image2[i][j - (int) high];

            }
            high -= moving;
        }
    }
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            image[i][j]=image3[i][j];
        }

    }
}