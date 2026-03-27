/**
 * @file main.cpp
 * @brief Programa principal – Simulación de una granja de paneles solares.
 *
 * El programa permite al usuario crear paneles solares, registrar sesiones
 * de generación de energía y consultar estadísticas de rendimiento.
 *
 * @author Juan Felipe Rodriguez Vargas
 * @date 2026
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>

#include "PanelSolar.h"

// ─────────────────────────────────────────────────────────────────────────── //
//  Utilidades de consola                                                       //
// ─────────────────────────────────────────────────────────────────────────── //

/** @brief Imprime una línea separadora decorativa. */
static void separador(char c = '=', int ancho = 60)
{
    std::cout << std::string(ancho, c) << '\n';
}

/** @brief Imprime un encabezado centrado entre separadores. */
static void encabezado(const std::string& titulo)
{
    separador();
    int espacios = static_cast<int>((60 - titulo.size()) / 2);
    std::cout << std::string(std::max(0, espacios), ' ') << titulo << '\n';
    separador();
}

/**
 * @brief Lee un número flotante validado desde la entrada estándar.
 * @param mensaje Texto que se muestra al usuario antes de la lectura.
 * @param minVal  Valor mínimo aceptado (exclusivo).
 * @param maxVal  Valor máximo aceptado (inclusivo).
 * @return Valor flotante dentro del rango indicado.
 */
static float leerFloat(const std::string& mensaje,
                        float minVal = 0.0f,
                        float maxVal = std::numeric_limits<float>::max())
{
    float valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor && valor > minVal && valor <= maxVal) {
            return valor;
        }
        std::cout << "  [!] Entrada inválida. Ingrese un número entre "
                  << minVal << " y " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Lee una cadena no vacía desde la entrada estándar.
 * @param mensaje Texto que se muestra al usuario.
 * @return Cadena de texto válida (no vacía).
 */
