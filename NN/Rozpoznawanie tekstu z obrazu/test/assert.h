//
// Created by joseph on 28.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ASSERT_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ASSERT_H

const double epsilon = 0.0001;

#define PRINT_MESSAGE() std::cerr << "Assertion failed in line: " << \
                  __LINE__ << " file: " << __FILE__ << std::endl

#define ASSERT(x) if(!x) { \
                    PRINT_MESSAGE(); \
                    std::cerr << "for " << #x << " = " << x << std::endl; \
                    }

#define ASSERT_EQUALS_I(x,y) if(x != y) { \
                                PRINT_MESSAGE(); \
                                std::cerr << "for " << #x << " = " << x << "\t" << \
                                #y << " = " << y << std::endl; \
                                }

#define ASSERT_EQUALS(x,y) if(fabs(x-y) > epsilon) { \
                            PRINT_MESSAGE(); \
                            std::cerr << "for " << #x << " = " << x << "\t" << \
                            #y << " = " << y << std::endl; \
                            }

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ASSERT_H
