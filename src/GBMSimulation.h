//
// Created by Matteo Campagnoli on 21/09/25.
//

#ifndef GBMSIMULATION_H
#define GBMSIMULATION_H
#include <Eigen/Dense>
#include <memory>
#include <random>
#include <cmath>

typedef double real;

struct GBMParameters {
    real S0;
    real mu;
    real sigma;
    real T;
    int n_steps;
    int n_paths;
    uint64_t seed;
};

class GBMSimulation {

typedef Eigen::MatrixXd matrix;

public:
    GBMSimulation() :
        m_S0(0.0), m_mu(0.0), m_sigma(0.0), m_T(1.0),
        m_n_steps(1), m_n_paths(1), m_seed(0),
        m_paths(std::make_unique<matrix>(m_n_steps + 1, m_n_paths)) {}

    GBMSimulation(real S0, real mu, real sigma, real T, int n_steps, int n_paths, uint64_t seed) :
        m_S0(S0), m_mu(mu), m_sigma(sigma), m_T(T),
        m_n_steps(n_steps), m_n_paths(n_paths), m_seed(seed),
        m_paths(std::make_unique<matrix>(m_n_steps + 1, m_n_paths)) {}

    explicit GBMSimulation(const GBMParameters& parameters){
        m_S0 = parameters.S0;
        m_mu = parameters.mu;
        m_sigma = parameters.sigma;
        m_T = parameters.T;
        m_n_paths = parameters.n_paths;
        m_n_steps = parameters.n_steps;
        m_seed = parameters.seed;

        m_paths = std::make_unique<matrix>(m_n_steps+1, m_n_paths);
    }

    void simulate() {
        const double dt = m_T / static_cast<double>(m_n_steps);
        const double drift = (m_mu - 0.5 * m_sigma * m_sigma) * dt;
        const double vol   = m_sigma * std::sqrt(dt);

        m_paths->row(0).setConstant(m_S0);

        // Generate all standard normals Z ~ N(0,1) in one go
        matrix Z(m_n_steps, m_n_paths);
        std::mt19937_64 rng(m_seed ? m_seed : std::random_device{}());
        std::normal_distribution<double> N01(0.0, 1.0);
        for (int i = 0; i < m_n_steps; ++i) {
            for (int j = 0; j < m_n_paths; ++j) {
                Z(i, j) = N01(rng);
            }
        }

        // Evolve: S_{t+1} = S_t * exp(drift + vol * Z)
        for (int i = 0; i < m_n_steps; ++i) {
            // vectorized over paths (columns)
            m_paths->row(i + 1) = m_paths->row(i).array() * (drift + vol * Z.row(i).array()).exp();
        }
    }

    [[nodiscard]] const matrix& paths_ref() const {
        return *m_paths;
    }

private:
    real m_S0, m_mu, m_sigma, m_T;
    int m_n_steps, m_n_paths;
    uint64_t m_seed;

    std::unique_ptr<matrix> m_paths;
};

#endif //GBMSIMULATION_H
