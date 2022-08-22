// #include <mono-2.0/mono/jit/jit.h>
// #include <mono-2.0/mono/metadata/assembly.h>
// #include <mono-2.0/mono/metadata/class.h>
// #include <mono-2.0/mono/metadata/debug-helpers.h>
// #include <mono-2.0/mono/metadata/environment.h>
// #include <mono-2.0/mono/metadata/mono-config.h>
// #include <mono-2.0/mono/metadata/mono-gc.h>
// #include <mono-2.0/mono/metadata/object.h>

// #include <boost/timer/timer.hpp>
// #include <cmath>
// #include <iostream>

// using namespace std;

// MonoDomain *domain;

// int main() {
//   // 需要将这个文件的 $
//   mono_config_parse("/etc/mono/config");
//   domain = mono_jit_init("");
//   MonoAssembly *assembly =
//       mono_domain_assembly_open(domain, "LogicFrameServer.dll");
//   MonoImage *image = mono_assembly_get_image(assembly);

//   int realArgs = 88888;
//   void *args = (void *)&realArgs;

//   MonoString *int_result;
//   {
//     boost::timer::auto_cpu_timer t;
//     MonoClass *my_class =
//         mono_class_from_name(image, "LogicFrameServer", "Startup");
//     MonoMethod *method;

//     method = mono_class_get_method_from_name(my_class, "Start", 0);

//     for (size_t i = 0; i < 1000000; i++) {
//       MonoObject *mono_object = mono_runtime_invoke(method, NULL, NULL,
//       NULL); int_result = (MonoString *)mono_object_to_string(mono_object,
//       NULL);
//       // if (i % 10 == 0) {
//       mono_gc_collect(mono_gc_max_generation());
//       //}
//       cout << "i " << i << endl;
//     }
//   }
//   std::cout << mono_string_to_utf8(int_result) << std::endl;
//   return 0;
// }

#include "log.h"

using namespace CHServer;
int main() {
  CHLog::Instance()->InitLog("test", "file");
  return 0;
}