#include "ShaderFunctions.h"
#include <STE/Assets/ShaderFunctions.h>

void ShaderUpdate_Disable(void* _app, void* _renderTarget, void* _shader)
{
    sctx();
    
    shader->disabled = !keys(Down, s);
    
    Shader_ParamCopy(shader, "Width", &renderTarget->size.X, sizeof(int));
    Shader_ParamCopy(shader, "Height", &renderTarget->size.Y, sizeof(int));
    
    float tmod = 1;
    
    Shader_ParamCopy(shader, "tmod", &tmod, sizeof(float));
}
