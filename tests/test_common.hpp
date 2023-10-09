#include <random>
#include <limits>

#define GET_RANDOM_BYTE() [] {     std::random_device dev;\
                                    std::mt19937 rng(dev());\
                                    std::uniform_int_distribution<unsigned char> dist(std::numeric_limits<unsigned char>::min(),std::numeric_limits<unsigned char>::max());\
                                    return dist(rng);\
                           }()

#define GET_RANDOM_WORD() [] {     std::random_device dev;\
                                    std::mt19937 rng(dev());\
                                    std::uniform_int_distribution<unsigned short> dist(std::numeric_limits<unsigned short>::min(),std::numeric_limits<unsigned short>::max());\
                                    return dist(rng);\
                           }()

#define GET_RANDOM_DWORD() [] {     std::random_device dev;\
                                    std::mt19937 rng(dev());\
                                    std::uniform_int_distribution<unsigned long> dist(std::numeric_limits<unsigned long>::min(),std::numeric_limits<unsigned long>::max());\
                                    return dist(rng);\
                            }()

#define GET_RANDOM_QWORD() [] {     std::random_device dev;\
                                    std::mt19937 rng(dev());\
                                    std::uniform_int_distribution<unsigned long long> dist(std::numeric_limits<unsigned long long>::min(),std::numeric_limits<unsigned long long>::max());\
                                    return dist(rng);\
                            }()

#define GET_RANDOM_INT() [] {     std::random_device dev;\
                                    std::mt19937 rng(dev());\
                                    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),std::numeric_limits<int>::max());\
                                    return dist(rng);\
                          }()
