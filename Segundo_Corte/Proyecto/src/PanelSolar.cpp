* @file PanelSolar.cpp
 * @brief Implementación de la clase PanelSolar.
 * @author Juan Felipe Rodriguez Vargas
 * @date 2026
 * @version 1.0
 */

#include "PanelSolar.h"
#include <numeric>    // std::accumulate
#include <algorithm>  // std::max_element
#include <stdexcept>

// ========================================================================== //
//  Constructor                                                                //
// ========================================================================== //

PanelSolar::PanelSolar(const std::string& id, float eficiencia)
    : id(id), eficiencia(eficiencia), energiaGenerada(0.0f)
{
    // Validación del identificador
    if (id.empty()) {
        throw std::invalid_argument(
            "El identificador del panel no puede estar vacío.");
    }

    // Validación del rango de eficiencia
    if (eficiencia <= 0.0f || eficiencia > 100.0f) {
        throw std::out_of_range(
            "La eficiencia debe estar en el rango (0, 100]. "
            "Valor recibido: " + std::to_string(eficiencia));
    }
}

// ========================================================================== //
//  Métodos públicos                                                           //
// ========================================================================== //

void PanelSolar::registrarGeneracion(float wattHora)
{
    if (wattHora <= 0.0f) {
        throw std::out_of_range(
            "El valor de generación debe ser positivo. "
            "Valor recibido: " + std::to_string(wattHora));
    }

    historialGeneracion.push_back(wattHora);
    energiaGenerada += wattHora;
}

float PanelSolar::energiaTotal() const
{
    // energiaGenerada ya es la acumulación, pero recalculamos desde
    // el historial para mantener consistencia numérica.
    return std::accumulate(
        historialGeneracion.begin(),
        historialGeneracion.end(),
        0.0f);
}

float PanelSolar::eficienciaPromedio() const
{
    // Sin registros → devolvemos la eficiencia nominal
    if (historialGeneracion.empty()) {
        return eficiencia;
    }

    // Con un solo registro → ídem
    if (historialGeneracion.size() == 1) {
        return eficiencia;
    }

    // Referencia: el máximo registrado representa el 100 % de la
    // eficiencia nominal; cada sesión se pondera proporcionalmente.
    float maxWh = *std::max_element(
        historialGeneracion.begin(),
        historialGeneracion.end());

    if (maxWh == 0.0f) {
        return eficiencia; // caso de seguridad (no debería ocurrir)
    }

    float sumaEficiencias = 0.0f;
    for (float wh : historialGeneracion) {
        sumaEficiencias += (wh / maxWh) * eficiencia;
    }

    return sumaEficiencias / static_cast<float>(historialGeneracion.size());
}

// ========================================================================== //
//  Getters                                                                    //
// ========================================================================== //

const std::string& PanelSolar::getId() const
{
    return id;
}

float PanelSolar::getEficiencia() const
{
    return eficiencia;
}

std::vector<float> PanelSolar::getHistorial() const
{
    return historialGeneracion;
}

std::size_t PanelSolar::totalSesiones() const
{
    return historialGeneracion.size();
}
