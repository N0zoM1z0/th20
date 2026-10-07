#include "GameRandom.hpp"
#include "LockRegistry.hpp"
#include <limits>
namespace th20 {
std::uint32_t GameRandom::next(){
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(10));
    last=engine();
    return last%modulus;
}
void GameRandom::seed(std::uint32_t value){
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(10));
    minimum=0;
    upper=std::numeric_limits<std::uint32_t>::max()>>1;
    modulus=upper-minimum;
    last=value;
    GameRandomEngine& generator=engine;
    generator.seed(last);
}
}