static std::string leerString(const std::string& mensaje)
{
    std::string valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;
        if (!valor.empty()) {
            return valor;
        }
        std::cout << "  [!] El valor no puede estar vacío.\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────── //
//  Función: mostrarEstadisticas                                                //
// ─────────────────────────────────────────────────────────────────────────── //

/**
 * @brief Imprime el resumen estadístico de un panel solar.
 * @param panel Referencia constante al panel a mostrar.
 */
static void mostrarEstadisticas(const PanelSolar& panel)
{
    separador('-');
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Panel ID          : " << panel.getId()           << '\n';
    std::cout << "  Eficiencia nominal: " << panel.getEficiencia()   << " %\n";
    std::cout << "  Sesiones registr. : " << panel.totalSesiones()   << '\n';
    std::cout << "  Energía total     : " << panel.energiaTotal()    << " Wh\n";
    std::cout << "  Efic. promedio    : " << panel.eficienciaPromedio() << " %\n";

    // Historial de sesiones
    const auto historial = panel.getHistorial();
    if (!historial.empty()) {
        std::cout << "  Historial (Wh)    : [ ";
        for (std::size_t i = 0; i < historial.size(); ++i) {
            std::cout << historial[i];
            if (i + 1 < historial.size()) std::cout << ", ";
        }
        std::cout << " ]\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────── //
//  Menú principal                                                              //
// ─────────────────────────────────────────────────────────────────────────── //

/**
 * @brief Muestra el menú de opciones disponibles.
 */
static void mostrarMenu()
{
    std::cout << "\n  1. Registrar generación en un panel\n";
    std::cout << "  2. Ver estadísticas de un panel\n";
    std::cout << "  3. Ver resumen de todos los paneles\n";
    std::cout << "  4. Agregar nuevo panel\n";
    std::cout << "  0. Salir\n";
    std::cout << "\n  Opción: ";
}

// ─────────────────────────────────────────────────────────────────────────── //
//  main                                                                        //
// ─────────────────────────────────────────────────────────────────────────── //

/**
 * @brief Punto de entrada del programa.
 *
 * Crea una granja de paneles solares, permite registrar generaciones
 * de energía y consultar estadísticas mediante un menú interactivo.
 *
 * @return 0 si la ejecución finaliza con éxito, 1 en caso de error fatal.
 */
int main()
{
    encabezado("SISTEMA DE GESTION DE PANELES SOLARES");

    // ── Contenedor STL principal ──────────────────────────────────────── //
    std::vector<PanelSolar> granja;

    // ── Creación inicial de dos paneles (mínimo requerido) ────────────── //
    std::cout << "\n  Se registrarán 2 paneles solares iniciales.\n\n";

    for (int i = 1; i <= 2; ++i) {
        std::cout << "  >>> Panel #" << i << " <<<\n";
        std::string id  = leerString("  ID del panel   : ");
        float efic      = leerFloat ("  Eficiencia (%)  [0-100]: ", 0.0f, 100.0f);

        try {
            granja.emplace_back(id, efic);
            std::cout << "  [OK] Panel \"" << id << "\" creado correctamente.\n\n";
        } catch (const std::exception& e) {
            std::cerr << "  [ERROR] " << e.what() << '\n';
            --i; // reintentar
        }
    }

    // ── Simulación: registros automáticos de demostración ─────────────── //
    std::cout << "\n  Cargando datos de ejemplo...\n";
    try {
        granja[0].registrarGeneracion(320.5f);
        granja[0].registrarGeneracion(290.0f);
        granja[0].registrarGeneracion(310.0f);

        granja[1].registrarGeneracion(410.0f);
        granja[1].registrarGeneracion(380.5f);
    } catch (const std::exception& e) {
        std::cerr << "  [ERROR en datos de ejemplo] " << e.what() << '\n';
    }

    // ── Bucle del menú interactivo ─────────────────────────────────────── //
    int opcion = -1;
    while (opcion != 0) {
        separador();
        std::cout << "  Granja activa: " << granja.size() << " panel(es)\n";
        mostrarMenu();

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcion = -1;
        }

        switch (opcion) {

        // ── Opción 1: registrar generación ────────────────────────────── //
        case 1: {
            encabezado("REGISTRAR GENERACION");
            std::cout << "  Paneles disponibles:\n";
            for (std::size_t k = 0; k < granja.size(); ++k) {
                std::cout << "    [" << k << "] " << granja[k].getId() << '\n';
            }
            std::cout << "  Seleccione índice: ";
            std::size_t idx;
            std::cin >> idx;
            if (idx >= granja.size()) {
                std::cout << "  [!] Índice fuera de rango.\n";
                break;
            }
            float wh = leerFloat("  Energía generada (Wh, > 0): ", 0.0f);
            try {
                granja[idx].registrarGeneracion(wh);
                std::cout << "  [OK] " << wh << " Wh registrados en '"
                          << granja[idx].getId() << "'.\n";
            } catch (const std::exception& e) {
                std::cerr << "  [ERROR] " << e.what() << '\n';
            }
            break;
        }

        // ── Opción 2: estadísticas de un panel ────────────────────────── //
        case 2: {
            encabezado("ESTADISTICAS DE UN PANEL");
            std::cout << "  Paneles disponibles:\n";
            for (std::size_t k = 0; k < granja.size(); ++k) {
                std::cout << "    [" << k << "] " << granja[k].getId() << '\n';
            }
            std::cout << "  Seleccione índice: ";
            std::size_t idx;
            std::cin >> idx;
            if (idx >= granja.size()) {
                std::cout << "  [!] Índice fuera de rango.\n";
                break;
            }
            mostrarEstadisticas(granja[idx]);
            break;
        }

        // ── Opción 3: resumen completo ────────────────────────────────── //
        case 3: {
            encabezado("RESUMEN COMPLETO DE LA GRANJA");
            float totalGranja = 0.0f;
            for (const auto& p : granja) {
                mostrarEstadisticas(p);
                totalGranja += p.energiaTotal();
            }
            separador();
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "  ENERGIA TOTAL DE LA GRANJA: "
                      << totalGranja << " Wh  ("
                      << totalGranja / 1000.0f << " kWh)\n";
            separador();
            break;
        }

        // ── Opción 4: agregar panel ───────────────────────────────────── //
        case 4: {
            encabezado("AGREGAR NUEVO PANEL");
            std::string id = leerString("  ID del nuevo panel  : ");
            float efic     = leerFloat ("  Eficiencia (%) [0-100]: ", 0.0f, 100.0f);
            try {
                granja.emplace_back(id, efic);
                std::cout << "  [OK] Panel \"" << id
                          << "\" agregado. Total: " << granja.size() << " paneles.\n";
            } catch (const std::exception& e) {
                std::cerr << "  [ERROR] " << e.what() << '\n';
            }
            break;
        }

        // ── Salir ─────────────────────────────────────────────────────── //
        case 0:
            std::cout << "\n  Cerrando sistema. ¡Hasta pronto!\n";
            break;

        default:
            std::cout << "  [!] Opción no válida. Intente nuevamente.\n";
            break;
        }
    }

    return 0;
}
