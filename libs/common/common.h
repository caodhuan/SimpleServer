#pragma once

#ifdef WIN32

#ifndef snprintf
#define snprintf _snprintf
#endif

#endif // WIN32

#define SAFE_DELETE(p) do {if(p) { delete p; p = nullptr; } } while(0);
