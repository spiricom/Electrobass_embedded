

#include "soundengine.h"
#include "main.h"
#include "SimpleOscModule.h"
#include "FilterModule.h"
#include "defs.h"

tOscModule oscModuleArray[4];

tFiltModule filtModuleArray[4];

typedef struct moduleHandle
{
	ModuleType type;
	uint32_t index;
} moduleHandle;

moduleHandle moduleChain[2][2];


void processModuleHandle(moduleHandle handle, float* buffer)
{
	switch(handle.type)
	{
	case ModuleTypeOscModule:
		tOscModule_tick(oscModuleArray[handle.index], buffer);
		break;

	case ModuleTypeFilterModule:
		tFiltModule_tick(filtModuleArray[handle.index], buffer);
		break;
	default:
		{};
	}

}
float sum = 0.0f;
void audioFrameFunction(int bufferOffset)
{
	for (int i = 0; i < HALF_BUFFER_SIZE; i+=2)
	{
		int iplusbuffer = bufferOffset + i;
		float outVal = 0.0f;
		for (int i = 0; i < 2; i++)
		{
			sum = 0.0f;
			for (int j = 0; j < 2; j++)
			{
				processModuleHandle(moduleChain[i][j], &sum);
			}
			outVal += sum * 0.5f;

		}
		audioOutBuffer[iplusbuffer] = (int32_t)(outVal * TWO_TO_23);
		audioOutBuffer[iplusbuffer + 1] = (int32_t)(outVal * TWO_TO_23);
	}
}


void audioChainInit()
{

	float initialParams[OscNumParams] = {0.5, 0.7, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

	tOscModule_init(&oscModuleArray[0], initialParams, 0, &leaf);
	moduleChain[0][0].type = ModuleTypeOscModule;
	moduleChain[0][0].index = 0;

	initialParams[1] = 0.4;
	tOscModule_init(&oscModuleArray[1], initialParams, 1, &leaf);
	moduleChain[1][0].type = ModuleTypeOscModule;
	moduleChain[1][0].index = 1;

	initialParams[1] = 0.0;
	initialParams[6] = 0.0;
	tFiltModule_init(&filtModuleArray[0], initialParams, 2, &leaf);
	moduleChain[0][1].type = ModuleTypeFilterModule;
	moduleChain[0][1].index = 0;

	initialParams[1] = 0.0;
	initialParams[6] = 0.0;
	tFiltModule_init(&filtModuleArray[1], initialParams, 3, &leaf);
	moduleChain[1][1].type = ModuleTypeFilterModule;
	moduleChain[1][1].index = 1;
}




