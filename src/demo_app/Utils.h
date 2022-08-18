#pragma once
#include <functional>
#include <random>
#include <memory>


namespace utils {
/*
    Random factory class.
    Allows to generate an object of type TProduct 
    according to one of the registered construction policies picked in a random manner.
*/
template<typename TProduct>
class RandomFactory {
    public:
    using TCreateFunction = std::function<std::unique_ptr<TProduct>(std::mt19937& rng)>;
    
    explicit RandomFactory(std::mt19937::result_type seed);
    void RegisterProducer(TCreateFunction create_function);
    std::unique_ptr<TProduct> Generate();

private:
    std::mt19937 rng_;
    std::vector<TCreateFunction> create_functions_;
};

template<typename TProduct>
RandomFactory<TProduct>::RandomFactory(std::mt19937::result_type seed) : rng_{seed} {}

template<typename TProduct>
void RandomFactory<TProduct>::RegisterProducer(TCreateFunction create_function) {
    create_functions_.push_back(std::move(create_function));
}

template<typename TProduct>
std::unique_ptr<TProduct> RandomFactory<TProduct>::Generate() {
    std::uniform_int_distribution<std::size_t> index_dist{0, create_functions_.size() - 1};
    return create_functions_[index_dist(rng_)](rng_);
}
}
