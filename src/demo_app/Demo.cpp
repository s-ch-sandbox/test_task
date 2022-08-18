#define _USE_MATH_DEFINES
#include "Demo.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>

#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "Utils.h"

static constexpr double CURVE_RADIUS_MIN = 1e-9;
static constexpr double CURVE_RADIUS_MAX = 1.0;
static constexpr double HELIX_STEP_MIN = 0.0;
static constexpr double HELIX_STEP_MAX = 1.0;
static constexpr std::size_t CURVES_SAMPLES_NUMBER_MIN = 1;
static constexpr std::size_t CURVES_SAMPLES_NUMBER_MAX = 10;
static constexpr double CURVE_ARGUMENT = M_PI / 4;

namespace {
std::vector<std::shared_ptr<curves::Curve>> GenerateRandomCurvesVector() {
    utils::RandomFactory<curves::Curve> curve_factory{std::random_device{}()};
    std::uniform_real_distribution<double> radius_dist{CURVE_RADIUS_MIN, CURVE_RADIUS_MAX};
    // Since CURVE_RADIUS_MIN is positive, the generated radius will always be positive.
    // Thus no need to catch the invalid_argument exceptions from curves' constructors
    curve_factory.RegisterProducer(
        [radius_dist](std::mt19937& rng) mutable { return std::make_unique<curves::Circle>(radius_dist(rng)); });
    curve_factory.RegisterProducer([radius_dist](std::mt19937& rng) mutable {
        return std::make_unique<curves::Ellipse>(radius_dist(rng), radius_dist(rng));
    });
    curve_factory.RegisterProducer(
        [radius_dist, step_dist = std::uniform_real_distribution<double>{HELIX_STEP_MIN, HELIX_STEP_MAX}](
            std::mt19937& rng) mutable { return std::make_unique<curves::Helix>(radius_dist(rng), step_dist(rng)); });

    std::mt19937 rng{std::random_device{}()};
    std::size_t curves_samples_number =
        std::uniform_int_distribution<size_t>{CURVES_SAMPLES_NUMBER_MIN, CURVES_SAMPLES_NUMBER_MAX}(rng);
    std::vector<std::shared_ptr<curves::Curve>> curves_vector;
    curves_vector.reserve(curves_samples_number);
    for (std::size_t i = 0; i < curves_samples_number; ++i) {
        curves_vector.push_back(curve_factory.Generate());
    }

    return curves_vector;
}

std::vector<std::shared_ptr<curves::Circle>> FilterCircles(std::vector<std::shared_ptr<curves::Curve>>& curves_vector) {
    std::vector<std::shared_ptr<curves::Circle>> circles_vector;
    for (auto& curve : curves_vector) {
        auto circle = std::dynamic_pointer_cast<curves::Circle>(curve);
        if (circle) {
            circles_vector.push_back(std::move(circle));
        }
    }
    return circles_vector;
}

void PrintPoints(const std::vector<std::shared_ptr<curves::Curve>>& curves_vector) {
    std::cout << "Curves points and gradients at t=PI/4:\n";
    std::cout << std::setw(5) << std::left << "No.";
    std::cout << std::setw(30) << std::left << "C(PI/4)";
    std::cout << std::setw(30) << std::left << "dC/dt(PI/4)";
    std::cout << "\n";
    for (std::size_t i = 0; i < curves_vector.size(); ++i) {
        std::cout << std::left << std::setw(5) << i + 1;
        std::cout << std::left << std::setw(30) << curves_vector[i]->ValueAt(CURVE_ARGUMENT);
        std::cout << std::left << std::setw(30) << curves_vector[i]->GradAt(CURVE_ARGUMENT);
        std::cout << "\n";
    }
    std::cout << "\n";
}
}  // namespace

namespace demo {
void Run() {
    // Populate a container with random curves
    auto curves_vector = GenerateRandomCurvesVector();

    // Print coordinates and derivative values
    PrintPoints(curves_vector);

    // Populate a second container with circles only
    auto circles_vector = FilterCircles(curves_vector);
    std::cout << "Filtered " << circles_vector.size() << " circles\n";

    // Sort the second container by radius
    std::sort(circles_vector.begin(), circles_vector.end(),
              [](const auto& lhs, const auto& rhs) { return lhs->GetRadius() < rhs->GetRadius(); });
    std::cout << "Circles' radii after sorting:\n";
    for (const auto& circle : circles_vector) {
        std::cout << circle->GetRadius() << "\n";
    }
    std::cout << "\n";

    // Compute the total sum of radii in the second container
    double radii_sum = std::accumulate(circles_vector.begin(), circles_vector.end(), 0.0,
                                       [](double init, const auto& circle) { return init + circle->GetRadius(); });
    std::cout << "Circles' radii sum: " << radii_sum << "\n";
}
}  // namespace demo
