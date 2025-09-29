#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <array>

class KalmanFilter {
public:
    KalmanFilter(float q = 1.0f);

    void setProcessNoise(float q);
    void setMeasurementNoise(int idx, float r); // R independiente por variable

    float update(int idx, float measurement);
    float getEstimate(int idx) const;

private:
    static const int N = 3;  // Número de variables

    std::array<float, N> x_hat;  // Estimaciones
    std::array<float, N> P;      // Error de estimación
    std::array<float, N> R;      // Ruido de medición individual
    float Q; // Varianza del proceso (igual para todos en este ejemplo)
};

#endif
