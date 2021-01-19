# StringEvaluation
Simple C++ library for string evaluation created for my college project.


### How to use
1.  Add StringEvaluation.h to your project
2. Include it:
```cpp
#include "StringEvaluation.h"
```
3. Call libary:
```cpp
// Example call
std::cout << KT::StringEvaluation::resolveMath("5+6-N7") << std::endl; // 5+6--7 = 18
```

### Supported symbols
- `+` \- Addition
-  `-` \- Subtraction
- `*` \- Multiplication
- `/` \- Division
- `N` - Negative: N100 = **-100**
- `P` - Pow: 2P2 = ![equation](http://www.sciweavers.org/tex2img.php?eq=2%5E2&bc=Black&fc=White&im=png&fs=12&ff=arev&edit=0)
- `S` - Sqrt: 2S4 = **√4**
- `( )` \- Brackets

# Warning!
This library probably contains many bugs. It was created just for my project, But if you find it useful feel free to use in any way you want in your projects.
