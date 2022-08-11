/*
 * parameters.h
 *
 *  Created on: Jul 24, 2022
 *      Author: jeffsnyder
 */

#ifndef INC_PARAMETERS_H_
#define INC_PARAMETERS_H_

typedef float (*scaler_t)(float);
//struct for every parameter
typedef struct param
    {
        float zeroToOneVal;
        float realVal;
        scaler_t scaleFunc;
    } param;



#define OSC_PARAMS_OFFSET 40

enum OscParamNames
{
	OscEnabled,
	OscPitch,
	OscFine,
	OscFreq,
	OscShape,
	OscAmp,
	OscisHarmonic,
	OscisStepped,
	OscShapeSet,
	OscFilterSend,
	OscParamsNum
};




enum ParamNames
{
	Master,
	M1,
	M2,
	M3,
	M4,
	M5,
	M6,
	M7,
	M8,
	M9,
	M10,
	M11,
	M12,
	M13,
	M14,
	M15,
	M16,
	A,
	B,
	X,
	Y,
	Ped,
	Transpose,
	PitchBend0,
	PitchBend1,
	PitchBend2,
	PitchBend3,
	PitchBend4,
	PitchBend5,
	PitchBend6,
	PitchBend7,
	PitchBend8,
	PitchBendRangeUp,
	PitchBendRangeDown,
	Noise,
	NoiseTilt,
	NoisePeakGain,
	NoisePeakFreq,
	NoiseAmp,
	NoiseFilterSend,
	Osc1,
	Osc1Pitch,
	Osc1Fine,
	Osc1Freq,
	Osc1Shape,
	Osc1Amp,
	Osc1isHarmonic,
	Osc1isStepped,
	Osc1ShapeSet,
	Osc1FilterSend,
	Osc2,
	Osc2Pitch,
	Osc2Fine,
	Osc2Freq,
	Osc2Shape,
	Osc2Amp,
	Osc2isHarmonic,
	Osc2isStepped,
	Osc2ShapeSet,
	Osc2FilterSend,
	Osc3,
	Osc3Pitch,
	Osc3Fine,
	Osc3Freq,
	Osc3Shape,
	Osc3Amp,
	Osc3isHarmonic,
	Osc3isStepped,
	Osc3ShapeSet,
	Osc3FilterSend,
	Effect1FXType,
	Effect1Param1,
	Effect1Param2,
	Effect1Param3,
	Effect1Param4,
	Effect1Param5,
	Effect1Mix,
	Effect2FXType,
	Effect2Param1,
	Effect2Param2,
	Effect2Param3,
	Effect2Param4,
	Effect2Param5,
	Effect2Mix,
	Effect3FXType,
	Effect3Param1,
	Effect3Param2,
	Effect3Param3,
	Effect3Param4,
	Effect3Param5,
	Effect3Mix,
	Effect4FXType,
	Effect4Param1,
	Effect4Param2,
	Effect4Param3,
	Effect4Param4,
	Effect4Param5,
	Effect4Mix,
	Filter1,
	Filter1Type,
	Filter1Cutoff,
	Filter1Gain,
	Filter1Resonance,
	Filter1KeyFollow,
	Filter2,
	Filter2Type,
	Filter2Cutoff,
	Filter2Gain,
	Filter2Resonance,
	Filter2KeyFollow,
	FilterSeriesParallelMix,
	Envelope1Attack,
	Envelope1Decay,
	Envelope1Sustain,
	Envelope1Release,
	Envelope1Leak,
	Envelope1Velocity,
	Envelope2Attack,
	Envelope2Decay,
	Envelope2Sustain,
	Envelope2Release,
	Envelope2Leak,
	Envelope2Velocity,
	Envelope3Attack,
	Envelope3Decay,
	Envelope3Sustain,
	Envelope3Release,
	Envelope3Leak,
	Envelope3Velocity,
	Envelope4Attack,
	Envelope4Decay,
	Envelope4Sustain,
	Envelope4Release,
	Envelope4Leak,
	Envelope4Velocity,
	LFO1Rate,
	LFO1Shape,
	LFO1Phase,
	LFO1ShapeSet,
	LFO1Sync,
	LFO2Rate,
	LFO2Shape,
	LFO2Phase,
	LFO2ShapeSet,
	LFO2Sync,
	LFO3Rate,
	LFO3Shape,
	LFO3Phase,
	LFO3ShapeSet,
	LFO3Sync,
	LFO4Rate,
	LFO4Shape,
	LFO4Phase,
	LFO4ShapeSet,
	LFO4Sync,
	OutputAmp,
};



