

#include "soundengine.h"
#include "main.h"
#include "SimpleOscModule.h"
#include "FilterModule.h"
#include "defs.h"

#define INIT_ARRAY(arrayVar, type, sizeVal, _mempool)         \
        (arrayVar).size = (sizeVal);                         \
        (arrayVar).array = (type**) mpool_alloc(sizeof(type*) * (sizeVal), (_mempool)); \
        (arrayVar).mempool = (_mempool);                      \


typedef enum
{
	PresetStart,
	PresetChainInit,
	PresetChainLength,
	PresetModuleArrayInit,
	PresetModuleInit,
	PresetMappingArrayInit,
	PresetMappingInit,
	PresetEnd
}PresetMessageType;




typedef struct oscModuleArray
{
	tOscModule* array;
	tMempool mempool;
	uint32_t size;
} oscModuleArray;

typedef struct filtModuleArray
{
	tFiltModule* array;
	tMempool mempool;
	uint32_t size;
} filtModuleArray;


oscModuleArray myOscModuleArray;
filtModuleArray myFiltModuleArray;

typedef struct moduleHandle
{
	ModuleType type;
	uint32_t index;
} moduleHandle;

typedef struct chainStruct
{
	moduleHandle* moduleChain;
	uint32_t maxLength;
	uint32_t numChains;
	uint32_t* chainLengths;
	tMempool mempool;
}chainStruct;

chainStruct audioChains;


void initModuleArraySize(ModuleType type, int size)
{
    _tMempool* m = leaf.mempool;

	switch (type)
	{
		case ModuleTypeOscModule:
			INIT_ARRAY(myOscModuleArray, _tOscModule, size, m);
			break;
		case ModuleTypeFilterModule:
			INIT_ARRAY(myFiltModuleArray, _tFiltModule, size, m);
			break;
		default:
			break;
	}
}

void initChainMemory(uint32_t numChains, uint32_t maxChainSize)
{
    _tMempool* m = leaf.mempool;
    audioChains.moduleChain = (moduleHandle*) mpool_alloc(sizeof(moduleHandle) * (maxChainSize * numChains), (m));
    audioChains.mempool = m;
    audioChains.maxLength = maxChainSize;
    audioChains.numChains = numChains;
    audioChains.chainLengths = (uint32_t*) mpool_alloc(sizeof(uint32_t) * (numChains), (m));

}

void setChainLength(uint32_t whichChain, uint32_t length)
{
	audioChains.chainLengths[whichChain] = length;
}

void processModuleHandle(moduleHandle handle, float* buffer)
{
	switch(handle.type)
	{
	case ModuleTypeOscModule:
		tOscModule_tick(myOscModuleArray.array[handle.index], buffer);
		break;

	case ModuleTypeFilterModule:
		tFiltModule_tick(myFiltModuleArray.array[handle.index], buffer);
		break;
	default:
		{};
	}
}

void moduleInit(moduleHandle handle, uint32_t uuid, uint32_t whichChain, uint32_t chainIndex,float* const initialParams)
{
	switch (handle.type)
	{
	case ModuleTypeOscModule :
		tOscModule_init((myOscModuleArray.array[handle.index]), initialParams, uuid, &leaf);
		break;

	case ModuleTypeFilterModule:
		tFiltModule_init((myFiltModuleArray.array[handle.index]), initialParams, uuid, &leaf);

		break;
	}
	audioChains.moduleChain[whichChain * audioChains.maxLength  + chainIndex] = handle;
}

void audioFrameFunction(int bufferOffset)
{


	for (int i = 0; i < HALF_BUFFER_SIZE; i+=2)
	{
		int iplusbuffer = bufferOffset + i;
		float outVal = 0.0f;
		for (int i = 0; i < audioChains.numChains; i++)
		{
			float sum = 0.0f;
			for (int j = 0; j < audioChains.chainLengths[i]; j++)
			{

				processModuleHandle(audioChains.moduleChain[i * audioChains.maxLength  + j], &sum);
			}
			outVal += sum * 0.5f;

		}
		audioOutBuffer[iplusbuffer] = (int32_t)(outVal * TWO_TO_23);
		audioOutBuffer[iplusbuffer + 1] = (int32_t)(outVal * TWO_TO_23);
	}
}

void fakePresetLoad()
{
//	presetMessageParse(PresetMess);
	initChainMemory(2, 2);
	setChainLength(0,1);
	setChainLength(1,2);
	initModuleArraySize(ModuleTypeOscModule, 2);
	initModuleArraySize(ModuleTypeFilterModule,1);
	float initialParams[OscNumParams] = {0.5, 0.7, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
//	ModuleHandle handle = {ModuleTypeOscModule,0};

	moduleInit((moduleHandle){ModuleTypeOscModule,0}, 0,0,0,initialParams);
	initialParams[1] = 0.4;
	moduleInit((moduleHandle){ModuleTypeOscModule,1}, 1,1,0,initialParams);
	initialParams[1] = 0.4;
	moduleInit((moduleHandle){ModuleTypeFilterModule,0}, 2,0,1,initialParams);
}

void audioChainInit()
{
//	float initialParams[OscNumParams] = {0.5, 0.7, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
//
//	tOscModule_init(&myOscModuleArray.array[0], initialParams, 0, &leaf);
//	moduleChain[0][0].type = ModuleTypeOscModule;
//	moduleChain[0][0].index = 0;
//
//	initialParams[1] = 0.4;
//	tOscModule_init(&myOscModuleArray[1], initialParams, 1, &leaf);
//	moduleChain[1][0].type = ModuleTypeOscModule;
//	moduleChain[1][0].index = 1;
//
//	initialParams[1] = 0.0;
//	initialParams[6] = 0.0;
//	tFiltModule_init(&myFiltModuleArray[0], initialParams, 2, &leaf);
//	moduleChain[0][1].type = ModuleTypeFilterModule;
//	moduleChain[0][1].index = 0;
//
//	initialParams[1] = 0.0;
//	initialParams[6] = 0.0;
//	tFiltModule_init(&myFiltModuleArray[1], initialParams, 3, &leaf);
//	moduleChain[1][1].type = ModuleTypeFilterModule;
//	moduleChain[1][1].index = 1;
	fakePresetLoad();
}





void presetMessageParse(uint32_t size)
{
//	PresetMessageType type = presetMessageBuffer.buffer[presetMessageBuffer.readPointer++];
//	switch (type)
//	case PresetChainInit:
//		uint32_t numChains = presetMessageBuffer.buffer[presetMessageBuffer.readPointer++];
//		uint32_t maxChainLength = presetMessageBuffer.buffer[presetMessageBuffer.readPointer++];
//		initChainMemory(numChains, maxChainLength);
//		break;
//	case PresetChainLength:
//
//
//	for ()//for each chain, initialize its size
//		setChainLength();
//
////initialize array sizes
//	for()
//		initArraySize();
//
//	for()
//	//for each module, put it into the array and chain position it belongs in
//		audioChainInit();
}


