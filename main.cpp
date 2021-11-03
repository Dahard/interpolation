#include<iostream>
#include<fstream>
#include <iomanip>

using namespace std;

typedef struct point {
    double x;
    double y;
};

void printIntArray(int a[]) {
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
        printf("%d ", a[i]);
}

int main() {

    //FILE IMPORT
    int numberOfPoints;
    int dataFromFile[8];
    int iA = 0, iB = 0, n;
    double interpolationPoint, lagrangeResult = 0, newtonResult = 0, p, mult, X, Y;
    int i, j;
    ifstream inFile;

    inFile.open("/Users/danielkubik/CLionProjects/untitled9/MN-1-zad1-1.txt", ios::in);

    inFile >> numberOfPoints;

    cout << "Number of points:" << numberOfPoints << endl;

    auto pointArray = new point *[numberOfPoints];
    for (int i = 0; i < numberOfPoints; i++) {
        inFile >> X;
        inFile >> Y;
        auto pt = new point;
        pt->x = X;
        pt->y = Y;
        pointArray[i] = pt;
    }

    inFile.close();

    for (int i = 0; i < numberOfPoints; i++) {
        cout << "Punkt " << i << ":" << " X: " << pointArray[i]->x << " Y: " << pointArray[i]->y << endl;
    }

    //FILE IMPORT
//    inFile.open("/Users/danielkubik/CLionProjects/untitled9/MN-1-zad1-1.txt");
//
//    if (inFile.peek() != EOF) {
//        inFile >> numberOfPoints;
//    }
//
//    while (iA < dataFromFile[8] && inFile >> n) {
//        dataFromFile[iA++] = n;
//    }
//
//    inFile.close();
//
//    int arraySize = sizeof(dataFromFile) / sizeof(dataFromFile[0]);
//
//    int x[arraySize / 2], y[arraySize / 2];
//    for (iA = 0, iB = 0; iB < arraySize; iA++, iB += 2) {
//        x[iA] = dataFromFile[iB];
//        y[iA] = dataFromFile[iB + 1];
//    }
//
//    int xSize = sizeof(x) / sizeof(x[0]);
//    int ySize = sizeof(y) / sizeof(y[0]);
//
//    cout << "Ilość punktów = " << numberOfPoints << endl;
//    cout << "Dane z pliku = " << endl;
//    printIntArray(dataFromFile, arraySize);
//    cout << endl;
//    cout << "Tablica X:" << endl;
//    printIntArray(x, xSize);
//    cout << endl;
//    cout << "Tablica Y:" << endl;
//    printIntArray(y, ySize);
//    cout << endl;

    int x[] = {
            -2,
            -1,
            0,
            2,
            4
    };

    int y[] = {
            -1,
            0,
            5,
            99,
            -55
    };

    numberOfPoints = 5;

    //Interpolation
    cout << "Wprowadz punkt interpolacji: ";
    cin >> interpolationPoint;

    //Lagrange
    for (i = 0; i < numberOfPoints; i++) {
        p = 1;
        for (j = 0; j < numberOfPoints; j++) {
            if (i != j) {
                p = p * (interpolationPoint - pointArray[j]->x) / (pointArray[i]->x - pointArray[j]->x);
            }
        }
        lagrangeResult = lagrangeResult + p * pointArray[i]->y;
    }

    //Newton
    for (j = 0; j < numberOfPoints - 1; j++) {
        for (i = numberOfPoints - 1; i > j; i--)
            y[i] = (y[i] - y[i - 1]) / (x[i] - x[i - j - 1]);
    }
    for (i = numberOfPoints - 1; i >= 0; i--) {
        mult = 1;
        for (j = 0; j < i; j++)
            mult *= (interpolationPoint - x[j]);

        mult *= y[j];
        newtonResult += mult;
    }

    cout << endl << "Wartosc interpolacji w " << interpolationPoint << " ,wedlug lagrange'a, to " << lagrangeResult;
    cout << endl << "Wartosc interpolacji w " << interpolationPoint << " ,wedlug newtona, to " << newtonResult;

    return 0;
}