/*
 * format = min max center
enum ParamNames
{
	Master, 0 2 1
	M1, 0 1 .5
	M2,
	M3,
	M4,
	M5,
	M6,
	M7,
	M8,
	M9,
	M10,
	M11,
	M12,
	M13,
	M14,
	M15,
	M16,
	A,
	B,
	X,
	Y,
	Ped,
	Transpose, -48, 48 0
	PitchBend0,
	PitchBend1,
	PitchBend2,
	PitchBend3,
	PitchBend4,
	PitchBend5,
	PitchBend6,
	PitchBend7,
	PitchBend8,
	PitchBendRangeUp, 0 24 12
	PitchBendRangeDown, 0 24 12
	Noise, 0 1 //button
	NoiseTilt, 0 1 .5
	NoisePeakGain, 0 1 .5
	NoisePeakFreq, 0 1 .5
	NoiseAmp, 0 2 1
	NoiseFilterSend, 0 1 .5
	Osc1, 0 1 button
	Osc1Pitch, -24 24 0
	Osc1Fine, -100 100 0
	Osc1Freq, -2000 2000 0
	Osc1Shape, 0 1 .5
	Osc1Amp, 0 2 1
	Osc1isHarmonic, 0 1 button
	Osc1isStepped, 0 1 button
	Osc1ShapeSet, 0 6 selector
	Osc1FilterSend,0 1 .5
	Osc2,
	Osc2Pitch,
	Osc2Fine,
	Osc2Freq,
	Osc2Shape,
	Osc2Amp,
	Osc2isHarmonic,
	Osc2isStepped,
	Osc2ShapeSet,
	Osc2FilterSend,
	Osc3,
	Osc3Pitch,
	Osc3Fine,
	Osc3Freq,
	Osc3Shape,
	Osc3Amp,
	Osc3isHarmonic,
	Osc3isStepped,
	Osc3ShapeSet,
	Osc3FilterSend,
	Effect1FXType, 0 11 (based on number of effects)
	Effect1Param1, // depends on which effect is selected
	Effect1Param2,
	Effect1Param3,
	Effect1Param4,
	Effect1Param5,
	Effect1Mix,
	Effect2FXType,
	Effect2Param1,
	Effect2Param2,
	Effect2Param3,
	Effect2Param4,
	Effect2Param5,
	Effect2Mix,
	Effect3FXType,
	Effect3Param1,
	Effect3Param2,
	Effect3Param3,
	Effect3Param4,
	Effect3Param5,
	Effect3Mix,
	Effect4FXType,
	Effect4Param1,
	Effect4Param2,
	Effect4Param3,
	Effect4Param4,
	Effect4Param5,
	Effect4Mix,
	Filter1, 0 1 button0
	Filter1Type, 0 9  based on number of possible filters
	Filter1Cutoff, 0 127 63.5
	Filter1Gain, 0 1 .5
	Filter1Resonance, 0.01f 10.0 0.5f skew1
	Filter1KeyFollow, 0 1 .5
	Filter2,
	Filter2Type,
	Filter2Cutoff,
	Filter2Gain,
	Filter2Resonance,
	Filter2KeyFollow,
	FilterSeriesParallelMix, 0 1 .5
	Envelope1Attack, 0 20000 4000 skew2
	Envelope1Decay, 0 20000 4000 skew2
	Envelope1Sustain, 0 1 .5
	Envelope1Release, 0 20000 4000 skew2
	Envelope1Leak, 0 1 .5
	Envelope1Velocity, 0 1 button
	Envelope2Attack,
	Envelope2Decay,
	Envelope2Sustain,
	Envelope2Release,
	Envelope2Leak,
	Envelope2Velocity,
	Envelope3Attack,
	Envelope3Decay,
	Envelope3Sustain,
	Envelope3Release,
	Envelope3Leak,
	Envelope3Velocity,
	Envelope4Attack,
	Envelope4Decay,
	Envelope4Sustain,
	Envelope4Release,
	Envelope4Leak,
	Envelope4Velocity,
	LFO1Rate, 0 30.0 2.0 skew3
	LFO1Shape, 0 1 .5
	LFO1Phase, 0 1 .5
	LFO1ShapeSet, 0 6 number of lfo shapes
	LFO1Sync, 0 1 button
	LFO2Rate,
	LFO2Shape,
	LFO2Phase,
	LFO2ShapeSet,
	LFO2Sync,
	LFO3Rate,
	LFO3Shape,
	LFO3Phase,
	LFO3ShapeSet,
	LFO3Sync,
	LFO4Rate,
	LFO4Shape,
	LFO4Phase,
	LFO4ShapeSet,
	LFO4Sync,
	OutputAmp, 0 2 1
};
 */

 /*!￼￼￼ @} */

typedef enum ParamNames ParamNames;


#endif /* INC_PARAMETERS_H_ */
