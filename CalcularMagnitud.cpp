#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};

double calcularMayorMagnitud(Point puntos[], int n, int &indiceMayor) {

    if (n <= 0) {
        indiceMayor = -1;
        return 0.0;
    }

    // Inicializar con el primer punto
    double maxMag = sqrt(puntos[0].x * puntos[0].x +
                         puntos[0].y * puntos[0].y);

    indiceMayor = 0;

    for (int i = 1; i < n; i++) {
        double magnitudActual = sqrt(puntos[i].x * puntos[i].x +
                                     puntos[i].y * puntos[i].y);

        if (magnitudActual > maxMag) {
            maxMag = magnitudActual;
            indiceMayor = i;
        }
    }

    return maxMag;
}

int main() {

    int n;

    cout << "Ingrese la cantidad de puntos: ";
    cin >> n;

    if (n <= 0) {
        cout << "Cantidad invalida de puntos." << endl;
        return 1;
    }

    Point puntos[n];

    for (int i = 0; i < n; i++) {
        cout << "\nPunto " << i + 1 << endl;
        cout << "Ingrese x: ";
        cin >> puntos[i].x;
        cout << "Ingrese y: ";
        cin >> puntos[i].y;
    }

    int indiceMayor;
    double mayorMagnitud = calcularMayorMagnitud(puntos, n, indiceMayor);

    cout << "\n============================" << endl;
    cout << "La mayor magnitud es: " << mayorMagnitud << endl;
    cout << "Corresponde al punto en la posicion: " << indiceMayor << endl;
    cout << "Coordenadas: (" 
         << puntos[indiceMayor].x << ", "
         << puntos[indiceMayor].y << ")" << endl;

    return 0;
}
