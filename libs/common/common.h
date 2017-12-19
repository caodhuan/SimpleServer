#pragma once

#ifdef WIN32

#ifndef snprintf
#define snprintf _snprintf
#endif

#define SAFE_DELETE(p) do {if(p) { delete p; p = nullptr; } } while(0);
#endif // WIN32

