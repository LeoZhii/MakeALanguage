/*
Copyright (c) Cohen ter Heide 2014-2023 All rights reserved.
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
Cohen ter Heide
support@lumpology.com
*/
#pragma once
#include <cstdint>
#include <cstring>
namespace vix {
	constexpr uint64_t UIRN_RUN(char const *s, unsigned int count) {
		return count ? (UIRN_RUN(s, count - 1) ^ s[count - 1]) * 16777619u : 2166136261u;
	}
	consteval uint64_t UIRN(char const *s, unsigned int count) {
		return count ? (UIRN(s, count - 1) ^ s[count - 1]) * 16777619u : 2166136261u;
	}

}

#define GENHASH(X) vix::UIRN_RUN(X, strlen(X))
#define SETHASH(X) vix::UIRN(X, strlen(X))
