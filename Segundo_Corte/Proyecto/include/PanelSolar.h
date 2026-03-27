/**
 * @file PanelSolar.h
 * @brief Declaración de la clase PanelSolar para gestión de paneles fotovoltaicos.
 * @author Juan Felipe Rodriguez Vargas
 * @date 2026
 * @version 1.0
 *
 * Este archivo contiene la definición de la clase PanelSolar, que modela
 * el comportamiento de un panel solar fotovoltaico, permitiendo registrar
 * generaciones de energía y calcular estadísticas de rendimiento.
 */

#ifndef PANELSOLAR_H
#define PANELSOLAR_H

#include <string>
#include <vector>
#include <stdexcept>

/**
 * @class PanelSolar
 * @brief Modela un panel solar fotovoltaico con registro histórico de generación.
 *
 * La clase permite crear paneles solares identificados de forma única,
 * registrar la energía generada en sesiones individuales (Wh), y calcular
 * métricas como la energía total acumulada y la eficiencia promedio.
 *
 * @invariant eficiencia debe estar en el rango (0.0, 100.0].
 * @invariant energiaGenerada >= 0.0 en todo momento.
 */
class PanelSolar {
private:
    /** @brief Identificador único del panel solar (ej. "PS-001"). */
    std::string id;

    /** @brief Eficiencia nominal del panel en porcentaje (0 < eficiencia <= 100). */
    float eficiencia;

    /** @brief Energía total acumulada generada en Watt-hora (Wh). */
    float energiaGenerada;

    /** @brief Historial cronológico de registros de generación en Wh. */
    std::vector<float> historialGeneracion;

public:
    // ------------------------------------------------------------------ //
    //  Constructor                                                         //
    // ------------------------------------------------------------------ //

    /**
     * @brief Construye un nuevo PanelSolar con el identificador y eficiencia dados.
     *
     * @param id         Identificador único del panel (no puede estar vacío).
     * @param eficiencia Eficiencia nominal en porcentaje; debe cumplir 0 < eficiencia <= 100.
     *
     * @throws std::invalid_argument Si @p id está vacío.
     * @throws std::out_of_range     Si @p eficiencia no está en (0, 100].
     *
     * @par Ejemplo
     * @code
     *   PanelSolar panel("PS-001", 18.5f);
     * @endcode
     */
    PanelSolar(const std::string& id, float eficiencia);

    // ------------------------------------------------------------------ //
    //  Métodos públicos                                                    //
    // ------------------------------------------------------------------ //

    /**
     * @brief Registra una nueva sesión de generación de energía.
     *
     * El valor se agrega al historial y se acumula en energiaGenerada.
     *
     * @param wattHora Energía generada en la sesión, en Wh. Debe ser > 0.
     *
     * @throws std::out_of_range Si @p wattHora es <= 0.
     *
     * @par Ejemplo
     * @code
     *   panel.registrarGeneracion(150.0f); // registra 150 Wh
     * @endcode
     */
    void registrarGeneracion(float wattHora);

    /**
     * @brief Retorna la energía total acumulada por el panel.
     *
     * @return Suma de todos los registros en historialGeneracion (Wh).
     *         Retorna 0.0 si aún no hay registros.
     */
    float energiaTotal() const;

    /**
     * @brief Calcula la eficiencia promedio de las sesiones registradas.
     *
     * La eficiencia por sesión se calcula como:
     * @f$ \eta_{sesion} = \frac{Wh_{sesion}}{Wh_{max}} \times eficiencia_{nominal} @f$
     * donde @f$Wh_{max}@f$ es el máximo registrado en el historial.
     *
     * @return Promedio ponderado de eficiencias por sesión (%).
     *         Retorna la eficiencia nominal si solo hay un registro o ninguno.
     */
    float eficienciaPromedio() const;

    // ------------------------------------------------------------------ //
    //  Getters                                                             //
    // ------------------------------------------------------------------ //

    /**
     * @brief Retorna el identificador del panel.
     * @return Referencia constante al id del panel.
     */
    const std::string& getId() const;

    /**
     * @brief Retorna la eficiencia nominal del panel.
     * @return Eficiencia en porcentaje.
     */
    float getEficiencia() const;

    /**
     * @brief Retorna una copia del historial de generación.
     * @return Vector con los valores Wh de cada sesión registrada.
     */
    std::vector<float> getHistorial() const;

    /**
     * @brief Indica cuántas sesiones de generación se han registrado.
     * @return Número de entradas en historialGeneracion.
     */
    std::size_t totalSesiones() const;
};

#endif // PANELSOLAR_H
