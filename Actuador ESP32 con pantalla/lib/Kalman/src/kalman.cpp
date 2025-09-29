#include "Kalman.h"

KalmanFilter::KalmanFilter(float q) : Q(q) {
    for (int i = 0; i < N; i++) {
        x_hat[i] = 0.0f;
        P[i] = 1.0f;   // Alta incertidumbre inicial
        R[i] = 1.0f;   // Valor por defecto (ajustar con varianza real)
    }
}

void KalmanFilter::setProcessNoise(float q) {
    Q = q;
}

void KalmanFilter::setMeasurementNoise(int idx, float r) {
    if (idx >= 0 && idx < N) {
        R[idx] = r;
    }
}

float KalmanFilter::update(int idx, float measurement) {
    if (idx < 0 || idx >= N) return 0.0f;

    // Predicción
    P[idx] += Q;

    // Ganancia de Kalman
    float K = P[idx] / (P[idx] + R[idx]);

    // Actualización
    x_hat[idx] = x_hat[idx] + K * (measurement - x_hat[idx]);
    P[idx] = (1 - K) * P[idx];

    return x_hat[idx];
}

float KalmanFilter::getEstimate(int idx) const {
    if (idx < 0 || idx >= N) return 0.0f;
    return x_hat[idx];
}
