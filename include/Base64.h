/*
 * Copyright (C) 2021 Yannick Lufimpu Luviya - All Rights Reserved
 */

/* 
 * File:   Base64.h
 * Author: yannick
 *
 * Created on 9 mars 2021, 22:03
 */

#include <string>

#ifndef _BASE64_H_
#define _BASE64_H_
namespace RSRCH {
    namespace JARVIS {
        namespace SMTP {
            class Base64 {
                public:
                    Base64();
                    ~Base64();
                    std::string base64_encode(unsigned char const* , unsigned int len);
                    std::string base64_decode(std::string const& s);
            };
        }
    }
}
#endif /* _BASE64_H_ */


